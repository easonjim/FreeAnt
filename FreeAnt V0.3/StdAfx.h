// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__58F9512D_E893_4EB2_A6F7_952FEA8B7102__INCLUDED_)
#define AFX_STDAFX_H__58F9512D_E893_4EB2_A6F7_952FEA8B7102__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "InitSocket.h"
#include "GroupTalk.h"//IP多播组的类；发送信息
#include <afxtempl.h> //动态数组所需头文件

#include <shlwapi.h>//获取文件途径用的函数
#pragma comment(lib,"shlwapi.lib")

#include "File64.h"//用于读取超过4G的大文件；自定义类
#include "Structure.h"//自定义结构体头文件
#include "FileTransfer.h"//发送文件功能的类
#include <mmsystem.h>		//导入声音头文件
#pragma comment(lib,"winmm.lib")//导入声音头文件库
#include <Shlwapi.h>//查询文件夹是否存在头文件
#pragma comment(lib,"Shlwapi.lib")//查询文件夹是否存在头文件库
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__58F9512D_E893_4EB2_A6F7_952FEA8B7102__INCLUDED_)
