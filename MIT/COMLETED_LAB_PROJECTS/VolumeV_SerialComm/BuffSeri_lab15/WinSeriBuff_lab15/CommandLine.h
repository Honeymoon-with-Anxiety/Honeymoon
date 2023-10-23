//  CommandLine.h : header file
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//  CommandLine - a simple command line interface control with 
//  a custom scrollbar
//
//  Author: Paul Grenz
//  Email:  pgrenz@irlabs.com
//
//  You may freely use or modify this code provided this
//  message is included in all derived versions.
//
//  History - 2004/10/28 Initial release to codeguru.com
//
//
//  This class implements a command line interface with a custom 
//  KDE/Unix-like scrollbar
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDLINE_H__0D53DA45_B989_482B_8615_81F1D7115A60__INCLUDED_)
#define AFX_COMMANDLINE_H__0D53DA45_B989_482B_8615_81F1D7115A60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CommandLine window
/////////////////////////////////////////////////////////////////////////////

//  notification message.
#define NM_COMMAND_SENT WM_USER+41

//  name of the class.
#define COMMAND_LINE_CLASSNAME (_T("CommandLine"))

#include <vector>

class CCommandLineTestDlg;

class CCommandLine : public CWnd
{
  //  constants.
  static enum
  {
    ID_EVENT_INCR =           (WM_USER+1),
    ID_EVENT_DECR =           (WM_USER+2),
    MAX_SCROLLBACK_SIZE =     100,
    MAX_DISPLAY_SIZE =        1000,
  };

  // Construction/Destruction
  public:
	  CCommandLine();
	  virtual ~CCommandLine();

  //  attributes.
  public:
    std::vector<CString>      m_vecLines;
    std::vector<CString>      m_vecInput;
    CFont                     m_fonText;
    CPen                      m_penArrows;
    CPen                      m_penShadow;
    CBrush                    m_brFace;
    CString                   m_szInputLine;
    CString                   m_szLastCommand;
    CString                   m_szPrompt;
    CString                   m_szClsCmd;
    int                       m_nCaretPosX;
    CPoint                    m_ptCaret;
    bool                      m_oCaretPositioned;
    bool                      m_oMouseDownThumb;
    int                       m_nInputPos;
    int                       m_nLineIndex;
    int                       m_nTabSpaces;
    int                       m_nVisibleLines;
    CWnd                      *m_pwndReceiver;
    bool                      m_oScrollUpTopPressed;
    bool                      m_oScrollUpPressed;
    bool                      m_oScrollDnPressed;
    CRect                     m_rcScrollBar;
    CRect                     m_rcScrollTrack;
    CRect                     m_rcScrollUpTop;
    CRect                     m_rcScrollUp;
    CRect                     m_rcScrollDn;
    CRect                     m_rcThumb;
    int                       m_nMinThumbY;
    int                       m_nThumbStartPos;
    bool                      m_oIsLocked;


  // Methods
  public:
  	BOOL                      Create(const RECT& rect, UINT uiFlags, CWnd* pwndParent, UINT uiID);
    int                       AddRecv(CString szText);
    int                       AddRecv(char *pcText, ULONG unLength);
    int                       AddSent(CString szText);
    int                       AddSent(char *pcText, ULONG unLength);
    int                       UpdateLine(int nIndex, CString szText);
    bool                      ClearScreen();
    bool                      RegisterWindowClass();

  //  attributes get/set
  public:
    CString                   GetLastCommand() { return m_szLastCommand; };
    void                      SetPrompt(CString szPrompt) { m_szPrompt = szPrompt; Invalidate(); };
    CString                   GetPrompt() { return m_szPrompt; };
    void                      SetClsCommand(CString szClsCmd) { m_szClsCmd = szClsCmd; };
    CString                   GetClsCommand() { return m_szClsCmd; };
    void                      SetTabSpaces(long nTabSpaces) { m_nTabSpaces = (nTabSpaces>0) ? (nTabSpaces) : (1); };
    int                       GetTabSpaces() { return m_nTabSpaces; };
    void                      SetReceiver(CWnd *pwndReceiver) { m_pwndReceiver = pwndReceiver; };
    CWnd*                     GetReceiver() { return m_pwndReceiver; };
    bool                      GetLocked() { return m_oIsLocked; };
    void                      SetLocked(bool oLock) { m_oIsLocked = oLock; };
    void                      SendChar(UINT nChar, UINT nRepCnt, UINT nFlags);    

  //  notifications
  private:
    void                      EmitCommandSent();

    //  functions.
  private:
    int                       ScreenPosFromLineIndex(int nLineIndex);
    int                       LineIndexFromScreenPos(int nScreenPos);

  // Overrides
  public:
	  void SetOwner(CCommandLineTestDlg* p);
	  CCommandLineTestDlg* m_pOwner;
	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CCommandLine)
	  //}}AFX_VIRTUAL

	// Generated message map functions
  protected:
	  //{{AFX_MSG(CCommandLine)
	  afx_msg void OnPaint();
    afx_msg void OnSysColorChange();
	  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  	afx_msg void OnKillFocus(CWnd* pNewWnd);
	  afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);    
    afx_msg void OnKeyDown(UINT uiChar, UINT uiRepCnt, UINT uiFlags);
		afx_msg void OnTimer(UINT nIDEvent);
	  afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg UINT OnGetDlgCode();
	  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	  afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	  //}}AFX_MSG

	  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDLINE_H__0D53DA45_B989_482B_8615_81F1D7115A60__INCLUDED_)
