//////////////////////////////////////
// InitSocket.h : header file

#ifndef _INITSOCKET_H_
#define _INITSOCKET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



void InitSocket();//初始化套接字库
class CInitSocket
{
public:
	CInitSocket();//加载2.2版本的Winsock库
	~CInitSocket();//终止Winsock库
};

#endif //#define _INITSOCKET_H_


/*
	加载2.2版本的套接字库的类

调用方法：
	1、在 StdAfx.h 添加 InitSocket.h 头文件
	2、在程序初始化调用 InitSocket() 初始化套接字库
说明：
	由于使用了内联函数且分开实现类里函数的方法（即有头文件和源文件共同实现一个类）,
所以必要时要在开头这样添加声明：InitSocket.cpp 。
	如果使用MFC基础类，要在InitSocket.cpp文件中声明 Stdafx.h 。
*/