//////////////////////////////////////
// Structure.h : header file 这样定义结构体不太好用

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"//因为下面运用了CChatDlg这个类的定义，所以要在这边定义ID头文件，不然会出现error C2065: 'IDD_CHAT_DIALOG' : undeclared identifier
#include "ChatDlg.h"

class CStructure
{
public:
	//因为SOCKET发送CString会出错，所以改用char;
	struct FileStruct//文件结构体；用于显示
	{
		CString FileName;//用于显示在列表上；文件名
		ULONGLONG Filelength;//用于显示；文件大小
		CString PathName;//用于打开文件；文件详细路径名；带后缀；c:\b\a.txt
		CString FileSize;//用于显示在列表上；文件大小；有带MB；1MB
		char FilePath[200];//用于显示在列表上；文件途径；不带后缀；c:\b
	};

	struct SockFileStruct//文件结构体；用于发送；相当于中转
	{
		char FileName[200];//用于发送和显示在列表上；文件名
		ULONGLONG Filelength;//用于发送；文件大小
		char PathName[300];//用于打开文件；文件详细路径名；带后缀；c:\b\a.txt
		char FileSize[30];//用于显示在列表上；文件大小；有带MB；1MB
		char FilePath[200];//用于显示在列表上；文件途径；不带后缀；c:\b
	};

	struct RecvFileDlgInfo//用于发送消息到接收文件对话框
	{
		SOCKET AcceptSocket;
		CArray<FileStruct,FileStruct&> *Carfilestruct;
	};

	struct UserInfo//用于主界面
	{
		char name[15];
		CString IP;
		DWORD dwAddr;
	};

	struct UserInfo2//用于聊天窗口
	{
		char name[15];
		CString IP;
		DWORD dwAddr;
		CChatDlg *dlg;
	};

};

#endif //#define _STRUCTURE_H_