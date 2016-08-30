// FreeAnt.h : main header file for the FREEANT application
//

#if !defined(AFX_FREEANT_H__A4655ED0_9A2E_4882_831A_D5578BB6223D__INCLUDED_)
#define AFX_FREEANT_H__A4655ED0_9A2E_4882_831A_D5578BB6223D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFreeAntApp:
// See FreeAnt.cpp for the implementation of this class
//

class CFreeAntApp : public CWinApp
{
public:
	CFreeAntApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreeAntApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFreeAntApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREEANT_H__A4655ED0_9A2E_4882_831A_D5578BB6223D__INCLUDED_)
