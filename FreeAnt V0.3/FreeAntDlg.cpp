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
extern CGroupTalk *g_pTalk;//声明有这个变量，前提是设置了全局
extern CFileTransfer *pTransfer;

CArray<CStructure::UserInfo2,CStructure::UserInfo2&> CFreeAntDlg::m_CarUserInfo2;//因为设置了静态，所以在这里初始化

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
	InitSetup();//初始化设置
	InitGroupTalk();
	InitFileTransfer();
	InitListCtrl();
	InitTaskbar();
	InitControlSite();
	m_pDlg = NULL;//初始化非模态对话框为NULL

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
/*CGroupTalk类的初始化及消息处理                                        */
/************************************************************************/
void CFreeAntDlg::WMGROUPTALK(WPARAM wParam,LPARAM lParam)//CGroupTalk发送过来的消息响应
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

void CFreeAntDlg::HandleGroupMsg(HWND hDlg, GT_HDR *pHeader)//函数实现体
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
			int nRow = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertItem(0,UserInfo1.name);
		 	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetItemText(nRow,1,UserInfo1.IP);

			//通知该用户的聊天窗口已经上线，前提是已经创建的聊天窗口
			for (int i=0;i<m_CarUserInfo2.GetSize();i++)
			{
				if (m_CarUserInfo2.ElementAt(i).dwAddr == pHeader->dwAddr)
				{
					m_CarUserInfo2.ElementAt(i).dlg->SetWindowText(m_CarUserInfo2.ElementAt(i).dlg->name);
				}
			}

			//显示人数
			int ItemSize = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();
			CString TmpStr;
			TmpStr.Format("%d 人",ItemSize);
			SetDlgItemText(IDC_STATIC_PEOPLESIZE,TmpStr);
	
		}		
		break;
		
	case MT_LEAVE:		// 用户离开
		{
			// 显示给用户
			char szText[56];
			wsprintf(szText, " 用户：《%s》离开！", pHeader->szUser);
			
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

			//通知该用户的聊天窗口已经下线
			for (i=0;i<m_CarUserInfo2.GetSize();i++)
			{
				if (m_CarUserInfo2.ElementAt(i).dwAddr == pHeader->dwAddr)
				{
					m_CarUserInfo2.ElementAt(i).dlg->SetWindowText("该用户已经下线！");
				}
			}

			//显示人数
			int ItemSize = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();
			CString TmpStr;
			TmpStr.Format("%d 人",ItemSize);
			SetDlgItemText(IDC_STATIC_PEOPLESIZE,TmpStr);
		}
		break;
		
 	case MT_MESG:		// 用户发送过来消息
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

				//托盘气球提示
				if (m_BalloonPrompt == 1)
				{
					nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO; 
					strcpy(nid.szInfo,_T("有新的消息！")); 
					strcpy(nid.szInfoTitle,_T("提示"));
					nid.dwInfoFlags=NIIF_INFO;
					nid.uTimeout=5000; 
					Shell_NotifyIcon(NIM_MODIFY,&nid);//在托盘区显示气球提示
				}
				
 				((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_SHOW);

				//播放声音
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

						//托盘气球提示
						if (m_BalloonPrompt == 1)
						{
							nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO; 
							strcpy(nid.szInfo,_T("有新的消息！")); 
							strcpy(nid.szInfoTitle,_T("提示"));
							nid.dwInfoFlags=NIIF_INFO;
							nid.uTimeout=5000; 
							Shell_NotifyIcon(NIM_MODIFY,&nid);//在托盘区显示气球提示
						}

						
						((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_SHOW);
					
						//播放声音
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
					wsprintf(szText, "【%s】说：", pHeader->szUser);
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

void CFreeAntDlg::InitGroupTalk()//初始化CGroupTalk
{
	g_pTalk = new CGroupTalk(m_hWnd, ::inet_addr("234.5.6.7"));
}

/************************************************************************/
/* 初始化列表控件的显示                                                 */
/************************************************************************/
void CFreeAntDlg::InitListCtrl()
{
	DWORD dwStyle = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES|
		LVS_EX_HEADERDRAGDROP|LVS_SHOWSELALWAYS;
    ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->SetExtendedStyle(dwStyle); //设置扩展风格
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(0,"主机名",LVCFMT_LEFT,80);
	((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->InsertColumn(1,"IP 地址",LVCFMT_LEFT,115);
}

/************************************************************************/
/* 发送按钮                                                             */
/************************************************************************/
void CFreeAntDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	//将发送文件筐的文件信息专过来主
	m_Carfilestruct.RemoveAll();//删除原来有的信息
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
	CSendFileDlg::m_Carfilestruct.RemoveAll();//转换之后删除发送文件筐的文件信息

	int SendBufID = 0;//检测有没有输入字符；0为没有；1为有
	GetDlgItemText(IDC_RICHEDIT_SEND,TmpSendBuf);
	if (TmpSendBuf != "")
	{
		SendBufID = 1;
	}
	strcpy(SendBuf,TmpSendBuf);
	ItemCheckCount = 0;
	ItemCount = ((CListCtrl*)GetDlgItem(IDC_LIST_USERINFO))->GetItemCount();//获取列表的数量
	for (i=0;i<ItemCount;i++)
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
		//发送信息
		if (SendBufID == 1)
		{
			g_pTalk->SendText(SendBuf,strlen(SendBuf)+1);//面向组的发送信息
			((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND))->SetWindowText("");
		}

		//发送文件
		if (m_Carfilestruct.GetSize() != 0)//判断有文件才发
		{	
			for (int i=0;i<ItemCount;i++)
			{
				char *UserIP = new char;
				strcpy(UserIP,m_CarUserInfo.ElementAt(i).IP);
				HANDLE handle = CreateThread(NULL,0,SendFileThread,(LPVOID)UserIP,0,NULL);//参数是传指针，就是首地址，那么必须要有它自己的一块内存
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
						//发送信息
						if (SendBufID == 1)
						{
							g_pTalk->SendText(SendBuf,strlen(SendBuf)+1,m_CarUserInfo.ElementAt(i).dwAddr);//面向单用户的发送信息
						}

						//发送文件
						if (m_Carfilestruct.GetSize() != 0)//判断有文件才发
						{
							char *UserIP = new char;
							strcpy(UserIP,ItemIP);
							HANDLE handle = CreateThread(NULL,0,SendFileThread,(LPVOID)UserIP,0,NULL);//参数是传指针，就是首地址，那么必须要有它自己的一块内存
							CloseHandle(handle);
						}
					}
				}
				((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND))->SetWindowText("");
			}
		}
	}
	
	//控件位置显示
	MoveControlN();
}

/************************************************************************/
/*提示按钮                                                              */
/************************************************************************/
void CFreeAntDlg::OnButtonMsgprompt()//信息提示 
{
	// TODO: Add your control notification handler code here
	for (int i=0;i<m_CarUserInfo2.GetSize();i++)
	{
		m_CarUserInfo2.ElementAt(i).dlg->ShowWindow(SW_SHOW);
		m_CarUserInfo2.ElementAt(i).dlg->MoveWindow(i*20+250,i*10+300,295,310);//设置窗口随机弹出的位置
	}
	((CButton*)GetDlgItem(IDC_BUTTON_MSGPROMPT))->ShowWindow(SW_HIDE);
}

/************************************************************************/
/*发送文件对话框按钮                                                    */
/************************************************************************/
void CFreeAntDlg::OnButtonSendfile() 
{
	// TODO: Add your control notification handler code here
	CSendFileDlg dlg;
	dlg.DoModal();
}

/************************************************************************/
/*发送文件线程                                                          */
/************************************************************************/
DWORD WINAPI CFreeAntDlg::SendFileThread(LPVOID lpParameter)//发送文件线程
{
 	CFreeAntDlg *dlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();//获得主对话框的首地址

	CString UserIP = (char*)lpParameter;//传进来参数转换

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
	Sockaddr.sin_family=AF_INET;//表示在INT上通信
	Sockaddr.sin_addr.S_un.S_addr=inet_addr(UserIP);
	Sockaddr.sin_port=htons(6000);
 	if(connect(ConnectSocket,(SOCKADDR*)&Sockaddr,sizeof(SOCKADDR)) == SOCKET_ERROR)//主动连接服务器
 	{
		dlg->MessageBox("建立连接失败","错误",MB_ICONSTOP);
		closesocket(ConnectSocket);
		return 0;
 	}

	int FileSize = Carfilestruct.GetSize();//文件个数
	char SendRequest[20];//发送请求
	recv(ConnectSocket,SendRequest,20,0);//接受发送请求，准备发送
	if (send(ConnectSocket,(char*)&FileSize,sizeof(FileSize),0) == SOCKET_ERROR)//发送文件个数
	{
		dlg->MessageBox("发送文件信息失败","错误",MB_ICONSTOP);
		return 0;
	}
	CStructure::SockFileStruct sendfilestruct;//用于发送文件结构；利用循环发送
	for (i=0;i<FileSize;i++)
	{
		sendfilestruct.Filelength = Carfilestruct.ElementAt(i).Filelength;
		strcpy(sendfilestruct.FileName,Carfilestruct.ElementAt(i).FileName);
		strcpy(sendfilestruct.FilePath,Carfilestruct.ElementAt(i).FilePath);
		strcpy(sendfilestruct.FileSize,Carfilestruct.ElementAt(i).FileSize);
		strcpy(sendfilestruct.PathName,Carfilestruct.ElementAt(i).PathName);
		recv(ConnectSocket,SendRequest,20,0);//接受发送请求，准备发送
		if (send(ConnectSocket, (char*)&sendfilestruct, sizeof(CStructure::SockFileStruct),0) == SOCKET_ERROR)//发送文件结构体
		{
			dlg->MessageBox("发送文件信息失败","错误",MB_ICONSTOP);
			return 0;
		}
	}
	//发送文件
	char sendBuf[8000];      //首先用来存放文件大小，后面用作发送文件缓冲区
	int  Sendlen =0;
	int  Readlen =0;
	CFile64 File;
	for (i=0;i<FileSize;i++)
	{
		ULONGLONG SendSize=0;
		if(!File.Open(Carfilestruct.ElementAt(i).PathName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone))
		{
			dlg->MessageBox("打开文件失败!","错误",MB_ICONSTOP);
			return i--;
		}
		recv(ConnectSocket,SendRequest,20,0);//接受发送请求，准备发送
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
				AfxMessageBox("对方取消接收文件！");
				break;
			}
		}
		File.Close();
		if (Sendlen == SOCKET_ERROR)
		{
			break;//跳出第2个循环
		}
		if (i == FileSize-1)
		{
			AfxMessageBox("文件发送完毕！");
		}
	}
 	closesocket(ConnectSocket);
	return 0;
}

/************************************************************************/
/*CFileTransfer类的初始化及消息过来之后具体的实现                       */
/************************************************************************/
void CFreeAntDlg::InitFileTransfer()//初始化CFileTransfer
{
	pTransfer = new CFileTransfer(m_hWnd);
}

void CFreeAntDlg::WMFILETRANSFER(WPARAM wParam,LPARAM lParam)//CFileTransfer发过来的消息响应
{
	//播放声音
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
/*弹出菜单的操作                                                        */
/************************************************************************/
void CFreeAntDlg::OnRclickListUserinfo(NMHDR* pNMHDR, LRESULT* pResult) //列表控件右键菜单
{
	// TODO: Add your control notification handler code here
	CMenu menu;			//定义菜单
	menu.LoadMenu(IDR_USERINFOLIST_MENU);//载入浮动菜单资源
	CMenu* pM=menu.GetSubMenu(0);//菜单的第一项作为浮动菜单
	CPoint pt;
	GetCursorPos(&pt);//获得鼠标位置
	pM->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);//弹出浮动菜单
	HMENU hmenu=menu.Detach();   //资源回收   //要注意资源的释放
    menu.DestroyMenu(); 
	*pResult = 0;
}

void CFreeAntDlg::OnButtonMainmenu() //主右键菜单
{
	// TODO: Add your control notification handler code here
	CMenu menu;			//定义菜单
	menu.LoadMenu(IDR_MAIN_MENU);//载入浮动菜单资源
	CMenu* pM=menu.GetSubMenu(0);//菜单的第一项作为浮动菜单
	CRect rect;
	((CButton*)GetDlgItem(IDC_BUTTON_MAINMENU))->GetWindowRect(&rect);//获取按钮位置
	pM->TrackPopupMenu(TPM_LEFTALIGN,rect.left,rect.bottom,this,&rect);//弹出浮动菜单
	HMENU hmenu=menu.Detach();   //资源回收   
    menu.DestroyMenu(); 
}

/************************************************************************/
/*托盘右键;功能美化效果                                                 */
/************************************************************************/
LRESULT CFreeAntDlg::WMTASKBAR(WPARAM wParam,LPARAM lParam)//wParam接收的是图标的ID，而lParam接收的是鼠标的行为
{
	if(wParam!=IDR_MAINFRAME) 
	{
		return 1;  
	}
    switch(lParam)  
    {  
	case WM_RBUTTONUP:          //右键起来时弹出快捷菜单;   
        {  
            LPPOINT lpoint=new tagPOINT;  
            ::GetCursorPos(lpoint);         //得到鼠标位置   
            CMenu menu;  
			menu.LoadMenu(IDR_TASKBAR_MENU);//载入浮动菜单资源
			CMenu* pM=menu.GetSubMenu(0);//菜单的第一项作为浮动菜单
			SetForegroundWindow();//注意顺序；之所以要在这里加这个焦点的函数，是使在弹出右键的时候，你不点的同时，可以使菜单消失，其实也就是焦点的问题
			pM->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);//弹出浮动菜单
			HMENU hmenu=menu.Detach();   //资源回收   
			menu.DestroyMenu(); 
            delete lpoint;  
        }break;  
	case WM_LBUTTONUP:    //单击左键的处理   
        {  
			if (this->ShowWindow(SW_SHOWNA) == 0)
			{
				this->ShowWindow(SW_SHOW);    //显示主窗口
				Sleep(150);//欺骗手法
				this->ShowWindow(SW_RESTORE);
				SetForegroundWindow();
			}
			else
			{
				this->ShowWindow(SW_MINIMIZE);
				Sleep(50);//欺骗手法
				this->ShowWindow(SW_HIDE);
			}
        }break;
    }  
    return 0;  
}

void CFreeAntDlg::InitTaskbar()//初始化
{
    nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);  
    nid.hWnd=this->m_hWnd;  
    nid.uID=IDR_MAINFRAME;  
    nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;  
    nid.uCallbackMessage=WM_TASKBAR;//自定义的消息名称,注意:这里的消息是用户自定义消息   
    nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  
    strcpy(nid.szTip,_T("Free Ant"));//信息提示条为"计划任务提醒"     
    Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标   
}

void CFreeAntDlg::OnSysCommand(UINT nID, LPARAM lParam)//重写标题栏按钮功能
{
	// TODO: Add your message handler code here and/or call default
	if ((nID & 0xFFF0) == SC_CLOSE)      //触发关闭按钮   
    {  
        //OnClose();           //不进行关闭   
        ShowWindow(SW_MINIMIZE);
		Sleep(50);//欺骗手法
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
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)//修改EXC键//屏蔽其退出功能
	{
		ShowWindow(SW_MINIMIZE);
		Sleep(50);//欺骗手法
		ShowWindow(SW_HIDE);
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/************************************************************************/
/* 右上角关闭按钮的具体操作，比如释放资源等                             */
/************************************************************************/
void CFreeAntDlg::OnClose() //在非模态对话框中，这个没有用，只做隐藏窗口作用，OnOK()也一样
{
	// TODO: Add your message handler code here and/or call default
	//CDialog::OnClose();
}

void CFreeAntDlg::OnDestroy() //OnClose()->OnDestroy();不管怎么样，这个函数一定会调用；OnClose()只有点右上角的X才会调用
{
	CDialog::OnDestroy();
//	CDialog::PostNcDestroy(); //删除指针
//	delete this;//因为主对话框设置为非模态对话框，所以要用这个释放资源;==静态动态数组问题，下一版本改进
	// TODO: Add your message handler code here
	
}

void CFreeAntDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_MINIMIZE);
	delete g_pTalk;//用户关闭程序
	//delete pTransfer;
	Shell_NotifyIcon(NIM_DELETE,&nid);//在托盘区删除图标
	DestroyWindow();//因为主对话框设置为非模态对话框，所以要用这个释放资源
}

/************************************************************************/
/* 控件调整位置，欺骗手法                                               */
/************************************************************************/
void CFreeAntDlg::MoveControlO()//老位置
{
	CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND);
	pEdit->MoveWindow(EditRect.left,EditRect.top,EditRect.Width(),EditRect.Height());
	((CButton*)GetDlgItem(IDC_BUTTON_SENDFILE))->ShowWindow(SW_SHOW);
	
}

void CFreeAntDlg::MoveControlN()//新位置
{
	CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND);
	pEdit->MoveWindow(EditRect.left,EditRect.top-32,EditRect.Width(),EditRect.Height()+32);
	((CButton*)GetDlgItem(IDC_BUTTON_SENDFILE))->ShowWindow(SW_HIDE);
	
}

void CFreeAntDlg::InitControlSite()//初始化控件位置
{
	CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_SEND);
	pEdit->GetWindowRect(&EditRect);
	ScreenToClient(&EditRect);//转换屏幕坐标
	pEdit->MoveWindow(EditRect.left,EditRect.top-32,EditRect.Width(),EditRect.Height()+32);
	((CButton*)GetDlgItem(IDC_BUTTON_SENDFILE))->ShowWindow(SW_HIDE);
}

/************************************************************************/
/*刷新按钮                                                              */
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
/* 初始化文件夹,ini创建,ini读取,设置全局设置变量                        */
/************************************************************************/
void CFreeAntDlg::InitSetup()
{
	//得到本程序文件途径
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	PathRemoveFileSpec(exeFullPath);//转换
	m_exePath = exeFullPath;
	m_IniPath = m_exePath + "\\Setup\\Setup.ini";

	if (::GetFileAttributes(m_IniPath) == INVALID_FILE_ATTRIBUTES)//判断文件时候存在
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
	::GetPrivateProfileString("Setup","RecvFilePath",""+m_exePath+"\\File",RecvFilePath,1024,m_IniPath);//读取ini
	::GetPrivateProfileString("Setup","Mute","0",Mute,5,m_IniPath);
	::GetPrivateProfileString("Setup","FileTonePath","",FileTonePath,1024,m_IniPath);
	::GetPrivateProfileString("Setup","MsgTonePath","",MsgTonePath,1024,m_IniPath);
	::GetPrivateProfileString("Setup","InitShowDlg","1",InitShowDlg,5,m_IniPath);
	::GetPrivateProfileString("Setup","BalloonPrompt","1",BalloonPrompt,5,m_IniPath);
	m_RecvFilePath = RecvFilePath;
	m_Mute = atoi(Mute);//字符转换为int
	m_FileTonePath = FileTonePath;
	m_MsgTonePath = MsgTonePath;
	m_InitShowDlg = atoi(InitShowDlg);
	m_BalloonPrompt = atoi(BalloonPrompt);
}

/************************************************************************/
/*托盘右键菜单菜单功能实现												*/
/*Taskbar		== IDR_TASLBAR_MENU										*/
/*Userinfolist	== IDR_USERINFOLIST_MENU								*/
/*Main			== IDR_MAIN_MENU										*/
/************************************************************************/
void CFreeAntDlg::OnTaskbarMenuitemExit() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_MINIMIZE);//效果
	OnButtonExit();//因为主对话框设置为非模态对话框，所以要用这个释放资源
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
	if (m_pDlg == NULL)//只创建一次
	{
		m_pDlg = new CSetupDlg;
		m_pDlg->Create(IDD_SETUP_DIALOG,GetDesktopWindow());
		m_pDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pDlg->ShowWindow(SW_RESTORE);
		m_pDlg->SetForegroundWindow();//设置为活动
	}
}

void CFreeAntDlg::OnTaskbarMenuitemAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg *pDlg = new CAboutDlg;
	pDlg->Create(IDD_ABOUT_DIALOG,GetDesktopWindow());
	pDlg->ShowWindow(SW_SHOW);
}
