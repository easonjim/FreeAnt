//////////////////////////////////////
// InitSocket.h : header file

#ifndef _INITSOCKET_H_
#define _INITSOCKET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



void InitSocket();//��ʼ���׽��ֿ�
class CInitSocket
{
public:
	CInitSocket();//����2.2�汾��Winsock��
	~CInitSocket();//��ֹWinsock��
};

#endif //#define _INITSOCKET_H_


/*
	����2.2�汾���׽��ֿ����

���÷�����
	1���� StdAfx.h ��� InitSocket.h ͷ�ļ�
	2���ڳ����ʼ������ InitSocket() ��ʼ���׽��ֿ�
˵����
	����ʹ�������������ҷֿ�ʵ�����ﺯ���ķ���������ͷ�ļ���Դ�ļ���ͬʵ��һ���ࣩ,
���Ա�ҪʱҪ�ڿ�ͷ�������������InitSocket.cpp ��
	���ʹ��MFC�����࣬Ҫ��InitSocket.cpp�ļ������� Stdafx.h ��
*/