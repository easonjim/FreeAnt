///////////////////////////////////////////////////
// FileTransfer.cpp : implementation file

#include "StdAfx.h"
#include <windows.h>
#include "FileTransfer.h"
#include "Structure.h"//结构体头文件；因为将头文件定义在一个类中；如果想单独使用这个类，把相关结构体复制到头文件中；



CFileTransfer::CFileTransfer(HWND hNotifyWnd)
{
	InitSocket();//初始化套接字
	m_hNotifyWnd = hNotifyWnd;
	//创建接收文件工作线程
	HANDLE m_Accept_RecvFileInfoThread = CreateThread(NULL,0,Accept_RecvFileStructThread,this,0,NULL);
	m_CarAccept_RecvFileInfoThread.Add(m_Accept_RecvFileInfoThread);//将句柄添加进去；以便销毁
}

CFileTransfer::~CFileTransfer()
{
	//释放资源
	for (int i=0;i<m_CarAccept_RecvFileInfoThread.GetSize();i++)
	{
		CloseHandle(m_CarAccept_RecvFileInfoThread.GetAt(i));
	}
}

BOOL CFileTransfer::InitSocket()
{
	m_SrvSocket = socket(AF_INET,SOCK_STREAM,0);//创建套接字
	//地址结构定义
	m_SrvSocketAddr.sin_family = AF_INET;
	m_SrvSocketAddr.sin_port = htons(FILETRANSFER_PROT);
	m_SrvSocketAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//计算地址结构长度
	m_SrvSocketAddrLen = sizeof(SOCKADDR);
	//绑定套接字
	if (bind(m_SrvSocket,(SOCKADDR*)&m_SrvSocketAddr,m_SrvSocketAddrLen) == SOCKET_ERROR)
	{
		AfxMessageBox("绑定套接字失败！");
		return FALSE;
	}
	//监听
	if (listen(m_SrvSocket,5) == SOCKET_ERROR)
	{
		AfxMessageBox("监听失败！");
		return FALSE;
	}

	return TRUE;
}

DWORD WINAPI CFileTransfer::Accept_RecvFileStructThread(LPVOID lpParameter)
{
	CFileTransfer *pFile = (CFileTransfer *)lpParameter;//传递进来的参数进行转换；这个是获得这个类的指针

	SOCKET AcceptSocket;
	//连接成功后会返回一个套接字；TCP是通过套接字进行通讯
	AcceptSocket = accept(pFile->m_SrvSocket,(SOCKADDR*)&(pFile->m_SrvSocketAddr),&(pFile->m_SrvSocketAddrLen));
	if (AcceptSocket != INVALID_SOCKET)//没错误发生；将创建另一个接收文件工作线程进行等待下一个连接
	{
		HANDLE m_Accept_RecvFileInfoThread = CreateThread(NULL,0,Accept_RecvFileStructThread,(LPVOID)pFile,0,NULL);
		pFile->m_CarAccept_RecvFileInfoThread.Add(m_Accept_RecvFileInfoThread);
	}
	//接收文件信息
	int FileSize;
	send(AcceptSocket,"RecvRequest",sizeof("RecvRequest"),0);//发送recv请求；使发送和接收保持一致；
	if (recv(AcceptSocket,(char*)&FileSize,sizeof(FileSize),0) == SOCKET_ERROR)//接收文件个数
	{
	 	AfxMessageBox("接收文件信息失败！",MB_ICONSTOP);
	 	return 0;
 	}
 	CStructure::SockFileStruct sockfilestruct;
 	CStructure::FileStruct filestruct;
	//动态数据要想作为消息进行发送，必须用new开内存，发送的只是地址，实际不发送内存
	//结构体也是，必须用new开内存，在发出首地址；
	CArray<CStructure::FileStruct,CStructure::FileStruct&> *Carfilestruct = new CArray<CStructure::FileStruct,CStructure::FileStruct&>;
 	for (int i=0;i<FileSize;i++)
 	{
		send(AcceptSocket,"RecvRequest",sizeof("RecvRequest"),0);//发送recv通知；使发送和接收保持一致；
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
	//发送消息给主窗口
	CStructure::RecvFileDlgInfo *TmpTur = new CStructure::RecvFileDlgInfo;
	TmpTur->AcceptSocket = AcceptSocket;
	TmpTur->Carfilestruct = Carfilestruct;
	::SendMessage(pFile->m_hNotifyWnd,WM_FILETRANSFER,NULL,(LPARAM)TmpTur);
	

	return 0;
}