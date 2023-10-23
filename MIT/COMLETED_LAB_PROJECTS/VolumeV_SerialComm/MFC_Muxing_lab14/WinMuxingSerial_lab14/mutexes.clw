; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COScopeCtrl
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mutexes.h"
LastPage=0

ClassCount=6
Class1=CAboutDlg
Class2=CMutexesDlg
Class3=CMutexesApp
Class4=CCounterThread
Class5=CDisplayThread

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class6=COScopeCtrl
Resource2=IDD_DIALOG_RS232

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=mutexdlg.cpp
ImplementationFile=mutexdlg.cpp
LastObject=CAboutDlg

[CLS:CMutexesDlg]
Type=0
BaseClass=CDialog
HeaderFile=mutexdlg.h
ImplementationFile=mutexdlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CMutexesApp]
Type=0
BaseClass=CWinApp
HeaderFile=mutexes.h
ImplementationFile=mutexes.cpp

[CLS:CCounterThread]
Type=0
BaseClass=CWinThread
HeaderFile=threads.h
ImplementationFile=threads.cpp

[CLS:CDisplayThread]
Type=0
BaseClass=CWinThread
HeaderFile=threads.h
ImplementationFile=threads.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:COScopeCtrl]
Type=0
HeaderFile=OScopeCtrl.h
ImplementationFile=OScopeCtrl.cpp
BaseClass=generic CWnd
Filter=W

[DLG:IDD_DIALOG_RS232]
Type=1
Class=CMutexesDlg
ControlCount=34
Control1=IDC_OSCOPE1,static,1342177287
Control2=IDC_CHECK_ENABLE_CHN1,button,1342242819
Control3=IDC_OSCOPE2,static,1342177287
Control4=IDC_OSCOPE3,static,1342177287
Control5=IDC_OSCOPE4,static,1342177287
Control6=IDC_LOWER_RANGE_CH1,combobox,1344473090
Control7=IDC_STATIC,static,1342308352
Control8=IDC_UPPER_RANGE_CH1,combobox,1344339970
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK_ENABLE_CHN2,button,1342242819
Control11=IDC_LOWER_RANGE_CH2,combobox,1344473090
Control12=IDC_STATIC,static,1342308352
Control13=IDC_UPPER_RANGE_CH2,combobox,1344339970
Control14=IDC_STATIC,static,1342308352
Control15=IDC_CHECK_ENABLE_CHN3,button,1342242819
Control16=IDC_LOWER_RANGE_CH3,combobox,1344473090
Control17=IDC_STATIC,static,1342308352
Control18=IDC_UPPER_RANGE_CH3,combobox,1344339970
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CHECK_ENABLE_CHN4,button,1342242819
Control21=IDC_LOWER_RANGE_CH4,combobox,1344473090
Control22=IDC_STATIC,static,1342308352
Control23=IDC_UPPER_RANGE_CH4,combobox,1344339970
Control24=IDC_STATIC,static,1342308352
Control25=IDC_NUM_DEMUX,combobox,1344339970
Control26=IDC_STATIC,static,1342308352
Control27=IDC_BAUD_CHANGE,combobox,1344339970
Control28=IDC_STATIC,static,1342308352
Control29=IDC_RS232_ENABLE,button,1342242819
Control30=IDC_STATIC,button,1342177287
Control31=IDC_STATIC,button,1342177287
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,button,1342177287

