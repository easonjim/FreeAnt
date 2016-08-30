// FreeAntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "FreeAntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg dialog
extern CGroupTalk *g_pTalk;

CFreeAntDlg::CFreeAntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFreeAntDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFreeAntDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreeAntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreeAntDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFreeAntDlg, CDialog)
	//{{AFX_MSG_MAP(CFreeAntDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GROUPTALK,WMGROUPTALK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg message handlers

BOOL CFreeAntDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitGroupTalk();
	InitListCtrl();
	//InitEditStasus
	SetDlgItemText(IDC_EDIT_STATUS,"Welcome to use FreeAnt!");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFreeAntDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFreeAntDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFreeAntDlg::WMGROUPTALK(WPARAM wParam,LPARAM lParam)
{
	if(wParam != 0) 
	{
		::MessageBox(m_hWnd, (LPCTSTR)lParam, "出错！", 0);
	}
	else
	{
		HandleGroupMsg(m_hWnd, (GT_HDR*)lParam);
	}
}

void CFreeAntDlg::HandleGroupMsg(HWND hDlg, GT_HDR *pHeader)
{
	switch(pHeader->gt_type)
	{
	case MT_JION:		// 新用户加入
		{
			// 显示给用户
			SOCKADDR_IN ip;
			ip.sin_addr.S_un.S_addr=pHeader->dwAddr;
			UserInfo1.IP=inet_ntoa(ip.sin_addr);
			UserInfo1.dwAddr=pHeader->dwAddr;
			strcpy(UserInfo1.name,pHeader->szUser);
			m_CarUserInfo.Add(UserInfo1);
		 	SetDlgItemText(IDC_EDIT_STATUS,"Welcome to use FreeAnt!");
			int nRow = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertItem(0,UserInfo1.name);
		 	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetItemText(nRow,1,UserInfo1.IP);
	
		}		
		break;
		
	case MT_LEAVE:		// 用户离开
		{
			// 显示给用户
			char szText[56];
			wsprintf(szText, " 用户：《%s》离开！", pHeader->szUser);
			SetDlgItemText(IDC_EDIT_STATUS,szText);
			
			// 将离开的用户从列表框中移除
			char ItemIP[100];
			ItemCount = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();//获取列表的数量
			for (int i=0;i<m_CarUserInfo.GetSize();i++)
			{
				if (m_CarUserInfo.ElementAt(i).dwAddr == pHeader->dwAddr)
				{
					for (int j=0;j<ItemCount;j++)
					{
						((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemText(j,1,ItemIP,100);
						if (m_CarUserInfo.ElementAt(i).IP == ItemIP)
						{
							((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->DeleteItem(j);
						}
					}
					m_CarUserInfo.RemoveAt(i);//删除在动态数组里的用户
				}
			}
		}
		break;
		
 	case MT_MESG:		// 用户发送消息
 		{
 			char *psz = pHeader->data();
 			psz[pHeader->nDataLength] = '\0';
 			char szText[1024];
 			wsprintf(szText, "【%s】说：\n\n", pHeader->szUser);
 			strncat(szText, psz, 1024 - strlen(szText));
			MessageBox((LPCTSTR)szText,"收到消息");
		}
 		break;
 	}
}

void CFreeAntDlg::InitGroupTalk()
{
	g_pTalk = new CGroupTalk(m_hWnd, ::inet_addr("234.5.6.7"));
}

void CFreeAntDlg::InitListCtrl()
{
	DWORD dwStyle = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES|
		LVS_EX_HEADERDRAGDROP|LVS_SHOWSELALWAYS;
    ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetExtendedStyle(dwStyle); //设置扩展风格
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(0,"主机名",LVCFMT_LEFT,100);
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(1,"IP 地址",LVCFMT_LEFT,150);
}

void CFreeAntDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_RICHEDIT_SEND,TmpSendBuf);
	if (TmpSendBuf == "")
	{
		MessageBox("请输入信息！","错误");
		return;
	}
	strcpy(SendBuf,TmpSendBuf);
	ItemCheckCount = 0;
	ItemCount = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();//获取列表的数量
	for (int i=0;i<ItemCount;i++)
	{
		if (((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetCheck(i) != 0)
		{
			ItemCheckCount++;
		}
	}
	if (ItemCheckCount == 0)
	{
		MessageBox("请选择用户！","错误");
		return;
	}
	if (ItemCheckCount == ItemCount)
	{
		g_pTalk->SendText(SendBuf,strlen(SendBuf)+1);//面向组的发送信息
		((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND))->SetWindowText("");
	}
	else
	{
		for (int i=0;i<ItemCount;i++)
		{
			if (((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetCheck(i) != 0)
			{
				char ItemIP[50];
				((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemText(i,1,ItemIP,50);
				for (int i=0;i<m_CarUserInfo.GetSize();i++)
				{
					if (m_CarUserInfo.ElementAt(i).IP==ItemIP)
					{
						g_pTalk->SendText(SendBuf,strlen(SendBuf)+1,m_CarUserInfo.ElementAt(i).dwAddr);//面向单用户的发送信息
					}
				}
				((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND))->SetWindowText("");
			}
		}
	}
}

void CFreeAntDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	delete g_pTalk;//用户关闭程序
	CDialog::OnClose();
}
