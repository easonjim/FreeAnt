#if !defined(AFX_RECVFILETHREADDLG_H__CA29F813_95C3_4A5F_81F6_D9A2ABAA200B__INCLUDED_)
#define AFX_RECVFILETHREADDLG_H__CA29F813_95C3_4A5F_81F6_D9A2ABAA200B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecvFileThreadDlg.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRecvFileThreadDlg thread
#include "RecvFileDlg.h"

class CRecvFileThreadDlg : public CWinThread
{
	DECLARE_DYNCREATE(CRecvFileThreadDlg)
protected:
	CRecvFileThreadDlg();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecvFileThreadDlg)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRecvFileDlg dlg;
	virtual ~CRecvFileThreadDlg();

	// Generated message map functions
	//{{AFX_MSG(CRecvFileThreadDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECVFILETHREADDLG_H__CA29F813_95C3_4A5F_81F6_D9A2ABAA200B__INCLUDED_)
