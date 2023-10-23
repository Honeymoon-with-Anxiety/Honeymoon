// mutexesDlg.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//
// This sample application is derived from the Mutex application
// distributed with Jeffrey Richter's "Advanced Windows" programming book
// (Microsoft Press).  See the book for more information about Win32
// programming topics, including thread synchronization.

#include "stdafx.h"
#include "mutexes.h"
#include "mutexdlg.h"
#include "threads.h"
#include "Serial.h"
#include "SeriBuffer.h"
#include "OScopeCtrl.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMutexesDlg dialog

CMutexesDlg::CMutexesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMutexesDlg::IDD, pParent),
	 m_mutex(FALSE, NULL),
	 m_strNumber(_T("0"))
{
	//{{AFX_DATA_INIT(CMutexesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pPeekerThread = NULL;
	m_pReaderThread = NULL;
}

void CMutexesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMutexesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMutexesDlg, CDialog)
	//{{AFX_MSG_MAP(CMutexesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_LOWER_RANGE_CH1,OnLowerRangeCH1Change)
	ON_CBN_SELCHANGE(IDC_UPPER_RANGE_CH1,OnUpperRangeCH1Change)
	ON_CBN_SELCHANGE(IDC_LOWER_RANGE_CH2,OnLowerRangeCH2Change)
	ON_CBN_SELCHANGE(IDC_UPPER_RANGE_CH2,OnUpperRangeCH2Change)
	ON_CBN_SELCHANGE(IDC_LOWER_RANGE_CH3,OnLowerRangeCH3Change)
	ON_CBN_SELCHANGE(IDC_UPPER_RANGE_CH3,OnUpperRangeCH3Change)
	ON_CBN_SELCHANGE(IDC_LOWER_RANGE_CH4,OnLowerRangeCH4Change)
	ON_CBN_SELCHANGE(IDC_UPPER_RANGE_CH4,OnUpperRangeCH4Change)
	ON_CBN_SELCHANGE(IDC_NUM_DEMUX,OnNumDemux)
	ON_CBN_SELCHANGE(IDC_BAUD_CHANGE,OnBaudChange)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_ENABLE_CHN1, OnEnableCH1)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_CHN2, OnEnableCH2)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_CHN3, OnEnableCH3)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_CHN4, OnEnableCH4)
	ON_BN_CLICKED(IDC_RS232_ENABLE, OnOpenEnableRS232)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMutexesDlg message handlers

BOOL CMutexesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Fill the Process Priority Class combo box and select
	// Normal.

	CComboBox* pBox;
	pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH1);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("-2^1"));
		pBox->AddString(_T("-2^2"));
		pBox->AddString(_T("-2^3"));
		pBox->AddString(_T("-2^4"));
		pBox->AddString(_T("-2^5"));
		pBox->AddString(_T("-2^6"));
		pBox->AddString(_T("-2^7"));
		pBox->AddString(_T("-2^8"));
		pBox->AddString(_T("-2^9"));
		pBox->AddString(_T("-2^10"));
		pBox->SetCurSel(0);  // 
	}

	pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH1);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("+2^1"));
		pBox->AddString(_T("+2^2"));
		pBox->AddString(_T("+2^3"));
		pBox->AddString(_T("+2^4"));
		pBox->AddString(_T("+2^5"));
		pBox->AddString(_T("+2^6"));
		pBox->AddString(_T("+2^7"));
		pBox->AddString(_T("+2^8"));
		pBox->AddString(_T("+2^9"));
		pBox->AddString(_T("+2^10"));
		pBox->SetCurSel(8);  // 
	}


	pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH2);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("-2^1"));
		pBox->AddString(_T("-2^2"));
		pBox->AddString(_T("-2^3"));
		pBox->AddString(_T("-2^4"));
		pBox->AddString(_T("-2^5"));
		pBox->AddString(_T("-2^6"));
		pBox->AddString(_T("-2^7"));
		pBox->AddString(_T("-2^8"));
		pBox->AddString(_T("-2^9"));
		pBox->AddString(_T("-2^10"));
		pBox->SetCurSel(0);  // 
	}

	pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH2);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("+2^1"));
		pBox->AddString(_T("+2^2"));
		pBox->AddString(_T("+2^3"));
		pBox->AddString(_T("+2^4"));
		pBox->AddString(_T("+2^5"));
		pBox->AddString(_T("+2^6"));
		pBox->AddString(_T("+2^7"));
		pBox->AddString(_T("+2^8"));
		pBox->AddString(_T("+2^9"));
		pBox->AddString(_T("+2^10"));
		pBox->SetCurSel(8);  // 
	}


	pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH3);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("-2^1"));
		pBox->AddString(_T("-2^2"));
		pBox->AddString(_T("-2^3"));
		pBox->AddString(_T("-2^4"));
		pBox->AddString(_T("-2^5"));
		pBox->AddString(_T("-2^6"));
		pBox->AddString(_T("-2^7"));
		pBox->AddString(_T("-2^8"));
		pBox->AddString(_T("-2^9"));
		pBox->AddString(_T("-2^10"));
		pBox->SetCurSel(0);  // 
	}

	pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH3);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("+2^1"));
		pBox->AddString(_T("+2^2"));
		pBox->AddString(_T("+2^3"));
		pBox->AddString(_T("+2^4"));
		pBox->AddString(_T("+2^5"));
		pBox->AddString(_T("+2^6"));
		pBox->AddString(_T("+2^7"));
		pBox->AddString(_T("+2^8"));
		pBox->AddString(_T("+2^9"));
		pBox->AddString(_T("+2^10"));
		pBox->SetCurSel(8);  // 
	}


	pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH4);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("-2^1"));
		pBox->AddString(_T("-2^2"));
		pBox->AddString(_T("-2^3"));
		pBox->AddString(_T("-2^4"));
		pBox->AddString(_T("-2^5"));
		pBox->AddString(_T("-2^6"));
		pBox->AddString(_T("-2^7"));
		pBox->AddString(_T("-2^8"));
		pBox->AddString(_T("-2^9"));
		pBox->AddString(_T("-2^10"));
		pBox->SetCurSel(0);  // 
	}

	pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH4);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("zero"));
		pBox->AddString(_T("+2^1"));
		pBox->AddString(_T("+2^2"));
		pBox->AddString(_T("+2^3"));
		pBox->AddString(_T("+2^4"));
		pBox->AddString(_T("+2^5"));
		pBox->AddString(_T("+2^6"));
		pBox->AddString(_T("+2^7"));
		pBox->AddString(_T("+2^8"));
		pBox->AddString(_T("+2^9"));
		pBox->AddString(_T("+2^10"));
		pBox->SetCurSel(8);  // 
	}

		pBox = (CComboBox*) GetDlgItem(IDC_NUM_DEMUX);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("one channel"));
		pBox->AddString(_T("two channels"));
		pBox->AddString(_T("three channels"));
		pBox->AddString(_T("four channels"));
		pBox->SetCurSel(0);  // 
	}

	pBox = (CComboBox*) GetDlgItem(IDC_BAUD_CHANGE);
	ASSERT(pBox != NULL);
	if (pBox != NULL)
	{
		pBox->AddString(_T("1200"));
		pBox->AddString(_T("2400"));
		pBox->AddString(_T("4800"));
		pBox->AddString(_T("9600"));
		pBox->AddString(_T("19200"));
		pBox->AddString(_T("38400"));
		pBox->AddString(_T("76800"));
		pBox->SetCurSel(3);  // 
	}

	// initialize the threads and let them start running!

	m_pReaderThread = (CReaderThread*)
		AfxBeginThread(RUNTIME_CLASS(CReaderThread), THREAD_PRIORITY_NORMAL,
			0, CREATE_SUSPENDED);
	m_pReaderThread->SetOwner(this);
	//m_pReaderThread->ResumeThread();

	m_pPeekerThread = (CPeekerThread*)
		AfxBeginThread(RUNTIME_CLASS(CPeekerThread), THREAD_PRIORITY_NORMAL,
			0, CREATE_SUSPENDED);
	m_pPeekerThread->SetOwner(this);
	//m_pPeekerThread->ResumeThread();

	
	//init the serial buffer
	CBuff = new CSeriBuffer(100,4);
	CBuff->initCSeriBuffer();

	//set up the oscilocope control
	// determine the rectangle for the control
	m_chn1_enable = false;
	m_chn2_enable = false;
	m_chn3_enable = false;
	m_chn4_enable = false;

	//set up channel 1
	m_channel1 = new COScopeCtrl();
	CRect rect1;
	GetDlgItem(IDC_OSCOPE1)->GetWindowRect(rect1) ;
	ScreenToClient(rect1) ;
	// create the control
	m_channel1->Create(WS_VISIBLE | WS_CHILD, rect1, this) ;
	CString yunits = "Chanel One Samples";
	m_channel1->SetXUnits(yunits);

	//set up channel 2
	m_channel2 = new COScopeCtrl();
	CRect rect2;
	GetDlgItem(IDC_OSCOPE2)->GetWindowRect(rect2) ;
	ScreenToClient(rect2) ;
	// create the control
	m_channel2->Create(WS_VISIBLE | WS_CHILD, rect2, this) ;
	yunits = "Chanel Two Samples";
	m_channel2->SetXUnits(yunits);

	//set up channel 3
	m_channel3 = new COScopeCtrl();
	CRect rect3;
	GetDlgItem(IDC_OSCOPE3)->GetWindowRect(rect3) ;
	ScreenToClient(rect3) ;
	// create the control
	m_channel3->Create(WS_VISIBLE | WS_CHILD, rect3, this) ;
	yunits = "Chanel Three Samples";
	m_channel3->SetXUnits(yunits);

	//set up channel 2
	m_channel4 = new COScopeCtrl();
	CRect rect4;
	GetDlgItem(IDC_OSCOPE4)->GetWindowRect(rect4) ;
	ScreenToClient(rect4) ;
	// create the control
	m_channel4->Create(WS_VISIBLE | WS_CHILD, rect4, this) ;
	yunits = "Chanel Four Samples";
	m_channel4->SetXUnits(yunits);

	RS232Port = NULL;
	m_RS232_enabled = false;
	m_nBaud = 9600;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMutexesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMutexesDlg::OnPaint()
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
			if(m_chn1_enable) m_channel1->AppendPoint(CBuff->GetData(0));
			if(m_chn2_enable) m_channel2->AppendPoint(CBuff->GetData(1));
			if(m_chn3_enable) m_channel3->AppendPoint(CBuff->GetData(2));
			if(m_chn4_enable) m_channel4->AppendPoint(CBuff->GetData(3));

		CDialog::OnPaint();
	}//end else
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMutexesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMutexesDlg::OnClose()
{
	int nCount = 0;
	DWORD   dwStatus;


	if (m_pPeekerThread != NULL)
	{
		VERIFY(::GetExitCodeThread(m_pPeekerThread->m_hThread, &dwStatus));
		if (dwStatus == STILL_ACTIVE)
		{
			nCount++;
			m_pPeekerThread->ResumeThread();
			m_pPeekerThread->m_bDone = TRUE;
		}
		else
		{
			delete m_pPeekerThread;
			m_pPeekerThread = NULL;
		}
	}

	if (m_pReaderThread != NULL)
	{
		VERIFY(::GetExitCodeThread(m_pReaderThread->m_hThread, &dwStatus));
		if (dwStatus == STILL_ACTIVE)
		{
			nCount++;
			m_pReaderThread->ResumeThread();
			m_pReaderThread->m_bDone = TRUE;
		}
		else
		{
			delete m_pReaderThread;
			m_pReaderThread = NULL;
		}
	}

	if (nCount == 0)
		CDialog::OnClose();
	else
		PostMessage(WM_CLOSE, 0, 0);
}


void CMutexesDlg::OnEnableCH1()
{
	if(!m_chn1_enable) 
	{
		m_chn1_enable = true;
		OnLowerRangeCH1Change();
		OnUpperRangeCH1Change();
	}
	else 
	{
		m_chn1_enable = false;
	}
}

void CMutexesDlg::OnEnableCH2()
{
	if(!m_chn2_enable) {
		m_chn2_enable = true;
		OnLowerRangeCH2Change();
		OnUpperRangeCH2Change();
	}
	else m_chn2_enable = false;
}

void CMutexesDlg::OnEnableCH3()
{
	if(!m_chn3_enable) {
		m_chn3_enable = true;
		OnLowerRangeCH3Change();
		OnUpperRangeCH3Change();
	}
	else m_chn3_enable = false;
}

void CMutexesDlg::OnEnableCH4()
{
	if(!m_chn4_enable) {
		m_chn4_enable = true;
		OnLowerRangeCH4Change();
		OnUpperRangeCH4Change();
	}
	else m_chn4_enable = false;
}

void CMutexesDlg::OnNumDemux()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_NUM_DEMUX);
	CButton* pEnBtn=NULL;
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		{
			dw = 1;
			if(!m_chn1_enable) 
			{
				m_chn1_enable = true;
				OnLowerRangeCH1Change();
				OnUpperRangeCH1Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN1);
				pEnBtn->SetCheck(1);
			}

			if(m_chn2_enable)
			{
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN2);
				pEnBtn->SetCheck(0);
				m_chn2_enable=false;
			}
			if(m_chn3_enable)
			{
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN3);
				pEnBtn->SetCheck(0);
				m_chn3_enable=false;
			}
			if(m_chn4_enable)
			{
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN4);
				pEnBtn->SetCheck(0);
				m_chn4_enable=false;
			}

			break;
		}

	case 1:
		{
			dw = 2;
			if(!m_chn1_enable) 
			{
				m_chn1_enable = true;
				OnLowerRangeCH1Change();
				OnUpperRangeCH1Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN1);
				pEnBtn->SetCheck(1);
			}

			if(!m_chn2_enable)
			{
				m_chn2_enable = true;
				OnLowerRangeCH2Change();
				OnUpperRangeCH2Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN2);
				pEnBtn->SetCheck(1);
			}
			if(m_chn3_enable)
			{
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN3);
				pEnBtn->SetCheck(0);
				m_chn3_enable=false;
			}
			if(m_chn4_enable)
			{
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN4);
				pEnBtn->SetCheck(0);
				m_chn4_enable=false;
			}
			break;
		}

	case 2:
		{
			dw = 3;
			if(!m_chn1_enable) 
			{
				m_chn1_enable = true;
				OnLowerRangeCH1Change();
				OnUpperRangeCH1Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN1);
				pEnBtn->SetCheck(1);
			}

			if(!m_chn2_enable)
			{
				m_chn2_enable = true;
				OnLowerRangeCH2Change();
				OnUpperRangeCH2Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN2);
				pEnBtn->SetCheck(1);
			}
			if(!m_chn3_enable)
			{
				m_chn3_enable = true;
				OnLowerRangeCH3Change();
				OnUpperRangeCH3Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN3);
				pEnBtn->SetCheck(1);
			}
			if(m_chn4_enable)
			{
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN4);
				pEnBtn->SetCheck(0);
				m_chn4_enable=false;
			}
			break;
		}

	case 3:
		{
			dw = 4;
			if(!m_chn1_enable) 
			{
				m_chn1_enable = true;
				OnLowerRangeCH1Change();
				OnUpperRangeCH1Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN1);
				pEnBtn->SetCheck(1);
			}

			if(!m_chn2_enable)
			{
				m_chn2_enable = true;
				OnLowerRangeCH2Change();
				OnUpperRangeCH2Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN2);
				pEnBtn->SetCheck(1);
			}
			if(!m_chn3_enable)
			{
				m_chn3_enable = true;
				OnLowerRangeCH3Change();
				OnUpperRangeCH3Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN3);
				pEnBtn->SetCheck(1);
			}
			if(!m_chn4_enable)
			{
				m_chn4_enable = true;
				OnLowerRangeCH4Change();
				OnUpperRangeCH4Change();
				pEnBtn = (CButton*) GetDlgItem(IDC_CHECK_ENABLE_CHN4);
				pEnBtn->SetCheck(1);
			}
			break;
		}
	
	default:
		dw = 1;
	}

	CBuff->num_channels=dw;
}

void CMutexesDlg::OnLowerRangeCH1Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH1);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = -2;
		break;

	case 2:
		dw = -4;
		break;

	case 3:
		dw = -8;
		break;

	case 4:
		dw = -16;
		break;

	case 5:
		dw = -32;
		break;

	case 6:
		dw = -64;
		break;
	case 7:
		dw = -128;
		break;
	case 8:
		dw = -256;
		break;
	case 9:
		dw = -512;
		break;

	case 10:
		dw = -1048;
		break;

	case 11:
		dw = -2096;
		break;
	default:
		dw = 0;
	}

	m_channel1->SetLowerRange(dw);
}

void CMutexesDlg::OnUpperRangeCH1Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH1);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = 2;
		break;

	case 2:
		dw = 4;
		break;

	case 3:
		dw = 8;
		break;

	case 4:
		dw = 16;
		break;

	case 5:
		dw = 32;
		break;

	case 6:
		dw = 64;
		break;
	case 7:
		dw = 128;
		break;
	case 8:
		dw = 256;
		break;
	case 9:
		dw = 512;
		break;

	case 10:
		dw = 1048;
		break;

	case 11:
		dw = 2096;
		break;
	default:
		dw = 0;
	}

	m_channel1->SetUpperRange(dw);
}

//***************************************
void CMutexesDlg::OnLowerRangeCH2Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH2);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = -2;
		break;

	case 2:
		dw = -4;
		break;

	case 3:
		dw = -8;
		break;

	case 4:
		dw = -16;
		break;

	case 5:
		dw = -32;
		break;

	case 6:
		dw = -64;
		break;
	case 7:
		dw = -128;
		break;
	case 8:
		dw = -256;
		break;
	case 9:
		dw = -512;
		break;

	case 10:
		dw = -1048;
		break;

	case 11:
		dw = -2096;
		break;
	default:
		dw = 0;
	}

	m_channel2->SetLowerRange(dw);
}

void CMutexesDlg::OnUpperRangeCH2Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH2);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = 2;
		break;

	case 2:
		dw = 4;
		break;

	case 3:
		dw = 8;
		break;

	case 4:
		dw = 16;
		break;

	case 5:
		dw = 32;
		break;

	case 6:
		dw = 64;
		break;
	case 7:
		dw = 128;
		break;
	case 8:
		dw = 256;
		break;
	case 9:
		dw = 512;
		break;

	case 10:
		dw = 1048;
		break;

	case 11:
		dw = 2096;
		break;
	default:
		dw = 0;
	}

	m_channel2->SetUpperRange(dw);
}

void CMutexesDlg::OnLowerRangeCH3Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH3);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = -2;
		break;

	case 2:
		dw = -4;
		break;

	case 3:
		dw = -8;
		break;

	case 4:
		dw = -16;
		break;

	case 5:
		dw = -32;
		break;

	case 6:
		dw = -64;
		break;
	case 7:
		dw = -128;
		break;
	case 8:
		dw = -256;
		break;
	case 9:
		dw = -512;
		break;

	case 10:
		dw = -1048;
		break;

	case 11:
		dw = -2096;
		break;
	default:
		dw = 0;
	}

	m_channel3->SetLowerRange(dw);
}

void CMutexesDlg::OnUpperRangeCH3Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH3);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = 2;
		break;

	case 2:
		dw = 4;
		break;

	case 3:
		dw = 8;
		break;

	case 4:
		dw = 16;
		break;

	case 5:
		dw = 32;
		break;

	case 6:
		dw = 64;
		break;
	case 7:
		dw = 128;
		break;
	case 8:
		dw = 256;
		break;
	case 9:
		dw = 512;
		break;

	case 10:
		dw = 1048;
		break;

	case 11:
		dw = 2096;
		break;
	default:
		dw = 0;
	}

	m_channel3->SetUpperRange(dw);
}

void CMutexesDlg::OnLowerRangeCH4Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_LOWER_RANGE_CH4);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = -2;
		break;

	case 2:
		dw = -4;
		break;

	case 3:
		dw = -8;
		break;

	case 4:
		dw = -16;
		break;

	case 5:
		dw = -32;
		break;

	case 6:
		dw = -64;
		break;
	case 7:
		dw = -128;
		break;
	case 8:
		dw = -256;
		break;
	case 9:
		dw = -512;
		break;

	case 10:
		dw = -1048;
		break;

	case 11:
		dw = -2096;
		break;
	default:
		dw = 0;
	}

	m_channel4->SetLowerRange(dw);
}

void CMutexesDlg::OnUpperRangeCH4Change()
{

	double dw;
	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_UPPER_RANGE_CH4);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		dw = 0;
		break;

	case 1:
		dw = 2;
		break;

	case 2:
		dw = 4;
		break;

	case 3:
		dw = 8;
		break;

	case 4:
		dw = 16;
		break;

	case 5:
		dw = 32;
		break;

	case 6:
		dw = 64;
		break;
	case 7:
		dw = 128;
		break;
	case 8:
		dw = 256;
		break;
	case 9:
		dw = 512;
		break;

	case 10:
		dw = 1048;
		break;

	case 11:
		dw = 2096;
		break;
	default:
		dw = 0;
	}

	m_channel4->SetUpperRange(dw);
}

void CMutexesDlg::OnBaudChange()
{

	CComboBox* pBox = (CComboBox*) GetDlgItem(IDC_BAUD_CHANGE);
	int nCurSel = pBox->GetCurSel();

	switch (nCurSel)
	{
	case 0:
		m_nBaud = 1200;
		break;

	case 1:
		m_nBaud = 2400;
		break;

	case 2:
		m_nBaud = 4800;;
		break;

	case 3:
		m_nBaud = 9600;
		break;

	case 4:
		m_nBaud = 19200;
		break;

	case 5:
		m_nBaud = 38400;
		break;

	case 6:
		m_nBaud = 76800;
		break;
	
	default:
		m_nBaud = 9600;
	}

}


void CMutexesDlg::OnOpenEnableRS232()
{
	if(!m_RS232_enabled)
	{
		m_RS232_enabled=true;
		if(RS232Port!=NULL) RS232Port->Close();
		RS232Port = new CSerial();
		ASSERT(RS232Port);
		CString messag1 = "COMM1 FAILURE";
		CString messag2 =	"RS232 port";
		if(!RS232Port->Open(1, m_nBaud)) MessageBox(messag1, messag2);
		else
		{
			messag1  = "COMM1 OPENED";
			MessageBox(messag1, messag2);
			m_pPeekerThread->ResumeThread();
			m_pReaderThread->ResumeThread();
		}
	
	}//if not enabled
	else
	{
		//you also have to suspend the reader and the peeker threads
		m_pPeekerThread->SuspendThread();
		m_pReaderThread->SuspendThread();

		m_RS232_enabled=false;
		m_nBaud = 9600;
		if(RS232Port!=NULL) RS232Port->Close();

	}
}

void CMutexesDlg::repaint()
{
	OnPaint();
}
