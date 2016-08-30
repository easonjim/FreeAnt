//////////////////////////////////////
// Structure.h : header file ��������ṹ�岻̫����

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"//��Ϊ����������CChatDlg�����Ķ��壬����Ҫ����߶���IDͷ�ļ�����Ȼ�����error C2065: 'IDD_CHAT_DIALOG' : undeclared identifier
#include "ChatDlg.h"

class CStructure
{
public:
	//��ΪSOCKET����CString��������Ը���char;
	struct FileStruct//�ļ��ṹ�壻������ʾ
	{
		CString FileName;//������ʾ���б��ϣ��ļ���
		ULONGLONG Filelength;//������ʾ���ļ���С
		CString PathName;//���ڴ��ļ����ļ���ϸ·����������׺��c:\b\a.txt
		CString FileSize;//������ʾ���б��ϣ��ļ���С���д�MB��1MB
		char FilePath[200];//������ʾ���б��ϣ��ļ�;����������׺��c:\b
	};

	struct SockFileStruct//�ļ��ṹ�壻���ڷ��ͣ��൱����ת
	{
		char FileName[200];//���ڷ��ͺ���ʾ���б��ϣ��ļ���
		ULONGLONG Filelength;//���ڷ��ͣ��ļ���С
		char PathName[300];//���ڴ��ļ����ļ���ϸ·����������׺��c:\b\a.txt
		char FileSize[30];//������ʾ���б��ϣ��ļ���С���д�MB��1MB
		char FilePath[200];//������ʾ���б��ϣ��ļ�;����������׺��c:\b
	};

	struct RecvFileDlgInfo//���ڷ�����Ϣ�������ļ��Ի���
	{
		SOCKET AcceptSocket;
		CArray<FileStruct,FileStruct&> *Carfilestruct;
	};

	struct UserInfo//����������
	{
		char name[15];
		CString IP;
		DWORD dwAddr;
	};

	struct UserInfo2//�������촰��
	{
		char name[15];
		CString IP;
		DWORD dwAddr;
		CChatDlg *dlg;
	};

};

#endif //#define _STRUCTURE_H_