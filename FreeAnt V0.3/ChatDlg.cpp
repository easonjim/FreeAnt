// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "ChatDlg.h"
#include "FreeAntDlg.h"//因为要在这里使用这个类里面的动态数组，所以在这里声明

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog
extern CGroupTalk *g_pTalk;

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	//{{AFX_MSG_MAP(CChatDlg)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg message handlers

BOOL CChatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString TmpStr;
	TmpStr += "用户：";
	TmpStr += name;
	TmpStr += "  IP：";
	TmpStr += IP;
	SetDlgItemText(IDC_EDIT_USERINFO,TmpStr);
	SetWindowText(name);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChatDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_RICHEDIT_SEND,TmpBuf);
	if (TmpBuf == "")
	{
		MessageBox("请输入信息！","错误");
		return;
	}
	strcpy(SendBuf,TmpBuf);
	g_pTalk->SendText(SendBuf,strlen(SendBuf)+1,dwAddr);
	GetDlgItemText(IDC_RICHEDIT_RECV,TmpBuf);
 	TmpBuf += "自己说：";
 	TmpBuf += SendBuf;
	TmpBuf += "\r\n";
	SetDlgItemText(IDC_RICHEDIT_RECV,TmpBuf);
	SetDlgItemText(IDC_RICHEDIT_SEND,"");
	((CEdit*)GetDlgItem(IDC_RICHEDIT_RECV))->SetSel(0,TmpBuf.GetLength());
}

void CChatDlg::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	for (int i=0;i<CFreeAntDlg::m_CarUserInfo2.GetSize();i++)
	{
		if (CFreeAntDlg::m_CarUserInfo2.ElementAt(i).dwAddr == dwAddr)
		{
			CFreeAntDlg::m_CarUserInfo2.RemoveAt(i);
		}
	}
	DestroyWindow();
	CDialog::PostNcDestroy(); //删除指针
	delete this;
}

void CChatDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	for (int i=0;i<CFreeAntDlg::m_CarUserInfo2.GetSize();i++)
	{
		if (CFreeAntDlg::m_CarUserInfo2.ElementAt(i).dwAddr == dwAddr)
		{
			CFreeAntDlg::m_CarUserInfo2.RemoveAt(i);
		}
	}
	DestroyWindow();
	CDialog::PostNcDestroy(); //删除指针
	delete this;
}

BOOL CChatDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)//修改EXC键//屏蔽其退出功能
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
