// FreeAntDlg.h : header file
//

#if !defined(AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_)
#define AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg dialog
struct UserInfo
{
	char name[15];
	CString IP;
	DWORD dwAddr;
};
class CFreeAntDlg : public CDialog
{
// Construction
public:

	UserInfo UserInfo1;
	CArray<UserInfo,UserInfo&> m_CarUserInfo;

	void HandleGroupMsg(HWND hDlg, GT_HDR *pHeader);
	CFreeAntDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFreeAntDlg)
	enum { IDD = IDD_FREEANT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreeAntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFreeAntDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg void WMGROUPTALK(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	char SendBuf[1024];
	CString TmpSendBuf;
	int ItemCheckCount;
	int ItemCount;
	void InitListCtrl();
	void InitGroupTalk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_)
