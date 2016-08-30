#if !defined(AFX_SETUPDLG_H__1CD0809B_3509_434D_9FD2_8F7127DFC683__INCLUDED_)
#define AFX_SETUPDLG_H__1CD0809B_3509_434D_9FD2_8F7127DFC683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog
#include "Setup1Dlg.h"
#include "Setup2Dlg.h"

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonEnter();
	afx_msg void OnButtonApplication();
	afx_msg void OnSelchangeListOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitSetup();
	void InitDlg();
	CSetup1Dlg setup1;//œÍœ∏…Ë÷√
	CSetup2Dlg setup2;//Õ¯¬Á…Ë÷√
	void InitListBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__1CD0809B_3509_434D_9FD2_8F7127DFC683__INCLUDED_)
