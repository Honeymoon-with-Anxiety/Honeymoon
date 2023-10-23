//  CommandLine.cpp : implementation file
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

#include "stdafx.h"
#include "MemDc.h"
#include "CommandLine.h"
#include "CommandLineTest.h"
#include "CommandLineTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CommandLine
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCommandLine, CWnd)
	//{{AFX_MSG_MAP(CCommandLine)
  ON_WM_PAINT()
  ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
  ON_WM_KILLFOCUS()
  ON_WM_SETFOCUS()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_CHAR()
  ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_SIZE()
  ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
  ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

// Register the window class if it has not already been registered.
bool CCommandLine::RegisterWindowClass()
{
  WNDCLASS wndcls;
  HINSTANCE hInst = AfxGetInstanceHandle();
  //  HINSTANCE hInst = AfxGetResourceHandle();

  if (!(::GetClassInfo(hInst, COMMAND_LINE_CLASSNAME, &wndcls)))
  {
    //  otherwise we need to register a new class
    wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc      = ::DefWindowProc;
    wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
    wndcls.hInstance        = hInst;
    wndcls.hIcon            = NULL;
    wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
    wndcls.lpszMenuName     = NULL;
    wndcls.lpszClassName    = COMMAND_LINE_CLASSNAME;

    if (!AfxRegisterClass(&wndcls))
    {
      AfxThrowResourceException();
      return FALSE;
    }
  }
  return TRUE;
}
/////////////////////////////////////////////////////////////////////////////

CCommandLine::CCommandLine()
{
  RegisterWindowClass();

  //  no reciever yet.
  m_pwndReceiver = NULL;
  //  create a default prompt.
  m_szPrompt = "Command: ";
  //  create the drawing objects to use.
  m_penArrows.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWTEXT));
  m_penShadow.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
  m_brFace.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
  //  create the font to use.
  LOGFONT lf;
  // Get a handle to the ANSI_FIXED_FONT.
  GetObject(GetStockObject(ANSI_FIXED_FONT), sizeof(LOGFONT), &lf);
  // Set the font attributes, as appropriate.
  lf.lfWeight = FW_NORMAL;
  //  make the font a bit bigger.
  lf.lfHeight *= 2;
  // Create the font, and then return its handle.
  m_fonText.CreateFontIndirect(&lf);
  //  set the input text.
  m_szInputLine = "";
  //  the initial caret position.
  m_nCaretPosX = 0;
  //  holds the position set for the caret by the mouse.
  m_ptCaret = CPoint(0, 0);
  //  was the caret positioned by the mouse?
  m_oCaretPositioned = false;
  //  set the command list index to -1.
  m_nInputPos = -1;
  //  there is no history yet.
  m_nLineIndex = -1;
  //  default number of spaces for each tab.
  m_nTabSpaces = 2;
  //  init last command.
  m_szLastCommand = "";
  //  how many lines can we see?
  m_nVisibleLines = 0;
  //  the default clear screen command.
  m_szClsCmd = "cls";
  //  the rectangles that hold the scroll buttons positions.
  m_rcScrollUpTop.SetRectEmpty();
  m_rcScrollUp.SetRectEmpty();
  m_rcScrollDn.SetRectEmpty();
  m_rcThumb.SetRectEmpty();
  m_rcScrollBar.SetRectEmpty();
  m_rcScrollTrack.SetRectEmpty();
  //  the scroll buttons are not pressed.
  m_oScrollUpTopPressed = false;
  m_oScrollUpPressed = false;
  m_oScrollDnPressed = false;
  //  the thumb is not being moved....
  m_oMouseDownThumb = false;
  //  where the thumb was dragged from.
  m_nThumbStartPos = 0;
  //  thumb min size.
  m_nMinThumbY = 0;
  //  not locked to start with.
  m_oIsLocked = false;
}
/////////////////////////////////////////////////////////////////////////////

CCommandLine::~CCommandLine()
{
  //  let go of the mouse
  ReleaseCapture();

  //  destroy the drawing objects.
  m_penArrows.DeleteObject();
  m_penShadow.DeleteObject();
  m_brFace.DeleteObject();
}
/////////////////////////////////////////////////////////////////////////////

BOOL CCommandLine::Create(const RECT &rect, UINT uiFlags, CWnd *pParentWnd, UINT uiID)
{
	return CWnd::Create(NULL, _T("CommandLine"), uiFlags, rect, pParentWnd, uiID);
}
/////////////////////////////////////////////////////////////////////////////

BOOL CCommandLine::OnEraseBkgnd(CDC* pDC)
{
  //  to eliminate flicker....
  return -1;
}
/////////////////////////////////////////////////////////////////////////////
    
int CCommandLine::UpdateLine(int nIndex, CString szText)
{
  if (nIndex<0 || nIndex>=m_vecLines.size())
    return -1;
  else
  {
    m_vecLines.at(nIndex) = szText;
    return nIndex;
  }
}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::AddRecv(CString szText)
{
  //  if display is full, remove the first line.
  if (m_vecLines.size()>MAX_DISPLAY_SIZE-1)
  {
    m_vecLines.erase(m_vecLines.begin());
  }
  //  add the line to the vector.
  m_vecLines.push_back(" MCU: " + szText);
  //  set the current line.
  m_nLineIndex = m_vecLines.size()-1;
  //  update the screen pos.
  m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
  //  redraw the control.
  Invalidate(FALSE);
  //  finished okay.
  return m_nLineIndex;
}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::AddRecv(char *pcText, ULONG unLength)
{
  //  if display is full - remove the first line.
  if (m_vecLines.size()>MAX_DISPLAY_SIZE-1)
  {
    m_vecLines.erase(m_vecLines.begin());
  }
  //  copy the text from the array of char
  //  to a string, making sure to handle unprintable chars.
  CString szText;
  for (ULONG ii=0; ii<unLength; ii++)
  {
    int iCurr = (int)(pcText[ii]);
    switch (iCurr)
    {
      case 0: szText += "0x0 "; break;
      default: szText += (char)(iCurr);
    }
  }
  //  add the line to the vector.
  m_vecLines.push_back(" MCU: " + szText);
  //  set the current line.
  m_nLineIndex = m_vecLines.size()-1;
  //  update the screen pos.
  m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
  //  redraw the control.
  Invalidate(FALSE);
  //  finished okay.
  return m_nLineIndex;
}
/////////////////////////////////////////////////////////////////////////////

bool CCommandLine::ClearScreen()
{
  //  clear the line vector.
  m_vecLines.clear();
  //  set the line index to reflect this.
  m_nLineIndex = -1;
  //  clear the line.
  m_szInputLine.Empty();
  //  caret at the front.
  m_nCaretPosX = 0;
  //  redraw the empty window.
  Invalidate(FALSE);
  return true;
}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::AddSent(CString szText)
{
  //  if display is full, remove the first line.
  if (m_vecLines.size()>MAX_DISPLAY_SIZE-1)
  {
    m_vecLines.erase(m_vecLines.begin());
  }
  //  add the line to the vector.
  m_vecLines.push_back(" PC: " + szText);
  //  is this the clear screen command?
  if (szText==m_szClsCmd)
    ClearScreen();
  //  set the current line.
  m_nLineIndex = m_vecLines.size()-1;
  //  update the screen pos.
  m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
  //  redraw the control.
  Invalidate(FALSE);
  //  finished okay.
  return m_nLineIndex;
}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::AddSent(char *pcText, ULONG unLength)
{
  //  if vector is full, remove the first line.
  if (m_vecLines.size()>MAX_DISPLAY_SIZE-1)
  {
    m_vecLines.erase(m_vecLines.begin());
  }
  //  copy the text from the array of char
  //  to a string, making sure to handle unprintable chars.
  CString szText;
  for (ULONG ii=0; ii<unLength; ii++)
  {
    int iCurr = (int)(pcText[ii]);
    switch (iCurr)
    {
      case 0: szText += "0x0 "; break;
      default: szText += (char)(iCurr);
    }
  }
  //  add the line to the vector.
  m_vecLines.push_back(" PC: " + szText);
  //  is this the clear screen command?
  if (szText==m_szClsCmd)
    ClearScreen();
  //  set the current line.
  m_nLineIndex = m_vecLines.size()-1;
  //  update the screen pos.
  m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
  //  redraw the control.
  Invalidate(FALSE);
  //  finished okay.
  return m_nLineIndex;
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnSysColorChange()
{
  //  destroy the drawing objects.
  m_penArrows.DeleteObject();
  m_penShadow.DeleteObject();
  m_brFace.DeleteObject();
  //  recreate the drawing objects to use.
  m_penArrows.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWTEXT));
  m_penShadow.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
  m_brFace.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnPaint()
{
  // device context for painting
  CPaintDC dc(this);

  //  create a memory dc.
  CMemDC dcMem(&dc);

  //  save their states.
  int nMemState = dcMem.SaveDC();
  int nDcState = dc.SaveDC();

  //  get the client rect.
  CRect rcClient;
  GetClientRect(rcClient);

  //  how wide & high is a scrollbar?
  SIZE siScroll;
  siScroll.cx = GetSystemMetrics(SM_CXVSCROLL);
  siScroll.cy = GetSystemMetrics(SM_CYVSCROLL);

  //  get the area to do the drawing in.
  CRect rcDisplay = rcClient;
  rcDisplay.DeflateRect(2, 2, siScroll.cx+2, 2);

  //  create the scrollbar rect.
  m_rcScrollBar = rcClient;
  m_rcScrollBar.DeflateRect(2, 2, 2, 2);
  m_rcScrollBar.left = rcDisplay.right;

  //  thumb min size in Y.
  m_nMinThumbY = siScroll.cy/2;

  //  create the scrollbar up top button rect
  m_rcScrollUpTop = m_rcScrollBar;
  m_rcScrollUpTop.top = m_rcScrollBar.top;
  m_rcScrollUpTop.bottom = m_rcScrollBar.top + siScroll.cy;

  //  create the scrollbar up button rect
  m_rcScrollUp = m_rcScrollBar;
  m_rcScrollUp.top = m_rcScrollBar.bottom - 2 * siScroll.cy;
  m_rcScrollUp.bottom = m_rcScrollBar.bottom - siScroll.cy;

  //  create the scrollbar dn button rect
  m_rcScrollDn = m_rcScrollBar;
  m_rcScrollDn.top = m_rcScrollBar.bottom - siScroll.cy;

  //  create a rect for the scroll track area.
  m_rcScrollTrack = m_rcScrollBar;
  m_rcScrollTrack.top += siScroll.cy + m_nMinThumbY;  //  one button on the top.
  m_rcScrollTrack.bottom -= 2 * siScroll.cy;  //  two buttons on the bottom.

  //  first select the font we want to use into the DC.
  CFont *pfonOld = dcMem.SelectObject(&m_fonText);

  //  then get the size of the input text.
  CSize siText = dcMem.GetTextExtent(m_szPrompt + m_szInputLine.Left(m_nCaretPosX));

  //  create a rect to hold the input line.
  CRect rcInputLine(rcDisplay);

  //  shrink the display so that it does not include the input line.
  rcDisplay.bottom -= siText.cy;
  //  shrink the input line so that it does not include the display.
  rcInputLine.top = rcInputLine.bottom - siText.cy;

  //  figure out how many whole lines will fit in the display area.
  m_nVisibleLines = (int)(rcDisplay.Height()/(siText.cy));

  //  what is the ratio of the track size to the number of lines?
  double xScrollRatio = (double)(m_rcScrollTrack.Height())/(double)(m_vecLines.size());
  //  calculate the number of visible lines in pixels = thumb size.
  int nThumbSize = m_nMinThumbY + (int)(xScrollRatio * (double)(m_nVisibleLines));

  //  is the the thumb at zero? (should be at the bottom, then)
  if (m_rcThumb.bottom == 0)
    m_rcThumb.bottom = m_rcScrollTrack.bottom;

  //  are there any lines at all?
  m_rcThumb.left = m_rcScrollTrack.left;
  m_rcThumb.right = m_rcScrollTrack.right;
  if (m_vecLines.size() > m_nVisibleLines)
  {
    m_rcThumb.top = m_rcThumb.bottom - nThumbSize;
  }
  else
  {
    m_rcThumb.bottom = m_rcScrollTrack.bottom;
    m_rcThumb.top = m_rcScrollTrack.top - m_nMinThumbY;
  }

  //  calculate a rect to hold one display line.
  CRect rcText(rcInputLine);
  rcText.OffsetRect(0, -siText.cy);

  //  if the mouse repositioned the caret,
  //  we must figure out where it should be drawn.
  if (m_oCaretPositioned==true)
  {
    CSize siPrompt = dcMem.GetTextExtent(m_szPrompt);
    CSize siInput = dcMem.GetTextExtent(m_szInputLine);
    int nChars = m_szInputLine.GetLength();
    int nAveCharWidth = (nChars>0) ? (siInput.cx / nChars) : (0);
    //  get the position in the input clicked on.
    int nPosX = m_ptCaret.x - siPrompt.cx;
    m_nCaretPosX = (nAveCharWidth>0) ? (nPosX / nAveCharWidth) : (0);
    m_nCaretPosX = (m_nCaretPosX>nChars) ? (nChars) : (m_nCaretPosX);
    m_oCaretPositioned = false;
  }

  //  draw the scrollbar background.
  dcMem.FillSolidRect(m_rcScrollBar, GetSysColor(COLOR_SCROLLBAR));

  //  select a pen & brush to draw the buttons.
  CPen *ppenOld = dcMem.SelectObject(&m_penShadow);
  CBrush *pbrOld = dcMem.SelectObject(&m_brFace);

  //  draw the thumb.
  dcMem.FillSolidRect(m_rcThumb, GetSysColor(COLOR_3DFACE));
  dcMem.DrawEdge(m_rcThumb, EDGE_RAISED, BF_RECT);

  //  draw the buttons as though they are down.
  dcMem.Rectangle(m_rcScrollUpTop);
  dcMem.Rectangle(m_rcScrollUp);
  dcMem.Rectangle(m_rcScrollDn);

  //  is the up top button NOT pressed (draw raised edge).
  if (m_oScrollUpTopPressed==false)
    dcMem.DrawEdge(m_rcScrollUpTop, EDGE_RAISED, BF_RECT);

  //  is the up bottom button NOT pressed (draw raised edge).
  if (m_oScrollUpPressed==false)
    dcMem.DrawEdge(m_rcScrollUp, EDGE_RAISED, BF_RECT);

  //  is the dn button NOT pressed (draw raised edge).
  if (m_oScrollDnPressed==false)
    dcMem.DrawEdge(m_rcScrollDn, EDGE_RAISED, BF_RECT);

  //  select the pen we wish to use for the arrows.
  dcMem.SelectObject(&m_penArrows);

  POINT ptCenter;

  //  draw the scrollbar up top arrow.
  ptCenter = m_rcScrollUpTop.CenterPoint();
  ptCenter.x += (m_oScrollUpTopPressed==true) ? (1) : (0);
  ptCenter.y += (m_oScrollUpTopPressed==true) ? (1) : (0);
  dcMem.MoveTo(ptCenter);
  dcMem.LineTo(ptCenter.x, ptCenter.y-1);
  dcMem.LineTo(ptCenter.x+2, ptCenter.y+1);
  dcMem.LineTo(ptCenter.x-2, ptCenter.y+1);
  dcMem.LineTo(ptCenter.x, ptCenter.y-1);

  //  draw the scrollbar up bottom arrow.
  ptCenter = m_rcScrollUp.CenterPoint();
  ptCenter.x += (m_oScrollUpPressed==true) ? (1) : (0);
  ptCenter.y += (m_oScrollUpPressed==true) ? (1) : (0);
  dcMem.MoveTo(ptCenter);
  dcMem.LineTo(ptCenter.x, ptCenter.y-1);
  dcMem.LineTo(ptCenter.x+2, ptCenter.y+1);
  dcMem.LineTo(ptCenter.x-2, ptCenter.y+1);
  dcMem.LineTo(ptCenter.x, ptCenter.y-1);

  //  draw the scrollbar dn arrow.
  ptCenter = m_rcScrollDn.CenterPoint();
  ptCenter.x += (m_oScrollDnPressed==true) ? (1) : (0);
  ptCenter.y += (m_oScrollDnPressed==true) ? (1) : (0);
  dcMem.MoveTo(ptCenter);
  dcMem.LineTo(ptCenter.x, ptCenter.y+1);
  dcMem.LineTo(ptCenter.x-2, ptCenter.y-1);
  dcMem.LineTo(ptCenter.x+2, ptCenter.y-1);
  dcMem.LineTo(ptCenter.x, ptCenter.y+1);

  //  paint the background.
  dcMem.FillSolidRect(rcDisplay, RGB(255,0,0));//GetSysColor(COLOR_WINDOW));

  //  paint the input line.
  dcMem.FillSolidRect(rcInputLine, RGB(0,0,0));//GetSysColor(COLOR_WINDOW));

  //  draw the sunken edge.
  dcMem.DrawEdge(rcClient, EDGE_SUNKEN, BF_RECT);

  //  set the color of all text.
  dcMem.SetBkMode(TRANSPARENT);
  dcMem.SetTextColor(RGB(0,255,0));//GetSysColor(COLOR_WINDOWTEXT));

  //  print out the input line on the bottom.
  BOOL oResult = dcMem.ExtTextOut(rcInputLine.left, rcInputLine.top,
      ETO_CLIPPED, rcInputLine, m_szPrompt + m_szInputLine, NULL);

  //  is there any space left?
  if (m_nVisibleLines>0)
  {
    // print out the lines.
    CString szText;
    int ii = m_nLineIndex;
    while (rcText.top>rcDisplay.top && ii>=0)
    {
      if (ii>=0 && ii<m_vecLines.size())
      {
        szText = m_vecLines.at(ii);
        oResult = dcMem.ExtTextOut(rcText.left, rcText.top,
            ETO_CLIPPED, rcText, szText, NULL);
        //  move the rect.
        rcText.OffsetRect(0, -siText.cy);
      }
      ii--;
    }

    //  set the cursor position after the input text.
    CPoint ptCaret(siText.cx, rcInputLine.top);
    CreateSolidCaret(2, siText.cy);
    SetCaretPos(ptCaret);
  }

  //  select the old font back
  dcMem.SelectObject(pfonOld);

  //  select the old pen back.
  dcMem.SelectObject(ppenOld);

  //  select the old brush back.
  dcMem.SelectObject(pbrOld);

  //  restore their states.
  dcMem.RestoreDC(nMemState);
  dc.RestoreDC(nDcState);

}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
  SetFocus();
	
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnSetFocus(CWnd* pOldWnd)
{
  CWnd::OnSetFocus(pOldWnd);

  SetCapture();
  ShowCaret();
}
///////////////////////////////////////////////////////////////////

void CCommandLine::OnKillFocus(CWnd* pNewWnd)
{
  CWnd::OnKillFocus(pNewWnd);

  HideCaret();
  DestroyCaret();

  //  let go of the mouse
  ReleaseCapture();
}
///////////////////////////////////////////////////////////////////

UINT CCommandLine::OnGetDlgCode()
{
  return CWnd::OnGetDlgCode() |
    //DLGC_WANTARROWS | 
    //DLGC_WANTCHARS |
    //DLGC_WANTMESSAGE |
    //DLGC_WANTTAB |
    DLGC_WANTALLKEYS;
}
///////////////////////////////////////////////////////////////////

void CCommandLine::SendChar(UINT uiChar, UINT uiRepCnt, UINT uiFlags)
{
  OnChar(uiChar, uiRepCnt, uiFlags);
}
///////////////////////////////////////////////////////////////////

void CCommandLine::OnChar(UINT uiChar, UINT uiRepCnt, UINT uiFlags)
{
  if (m_oIsLocked==false)
  {
    int nInputLength = m_szInputLine.GetLength();
    CString szLeft;
    CString szRight;
    int nRepeat = 1;
    int ii =0;

    switch (uiChar)
    {
      case VK_BACK:       //  backspace.
        break;
      case VK_RETURN:     //  return key
        break;
      case VK_TAB:        //  tab key - insert spaces.
        //  place the number spaces in the current caret position.
        nRepeat = m_nTabSpaces;
        uiChar = ' ';
      default:
        //  place the new char(s) in the current caret position.
        for (ii=0; ii<nRepeat; ii++)
        {
          szLeft = m_szInputLine.Left(m_nCaretPosX);
          szRight = m_szInputLine.Right(nInputLength-m_nCaretPosX);
          m_szInputLine = szLeft + CString(uiChar) + szRight;
          m_nCaretPosX++;
        }
        break;
    }

    Invalidate(FALSE);

    CWnd::OnChar(uiChar, uiRepCnt, uiFlags);
  }
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnKeyDown(UINT uiChar, UINT uiRepCnt, UINT uiFlags)
{
  if (m_oIsLocked==false)
  {
    int nInputLength = m_szInputLine.GetLength();
    CString szLeft;
    CString szRight;
    int nCommands = m_vecInput.size();
    CString szCommand;
    int nThumbHeight = 0;

	//simple version
	//serial comms for the shell
	CString S="";
	char send_buff[64];
	char rec_buff[64];
	int t=0;
	int i=0;
	int to_transmit=0;
	int num_transmitted=0;
	int received=0;
	int to_receive=0;
	//serial comms for the shell
	
/*
	//the handshake version doesn't work
	int i;
	std::string received_line = "";
	std::string send_line="";
	CString a;
	BOOL got_XOFF=false;
*/

    switch (uiChar)
    {
      case VK_HOME:       // Home
        m_nCaretPosX = 0;
        break;

      case VK_END:        // End
        m_nCaretPosX = nInputLength;
        break;

      case VK_PRIOR:
        m_nLineIndex -= m_nVisibleLines;
        //  make sure it is safe.
        m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
        m_nLineIndex = max(m_nVisibleLines-1, m_nLineIndex);
        nThumbHeight = m_rcThumb.Height();
        m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
        m_rcThumb.top = m_rcThumb.bottom - nThumbHeight;
        break;

      case VK_NEXT:
        m_nLineIndex += m_nVisibleLines;
        //  make sure it is safe.
        m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
        m_nLineIndex = max(m_nVisibleLines-1, m_nLineIndex);
        //m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
        nThumbHeight = m_rcThumb.Height();
        m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
        m_rcThumb.top = m_rcThumb.bottom - nThumbHeight;
        break;

      case VK_UP:      // command list up.
      case VK_F3:
        if (nCommands>0)
        {
          m_szInputLine = m_vecInput.at(m_nInputPos);
          m_nInputPos--;
          m_nInputPos = (m_nInputPos<0) ? (nCommands-1) : (m_nInputPos);
          m_nCaretPosX = m_szInputLine.GetLength();
        }
        break;

      case VK_DOWN:       // command list down.
        if (nCommands>=0)
        {
          m_szInputLine = m_vecInput.at(m_nInputPos);
          m_nInputPos++;
          m_nInputPos = (m_nInputPos>=nCommands) ? (0) : (m_nInputPos);
          m_nCaretPosX = m_szInputLine.GetLength();
        }
        break;

      case VK_LEFT:       // Left arrow
        m_nCaretPosX = m_nCaretPosX - uiRepCnt;
        m_nCaretPosX = (m_nCaretPosX>0) ? (m_nCaretPosX) : (0);
        break;

      case VK_RIGHT:      //  command buffer up.
        m_nCaretPosX = m_nCaretPosX + uiRepCnt;
        m_nCaretPosX = (m_nCaretPosX>nInputLength) ? (nInputLength) : (m_nCaretPosX);
        break;

      case VK_DELETE:     // Delete
        szLeft = m_szInputLine.Left(m_nCaretPosX);
        szRight = m_szInputLine.Right(nInputLength-m_nCaretPosX-1);
        m_szInputLine = szLeft + szRight;
        break;

      case VK_BACK:  //  backspace.
        szLeft = m_szInputLine.Left(m_nCaretPosX-1);
        szRight = m_szInputLine.Right(nInputLength-m_nCaretPosX);
        m_szInputLine = szLeft + szRight;
        m_nCaretPosX = (m_nCaretPosX>0) ? (m_nCaretPosX-1) : (0);
        break;

      case VK_RETURN:
        //  add the current input line to the command list.
        if (m_vecInput.size()>MAX_SCROLLBACK_SIZE-1)
          m_vecInput.erase(m_vecInput.begin());
        m_vecInput.push_back(m_szInputLine);
        //  set the command index to the end.
        m_nInputPos = m_vecInput.size()-1;
        //  add the entered text to the display buffer.
        AddSent(m_szInputLine);
        //  save as last command;
        m_szLastCommand = m_szInputLine;
		
        //  clear the line.
        m_szInputLine.Empty();
        m_nCaretPosX = 0;
        //  notify the receiver that a command was sent.
        EmitCommandSent();

		//you might expect the size of a response to a command
		//to be set here...
		//simple version 
		to_transmit = m_szLastCommand.GetLength();

		for(i =0;i<to_transmit;i++) send_buff[i]=m_szLastCommand[i];
			
			num_transmitted=0;
			while(num_transmitted<to_transmit)
			{
				t = m_pOwner->m_pRS232Port->
					SendData(send_buff+num_transmitted, 
					to_transmit-num_transmitted);
				 num_transmitted+=t;
			}
		
			to_receive = to_transmit;
			received=0;

			while(received<to_receive)
			{	
				t=m_pOwner->m_pRS232Port->
					ReadData(rec_buff+received,to_receive-received);
				received+=t;
			}
			m_pOwner->m_CommandLine.AddRecv(rec_buff,to_receive);
		/*

		received_line="";
		send_line=m_szLastCommand;

		
//		while(!
		m_pOwner->m_pRS232Port->
			SendLineSWHandshake(*(m_pOwner->m_pRS232Port),
					send_line,received_line,got_XOFF);//)
//		{
//			CString report = "\n		waiting for XON from MCU...\n";
//			m_pOwner->m_CommandLine.AddRecv(report);
//		}
//
		for(i=0;i<received_line.length();i++)
		a+=received_line[i];
		m_pOwner->m_CommandLine.AddRecv(a);
*/
        break;

      default:
        break;
    }
    Invalidate(FALSE);

    CWnd::OnKeyDown(uiChar, uiRepCnt, uiFlags);    
  }
}
/////////////////////////////////////////////////////////////////////////////
    
void CCommandLine::EmitCommandSent()
{
  if (m_pwndReceiver != NULL)
  {
    NMHDR msgNotif;
    msgNotif.code = NM_COMMAND_SENT;
    msgNotif.hwndFrom = this->GetSafeHwnd();
    msgNotif.idFrom = this->GetDlgCtrlID();
    m_pwndReceiver->SendMessage(WM_NOTIFY, 0, (UINT)&msgNotif);
  }
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnLButtonDown(UINT nFlags, CPoint point)
{
  CRect rcClient;
  GetClientRect(rcClient);

  SetFocus();
  SetCapture();

  // If outside client area, do nothing.
  if (rcClient.PtInRect(point)==TRUE)
  {
    m_ptCaret = point;
    m_oCaretPositioned = true;
  }

  if (m_rcThumb.PtInRect(point)==TRUE)
  {
    m_nThumbStartPos = point.y;
    m_oMouseDownThumb = true;
  }

  //  are we scrolling using the up top button?
  else if (m_rcScrollUpTop.PtInRect(point)==TRUE)
  {
    //  the button is down.
    m_oScrollUpTopPressed = true;
    //  decrement the index.
    m_nLineIndex--;
    //  make sure it is safe.
    m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
    m_nLineIndex = max(m_nVisibleLines-1, m_nLineIndex);
    //m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
    int nThumbHeight = m_rcThumb.Height();
    m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
    m_rcThumb.top = m_rcThumb.bottom - nThumbHeight;
    //  start the timer to decrement.
    SetTimer(ID_EVENT_DECR, 500, NULL);
  }

  //  are we scrolling using the up button?
  else if (m_rcScrollUp.PtInRect(point)==TRUE)
  {
    //  the button is down.
    m_oScrollUpPressed = true;
    //  decrement the index.
    m_nLineIndex--;
    //  make sure it is safe.
    m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
    m_nLineIndex = max(m_nVisibleLines-1, m_nLineIndex);
    //m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
    int nThumbHeight = m_rcThumb.Height();
    m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
    m_rcThumb.top = m_rcThumb.bottom - nThumbHeight;
    //  start the timer to decrement.
    SetTimer(ID_EVENT_DECR, 500, NULL);
  }

  //  are we scrolling using the down button?
  else if (m_rcScrollDn.PtInRect(point)==TRUE)
  {
    //  the button is down.
    m_oScrollDnPressed = true;
    //  decrement the index.
    m_nLineIndex++;
    //  make sure the index is safe.
    m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
    m_nLineIndex = max(m_nVisibleLines-1, m_nLineIndex);
    //m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
    int nThumbHeight = m_rcThumb.Height();
    m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
    m_rcThumb.top = m_rcThumb.bottom - nThumbHeight;
    //  start the timer to decrement.
    SetTimer(ID_EVENT_INCR, 500, NULL);
  }

  //  are we on the scrollbar?
  else if (m_rcScrollBar.PtInRect(point)==TRUE)
  {
    //  are we above the thumb?
    if (point.y < m_rcThumb.top)
    {
      OnKeyDown(VK_PRIOR, 1, 0);
    }
    else if (point.y > m_rcThumb.bottom)
    {
      OnKeyDown(VK_NEXT, 1, 0);
    }
  }

  Invalidate(FALSE);

  CWnd::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnLButtonUp(UINT nFlags, CPoint point)
{
  //  end the scrolling....
  m_oScrollUpTopPressed = false;
  m_oScrollUpPressed = false;
  m_oScrollDnPressed = false;

  //  the thumb is not being moved....
  m_oMouseDownThumb = false;

  KillTimer(ID_EVENT_INCR);
  KillTimer(ID_EVENT_DECR);

  //  let go of the mouse
  ReleaseCapture();

  Invalidate(FALSE);

  CWnd::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnTimer(UINT nIDEvent)
{
  //  change the timer to a shorter interval.
  SetTimer(nIDEvent, 100, NULL);

  switch (nIDEvent)
  {
    case ID_EVENT_INCR: m_nLineIndex++; break;
    case ID_EVENT_DECR: m_nLineIndex--; break;
  }

  //  make sure it is safe.
  m_nLineIndex = min((int)(m_vecLines.size())-1, m_nLineIndex);
  m_nLineIndex = max(m_nVisibleLines-1, m_nLineIndex);

  int nThumbHeight = m_rcThumb.Height();
  m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
  m_rcThumb.top = m_rcThumb.bottom - nThumbHeight;

  TRACE ("Timer fired. Display pos is: %d.\n", m_nLineIndex);

  Invalidate(FALSE);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

  m_rcThumb.bottom = ScreenPosFromLineIndex(m_nLineIndex);
  Invalidate(FALSE);
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::OnMouseMove(UINT nFlags, CPoint point)
{
  if (m_oMouseDownThumb==true)
  {
    //  get the new screen position.
    int nScreenDy = point.y - m_nThumbStartPos;
    if (nScreenDy!=0)
    {
      //  calculate a new position
      int nNewBottom = m_rcThumb.bottom + nScreenDy;
      //  make sure the new pos is within bounds.
      nNewBottom = min(m_rcScrollTrack.bottom, nNewBottom);
      nNewBottom = max(m_rcScrollTrack.top+m_rcThumb.Height()-m_nMinThumbY, nNewBottom);
      //  offset the thumb.
      m_rcThumb.top = nNewBottom - m_rcThumb.Height();
      m_rcThumb.bottom = nNewBottom;
      //  reset the thumb start pos.
      m_nThumbStartPos = point.y;
      //  calculate the line index.
      m_nLineIndex = LineIndexFromScreenPos(m_rcThumb.bottom);
      //  make sure we redraw the control.
      Invalidate(FALSE);
    }
  }

  CWnd::OnMouseMove(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::ScreenPosFromLineIndex(int nLineIndex)
{
  //  what is the ratio of the position to the number of lines?
  double xPosRatio = (double)(nLineIndex)/(double)(m_vecLines.size());
  //  what is the ratio of the minimum to the number of lines?
  double xMinRatio = (double)(m_nVisibleLines)/(double)(m_vecLines.size());
  //  calculate the number of visible lines in pixels.
  int iTopPos = m_rcScrollTrack.top + //m_nMinThumbY +
    (int)(xMinRatio * (double)(m_rcScrollTrack.Height()));
  //  this is the bottom of the thumb.
  int iScreenPos =  m_rcScrollTrack.top + //m_nMinThumbY +
      (int)(xPosRatio * (double)(m_rcScrollTrack.Height()));
  //  make sure the new pos is within bounds.
  iScreenPos = min(m_rcScrollTrack.bottom, iScreenPos);
  iScreenPos = max(iTopPos, iScreenPos);
  TRACE("Calculated thumb bottom: %d\n", iScreenPos);
  return iScreenPos;
}
/////////////////////////////////////////////////////////////////////////////

int CCommandLine::LineIndexFromScreenPos(int nScreenPos)
{
  //  what fraction of the total scroll distance was moved?
  double xRatio = (double)(nScreenPos - m_rcScrollTrack.top) / // - m_nMinThumbY) /
      (double)(m_rcScrollTrack.Height());
  //  calculate the new index
  int iPos = (int)(xRatio * (double)(m_vecLines.size()));
  //  make sure the new pos is within bounds.
  iPos = min(m_vecLines.size()-1, iPos);
  iPos = max(m_nVisibleLines-1, iPos);
  TRACE("Calculated display pos: %d\n", iPos);
  return iPos;
}
/////////////////////////////////////////////////////////////////////////////

void CCommandLine::SetOwner(CCommandLineTestDlg* p)
{
	m_pOwner=p;
}
