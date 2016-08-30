// RecvFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "RecvFileDlg.h"
#include "FreeAntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecvFileDlg dialog

CRecvFileDlg::CRecvFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecvFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecvFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CRecvFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecvFileDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecvFileDlg, CDialog)
	//{{AFX_MSG_MAP(CRecvFileDlg)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS, OnButtonSaveas)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVER, OnButtonReceiver)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_OPENFILEDIR, OnButtonOpenFileDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecvFileDlg message handlers

BOOL CRecvFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitListCtrl();//初始化列表控件
	ButtonRtID = 0;//初始化按钮ID
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecvFileDlg::InitListCtrl()
{
	DWORD dwStyle = ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP;
    ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetExtendedStyle(dwStyle); //设置扩展风格
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(0,"文件名",LVCFMT_LEFT,130);
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(1,"大小",LVCFMT_LEFT,85);
  	for (int i=0;i<m_Carfilestruct->GetSize();i++)
  	{
  		int nRow = ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertItem(0,m_Carfilestruct->ElementAt(i).FileName);
  		((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetItemText(nRow,1,m_Carfilestruct->ElementAt(i).FileSize);
	}
}

void CRecvFileDlg::OnButtonSaveas() 
{
	// TODO: Add your control notification handler code here
	ButtonRtID = 2;
	((CButton*)GetDlgItem(IDC_BUTTON_RECEIVER))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_SAVEAS))->EnableWindow(FALSE);
	m_RecvFileThreadHandle = CreateThread(NULL,0,RecvFileThread,this,0,NULL);
}

void CRecvFileDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	DWORD dwExitCode = 0;
	GetExitCodeThread(m_RecvFileThreadHandle, &dwExitCode);
	if (STILL_ACTIVE == dwExitCode)
	{
		if (::MessageBox(m_hWnd,"正在接收文件,确定要退出吗？","提示",MB_YESNO) == IDYES)
		{
			ButtonRtID = 3;
			CloseHandle(m_RecvFileThreadHandle);
			DestroyWindow();
			CDialog::PostNcDestroy(); //删除指针
			delete this;
		}
	}
	else
	{
		closesocket(m_AcceptSocket);//因为关闭了套接字，所以接收线程也会停止
		CloseHandle(m_RecvFileThreadHandle);
		DestroyWindow();
		CDialog::PostNcDestroy(); //删除指针
		delete this;
	}

}

void CRecvFileDlg::OnButtonReceiver() 
{
	// TODO: Add your control notification handler code here
	ButtonRtID = 1;
}

void CRecvFileDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//释放资源
	DWORD dwExitCode = 0;
	GetExitCodeThread(m_RecvFileThreadHandle, &dwExitCode);
	if (STILL_ACTIVE == dwExitCode)
	{
		if (::MessageBox(m_hWnd,"正在接收文件,确定要退出吗？","提示",MB_YESNO) == IDYES)
		{
			ButtonRtID = 3;
			CloseHandle(m_RecvFileThreadHandle);
			DestroyWindow();
			CDialog::PostNcDestroy(); //删除指针
			delete this;
		}
	}
	else
	{
		closesocket(m_AcceptSocket);
		CloseHandle(m_RecvFileThreadHandle);
		DestroyWindow();
		CDialog::PostNcDestroy(); //删除指针
		delete this;
	}

}

DWORD WINAPI CRecvFileDlg::RecvFileThread(LPVOID lpParameter)
{
	CRecvFileDlg *pDlg = (CRecvFileDlg*) lpParameter;

	CString FileName=pDlg->m_Carfilestruct->ElementAt(0).FileName;//得到文件名
 	CFileDialog FileDlg(FALSE,NULL,FileName,OFN_EXTENSIONDIFFERENT|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST| 
 	         OFN_HIDEREADONLY,"All Files(*.*)|*.*||", pDlg);//最后一个参数是指定父窗口的指针，这里添当前的；
 	//保存文件夹的风格
	int structsize=0; 
	DWORD dwVersion,dwWindowsMajorVersion,dwWindowsMinorVersion; 
	//检测目前的操作系统
	dwVersion = GetVersion(); 
	dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion))); 
	dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion))); 
	// 如果运行的操作系统是Windows NT/2000 
	if (dwVersion < 0x80000000)  
	{
		structsize =88;//显示新的文件对话框 
	}
	else 
	{
		//运行的操作系统Windows 95/98  
		structsize =76;//显示老的文件对话框 
	}
	FileDlg.m_ofn.lStructSize=structsize; 
	
	CString PathName;
	char FilePath[200];
	int FileSize = pDlg->m_Carfilestruct->GetSize();
	int recvRt = 1;
	int recvEndID = 0;//接收完毕标记
	char recvBut[8000];

	//进度条设置;欺骗视觉的技巧
	CProgressCtrl *pPro1 = (CProgressCtrl*)(pDlg->GetDlgItem(IDC_PROGRESS1));//单个进度
	CProgressCtrl *pPro2 = (CProgressCtrl*)(pDlg->GetDlgItem(IDC_PROGRESS2));//总进度
	ULONGLONG Pro1Range = 0,Pro2Range = 0;//总值
	ULONGLONG Pro1Pos = 0,Pro2Pos = 0;//刻度
	for (int i=0;i<FileSize;i++)
	{
			Pro2Range += pDlg->m_Carfilestruct->ElementAt(i).Filelength;//总进度值
	}
	pPro2->SetRange32(0,Pro2Range/(1024*FileSize));

	while (1)
	{
		if (pDlg->ButtonRtID == 2)//按下另存为按钮
		{
			pDlg->ButtonRtID = 0;//设置成初始化
			if (FileDlg.DoModal() == IDOK)
			{
				PathName = FileDlg.GetPathName();
				//转换输出的途径,比如c:\a\b.txt,转换之后为c:\a
				strcpy(FilePath,PathName);
 	  			PathRemoveFileSpec(FilePath);
				for (int i=0;i<FileSize;i++)
				{
					//初始化进度条
					Pro1Range = pDlg->m_Carfilestruct->ElementAt(i).Filelength;//总进度值
					pPro1->SetRange32(0,Pro1Range/1024);

					PathName = FilePath;
					PathName += "\\";//转换保存地址；因为这里运用了循环接收文件；所以循环更改文件名
 	 				PathName +=pDlg->m_Carfilestruct->ElementAt(i).FileName;
					pDlg->m_PathName = PathName;//全局为后面打开做准备
					CFile64 File(PathName, CFile64::modeCreate | CFile64::modeWrite);
					ULONGLONG recvSize = 0;
					send(pDlg->m_AcceptSocket,"RecvRequest",sizeof("RecvRequest"),0);//发送recv通知；使发送和接收保持一致；
					while (recvRt != SOCKET_ERROR)
					{
						recvRt = recv(pDlg->m_AcceptSocket,recvBut,8000,0);
						if (recvRt == SOCKET_ERROR)
						{
							::MessageBox(pDlg->m_hWnd,"对方停止发送！","错误",MB_OK);
							break;
						}
						if (pDlg->ButtonRtID == 3)//按了退出键
						{
							pDlg->ButtonRtID = 0;
							closesocket(pDlg->m_AcceptSocket);//第3个按钮特有的动作
							ExitThread(0);//退出线程；这个更直接一点；破不得以用这个；会导致类的资源无法释放
						}
						File.Write(recvBut,recvRt);		
						recvSize += recvRt;

						//进度条显示
 						Pro1Pos = recvSize;//转换
 						pPro1->SetPos(Pro1Pos/1024);//第1条

						if (recvSize == pDlg->m_Carfilestruct->ElementAt(i).Filelength)
						{
							break;
						}
					}
					//进度条显示
					Pro2Pos += Pro1Pos;
 					pPro2->SetPos(Pro2Pos/(1024*FileSize));//第2条

					if (recvRt == SOCKET_ERROR)
					{
						break;//跳出第2重循环
					}
					if (i == FileSize-1)
					{
						recvEndID = 1;
						(CButton*)(pDlg->GetDlgItem(IDC_BUTTON_OPENFILEDIR))->ShowWindow(TRUE);
						(CButton*)(pDlg->GetDlgItem(IDC_BUTTON_CANCEL))->ShowWindow(FALSE);
					}
				}
			}
			else
			{
				((CButton*)(pDlg->GetDlgItem(IDC_BUTTON_RECEIVER)))->EnableWindow(TRUE);
				((CButton*)(pDlg->GetDlgItem(IDC_BUTTON_SAVEAS)))->EnableWindow(TRUE);
				break;//退出线程
			}
		}
		if (pDlg->ButtonRtID == 1)//按下接收按钮
		{
			pDlg->ButtonRtID = 0;//设置成初始化
			AfxMessageBox("接收");
		}
		if (recvRt == SOCKET_ERROR)
		{
			break;//跳出第3重循环
		}
		if (recvEndID == 1)
		{
			break;//跳出循环
		}
		Sleep(100);//节约资源
	}
	return 0;
}

void CRecvFileDlg::OnButtonOpenFileDir() 
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, "open", "explorer.exe", "/select,"+m_PathName+"", NULL,SW_SHOWMAXIMIZED);
}


BOOL CRecvFileDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)//修改EXC键//屏蔽其退出功能
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
