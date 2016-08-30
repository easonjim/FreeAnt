// Setup1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "Setup1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup1Dlg dialog


CSetup1Dlg::CSetup1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetup1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetup1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetup1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup1Dlg, CDialog)
	//{{AFX_MSG_MAP(CSetup1Dlg)
	ON_BN_CLICKED(IDC_CHECK_MUTE, OnCheckMute)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup1Dlg message handlers

void CSetup1Dlg::OnCheckMute() 
{
	// TODO: Add your control notification handler code here
	if (((CButton*)GetDlgItem(IDC_CHECK_MUTE))->GetCheck())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_MSGTONEPATH))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_FILETONEPATH))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_BUTTON3))->EnableWindow(TRUE);
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT_MSGTONEPATH))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_FILETONEPATH))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_BUTTON3))->EnableWindow(FALSE);
	}
}

void CSetup1Dlg::OnButton1() //���ļ���
{
	// TODO: Add your control notification handler code here
	char szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = "��ѡ��Ŀ¼";
	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);
	if(pidl == NULL)  
	{
		return;
	}
	if(!SHGetPathFromIDList(pidl, szDir))   
	{
		return;
	}
	else
	{
		CString str;
		str = szDir;
		((CEdit*)GetDlgItem(IDC_EDIT_RECVFILEPATH))->SetWindowText(str);
	}
}

void CSetup1Dlg::OnButton2() //���ļ�
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFileOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT, "*.wav|*.wav||", this);
	int structsize=0; 
	DWORD dwVersion,dwWindowsMajorVersion,dwWindowsMinorVersion; 
	//���Ŀǰ�Ĳ���ϵͳ
	dwVersion = GetVersion(); 
	dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion))); 
	dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion))); 
	// ������еĲ���ϵͳ��Windows NT/2000 
	if (dwVersion < 0x80000000)  
	{
		structsize =88;//��ʾ�µ��ļ��Ի��� 
	}
	else 
	{
		//���еĲ���ϵͳWindows 95/98  
		structsize =76;//��ʾ�ϵ��ļ��Ի��� 
	}
	dlgFileOpen.m_ofn.lStructSize=structsize;
	if (dlgFileOpen.DoModal() == IDOK)
	{
		CString FilePathName;
		FilePathName = dlgFileOpen.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDIT_MSGTONEPATH))->SetWindowText(FilePathName);
	}
}

void CSetup1Dlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFileOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT, "*.wav|*.wav||", this);
	int structsize=0; 
	DWORD dwVersion,dwWindowsMajorVersion,dwWindowsMinorVersion; 
	//���Ŀǰ�Ĳ���ϵͳ
	dwVersion = GetVersion(); 
	dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion))); 
	dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion))); 
	// ������еĲ���ϵͳ��Windows NT/2000 
	if (dwVersion < 0x80000000)  
	{
		structsize =88;//��ʾ�µ��ļ��Ի��� 
	}
	else 
	{
		//���еĲ���ϵͳWindows 95/98  
		structsize =76;//��ʾ�ϵ��ļ��Ի��� 
	}
	dlgFileOpen.m_ofn.lStructSize=structsize;
	if (dlgFileOpen.DoModal() == IDOK)
	{
		CString FilePathName;
		FilePathName = dlgFileOpen.GetPathName();
		((CEdit*)GetDlgItem(IDC_EDIT_FILETONEPATH))->SetWindowText(FilePathName);
	}
}
