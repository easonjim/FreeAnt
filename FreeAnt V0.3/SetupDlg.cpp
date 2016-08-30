// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "SetupDlg.h"
#include "FreeAntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_ENTER, OnButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_APPLICATION, OnButtonApplication)
	ON_LBN_SELCHANGE(IDC_LIST_OPTIONS, OnSelchangeListOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CFreeAntDlg *dlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_pDlg = NULL;
	DestroyWindow();//非模式对话框的销毁
	CDialog::PostNcDestroy(); //删除指针
	delete this;
}

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitListBox();
	InitDlg();
	InitSetup();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::InitListBox()
{
	CListBox *pList = (CListBox*)GetDlgItem(IDC_LIST_OPTIONS);
	pList->AddString("    详细设置");
	pList->AddString("    网络设置");
	pList->SetItemHeight(1,13);
	pList->SetCurSel(0);
}

void CSetupDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	CFreeAntDlg *dlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_pDlg = NULL;
	DestroyWindow();//非模式对话框的销毁
	CDialog::PostNcDestroy(); //删除指针
	delete this;
}

void CSetupDlg::OnButtonEnter() 
{
	// TODO: Add your control notification handler code here
	OnButtonApplication();
	OnButtonCancel();
}

void CSetupDlg::OnButtonApplication() 
{
	// TODO: Add your control notification handler code here
	CFreeAntDlg *pdlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();
	CString RecvFilePath;
	CString Mute;
	CString FileTonePath;
	CString MsgTonePath;
	CString InitShowDlg;
	CString BalloonPrompt;
	if (((CButton*)setup1.GetDlgItem(IDC_CHECK_MUTE))->GetCheck())
	{
		Mute = "0";
	}
	else
	{
		Mute = "1";
	}
	if (((CButton*)setup1.GetDlgItem(IDC_CHECK_INITSHOWDLG))->GetCheck())
	{
		InitShowDlg = "1";
	}
	else
	{
		InitShowDlg = "0";
	}
	if (((CButton*)setup1.GetDlgItem(IDC_CHECK_BALLOONPROMPT))->GetCheck())
	{
		BalloonPrompt = "1";
	}
	else
	{
		BalloonPrompt = "0";
	}
	setup1.GetDlgItemText(IDC_EDIT_RECVFILEPATH,RecvFilePath);
	setup1.GetDlgItemText(IDC_EDIT_MSGTONEPATH,MsgTonePath);
	setup1.GetDlgItemText(IDC_EDIT_FILETONEPATH,FileTonePath);
  	::WritePrivateProfileString("Setup","Mute",Mute,pdlg->m_IniPath);
  	::WritePrivateProfileString("Setup","InitShowDlg",InitShowDlg,pdlg->m_IniPath);
  	::WritePrivateProfileString("Setup","BalloonPrompt",BalloonPrompt,pdlg->m_IniPath);
	::WritePrivateProfileString("Setup","RecvFilePath",RecvFilePath,pdlg->m_IniPath);
	::WritePrivateProfileString("Setup","FileTonePath",FileTonePath,pdlg->m_IniPath);
	::WritePrivateProfileString("Setup","MsgTonePath",MsgTonePath,pdlg->m_IniPath);
	pdlg->m_Mute = atoi(Mute);
	pdlg->m_RecvFilePath = RecvFilePath;
	pdlg->m_FileTonePath = FileTonePath;
	pdlg->m_MsgTonePath = MsgTonePath;
	pdlg->m_InitShowDlg = atoi(InitShowDlg);
	pdlg->m_BalloonPrompt = atoi(BalloonPrompt);

}

void CSetupDlg::OnSelchangeListOptions() 
{
	// TODO: Add your control notification handler code here
	CString SelStr;
	((CListBox*)GetDlgItem(IDC_LIST_OPTIONS))->
		GetText(((CListBox*)GetDlgItem(IDC_LIST_OPTIONS))->
		GetCurSel(),SelStr);
	if (SelStr == "    详细设置")
	{
		setup1.ShowWindow(SW_SHOW);
		setup2.ShowWindow(SW_HIDE);
	}
	if (SelStr == "    网络设置")
	{
		setup1.ShowWindow(SW_HIDE);
		setup2.ShowWindow(SW_SHOW);
	}
}

void CSetupDlg::InitDlg()
{	
	CRect rc;
	this->GetClientRect(rc);
 	rc.top += 15;
 	rc.left += 145;
 	rc.right -= 15;
	rc.bottom -= 15;
	setup1.Create(IDD_SETUP1_DIALOG,this);
	setup2.Create(IDD_SETUP2_DIALOG,this);
	setup1.MoveWindow(&rc);
	setup2.MoveWindow(&rc);
	setup1.ShowWindow(SW_SHOW);
}


void CSetupDlg::InitSetup()
{	
	CFreeAntDlg *pdlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();
	if (pdlg->m_Mute == 0)
	{
		((CButton*)setup1.GetDlgItem(IDC_CHECK_MUTE))->SetCheck(1);
		((CEdit*)setup1.GetDlgItem(IDC_EDIT_FILETONEPATH))->EnableWindow(TRUE);
		((CEdit*)setup1.GetDlgItem(IDC_EDIT_MSGTONEPATH))->EnableWindow(TRUE);
		((CEdit*)setup1.GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
		((CEdit*)setup1.GetDlgItem(IDC_BUTTON3))->EnableWindow(TRUE);
		setup1.SetDlgItemText(IDC_EDIT_MSGTONEPATH,pdlg->m_MsgTonePath);
		setup1.SetDlgItemText(IDC_EDIT_FILETONEPATH,pdlg->m_FileTonePath);
	}
	if (pdlg->m_InitShowDlg == 1)
	{
		((CButton*)setup1.GetDlgItem(IDC_CHECK_INITSHOWDLG))->SetCheck(1);
	}	
	if (pdlg->m_BalloonPrompt == 1)
	{
		((CButton*)setup1.GetDlgItem(IDC_CHECK_BALLOONPROMPT))->SetCheck(1);
	}	
	setup1.SetDlgItemText(IDC_EDIT_RECVFILEPATH,pdlg->m_RecvFilePath);
}
