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

class CSerial;

class CExampleThread : public CWinThread
{
	DECLARE_DYNCREATE(CExampleThread)
protected:
	CExampleThread();

public:
	CSerial* m_pOwner;
	BOOL m_bDone;
	void SetOwner(CSerial* pOwner) { m_pOwner = pOwner; };
};

/////////////////////////////////////////////////////////////////////////////
// CCounterThread thread

class COutputThread : public CExampleThread
{
	DECLARE_DYNCREATE(COutputThread)
protected:
	COutputThread();           // protected constructor used by dynamic creation

// Attributes
public:
	unsigned char*	buffer_out;
	int		buffer_out_length;
	int		cur_byte;
// Operations
public:
	void SetBufferOut(CString& S);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputThread)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputThread();

	// Generated message map functions
	//{{AFX_MSG(COutputThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CInputThread thread

class CInputThread : public CExampleThread
{
	DECLARE_DYNCREATE(CInputThread)
protected:
	CInputThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CString ReadLine; //in principle the read buffer
	BOOL m_bX_OFF;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputThread)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInputThread();

	// Generated message map functions
	//{{AFX_MSG(CDisplayThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
