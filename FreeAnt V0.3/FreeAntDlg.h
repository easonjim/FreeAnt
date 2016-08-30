// FreeAntDlg.h : header file
//

#if !defined(AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_)
#define AFX_FREEANTDLG_H__1025A32B_4B06_4A4B_B737_013B971AF3D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg dialog
#define WM_TASKBAR WM_USER+101//100����
#include "SetupDlg.h"

class CFreeAntDlg : public CDialog
{
// Construction
public://ini�ļ�����
	CString m_RecvFilePath;//Ĭ�ϱ����ļ���ַ
	int	m_Mute;//������0Ϊ��1Ϊ��
	CString	m_FileTonePath;//�ļ���;��
	CString	m_MsgTonePath;
	int	m_InitShowDlg;//��ʼ����ʾ���ڣ�0Ϊ��1Ϊ��
	int m_BalloonPrompt;//������ʾ��0Ϊ��1Ϊ��
	CString m_exePath;//������;��
	CString m_IniPath;//ini;��
public:
	CSetupDlg *m_pDlg;//��Ϊֻ����һ�Σ����Զ���Ϊȫ��
	
	CRect EditRect;//��ȡ�ؼ�λ��
	void MoveControlO();//ԭ���ؼ���λ��
	void MoveControlN();//�¿ؼ���λ��

	CArray<CStructure::FileStruct,CStructure::FileStruct&> m_Carfilestruct;//�����ļ���Ϣ
	CStructure::UserInfo UserInfo1;
	CArray<CStructure::UserInfo,CStructure::UserInfo&> m_CarUserInfo;//���ڴ����û���Ϣ
	CStructure::UserInfo2 UserInfo3;
	static CArray<CStructure::UserInfo2,CStructure::UserInfo2&> m_CarUserInfo2;//�����ж��Ƿ��Ѿ����������촰��

	
	CFreeAntDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFreeAntDlg)
	enum { IDD = IDD_FREEANT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreeAntDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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
	afx_msg void OnButtonSendfile();
	afx_msg void OnRclickListUserinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonMainmenu();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTaskbarMenuitemExit();
	afx_msg void OnUserinfolistMenuitemSendfile();
	afx_msg void OnUserinfolistMenuitemSendfolder();
	afx_msg void OnMainMenuitemSendfile();
	afx_msg void OnMainMenuitemSendfolder();
	afx_msg void OnUserinfolistMenuitemSelectall();
	afx_msg void OnUserinfolistMenuitemInverse();
	afx_msg void OnButtonRefresh();
	afx_msg void OnTaskbarMenuitemSetup();
	afx_msg void OnTaskbarMenuitemAbout();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	afx_msg LRESULT WMTASKBAR(WPARAM wParam,LPARAM lParam);
	afx_msg void WMFILETRANSFER(WPARAM wParam,LPARAM lParam);
	afx_msg void WMGROUPTALK(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void InitSetup();//��ʼ�����ã����紴���ļ���
	void InitControlSite();
	void InitTaskbar();
	NOTIFYICONDATA nid;//����ͼ�����
	void InitFileTransfer();
	static DWORD WINAPI SendFileThread(LPVOID lpParameter);
	void HandleGroupMsg(HWND hDlg, GT_HDR *pHeader);
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
