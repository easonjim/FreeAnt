// FreeAnt.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "FreeAntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreeAntApp

BEGIN_MESSAGE_MAP(CFreeAntApp, CWinApp)
	//{{AFX_MSG_MAP(CFreeAntApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreeAntApp construction

CFreeAntApp::CFreeAntApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFreeAntApp object

CFreeAntApp theApp;
CGroupTalk *g_pTalk;
CFileTransfer *pTransfer;


/////////////////////////////////////////////////////////////////////////////
// CFreeAntApp initialization

BOOL CFreeAntApp::InitInstance()
{
	AfxEnableControlContainer();
	AfxInitRichEdit();
	InitSocket();//加载2.2版本WinSock库


/************************************************************************/
/*只运行一个实例                                                        */
/************************************************************************/
	// 创建互斥量
	HANDLE m_hMutex = CreateMutex(NULL, FALSE, "FreeAnt");
	// 检查错误代码
	
	// 如果程序已经存在并且正在运行
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		
	{
		// 如果已有互斥量存在则释放句柄并复位互斥量
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
		// 程序退出
		return FALSE;
	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	/************************************************************************/
	/* 使主对话框一启动就是非模态对话框										*/
	/*切记一定要在对话框属性，可见样式，把可见的钩去掉						*/
	/************************************************************************/
	CFreeAntDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.Create(CFreeAntDlg::IDD);
	//判断是否一定一次使用
	if (::GetFileAttributes(".\\Setup\\Setup.ini") != INVALID_FILE_ATTRIBUTES)
	{
		char cInitShowDlg[5];
		int iInitShowDlg;
		::GetPrivateProfileString("Setup","InitShowDlg","1",cInitShowDlg,5,".\\Setup\\Setup.ini");
		iInitShowDlg = atoi(cInitShowDlg);
		if (iInitShowDlg == 1)//根据ini文件判断
		{
			dlg.ShowWindow(SW_SHOW);
		}
		if (iInitShowDlg == 0)
		{
			dlg.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		dlg.ShowWindow(SW_SHOW);
	}
	dlg.RunModalLoop();
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}