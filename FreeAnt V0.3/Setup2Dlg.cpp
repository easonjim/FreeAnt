// Setup2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeAnt.h"
#include "Setup2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup2Dlg dialog


CSetup2Dlg::CSetup2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetup2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetup2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetup2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup2Dlg, CDialog)
	//{{AFX_MSG_MAP(CSetup2Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup2Dlg message handlers
