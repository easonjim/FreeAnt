///////////////////////////////////////////////////
// FileTransfer.cpp : implementation file

#include "StdAfx.h"
#include <windows.h>
#include "FileTransfer.h"
#include "Structure.h"//�ṹ��ͷ�ļ�����Ϊ��ͷ�ļ�������һ�����У�����뵥��ʹ������࣬����ؽṹ�帴�Ƶ�ͷ�ļ��У�



CFileTransfer::CFileTransfer(HWND hNotifyWnd)
{
	InitSocket();//��ʼ���׽���
	m_hNotifyWnd = hNotifyWnd;
	//���������ļ������߳�
	HANDLE m_Accept_RecvFileInfoThread = CreateThread(NULL,0,Accept_RecvFileStructThread,this,0,NULL);
	m_CarAccept_RecvFileInfoThread.Add(m_Accept_RecvFileInfoThread);//�������ӽ�ȥ���Ա�����
}

CFileTransfer::~CFileTransfer()
{
	//�ͷ���Դ
	for (int i=0;i<m_CarAccept_RecvFileInfoThread.GetSize();i++)
	{
		CloseHandle(m_CarAccept_RecvFileInfoThread.GetAt(i));
	}
}

BOOL CFileTransfer::InitSocket()
{
	m_SrvSocket = socket(AF_INET,SOCK_STREAM,0);//�����׽���
	//��ַ�ṹ����
	m_SrvSocketAddr.sin_family = AF_INET;
	m_SrvSocketAddr.sin_port = htons(FILETRANSFER_PROT);
	m_SrvSocketAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//�����ַ�ṹ����
	m_SrvSocketAddrLen = sizeof(SOCKADDR);
	//���׽���
	if (bind(m_SrvSocket,(SOCKADDR*)&m_SrvSocketAddr,m_SrvSocketAddrLen) == SOCKET_ERROR)
	{
		AfxMessageBox("���׽���ʧ�ܣ�");
		return FALSE;
	}
	//����
	if (listen(m_SrvSocket,5) == SOCKET_ERROR)
	{
		AfxMessageBox("����ʧ�ܣ�");
		return FALSE;
	}

	return TRUE;
}

DWORD WINAPI CFileTransfer::Accept_RecvFileStructThread(LPVOID lpParameter)
{
	CFileTransfer *pFile = (CFileTransfer *)lpParameter;//���ݽ����Ĳ�������ת��������ǻ��������ָ��

	SOCKET AcceptSocket;
	//���ӳɹ���᷵��һ���׽��֣�TCP��ͨ���׽��ֽ���ͨѶ
	AcceptSocket = accept(pFile->m_SrvSocket,(SOCKADDR*)&(pFile->m_SrvSocketAddr),&(pFile->m_SrvSocketAddrLen));
	if (AcceptSocket != INVALID_SOCKET)//û����������������һ�������ļ������߳̽��еȴ���һ������
	{
		HANDLE m_Accept_RecvFileInfoThread = CreateThread(NULL,0,Accept_RecvFileStructThread,(LPVOID)pFile,0,NULL);
		pFile->m_CarAccept_RecvFileInfoThread.Add(m_Accept_RecvFileInfoThread);
	}
	//�����ļ���Ϣ
	int FileSize;
	send(AcceptSocket,"RecvRequest",sizeof("RecvRequest"),0);//����recv����ʹ���ͺͽ��ձ���һ�£�
	if (recv(AcceptSocket,(char*)&FileSize,sizeof(FileSize),0) == SOCKET_ERROR)//�����ļ�����
	{
	 	AfxMessageBox("�����ļ���Ϣʧ�ܣ�",MB_ICONSTOP);
	 	return 0;
 	}
 	CStructure::SockFileStruct sockfilestruct;
 	CStructure::FileStruct filestruct;
	//��̬����Ҫ����Ϊ��Ϣ���з��ͣ�������new���ڴ棬���͵�ֻ�ǵ�ַ��ʵ�ʲ������ڴ�
	//�ṹ��Ҳ�ǣ�������new���ڴ棬�ڷ����׵�ַ��
	CArray<CStructure::FileStruct,CStructure::FileStruct&> *Carfilestruct = new CArray<CStructure::FileStruct,CStructure::FileStruct&>;
 	for (int i=0;i<FileSize;i++)
 	{
		send(AcceptSocket,"RecvRequest",sizeof("RecvRequest"),0);//����recv֪ͨ��ʹ���ͺͽ��ձ���һ�£�
 		if (recv(AcceptSocket,(char*)&sockfilestruct, sizeof(CStructure::SockFileStruct), 0) != SOCKET_ERROR)
 		{
 			filestruct.Filelength = sockfilestruct.Filelength;
	 		filestruct.FileName = sockfilestruct.FileName;
	 		strcpy(filestruct.FilePath,sockfilestruct.FilePath);
	 		filestruct.FileSize = sockfilestruct.FileSize;
	 		filestruct.PathName = sockfilestruct.PathName;
	 		Carfilestruct->Add(filestruct);
	 	}
 	}
	//������Ϣ��������
	CStructure::RecvFileDlgInfo *TmpTur = new CStructure::RecvFileDlgInfo;
	TmpTur->AcceptSocket = AcceptSocket;
	TmpTur->Carfilestruct = Carfilestruct;
	::SendMessage(pFile->m_hNotifyWnd,WM_FILETRANSFER,NULL,(LPARAM)TmpTur);
	

	return 0;
}