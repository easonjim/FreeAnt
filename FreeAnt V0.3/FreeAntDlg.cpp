// FreeAntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "FreeAntDlg.h"
#include "ChatDlg.h"
#include "SendFileDlg.h"
#include "RecvFileDlg.h"
#include "SetupDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreeAntDlg dialog
extern CGroupTalk *g_pTalk;//���������������ǰ����������ȫ��
extern CFileTransfer *pTransfer;

CArray<CStructure::UserInfo2,CStructure::UserInfo2&> CFreeAntDlg::m_CarUserInfo2;//��Ϊ�����˾�̬�������������ʼ��

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
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, OnButtonSendfile)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_USERINFO, OnRclickListUserinfo)
	ON_BN_CLICKED(IDC_BUTTON_MAINMENU, OnButtonMainmenu)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(IDR_TASKBAR_MENUITEM_EXIT, OnTaskbarMenuitemExit)
	ON_COMMAND(IDR_USERINFOLIST_MENUITEM_SENDFILE, OnUserinfolistMenuitemSendfile)
	ON_COMMAND(IDR_USERINFOLIST_MENUITEM_SENDFOLDER, OnUserinfolistMenuitemSendfolder)
	ON_COMMAND(IDR_MAIN_MENUITEM_SENDFILE, OnMainMenuitemSendfile)
	ON_COMMAND(IDR_MAIN_MENUITEM_SENDFOLDER, OnMainMenuitemSendfolder)
	ON_COMMAND(IDR_USERINFOLIST_MENUITEM_SELECTALL, OnUserinfolistMenuitemSelectall)
	ON_COMMAND(IDR_USERINFOLIST_MENUITEM_INVERSE, OnUserinfolistMenuitemInverse)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_COMMAND(IDR_TASKBAR_MENUITEM_SETUP, OnTaskbarMenuitemSetup)
	ON_COMMAND(IDR_TASKBAR_MENUITEM_ABOUT, OnTaskbarMenuitemAbout)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GROUPTALK,WMGROUPTALK)
	ON_MESSAGE(WM_FILETRANSFER,WMFILETRANSFER)
	ON_MESSAGE(WM_TASKBAR,WMTASKBAR)
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
	InitSetup();//��ʼ������
	InitGroupTalk();
	InitFileTransfer();
	InitListCtrl();
	InitTaskbar();
	InitControlSite();
	m_pDlg = NULL;//��ʼ����ģ̬�Ի���ΪNULL

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

/************************************************************************/
/*CGroupTalk��ĳ�ʼ������Ϣ����                                        */
/************************************************************************/
void CFreeAntDlg::WMGROUPTALK(WPARAM wParam,LPARAM lParam)//CGroupTalk���͹�������Ϣ��Ӧ
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

void CFreeAntDlg::HandleGroupMsg(HWND hDlg, GT_HDR *pHeader)//����ʵ����
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

			//��ʾ����
			int ItemSize = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();
			CString TmpStr;
			TmpStr.Format("%d ��",ItemSize);
			SetDlgItemText(IDC_STATIC_PEOPLESIZE,TmpStr);
	
		}		
		break;
		
	case MT_LEAVE:		// �û��뿪
		{
			// ��ʾ���û�
			char szText[56];
			wsprintf(szText, " �û�����%s���뿪��", pHeader->szUser);
			
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

			//��ʾ����
			int ItemSize = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();
			CString TmpStr;
			TmpStr.Format("%d ��",ItemSize);
			SetDlgItemText(IDC_STATIC_PEOPLESIZE,TmpStr);
		}
		break;
		
 	case MT_MESG:		// �û����͹�����Ϣ
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

				//����������ʾ
				if (m_BalloonPrompt == 1)
				{
					nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO; 
					strcpy(nid.szInfo,_T("���µ���Ϣ��")); 
					strcpy(nid.szInfoTitle,_T("��ʾ"));
					nid.dwInfoFlags=NIIF_INFO;
					nid.uTimeout=5000; 
					Shell_NotifyIcon(NIM_MODIFY,&nid);//����������ʾ������ʾ
				}
				
 				((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_SHOW);

				//��������
				if (m_Mute == 0)
				{
					PlaySound(m_MsgTonePath,NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
				}
				
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

						//����������ʾ
						if (m_BalloonPrompt == 1)
						{
							nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO; 
							strcpy(nid.szInfo,_T("���µ���Ϣ��")); 
							strcpy(nid.szInfoTitle,_T("��ʾ"));
							nid.dwInfoFlags=NIIF_INFO;
							nid.uTimeout=5000; 
							Shell_NotifyIcon(NIM_MODIFY,&nid);//����������ʾ������ʾ
						}

						
						((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_SHOW);
					
						//��������
						if (m_Mute == 0)
						{
							PlaySound(m_MsgTonePath,NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
						}
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

void CFreeAntDlg::InitGroupTalk()//��ʼ��CGroupTalk
{
	g_pTalk = new CGroupTalk(m_hWnd, ::inet_addr("234.5.6.7"));
}

/************************************************************************/
/* ��ʼ���б�ؼ�����ʾ                                                 */
/************************************************************************/
void CFreeAntDlg::InitListCtrl()
{
	DWORD dwStyle = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES|
		LVS_EX_HEADERDRAGDROP|LVS_SHOWSELALWAYS;
    ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetExtendedStyle(dwStyle); //������չ���
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(0,"������",LVCFMT_LEFT,80);
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(1,"IP ��ַ",LVCFMT_LEFT,115);
}

/************************************************************************/
/* ���Ͱ�ť                                                             */
/************************************************************************/
void CFreeAntDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	//�������ļ�����ļ���Ϣר������
	m_Carfilestruct.RemoveAll();//ɾ��ԭ���е���Ϣ
	CStructure::FileStruct filestruct;
	for (int i=0;i<CSendFileDlg::m_Carfilestruct.GetSize();i++)
	{
		filestruct.Filelength = CSendFileDlg::m_Carfilestruct.ElementAt(i).Filelength;
		filestruct.FileName = CSendFileDlg::m_Carfilestruct.ElementAt(i).FileName;
		strcpy(filestruct.FilePath,CSendFileDlg::m_Carfilestruct.ElementAt(i).FilePath);
		filestruct.FileSize = CSendFileDlg::m_Carfilestruct.ElementAt(i).FileSize;
		filestruct.PathName = CSendFileDlg::m_Carfilestruct.ElementAt(i).PathName;
		m_Carfilestruct.Add(filestruct);
	}
	CSendFileDlg::m_Carfilestruct.RemoveAll();//ת��֮��ɾ�������ļ�����ļ���Ϣ

	int SendBufID = 0;//�����û�������ַ���0Ϊû�У�1Ϊ��
	GetDlgItemText(IDC_RICHEDIT_SEND,TmpSendBuf);
	if (TmpSendBuf != "")
	{
		SendBufID = 1;
	}
	strcpy(SendBuf,TmpSendBuf);
	ItemCheckCount = 0;
	ItemCount = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();//��ȡ�б������
	for (i=0;i<ItemCount;i++)
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
		//������Ϣ
		if (SendBufID == 1)
		{
			g_pTalk->SendText(SendBuf,strlen(SendBuf)+1);//������ķ�����Ϣ
			((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND))->SetWindowText("");
		}

		//�����ļ�
		if (m_Carfilestruct.GetSize() != 0)//�ж����ļ��ŷ�
		{	
			for (int i=0;i<ItemCount;i++)
			{
				char *UserIP = new char;
				strcpy(UserIP,m_CarUserInfo.ElementAt(i).IP);
				HANDLE handle = CreateThread(NULL,0,SendFileThread,(LPVOID)UserIP,0,NULL);//�����Ǵ�ָ�룬�����׵�ַ����ô����Ҫ�����Լ���һ���ڴ�
				CloseHandle(handle);
			}
		}
	
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
						//������Ϣ
						if (SendBufID == 1)
						{
							g_pTalk->SendText(SendBuf,strlen(SendBuf)+1,m_CarUserInfo.ElementAt(i).dwAddr);//�����û��ķ�����Ϣ
						}

						//�����ļ�
						if (m_Carfilestruct.GetSize() != 0)//�ж����ļ��ŷ�
						{
							char *UserIP = new char;
							strcpy(UserIP,ItemIP);
							HANDLE handle = CreateThread(NULL,0,SendFileThread,(LPVOID)UserIP,0,NULL);//�����Ǵ�ָ�룬�����׵�ַ����ô����Ҫ�����Լ���һ���ڴ�
							CloseHandle(handle);
						}
					}
				}
				((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND))->SetWindowText("");
			}
		}
	}
	
	//�ؼ�λ����ʾ
	MoveControlN();
}

/************************************************************************/
/*��ʾ��ť                                                              */
/************************************************************************/
void CFreeAntDlg::OnButtonMsgprompt()//��Ϣ��ʾ 
{
	// TODO: Add your control notification handler code here
	for (int i=0;i<m_CarUserInfo2.GetSize();i++)
	{
		m_CarUserInfo2.ElementAt(i).dlg->ShowWindow(SW_SHOW);
		m_CarUserInfo2.ElementAt(i).dlg->MoveWindow(i*20+250,i*10+300,295,310);//���ô������������λ��
	}
	((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_HIDE);
}

/************************************************************************/
/*�����ļ��Ի���ť                                                    */
/************************************************************************/
void CFreeAntDlg::OnButtonSendfile() 
{
	// TODO: Add your control notification handler code here
	CSendFileDlg dlg;
	dlg.DoModal();
}

/************************************************************************/
/*�����ļ��߳�                                                          */
/************************************************************************/
DWORD WINAPI CFreeAntDlg::SendFileThread(LPVOID lpParameter)//�����ļ��߳�
{
 	CFreeAntDlg *dlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();//������Ի�����׵�ַ

	CString UserIP = (char*)lpParameter;//����������ת��

	CStructure::FileStruct filestruct;
	CArray<CStructure::FileStruct,CStructure::FileStruct&> Carfilestruct;
	for (int i=0;i<dlg->m_Carfilestruct.GetSize();i++)
	{
		filestruct.Filelength = dlg->m_Carfilestruct.ElementAt(i).Filelength;
		filestruct.FileName = dlg->m_Carfilestruct.ElementAt(i).FileName;
		strcpy(filestruct.FilePath,dlg->m_Carfilestruct.ElementAt(i).FilePath);
		filestruct.FileSize = dlg->m_Carfilestruct.ElementAt(i).FileSize;
		filestruct.PathName = dlg->m_Carfilestruct.ElementAt(i).PathName;
		Carfilestruct.Add(filestruct);
	}

	SOCKET ConnectSocket=socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in Sockaddr;
	Sockaddr.sin_family=AF_INET;//��ʾ��INT��ͨ��
	Sockaddr.sin_addr.S_un.S_addr=inet_addr(UserIP);
	Sockaddr.sin_port=htons(6000);
 	if(connect(ConnectSocket,(SOCKADDR*)&Sockaddr,sizeof(SOCKADDR)) == SOCKET_ERROR)//�������ӷ�����
 	{
		dlg->MessageBox("��������ʧ��","����",MB_ICONSTOP);
		closesocket(ConnectSocket);
		return 0;
 	}

	int FileSize = Carfilestruct.GetSize();//�ļ�����
	char SendRequest[20];//��������
	recv(ConnectSocket,SendRequest,20,0);//���ܷ�������׼������
	if (send(ConnectSocket,(char*)&FileSize,sizeof(FileSize),0) == SOCKET_ERROR)//�����ļ�����
	{
		dlg->MessageBox("�����ļ���Ϣʧ��","����",MB_ICONSTOP);
		return 0;
	}
	CStructure::SockFileStruct sendfilestruct;//���ڷ����ļ��ṹ������ѭ������
	for (i=0;i<FileSize;i++)
	{
		sendfilestruct.Filelength = Carfilestruct.ElementAt(i).Filelength;
		strcpy(sendfilestruct.FileName,Carfilestruct.ElementAt(i).FileName);
		strcpy(sendfilestruct.FilePath,Carfilestruct.ElementAt(i).FilePath);
		strcpy(sendfilestruct.FileSize,Carfilestruct.ElementAt(i).FileSize);
		strcpy(sendfilestruct.PathName,Carfilestruct.ElementAt(i).PathName);
		recv(ConnectSocket,SendRequest,20,0);//���ܷ�������׼������
		if (send(ConnectSocket, (char*)&sendfilestruct, sizeof(CStructure::SockFileStruct),0) == SOCKET_ERROR)//�����ļ��ṹ��
		{
			dlg->MessageBox("�����ļ���Ϣʧ��","����",MB_ICONSTOP);
			return 0;
		}
	}
	//�����ļ�
	char sendBuf[8000];      //������������ļ���С���������������ļ�������
	int  Sendlen =0;
	int  Readlen =0;
	CFile64 File;
	for (i=0;i<FileSize;i++)
	{
		ULONGLONG SendSize=0;
		if(!File.Open(Carfilestruct.ElementAt(i).PathName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone))
		{
			dlg->MessageBox("���ļ�ʧ��!","����",MB_ICONSTOP);
			return i--;
		}
		recv(ConnectSocket,SendRequest,20,0);//���ܷ�������׼������
		while (Sendlen != SOCKET_ERROR)
		{
			Readlen = File.Read(sendBuf, 8000);
			Sendlen = send(ConnectSocket,sendBuf,Readlen,0);
			SendSize += Sendlen;
			if (SendSize == Carfilestruct.ElementAt(i).Filelength)
			{
				break;
			}
			if (Sendlen == SOCKET_ERROR)
			{
				AfxMessageBox("�Է�ȡ�������ļ���");
				break;
			}
		}
		File.Close();
		if (Sendlen == SOCKET_ERROR)
		{
			break;//������2��ѭ��
		}
		if (i == FileSize-1)
		{
			AfxMessageBox("�ļ�������ϣ�");
		}
	}
 	closesocket(ConnectSocket);
	return 0;
}

/************************************************************************/
/*CFileTransfer��ĳ�ʼ������Ϣ����֮������ʵ��                       */
/************************************************************************/
void CFreeAntDlg::InitFileTransfer()//��ʼ��CFileTransfer
{
	pTransfer = new CFileTransfer(m_hWnd);
}

void CFreeAntDlg::WMFILETRANSFER(WPARAM wParam,LPARAM lParam)//CFileTransfer����������Ϣ��Ӧ
{
	//��������
	if (m_Mute == 0)
	{
		PlaySound(m_FileTonePath,NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	}

 	CRecvFileDlg *pdlg;
 	pdlg = new CRecvFileDlg;
	CStructure::RecvFileDlgInfo *TmpTur = (CStructure::RecvFileDlgInfo *)lParam;
	pdlg->m_AcceptSocket = TmpTur->AcceptSocket;
	pdlg->m_Carfilestruct = TmpTur->Carfilestruct;
	pdlg->Create(IDD_RECVFILE_DIALOG,GetDesktopWindow());
	pdlg->ShowWindow(SW_SHOW);


}

/************************************************************************/
/*�����˵��Ĳ���                                                        */
/************************************************************************/
void CFreeAntDlg::OnRclickListUserinfo(NMHDR* pNMHDR, LRESULT* pResult) //�б�ؼ��Ҽ��˵�
{
	// TODO: Add your control notification handler code here
	CMenu menu;			//����˵�
	menu.LoadMenu(IDR_USERINFOLIST_MENU);//���븡���˵���Դ
	CMenu* pM=menu.GetSubMenu(0);//�˵��ĵ�һ����Ϊ�����˵�
	CPoint pt;
	GetCursorPos(&pt);//������λ��
	pM->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);//���������˵�
	HMENU hmenu=menu.Detach();   //��Դ����   //Ҫע����Դ���ͷ�
    menu.DestroyMenu(); 
	*pResult = 0;
}

void CFreeAntDlg::OnButtonMainmenu() //���Ҽ��˵�
{
	// TODO: Add your control notification handler code here
	CMenu menu;			//����˵�
	menu.LoadMenu(IDR_MAIN_MENU);//���븡���˵���Դ
	CMenu* pM=menu.GetSubMenu(0);//�˵��ĵ�һ����Ϊ�����˵�
	CRect rect;
	((CButton*)GetDlgItem(IDC_BUTTON_MAINMENU))->GetWindowRect(&rect);//��ȡ��ťλ��
	pM->TrackPopupMenu(TPM_LEFTALIGN,rect.left,rect.bottom,this,&rect);//���������˵�
	HMENU hmenu=menu.Detach();   //��Դ����   
    menu.DestroyMenu(); 
}

/************************************************************************/
/*�����Ҽ�;��������Ч��                                                 */
/************************************************************************/
LRESULT CFreeAntDlg::WMTASKBAR(WPARAM wParam,LPARAM lParam)//wParam���յ���ͼ���ID����lParam���յ���������Ϊ
{
	if(wParam!=IDR_MAINFRAME) 
	{
		return 1;  
	}
    switch(lParam)  
    {  
	case WM_RBUTTONUP:          //�Ҽ�����ʱ������ݲ˵�;   
        {  
            LPPOINT lpoint=new tagPOINT;  
            ::GetCursorPos(lpoint);         //�õ����λ��   
            CMenu menu;  
			menu.LoadMenu(IDR_TASKBAR_MENU);//���븡���˵���Դ
			CMenu* pM=menu.GetSubMenu(0);//�˵��ĵ�һ����Ϊ�����˵�
			SetForegroundWindow();//ע��˳��֮����Ҫ��������������ĺ�������ʹ�ڵ����Ҽ���ʱ���㲻���ͬʱ������ʹ�˵���ʧ����ʵҲ���ǽ��������
			pM->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);//���������˵�
			HMENU hmenu=menu.Detach();   //��Դ����   
			menu.DestroyMenu(); 
            delete lpoint;  
        }break;  
	case WM_LBUTTONUP:    //��������Ĵ���   
        {  
			if (this->ShowWindow(SW_SHOWNA) == 0)
			{
				this->ShowWindow(SW_SHOW);    //��ʾ������
				Sleep(150);//��ƭ�ַ�
				this->ShowWindow(SW_RESTORE);
				SetForegroundWindow();
			}
			else
			{
				this->ShowWindow(SW_MINIMIZE);
				Sleep(50);//��ƭ�ַ�
				this->ShowWindow(SW_HIDE);
			}
        }break;
    }  
    return 0;  
}

void CFreeAntDlg::InitTaskbar()//��ʼ��
{
    nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);  
    nid.hWnd=this->m_hWnd;  
    nid.uID=IDR_MAINFRAME;  
    nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;  
    nid.uCallbackMessage=WM_TASKBAR;//�Զ������Ϣ����,ע��:�������Ϣ���û��Զ�����Ϣ   
    nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  
    strcpy(nid.szTip,_T("Free Ant"));//��Ϣ��ʾ��Ϊ"�ƻ���������"     
    Shell_NotifyIcon(NIM_ADD,&nid);//�����������ͼ��   
}

void CFreeAntDlg::OnSysCommand(UINT nID, LPARAM lParam)//��д��������ť����
{
	// TODO: Add your message handler code here and/or call default
	if ((nID & 0xFFF0) == SC_CLOSE)      //�����رհ�ť   
    {  
        //OnClose();           //�����йر�   
        ShowWindow(SW_MINIMIZE);
		Sleep(50);//��ƭ�ַ�
		ShowWindow(SW_HIDE);
    }  
    else  
    {  
        CDialog::OnSysCommand(nID, lParam);  
    }  
}

BOOL CFreeAntDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)//�޸�EXC��//�������˳�����
	{
		ShowWindow(SW_MINIMIZE);
		Sleep(50);//��ƭ�ַ�
		ShowWindow(SW_HIDE);
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/************************************************************************/
/* ���Ͻǹرհ�ť�ľ�������������ͷ���Դ��                             */
/************************************************************************/
void CFreeAntDlg::OnClose() //�ڷ�ģ̬�Ի����У����û���ã�ֻ�����ش������ã�OnOK()Ҳһ��
{
	// TODO: Add your message handler code here and/or call default
	//CDialog::OnClose();
}

void CFreeAntDlg::OnDestroy() //OnClose()->OnDestroy();������ô�����������һ������ã�OnClose()ֻ�е����Ͻǵ�X�Ż����
{
	CDialog::OnDestroy();
//	CDialog::PostNcDestroy(); //ɾ��ָ��
//	delete this;//��Ϊ���Ի�������Ϊ��ģ̬�Ի�������Ҫ������ͷ���Դ;==��̬��̬�������⣬��һ�汾�Ľ�
	// TODO: Add your message handler code here
	
}

void CFreeAntDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_MINIMIZE);
	delete g_pTalk;//�û��رճ���
	//delete pTransfer;
	Shell_NotifyIcon(NIM_DELETE,&nid);//��������ɾ��ͼ��
	DestroyWindow();//��Ϊ���Ի�������Ϊ��ģ̬�Ի�������Ҫ������ͷ���Դ
}

/************************************************************************/
/* �ؼ�����λ�ã���ƭ�ַ�                                               */
/************************************************************************/
void CFreeAntDlg::MoveControlO()//��λ��
{
	CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND);
	pEdit->MoveWindow(EditRect.left,EditRect.top,EditRect.Width(),EditRect.Height());
	((CButton*)GetDlgItem(IDC_BUTTON_SENDFILE))->ShowWindow(SW_SHOW);
	
}

void CFreeAntDlg::MoveControlN()//��λ��
{
	CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND);
	pEdit->MoveWindow(EditRect.left,EditRect.top-32,EditRect.Width(),EditRect.Height()+32);
	((CButton*)GetDlgItem(IDC_BUTTON_SENDFILE))->ShowWindow(SW_HIDE);
	
}

void CFreeAntDlg::InitControlSite()//��ʼ���ؼ�λ��
{
	CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND);
	pEdit->GetWindowRect(&EditRect);
	ScreenToClient(&EditRect);//ת����Ļ����
	pEdit->MoveWindow(EditRect.left,EditRect.top-32,EditRect.Width(),EditRect.Height()+32);
	((CButton*)GetDlgItem(IDC_BUTTON_SENDFILE))->ShowWindow(SW_HIDE);
}

/************************************************************************/
/*ˢ�°�ť                                                              */
/************************************************************************/
void CFreeAntDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->DeleteAllItems();
	m_CarUserInfo.RemoveAll();
	delete g_pTalk;
	g_pTalk = new CGroupTalk(m_hWnd, ::inet_addr("234.5.6.7"));
}

/************************************************************************/
/* ��ʼ���ļ���,ini����,ini��ȡ,����ȫ�����ñ���                        */
/************************************************************************/
void CFreeAntDlg::InitSetup()
{
	//�õ��������ļ�;��
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//�õ�����ģ�����ƣ�ȫ·��
	PathRemoveFileSpec(exeFullPath);//ת��
	m_exePath = exeFullPath;
	m_IniPath = m_exePath + "\\Setup\\Setup.ini";

	if (::GetFileAttributes(m_IniPath) == INVALID_FILE_ATTRIBUTES)//�ж��ļ�ʱ�����
	{
		if (!::PathIsDirectory(""+m_exePath+"\\Files"))
		{
			::CreateDirectory(""+m_exePath+"\\Files",NULL);
		}
		if (!::PathIsDirectory(""+m_exePath+"\\Log"))
		{
			::CreateDirectory(""+m_exePath+"\\Log",NULL);
		}
		if (!::PathIsDirectory(""+m_exePath+"\\Setup"))
		{
			::CreateDirectory(""+m_exePath+"\\Setup",NULL);
		}
		::WritePrivateProfileString("Setup","RecvFilePath",""+m_exePath+"\\File",m_IniPath);
		::WritePrivateProfileString("Setup","Mute","1",m_IniPath);
		::WritePrivateProfileString("Setup","FileTonePath","",m_IniPath);
		::WritePrivateProfileString("Setup","MsgTonePath","",m_IniPath);
		::WritePrivateProfileString("Setup","InitShowDlg","1",m_IniPath);
		::WritePrivateProfileString("Setup","BalloonPrompt","1",m_IniPath);
	}
	char RecvFilePath[1024];
	char Mute[5];
	char FileTonePath[1024];
	char MsgTonePath[1024];
	char InitShowDlg[5];
	char BalloonPrompt[5];
	::GetPrivateProfileString("Setup","RecvFilePath",""+m_exePath+"\\File",RecvFilePath,1024,m_IniPath);//��ȡini
	::GetPrivateProfileString("Setup","Mute","0",Mute,5,m_IniPath);
	::GetPrivateProfileString("Setup","FileTonePath","",FileTonePath,1024,m_IniPath);
	::GetPrivateProfileString("Setup","MsgTonePath","",MsgTonePath,1024,m_IniPath);
	::GetPrivateProfileString("Setup","InitShowDlg","1",InitShowDlg,5,m_IniPath);
	::GetPrivateProfileString("Setup","BalloonPrompt","1",BalloonPrompt,5,m_IniPath);
	m_RecvFilePath = RecvFilePath;
	m_Mute = atoi(Mute);//�ַ�ת��Ϊint
	m_FileTonePath = FileTonePath;
	m_MsgTonePath = MsgTonePath;
	m_InitShowDlg = atoi(InitShowDlg);
	m_BalloonPrompt = atoi(BalloonPrompt);
}

/************************************************************************/
/*�����Ҽ��˵��˵�����ʵ��												*/
/*Taskbar		== IDR_TASLBAR_MENU										*/
/*Userinfolist	== IDR_USERINFOLIST_MENU								*/
/*Main			== IDR_MAIN_MENU										*/
/************************************************************************/
void CFreeAntDlg::OnTaskbarMenuitemExit() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_MINIMIZE);//Ч��
	OnButtonExit();//��Ϊ���Ի�������Ϊ��ģ̬�Ի�������Ҫ������ͷ���Դ
}

void CFreeAntDlg::OnUserinfolistMenuitemSendfile() 
{
	// TODO: Add your command handler code here
	CSendFileDlg dlg;
	dlg.DoModal();
}

void CFreeAntDlg::OnUserinfolistMenuitemSendfolder() 
{
	// TODO: Add your command handler code here
}

void CFreeAntDlg::OnMainMenuitemSendfile() 
{
	// TODO: Add your command handler code here
	CSendFileDlg dlg;
	dlg.DoModal();
}

void CFreeAntDlg::OnMainMenuitemSendfolder() 
{
	// TODO: Add your command handler code here
}

void CFreeAntDlg::OnUserinfolistMenuitemSelectall() 
{
	// TODO: Add your command handler code here
	for (int i=0;i<((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();i++)
	{
		((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetCheck(i);
	}
}

void CFreeAntDlg::OnUserinfolistMenuitemInverse() 
{
	// TODO: Add your command handler code here
	for (int i=0;i<((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();i++)
	{
		if (((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetCheck(i) != 0)
		{
			((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetCheck(i,FALSE);
		}
		else if (((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetCheck(i) == 0)
		{
			((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetCheck(i);
		}
	}
}

void CFreeAntDlg::OnTaskbarMenuitemSetup() 
{
	// TODO: Add your command handler code here
	if (m_pDlg == NULL)//ֻ����һ��
	{
		m_pDlg = new CSetupDlg;
		m_pDlg->Create(IDD_SETUP_DIALOG,GetDesktopWindow());
		m_pDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pDlg->ShowWindow(SW_RESTORE);
		m_pDlg->SetForegroundWindow();//����Ϊ�
	}
}

void CFreeAntDlg::OnTaskbarMenuitemAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg *pDlg = new CAboutDlg;
	pDlg->Create(IDD_ABOUT_DIALOG,GetDesktopWindow());
	pDlg->ShowWindow(SW_SHOW);
}
