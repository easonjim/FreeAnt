// FreeAntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "FreeAntDlg.h"
#include "ChatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg dialog
extern CGroupTalk *g_pTalk;
CArray<UserInfo2,UserInfo2&> CFreeAntDlg::m_CarUserInfo2;//��Ϊ�����˾�̬����������������

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
	ON_BN_CLICKED(IDC_BUTTON_MSGPROMPT, OnButtonMsgprompt)
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
		::MessageBox(m_hWnd, (LPCTSTR)lParam, "����", 0);
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
	case MT_JION:		// ���û�����
		{
			// ��ʾ���û�
			SOCKADDR_IN ip;
			ip.sin_addr.S_un.S_addr=pHeader->dwAddr;
			UserInfo1.IP=inet_ntoa(ip.sin_addr);
			UserInfo1.dwAddr=pHeader->dwAddr;
			strcpy(UserInfo1.name,pHeader->szUser);
			m_CarUserInfo.Add(UserInfo1);
		 	SetDlgItemText(IDC_EDIT_STATUS,"Welcome to use FreeAnt!");
			int nRow = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertItem(0,UserInfo1.name);
		 	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetItemText(nRow,1,UserInfo1.IP);

			//֪ͨ���û������촰���Ѿ����ߣ�ǰ�����Ѿ����������촰��
			for (int i=0;i<m_CarUserInfo2.GetSize();i++)
			{
				if (m_CarUserInfo2.ElementAt(i).dwAddr == pHeader->dwAddr)
				{
					m_CarUserInfo2.ElementAt(i).dlg->SetWindowText(m_CarUserInfo2.ElementAt(i).dlg->name);
				}
			}
	
		}		
		break;
		
	case MT_LEAVE:		// �û��뿪
		{
			// ��ʾ���û�
			char szText[56];
			wsprintf(szText, " �û�����%s���뿪��", pHeader->szUser);
			SetDlgItemText(IDC_EDIT_STATUS,szText);
			
			// ���뿪���û����б�����Ƴ�
			char ItemIP[100];
			ItemCount = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();//��ȡ�б������
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
					m_CarUserInfo.RemoveAt(i);//ɾ���ڶ�̬��������û�
				}
			}

			//֪ͨ���û������촰���Ѿ�����
			for (i=0;i<m_CarUserInfo2.GetSize();i++)
			{
				if (m_CarUserInfo2.ElementAt(i).dwAddr == pHeader->dwAddr)
				{
					m_CarUserInfo2.ElementAt(i).dlg->SetWindowText("���û��Ѿ����ߣ�");
				}
			}
		}
		break;
		
 	case MT_MESG:		// �û�������Ϣ
 		{
			if (m_CarUserInfo2.GetSize() == 0)
			{
				CChatDlg *dlg = new CChatDlg;

				strcpy(UserInfo3.name,pHeader->szUser);
				SOCKADDR_IN ip;
				ip.sin_addr.S_un.S_addr = pHeader->dwAddr;
				UserInfo3.IP = inet_ntoa(ip.sin_addr);
				UserInfo3.dwAddr = pHeader->dwAddr;
				UserInfo3.dlg = dlg;
				m_CarUserInfo2.Add(UserInfo3);

				strcpy(dlg->name,pHeader->szUser);
				dlg->IP = inet_ntoa(ip.sin_addr);
				dlg->dwAddr = pHeader->dwAddr;
				dlg->Create(IDD_CHAT_DIALOG,GetDesktopWindow());
				
 				((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_SHOW);
 				((CEdit*)GetDlgItem(IDC_EDIT_STATUS))->ShowWindow(SW_HIDE);
			}
			else
			{
				for (int i=0;i<m_CarUserInfo2.GetSize();i++)
				{
					if (m_CarUserInfo2.ElementAt(i).dwAddr == pHeader->dwAddr)
					{
						break;
					}
					if (m_CarUserInfo2.GetSize()-1 == i)
					{
						CChatDlg *dlg = new CChatDlg;

						strcpy(UserInfo3.name,pHeader->szUser);
						SOCKADDR_IN ip;
						ip.sin_addr.S_un.S_addr = pHeader->dwAddr;
						UserInfo3.IP = inet_ntoa(ip.sin_addr);
						UserInfo3.dwAddr = pHeader->dwAddr;
						UserInfo3.dlg = dlg;
						m_CarUserInfo2.Add(UserInfo3);

						strcpy(dlg->name,pHeader->szUser);
						dlg->IP = inet_ntoa(ip.sin_addr);
						dlg->dwAddr = pHeader->dwAddr;
						dlg->Create(IDD_CHAT_DIALOG,GetDesktopWindow());
						
						((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_SHOW);
 						((CEdit*)GetDlgItem(IDC_EDIT_STATUS))->ShowWindow(SW_HIDE);
					}
				}
			}

			for (int i=0;i<m_CarUserInfo2.GetSize();i++)
			{
				if (m_CarUserInfo2.ElementAt(i).dwAddr == pHeader->dwAddr)
				{
					char *psz = pHeader->data();
					psz[pHeader->nDataLength] = '\0';
					char szText[1024];
					CString TmpszText;
					m_CarUserInfo2.ElementAt(i).dlg->GetDlgItemText(IDC_RICHEDIT_RECV,TmpszText);
					wsprintf(szText, "��%s��˵��", pHeader->szUser);
 					strncat(szText, psz, 1024 - strlen(szText));
					TmpszText += szText;
					TmpszText += "\r\n";
					m_CarUserInfo2.ElementAt(i).dlg->SetDlgItemText(IDC_RICHEDIT_RECV,TmpszText);
					((CEdit*)(m_CarUserInfo2.ElementAt(i).dlg->GetDlgItem(IDC_RICHEDIT_RECV)))->
						SetSel(0,TmpszText.GetLength());
				}
			}
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
    ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetExtendedStyle(dwStyle); //������չ���
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(0,"������",LVCFMT_LEFT,100);
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(1,"IP ��ַ",LVCFMT_LEFT,150);
}

void CFreeAntDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_RICHEDIT_SEND,TmpSendBuf);
	if (TmpSendBuf == "")
	{
		MessageBox("��������Ϣ��","����");
		return;
	}
	strcpy(SendBuf,TmpSendBuf);
	ItemCheckCount = 0;
	ItemCount = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();//��ȡ�б������
	for (int i=0;i<ItemCount;i++)
	{
		if (((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetCheck(i) != 0)
		{
			ItemCheckCount++;
		}
	}
	if (ItemCheckCount == 0)
	{
		MessageBox("��ѡ���û���","����");
		return;
	}
	if (ItemCheckCount == ItemCount)
	{
		g_pTalk->SendText(SendBuf,strlen(SendBuf)+1);//������ķ�����Ϣ
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
						g_pTalk->SendText(SendBuf,strlen(SendBuf)+1,m_CarUserInfo.ElementAt(i).dwAddr);//�����û��ķ�����Ϣ
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
	delete g_pTalk;//�û��رճ���
	CDialog::OnClose();
}

void CFreeAntDlg::OnButtonMsgprompt() 
{
	// TODO: Add your control notification handler code here
	for (int i=0;i<m_CarUserInfo2.GetSize();i++)
	{
		m_CarUserInfo2.ElementAt(i).dlg->ShowWindow(SW_SHOW);
		m_CarUserInfo2.ElementAt(i).dlg->MoveWindow(i*20+250,i*10+300,295,310);//���ô������������λ��
	}
	((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_HIDE);
	((CEdit*)GetDlgItem(IDC_EDIT_STATUS))->ShowWindow(SW_SHOW);
}
