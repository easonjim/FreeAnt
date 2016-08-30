; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FreeAnt.h"

ClassCount=3
Class1=CFreeAntApp
Class2=CFreeAntDlg

ResourceCount=3
Resource2=IDD_FREEANT_DIALOG
Resource1=IDR_MAINFRAME
Class3=CChatDlg
Resource3=IDD_CHAT_DIALOG

[CLS:CFreeAntApp]
Type=0
HeaderFile=FreeAnt.h
ImplementationFile=FreeAnt.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CFreeAntApp

[CLS:CFreeAntDlg]
Type=0
HeaderFile=FreeAntDlg.h
ImplementationFile=FreeAntDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CFreeAntDlg



[DLG:IDD_FREEANT_DIALOG]
Type=1
Class=CFreeAntDlg
ControlCount=8
Control1=IDC_RICHEDIT_SEND,RICHEDIT,1352728644
Control2=IDC_LIST_USERINFO,SysListView32,1350631425
Control3=IDC_BUTTON_SEND,button,1342242817
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_EDIT_STATUS,edit,1476462721
Control7=IDC_STATIC,button,1342177287
Control8=IDC_BUTTON_MSGPROMPT,button,1073807360

[DLG:IDD_CHAT_DIALOG]
Type=1
Class=CChatDlg
ControlCount=7
Control1=IDC_RICHEDIT_SEND,RICHEDIT,1350631552
Control2=IDC_BUTTON_SEND,button,1342242817
Control3=IDC_BUTTON_QUIT,button,1342242816
Control4=IDC_STATIC,button,1342178055
Control5=IDC_RICHEDIT_RECV,RICHEDIT,1352730692
Control6=IDC_STATIC,button,1342178055
Control7=IDC_EDIT_USERINFO,edit,1476462721

[CLS:CChatDlg]
Type=0
HeaderFile=ChatDlg.h
ImplementationFile=ChatDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CChatDlg
VirtualFilter=dWC

