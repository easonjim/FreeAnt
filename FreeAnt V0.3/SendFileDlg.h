#if !defined(AFX_SENDFILEDLG_H__5134C72F_90F8_4598_AD8E_93963ACBB581__INCLUDED_)
#define AFX_SENDFILEDLG_H__5134C72F_90F8_4598_AD8E_93963ACBB581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendFileDlg dialog

class CSendFileDlg : public CDialog
{
// Construction
public:
	CStructure::FileStruct filestruct;
	static CArray<CStructure::FileStruct,CStructure::FileStruct&> m_Carfilestruct;//用于显示在发送文件列表
	CSendFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendFileDlg)
	enum { IDD = IDD_SENDFILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFileDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSendFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonDelete();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitListCtrl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILEDLG_H__5134C72F_90F8_4598_AD8E_93963ACBB581__INCLUDED_)
