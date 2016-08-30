#if !defined(AFX_SETUP2DLG_H__2EAAD732_DF74_49B6_8A8D_7E0E55E5092C__INCLUDED_)
#define AFX_SETUP2DLG_H__2EAAD732_DF74_49B6_8A8D_7E0E55E5092C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup2Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup2Dlg dialog

class CSetup2Dlg : public CDialog
{
// Construction
public:
	CSetup2Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetup2Dlg)
	enum { IDD = IDD_SETUP2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetup2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetup2Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP2DLG_H__2EAAD732_DF74_49B6_8A8D_7E0E55E5092C__INCLUDED_)
