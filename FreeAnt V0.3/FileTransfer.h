////////////////////////////////
// FileTransfer.h : header file

#ifndef _CFILETRANSFER_H_
#define _CFILETRANSFER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <winsock.h>
#pragma comment(lib, "wsock32.lib")

#define WM_FILETRANSFER WM_USER+1

/*

  uMsg:		WM_FILETRANSFER
  wParam:	û�ã�ΪNULL
  lParam:	���ݽṹͷָ��
  
*/

#define FILETRANSFER_PROT 6000   //�˿�

class CFileTransfer
{
public:
	CFileTransfer(HWND hNotifyWnd);
	~CFileTransfer();

protected:
	//��ʼ���׽���
	BOOL InitSocket();

	static DWORD WINAPI Accept_RecvFileStructThread(LPVOID lpParameter);

protected:
	HWND m_hNotifyWnd;		// �����ھ��
	CArray<HANDLE,HANDLE&> m_CarAccept_RecvFileInfoThread;		//�����ļ��߳̾����̬���飻Ҳ�ǽ������ӿͻ���

	SOCKET m_SrvSocket;				//�������׽���
	SOCKADDR_IN m_SrvSocketAddr;	//��������ַ�ṹ
	int m_SrvSocketAddrLen;			//��������ַ�ṹ����

};

#endif //#define _CFILETRANSFER_H_

/*
	����ֻ�����տͻ��������ӣ��������ɿͻ�����SOCKET���ļ���Ϣ���ͳ�ȥ��
�����߳��ڽ��նԻ����У������߳��ڷ��ͶԻ����У�
*/