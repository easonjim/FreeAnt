// FreeAntDlg.h : header file
//

#if !defined(AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_)
#define AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg dialog
#include "ChatDlg.h"
struct UserInfo
{
	char name[15];
	CString IP;
	DWORD dwAddr;
};
struct UserInfo2
{
	char name[15];
	CString IP;
	DWORD dwAddr;
	CChatDlg *dlg;
};
class CFreeAntDlg : public CDialog
{
// Construction
public:

	UserInfo UserInfo1;
	CArray<UserInfo,UserInfo&> m_CarUserInfo;//用于储存用户信息
	UserInfo2 UserInfo3;
	static CArray<UserInfo2,UserInfo2&> m_CarUserInfo2;//用于判断是否已经创建了聊天窗口

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
	afx_msg void OnButtonMsgprompt();
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
