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
  wParam:	没用；为NULL
  lParam:	数据结构头指针
  
*/

#define FILETRANSFER_PROT 6000   //端口

class CFileTransfer
{
public:
	CFileTransfer(HWND hNotifyWnd);
	~CFileTransfer();

protected:
	//初始化套接字
	BOOL InitSocket();

	static DWORD WINAPI Accept_RecvFileStructThread(LPVOID lpParameter);

protected:
	HWND m_hNotifyWnd;		// 主窗口句柄
	CArray<HANDLE,HANDLE&> m_CarAccept_RecvFileInfoThread;		//接收文件线程句柄动态数组；也是接收连接客户端

	SOCKET m_SrvSocket;				//服务器套接字
	SOCKADDR_IN m_SrvSocketAddr;	//服务器地址结构
	int m_SrvSocketAddrLen;			//服务器地址结构长度

};

#endif //#define _CFILETRANSFER_H_

/*
	此类只做接收客户机的连接，并把生成客户机的SOCKET、文件信息发送出去；
接收线程在接收对话框中，发送线程在发送对话框中；
*/