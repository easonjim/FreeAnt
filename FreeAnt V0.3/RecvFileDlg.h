#if !defined(AFX_RECVFILEDLG_H__997339DC_90A5_428D_975B_12A121DE1055__INCLUDED_)
#define AFX_RECVFILEDLG_H__997339DC_90A5_428D_975B_12A121DE1055__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecvFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecvFileDlg dialog

class CRecvFileDlg : public CDialog
{
// Construction
public:
	CString m_PathName;//全局
	SOCKET m_AcceptSocket;
	CArray<CStructure::FileStruct,CStructure::FileStruct&> *m_Carfilestruct;
	CRecvFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecvFileDlg)
	enum { IDD = IDD_RECVFILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecvFileDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRecvFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSaveas();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonReceiver();
	afx_msg void OnClose();
	afx_msg void OnButtonOpenFileDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitListCtrl();
protected:
	int ButtonRtID;//确认按下是哪个按钮；1为接收；2为另存为；
	HANDLE m_RecvFileThreadHandle;
	static DWORD WINAPI RecvFileThread(LPVOID lpParameter);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECVFILEDLG_H__997339DC_90A5_428D_975B_12A121DE1055__INCLUDED_)
