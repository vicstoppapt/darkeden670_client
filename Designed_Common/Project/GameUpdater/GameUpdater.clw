; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGameUpdaterDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gameupdater.h"
LastPage=0

ClassCount=4
Class1=CGameUpdaterApp
Class2=CAboutDlg
Class3=CGameUpdaterDlg
Class4=CProgressST

ResourceCount=3
Resource1=IDD_NEW_UPDATER3_DLG (Korean)
Resource2=IDD_ABOUTBOX
Resource3=IDD_NEWUPDATER2_DIALOG (Korean)

[CLS:CGameUpdaterApp]
Type=0
BaseClass=CWinApp
HeaderFile=GameUpdater.h
ImplementationFile=GameUpdater.cpp
LastObject=CGameUpdaterApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GameUpdaterDlg.cpp
ImplementationFile=GameUpdaterDlg.cpp
LastObject=CAboutDlg

[CLS:CGameUpdaterDlg]
Type=0
BaseClass=CDialog
HeaderFile=GameUpdaterDlg.h
ImplementationFile=GameUpdaterDlg.cpp
LastObject=IDC_COMBO_RESOULVLIST
Filter=D
VirtualFilter=dWC

[CLS:CProgressST]
Type=0
BaseClass=CProgressCtrl
HeaderFile=ProgressST.h
ImplementationFile=ProgressST.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NEW_UPDATER3_DLG (Korean)]
Type=1
Class=?
ControlCount=2
Control1=IDC_PROGRESS1,msctls_progress32,1342177281
Control2=IDC_PROGRESS2,msctls_progress32,1342177281

[DLG:IDD_NEWUPDATER2_DIALOG (Korean)]
Type=1
Class=CGameUpdaterDlg
ControlCount=5
Control1=IDC_EXPLORER,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control2=IDC_PROGRESS1,msctls_progress32,1342177281
Control3=IDC_PROGRESS2,msctls_progress32,1342177281
Control4=IDC_COMBO_PROXYLIST,combobox,1344342019
Control5=IDC_COMBO_RESOULVLIST,combobox,1344342019

