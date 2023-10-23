// CommandLineTestDlg.h : header file
//

#if !defined(AFX_COMMANDLINETESTDLG_H__2B7C15E7_EF20_49C5_A59A_100B36A474EA__INCLUDED_)
#define AFX_COMMANDLINETESTDLG_H__2B7C15E7_EF20_49C5_A59A_100B36A474EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCommandLineTestDlg dialog


#include "CommandLine.h"
#include "Serial.h"
#include <math.h>

#define ID_CTRL_COMMAND_LINE (WM_USER+1001)

class CCommandLineTestDlg : public CDialog
{
  // Construction/Destruction
  public:
	  CCommandLineTestDlg(CWnd* pParent = NULL);	// standard constructor

  private:
    void SizeControls();

  // Dialog Data
  public:	  
		CSerial* m_pRS232Port;
		 bool m_bEnabled_RS232;

	  //{{AFX_DATA(CCommandLineTestDlg)
	enum { IDD = IDD_COMMANDLINETEST_DIALOG };
	CEdit	m_edtResponse;
	CEdit	m_edtReceived;
    CCommandLine m_CommandLine;
	  CListBox	m_lstReceived;
	//}}AFX_DATA

	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CCommandLineTestDlg)
	protected:
	  virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

  // Implementation
  protected:
	  HICON m_hIcon;

	  // Generated message map functions
	  //{{AFX_MSG(CCommandLineTestDlg)
			virtual BOOL OnInitDialog();
			afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
			afx_msg void OnPaint();
			afx_msg HCURSOR OnQueryDragIcon();
			afx_msg void OnSize(UINT nType, int cx, int cy);
  			afx_msg void OnBtnClear();
			afx_msg void OnCloseupCmbStyle();
			afx_msg void OnCommandSent(NMHDR* pNMHDR, LRESULT* pResult);
			afx_msg void OnBtnSend();
			afx_msg void OnEnableRs232();
	//}}AFX_MSG
	  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDLINETESTDLG_H__2B7C15E7_EF20_49C5_A59A_100B36A474EA__INCLUDED_)
