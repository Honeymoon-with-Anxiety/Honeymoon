// mutexesDlg.h : header file
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

class CPeekerThread;	//peeks into the RS232 buffer
class CReaderThread;
class CSerial;
class CSeriBuffer;
class COScopeCtrl;

/////////////////////////////////////////////////////////////////////////////
// CMutexesDlg dialog

class CMutexesDlg : public CDialog
{
// Construction
public:
	CMutexesDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
	//{{AFX_DATA(CMutexesDlg)
	enum { IDD = IDD_MUTEXES_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMutexesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void repaint();
	CSerial* RS232Port;
	CSeriBuffer* CBuff;
	CString m_strNumber;

	CMutex m_mutex;

	CPeekerThread* m_pPeekerThread;
	CReaderThread* m_pReaderThread;

	COScopeCtrl* m_channel1;
	COScopeCtrl* m_channel2;
	COScopeCtrl* m_channel3;
	COScopeCtrl* m_channel4;
// Implementation
protected:
	bool m_RS232_enabled;
	int m_nBaud;
	
	

	HICON m_hIcon;

	//variables to enable channels 1 through 4
	bool m_chn1_enable;
	bool m_chn2_enable;
	bool m_chn3_enable;
	bool m_chn4_enable;

	// Generated message map functions
	//{{AFX_MSG(CMutexesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnEnableCH1();
	afx_msg void OnEnableCH2();
	afx_msg void OnEnableCH3();
	afx_msg void OnEnableCH4();
	afx_msg void OnLowerRangeCH1Change();
	afx_msg void OnUpperRangeCH1Change();
	afx_msg void OnLowerRangeCH2Change();
	afx_msg void OnUpperRangeCH2Change();
	afx_msg void OnLowerRangeCH3Change();
	afx_msg void OnUpperRangeCH3Change();
	afx_msg void OnLowerRangeCH4Change();
	afx_msg void OnUpperRangeCH4Change();
	afx_msg void OnBaudChange();
	afx_msg void OnNumDemux();
	afx_msg void OnOpenEnableRS232();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
