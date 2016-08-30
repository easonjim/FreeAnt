; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetup1Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FreeAnt.h"

ClassCount=9
Class1=CFreeAntApp
Class2=CFreeAntDlg

ResourceCount=12
Resource2=IDD_SENDFILE_DIALOG
Resource1=IDR_MAINFRAME
Class3=CChatDlg
Resource3=IDR_USERINFOLIST_MENU
Class4=CSendFileDlg
Resource4=IDD_ABOUT_DIALOG
Class5=CRecvFileDlg
Resource5=IDD_FREEANT_DIALOG
Resource6=IDD_SETUP_DIALOG
Resource7=IDD_SETUP2_DIALOG
Resource8=IDD_RECVFILE_DIALOG
Class6=CSetupDlg
Resource9=IDR_MAIN_MENU
Class7=CAboutDlg
Resource10=IDD_CHAT_DIALOG
Resource11=IDD_SETUP1_DIALOG
Class8=CSetup1Dlg
Class9=CSetup2Dlg
Resource12=IDR_TASKBAR_MENU

[CLS:CFreeAntApp]
Type=0
HeaderFile=FreeAnt.h
ImplementationFile=FreeAnt.cpp
Filter=W
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CFreeAntApp

[CLS:CFreeAntDlg]
Type=0
HeaderFile=FreeAntDlg.h
ImplementationFile=FreeAntDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CFreeAntDlg



[DLG:IDD_FREEANT_DIALOG]
Type=1
Class=CFreeAntDlg
ControlCount=14
Control1=IDC_RICHEDIT_SEND,RICHEDIT,1352728644
Control2=IDC_LIST_USERINFO,SysListView32,1350631425
Control3=IDC_BUTTON_SEND,button,1342242817
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON_MSGPROMPT,button,1073807360
Control7=IDC_BUTTON_SENDFILE,button,1342242816
Control8=IDC_BUTTON_REFRESH,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC_PEOPLESIZE,static,1342308352
Control12=IDC_BUTTON_EXIT,button,1342242816
Control13=IDC_BUTTON_MAINMENU,button,1342242816
Control14=IDC_STATIC,button,1342177287

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

[DLG:IDD_SENDFILE_DIALOG]
Type=1
Class=CSendFileDlg
ControlCount=5
Control1=IDC_LIST_FILE,SysListView32,1350631425
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUTTON_ADD,button,1342242817
Control4=IDC_BUTTON_DELETE,button,1342242816
Control5=IDC_BUTTON_CLOSE,button,1342242816

[CLS:CSendFileDlg]
Type=0
HeaderFile=SendFileDlg.h
ImplementationFile=SendFileDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSendFileDlg
VirtualFilter=dWC

[DLG:IDD_RECVFILE_DIALOG]
Type=1
Class=CRecvFileDlg
ControlCount=9
Control1=IDC_LIST_FILE,SysListView32,1350631425
Control2=IDC_BUTTON_RECEIVER,button,1342242816
Control3=IDC_BUTTON_SAVEAS,button,1342242816
Control4=IDC_BUTTON_CANCEL,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342178055
Control7=IDC_PROGRESS1,msctls_progress32,1350565888
Control8=IDC_PROGRESS2,msctls_progress32,1350565888
Control9=IDC_BUTTON_OPENFILEDIR,button,1073807360

[CLS:CRecvFileDlg]
Type=0
HeaderFile=RecvFileDlg.h
ImplementationFile=RecvFileDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=CRecvFileDlg
VirtualFilter=dWC

[MNU:IDR_USERINFOLIST_MENU]
Type=1
Class=?
Command1=IDR_USERINFOLIST_MENUITEM_SELECTALL
Command2=IDR_USERINFOLIST_MENUITEM_INVERSE
Command3=IDR_USERINFOLIST_MENUITEM_SENDFILE
Command4=IDR_USERINFOLIST_MENUITEM_SENDFOLDER
CommandCount=4

[MNU:IDR_MAIN_MENU]
Type=1
Class=?
Command1=IDR_MAIN_MENUITEM_SENDFILE
Command2=IDR_MAIN_MENUITEM_SENDFOLDER
Command3=IDR_MAIN_MENUITEM32784
CommandCount=3

[MNU:IDR_TASKBAR_MENU]
Type=1
Class=?
Command1=ID_MENUITEM32793
Command2=IDR_TASKBAR_MENUITEM_SETUP
Command3=IDR_TASKBAR_MENUITEM_ABOUT
Command4=IDR_TASKBAR_MENUITEM_EXIT
CommandCount=4

[DLG:IDD_SETUP_DIALOG]
Type=1
Class=CSetupDlg
ControlCount=6
Control1=IDC_STATIC1,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUTTON_ENTER,button,1342242816
Control4=IDC_BUTTON_APPLICATION,button,1342242816
Control5=IDC_BUTTON_CANCEL,button,1342242816
Control6=IDC_LIST_OPTIONS,listbox,1352728833

[CLS:CSetupDlg]
Type=0
HeaderFile=SetupDlg.h
ImplementationFile=SetupDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=CSetupDlg
VirtualFilter=dWC

[DLG:IDD_ABOUT_DIALOG]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON_ENTER,button,1342242816

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENUITEM32790
VirtualFilter=dWC

[DLG:IDD_SETUP1_DIALOG]
Type=1
Class=CSetup1Dlg
ControlCount=14
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECK_INITSHOWDLG,button,1342242819
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_EDIT_RECVFILEPATH,edit,1350631552
Control6=IDC_BUTTON1,button,1342242816
Control7=IDC_CHECK_BALLOONPROMPT,button,1342242819
Control8=IDC_CHECK_MUTE,button,1342373891
Control9=IDC_EDIT_MSGTONEPATH,edit,1484849280
Control10=IDC_EDIT_FILETONEPATH,edit,1484849280
Control11=IDC_BUTTON2,button,1476460544
Control12=IDC_BUTTON3,button,1476460544
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_SETUP2_DIALOG]
Type=1
Class=CSetup2Dlg
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CSetup1Dlg]
Type=0
HeaderFile=Setup1Dlg.h
ImplementationFile=Setup1Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_MUTE
VirtualFilter=dWC

[CLS:CSetup2Dlg]
Type=0
HeaderFile=Setup2Dlg.h
ImplementationFile=Setup2Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetup2Dlg

