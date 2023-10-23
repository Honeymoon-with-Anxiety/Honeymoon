// threads.cpp : implementation file
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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExampleThread, CWinThread)

CExampleThread::CExampleThread()
{
	m_bDone = FALSE;
	m_pOwner = NULL;
	m_bAutoDelete = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CCounterThread

IMPLEMENT_DYNCREATE(CPeekerThread, CExampleThread)

CPeekerThread::CPeekerThread()
{
}

CPeekerThread::~CPeekerThread()
{
}

BOOL CPeekerThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPeekerThread::Run()
{
	if (m_pOwner == NULL)return -1;

	CSingleLock sLock(&(m_pOwner->m_mutex));//just accessing

	while (!m_bDone)
	{	
		//checkif there are bytes to read from the Q
//sLock.Lock();
//		m_pOwner->repaint();
			
	}
	m_pOwner->PostMessage(WM_CLOSE, 0, 0L);
	return 0;
}

BEGIN_MESSAGE_MAP(CPeekerThread, CWinThread)
	//{{AFX_MSG_MAP(CPeekerThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeekerThread message handlers
/////////////////////////////////////////////////////////////////////////////
// CDisplayThread

IMPLEMENT_DYNCREATE(CReaderThread, CExampleThread)

CReaderThread::CReaderThread()
{
}

CReaderThread::~CReaderThread()
{
}

BOOL CReaderThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CReaderThread::Run()
{

	ASSERT(m_pOwner != NULL);
	if (m_pOwner == NULL)
		return -1;

	BYTE buff[4];
	while (!m_bDone)
	{
		if(m_pOwner->RS232Port->ReadDataWaiting()>=4)
		{
			m_pOwner->RS232Port->ReadData(buff,4);	
			m_pOwner->CBuff->insert(buff[0],0);//put first byte into channel 1 Q
			m_pOwner->CBuff->insert(buff[1],1);//put first byte into channel 2 Q
			m_pOwner->CBuff->insert(buff[2],2);//put first byte into channel 3 Q
			m_pOwner->CBuff->insert(buff[3],3);//put first byte into channel 4 Q
			m_pOwner->repaint();
		}
	}

	m_pOwner->PostMessage(WM_CLOSE, 0, 0L);

  return 0;
}

BEGIN_MESSAGE_MAP(CReaderThread, CWinThread)
	//{{AFX_MSG_MAP(CDisplayThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayThread message handlers
