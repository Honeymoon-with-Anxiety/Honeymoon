// threads.h : header file
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

class CMutexesDlg;

class CExampleThread : public CWinThread
{
	DECLARE_DYNCREATE(CExampleThread)
protected:
	CExampleThread();

public:
	CMutexesDlg* m_pOwner;
	BOOL m_bDone;
	void SetOwner(CMutexesDlg* pOwner) { m_pOwner = pOwner; };
};

/////////////////////////////////////////////////////////////////////////////
// CPeekerThread thread

class CPeekerThread : public CExampleThread
{
	//this thread is only peeking if there are any 
	//characters to read in the RS232 buffer

	DECLARE_DYNCREATE(CPeekerThread)
protected:
	CPeekerThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeekerThread)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPeekerThread();

	// Generated message map functions
	//{{AFX_MSG(CPeekerThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CDisplayThread thread

class CReaderThread : public CExampleThread
{
	DECLARE_DYNCREATE(CReaderThread)
protected:
	CReaderThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayThread)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReaderThread();

	// Generated message map functions
	//{{AFX_MSG(CDisplayThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
