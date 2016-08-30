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

/////////////////////////////////////////////////////////////////////////////
// CFreeAntApp initialization

BOOL CFreeAntApp::InitInstance()
{
	AfxEnableControlContainer();
	AfxInitRichEdit();
	InitSocket();
	
	/*******只运行一个实例*******/
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

	CFreeAntDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
