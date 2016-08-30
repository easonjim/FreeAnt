// SendFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "SendFileDlg.h"
#include "FreeAntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFileDlg dialog
CArray<CStructure::FileStruct,CStructure::FileStruct&> CSendFileDlg::m_Carfilestruct;

CSendFileDlg::CSendFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CSendFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendFileDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendFileDlg, CDialog)
	//{{AFX_MSG_MAP(CSendFileDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFileDlg message handlers

BOOL CSendFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	InitListCtrl();//��ʼ���б�ؼ�

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSendFileDlg::InitListCtrl()
{
	DWORD dwStyle = ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP;
    ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetExtendedStyle(dwStyle); //������չ���
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(0,"�ļ���",LVCFMT_LEFT,100);
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(1,"��С",LVCFMT_LEFT,100);
	((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertColumn(2,"��ַ",LVCFMT_LEFT,225);
	for (int i=0;i<m_Carfilestruct.GetSize();i++)
	{
		int nRow = ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertItem(0,m_Carfilestruct.ElementAt(i).FileName);
		((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetItemText(nRow,1,m_Carfilestruct.ElementAt(i).FileSize);
		((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetItemText(nRow,2,m_Carfilestruct.ElementAt(i).FilePath);
	}
}

void CSendFileDlg::OnButtonAdd()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFileOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, "All Files(*.*)|*.*||", NULL); 
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
	DWORD MAXFILE = 4000;
	dlgFileOpen.m_ofn.nMaxFile = MAXFILE;
	char* pc = new char[MAXFILE];
	dlgFileOpen.m_ofn.lpstrFile = pc;
	dlgFileOpen.m_ofn.lpstrFile[0] = NULL;

	if (dlgFileOpen.DoModal() == IDOK)
	{
		POSITION pos = dlgFileOpen.GetStartPosition();
		while (pos != NULL)
		{
			filestruct.PathName = dlgFileOpen.GetNextPathName(pos);//��ȡ��������;��������׺�� �磺c:\a\b.txt
 			filestruct.FileName = PathFindFileName(filestruct.PathName);
 			//ת�������;��,����c:\a\b.txt,ת��֮��Ϊc:\a
 			strcpy(filestruct.FilePath,filestruct.PathName);
 			PathRemoveFileSpec(filestruct.FilePath);
 
			CFile64 file;
			file.Open(filestruct.PathName, CFile::modeRead); 
			filestruct.Filelength = file.GetLength(); //����������ص������ֽ�Ϊ��λ��;����CFile64�࣬ʹ��֧�ֳ���4G���ļ�
			//ת��Ϊ��λ
			double length = (double)(LONGLONG)filestruct.Filelength;//ULONGLONGתdouble��Ϊ������С����
			if (length<1024)
			{
				filestruct.FileSize.Format("%.2f�ֽ�",length);
			}
			if (length>=1024 && length<1024*1024)//KB
			{
				filestruct.FileSize.Format("%.2fKB",length/1024);
			}
			if (length>=1024*1024 && length<1024*1024*1024)//MB
			{
				filestruct.FileSize.Format("%.2fMB",length/(1024*1024));
			}
			if (length>=1024*1024*1024)//GB
			{
				filestruct.FileSize.Format("%.2fGB",length/(1024*1024*1024));
			}

			for (int i=0;i<m_Carfilestruct.GetSize();i++)//�ж��Ƿ�����ͬ���ļ�
			{
				if (m_Carfilestruct.ElementAt(i).FileName == filestruct.FileName)
				{
					return;
				}
			}

			m_Carfilestruct.Add(filestruct);//��ӵ���̬����
			
			int nRow = ((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->InsertItem(0,filestruct.FileName);
			((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetItemText(nRow,1,filestruct.FileSize);
  			((CListCtrl*)GetDlgItem(IDC_LIST_FILE))->SetItemText(nRow,2,filestruct.FilePath);
		}
	}



}



void CSendFileDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CFreeAntDlg *dlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();
	if (m_Carfilestruct.GetSize() == 0)
	{
		dlg->MoveControlN();
	}
	else
	{
		dlg->MoveControlO();
	}
	CSendFileDlg::OnOK();
}

void CSendFileDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	CString rtFileName;
	CListCtrl* pListCtrl=(CListCtrl*)GetDlgItem(IDC_LIST_FILE);
	ASSERT(pListCtrl !=NULL);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem=pListCtrl->GetNextSelectedItem(pos);//�ж��Ƿ�ѡ��
		rtFileName = pListCtrl->GetItemText(nItem,0);
		pListCtrl->DeleteItem(nItem);//ɾ��֮�������ض��仯��
		pos = pListCtrl->GetFirstSelectedItemPosition();//��������ͳ������
		for (int i=0;i<m_Carfilestruct.GetSize();i++)
		{
			if (m_Carfilestruct.ElementAt(i).FileName == rtFileName)
			{
				m_Carfilestruct.RemoveAt(i);
			}
		}
	}


}

void CSendFileDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CFreeAntDlg *dlg = (CFreeAntDlg*)AfxGetApp()->GetMainWnd();
	if (m_Carfilestruct.GetSize() == 0)
	{
		dlg->MoveControlN();
	}
	else
	{
		dlg->MoveControlO();
	}
	CDialog::OnClose();
}

void CSendFileDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	
}

BOOL CSendFileDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)//�޸�EXC��//�������˳�����
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
