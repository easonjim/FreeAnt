#if !defined(AFX_SETUP1DLG_H__F8C62123_100F_4567_B00C_4B39DD624860__INCLUDED_)
#define AFX_SETUP1DLG_H__F8C62123_100F_4567_B00C_4B39DD624860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup1Dlg dialog

class CSetup1Dlg : public CDialog
{
// Construction
public:
	CSetup1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetup1Dlg)
	enum { IDD = IDD_SETUP1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetup1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetup1Dlg)
	afx_msg void OnCheckMute();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP1DLG_H__F8C62123_100F_4567_B00C_4B39DD624860__INCLUDED_)
