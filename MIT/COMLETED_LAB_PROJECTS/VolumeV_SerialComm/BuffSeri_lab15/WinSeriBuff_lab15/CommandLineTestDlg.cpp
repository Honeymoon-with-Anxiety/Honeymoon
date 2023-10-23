// CommandLineTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CommandLineTest.h"
#include "CommandLineTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
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

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}
/////////////////////////////////////////////////////////////////////////////

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandLineTestDlg dialog

CCommandLineTestDlg::CCommandLineTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommandLineTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommandLineTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandLineTestDlg)
	DDX_Control(pDX, ID_EDT_RESPONSE, m_edtResponse);
	DDX_Control(pDX, ID_EDT_RECEIVED, m_edtReceived);
	DDX_Control(pDX, ID_LST_RECEIVED, m_lstReceived);
	//}}AFX_DATA_MAP
}
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCommandLineTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCommandLineTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_BTN_CLEAR, OnBtnClear)
  ON_NOTIFY(NM_COMMAND_SENT, ID_CTRL_COMMAND_LINE, OnCommandSent)
	ON_BN_CLICKED(ID_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_ENABLE_RS232, OnEnableRs232)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandLineTestDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CCommandLineTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

  CRect rcClient;
  GetWindowRect(&rcClient);
  rcClient.bottom = rcClient.top + 300;
  rcClient.right = rcClient.left + 700;
  MoveWindow(&rcClient);

  //  create the line plot control.
  UINT uiFlags = WS_CHILD | WS_VISIBLE | WS_TABSTOP;
  m_CommandLine.Create(CRect(0, 0, 1, 1), uiFlags, this, ID_CTRL_COMMAND_LINE);
  m_CommandLine.SetReceiver(this);
  m_CommandLine.SetFocus();
  m_CommandLine.SetOwner(this);
/*
  //  fill the command line with some data....
  for (UINT ii=0; ii<100; ii++)
  {
    CString szResponse;
    szResponse.Format("%d", ii);
    m_CommandLine.AddRecv(szResponse);
  }
*/
  //  size all controls correctly;
	SizeControls();



	m_pRS232Port=NULL;
	m_bEnabled_RS232 = false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
/////////////////////////////////////////////////////////////////////////////

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCommandLineTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}
/////////////////////////////////////////////////////////////////////////////

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCommandLineTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::SizeControls()
{
  CRect rcClient;
  GetClientRect(&rcClient);
  rcClient.left += 200;

  if (m_CommandLine.m_hWnd!=NULL)
    m_CommandLine.MoveWindow(200, 0, rcClient.Width(), rcClient.Height());

  if (m_lstReceived.m_hWnd!=NULL)
  {
    CRect rcArea;
    m_lstReceived.GetWindowRect(&rcArea);
    ScreenToClient(&rcArea);
    rcArea.bottom = rcClient.bottom;
    m_lstReceived.MoveWindow(rcArea.left, rcArea.top, rcArea.Width(), rcArea.Height());
  }
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	SizeControls();
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::OnCommandSent(NMHDR* pNMHDR, LRESULT* pResult)
{
  //  add this message to the notification list.
  m_lstReceived.AddString(_T("NM_COMMAND_SENT"));
  //  copy the last command to the edit box.
  m_edtReceived.SetWindowText(m_CommandLine.GetLastCommand());
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::OnBtnClear() 
{
	m_lstReceived.ResetContent();
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::OnBtnSend() 
{
  CString szResponse;
  m_edtResponse.GetWindowText(szResponse);
  m_CommandLine.AddRecv(szResponse);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLineTestDlg::OnEnableRs232() 
{	
	if(!m_bEnabled_RS232)
	{
		m_bEnabled_RS232 = true;
		
		//just in case
		if(m_pRS232Port!=NULL)
		{
			m_pRS232Port->Close();
			delete m_pRS232Port;
			m_pRS232Port= NULL;
		}

		m_pRS232Port = new CSerial();
		if(!m_pRS232Port) MessageBox("COULD NOT ALLOCATE RS232 PORT");
		else if(!m_pRS232Port->Open(1,9600))
		{
			MessageBox("COULD NOT OPEN RS232 PORT");
		}
	}
	else//you are enabled so you are disconnecting from the existing port
	{
		m_bEnabled_RS232=false;
		if(m_pRS232Port!=NULL)
		{
			m_pRS232Port->Close();
			delete m_pRS232Port;
			m_pRS232Port=NULL;
		}
	}
}//******************************************* end OnEnableRS232Port()
