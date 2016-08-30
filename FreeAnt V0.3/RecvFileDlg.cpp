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
	InitListCtrl();//��ʼ���б�ؼ�
	ButtonRtID = 0;//��ʼ����ťID
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecvFileDlg::InitListCtrl()
{
	DWORD dwStyle = ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP;
    ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetExtendedStyle(dwStyle); //������չ���
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(0,"�ļ���",LVCFMT_LEFT,130);
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(1,"��С",LVCFMT_LEFT,85);
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
		if (::MessageBox(m_hWnd,"���ڽ����ļ�,ȷ��Ҫ�˳���","��ʾ",MB_YESNO) == IDYES)
		{
			ButtonRtID = 3;
			CloseHandle(m_RecvFileThreadHandle);
			DestroyWindow();
			CDialog::PostNcDestroy(); //ɾ��ָ��
			delete this;
		}
	}
	else
	{
		closesocket(m_AcceptSocket);//��Ϊ�ر����׽��֣����Խ����߳�Ҳ��ֹͣ
		CloseHandle(m_RecvFileThreadHandle);
		DestroyWindow();
		CDialog::PostNcDestroy(); //ɾ��ָ��
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
	//�ͷ���Դ
	DWORD dwExitCode = 0;
	GetExitCodeThread(m_RecvFileThreadHandle, &dwExitCode);
	if (STILL_ACTIVE == dwExitCode)
	{
		if (::MessageBox(m_hWnd,"���ڽ����ļ�,ȷ��Ҫ�˳���","��ʾ",MB_YESNO) == IDYES)
		{
			ButtonRtID = 3;
			CloseHandle(m_RecvFileThreadHandle);
			DestroyWindow();
			CDialog::PostNcDestroy(); //ɾ��ָ��
			delete this;
		}
	}
	else
	{
		closesocket(m_AcceptSocket);
		CloseHandle(m_RecvFileThreadHandle);
		DestroyWindow();
		CDialog::PostNcDestroy(); //ɾ��ָ��
		delete this;
	}

}

DWORD WINAPI CRecvFileDlg::RecvFileThread(LPVOID lpParameter)
{
	CRecvFileDlg *pDlg = (CRecvFileDlg*) lpParameter;

	CString FileName=pDlg->m_Carfilestruct->ElementAt(0).FileName;//�õ��ļ���
 	CFileDialog FileDlg(FALSE,NULL,FileName,OFN_EXTENSIONDIFFERENT|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST| 
 	         OFN_HIDEREADONLY,"All Files(*.*)|*.*||", pDlg);//���һ��������ָ�������ڵ�ָ�룬������ǰ�ģ�
 	//�����ļ��еķ��
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
	FileDlg.m_ofn.lStructSize=structsize; 
	
	CString PathName;
	char FilePath[200];
	int FileSize = pDlg->m_Carfilestruct->GetSize();
	int recvRt = 1;
	int recvEndID = 0;//������ϱ��
	char recvBut[8000];

	//����������;��ƭ�Ӿ��ļ���
	CProgressCtrl *pPro1 = (CProgressCtrl*)(pDlg->GetDlgItem(IDC_PROGRESS1));//��������
	CProgressCtrl *pPro2 = (CProgressCtrl*)(pDlg->GetDlgItem(IDC_PROGRESS2));//�ܽ���
	ULONGLONG Pro1Range = 0,Pro2Range = 0;//��ֵ
	ULONGLONG Pro1Pos = 0,Pro2Pos = 0;//�̶�
	for (int i=0;i<FileSize;i++)
	{
			Pro2Range += pDlg->m_Carfilestruct->ElementAt(i).Filelength;//�ܽ���ֵ
	}
	pPro2->SetRange32(0,Pro2Range/(1024*FileSize));

	while (1)
	{
		if (pDlg->ButtonRtID == 2)//�������Ϊ��ť
		{
			pDlg->ButtonRtID = 0;//���óɳ�ʼ��
			if (FileDlg.DoModal() == IDOK)
			{
				PathName = FileDlg.GetPathName();
				//ת�������;��,����c:\a\b.txt,ת��֮��Ϊc:\a
				strcpy(FilePath,PathName);
 	  			PathRemoveFileSpec(FilePath);
				for (int i=0;i<FileSize;i++)
				{
					//��ʼ��������
					Pro1Range = pDlg->m_Carfilestruct->ElementAt(i).Filelength;//�ܽ���ֵ
					pPro1->SetRange32(0,Pro1Range/1024);

					PathName = FilePath;
					PathName += "\\";//ת�������ַ����Ϊ����������ѭ�������ļ�������ѭ�������ļ���
 	 				PathName +=pDlg->m_Carfilestruct->ElementAt(i).FileName;
					pDlg->m_PathName = PathName;//ȫ��Ϊ�������׼��
					CFile64 File(PathName, CFile64::modeCreate | CFile64::modeWrite);
					ULONGLONG recvSize = 0;
					send(pDlg->m_AcceptSocket,"RecvRequest",sizeof("RecvRequest"),0);//����recv֪ͨ��ʹ���ͺͽ��ձ���һ�£�
					while (recvRt != SOCKET_ERROR)
					{
						recvRt = recv(pDlg->m_AcceptSocket,recvBut,8000,0);
						if (recvRt == SOCKET_ERROR)
						{
							::MessageBox(pDlg->m_hWnd,"�Է�ֹͣ���ͣ�","����",MB_OK);
							break;
						}
						if (pDlg->ButtonRtID == 3)//�����˳���
						{
							pDlg->ButtonRtID = 0;
							closesocket(pDlg->m_AcceptSocket);//��3����ť���еĶ���
							ExitThread(0);//�˳��̣߳������ֱ��һ�㣻�Ʋ�������������ᵼ�������Դ�޷��ͷ�
						}
						File.Write(recvBut,recvRt);		
						recvSize += recvRt;

						//��������ʾ
 						Pro1Pos = recvSize;//ת��
 						pPro1->SetPos(Pro1Pos/1024);//��1��

						if (recvSize == pDlg->m_Carfilestruct->ElementAt(i).Filelength)
						{
							break;
						}
					}
					//��������ʾ
					Pro2Pos += Pro1Pos;
 					pPro2->SetPos(Pro2Pos/(1024*FileSize));//��2��

					if (recvRt == SOCKET_ERROR)
					{
						break;//������2��ѭ��
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
				break;//�˳��߳�
			}
		}
		if (pDlg->ButtonRtID == 1)//���½��հ�ť
		{
			pDlg->ButtonRtID = 0;//���óɳ�ʼ��
			AfxMessageBox("����");
		}
		if (recvRt == SOCKET_ERROR)
		{
			break;//������3��ѭ��
		}
		if (recvEndID == 1)
		{
			break;//����ѭ��
		}
		Sleep(100);//��Լ��Դ
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
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)//�޸�EXC��//�������˳�����
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
