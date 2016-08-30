#if !defined(AFX_CHATDLG_H__A3B36F7E_1125_4799_9148_8BE117DEA290__INCLUDED_)
#define AFX_CHATDLG_H__A3B36F7E_1125_4799_9148_8BE117DEA290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

class CChatDlg : public CDialog
{
// Construction
public:
	char name[15];
	CString IP;
	DWORD dwAddr;
	CChatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChatDlg)
	enum { IDD = IDD_CHAT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonQuit();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString TmpBuf;
	char SendBuf[1024];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__A3B36F7E_1125_4799_9148_8BE117DEA290__INCLUDED_)
