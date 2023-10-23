#if !defined(AFX_OSCOPECTRL_H__832AB65F_B7EB_4265_BD0C_6CA600975FE9__INCLUDED_)
#define AFX_OSCOPECTRL_H__832AB65F_B7EB_4265_BD0C_6CA600975FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OScopeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COScopeCtrl window

class COScopeCtrl : public CWnd
{
// Construction
public:
  COScopeCtrl();

// Attributes
public:
	double AppendPoint(double dNewPoint);
	void SetRange(double dLower, double dUpper, int nDecimalPlaces=1);
	void SetLowerRange(double dLower);
	void SetUpperRange(double dUpper);
  void SetXUnits(CString string);
  void SetYUnits(CString string);
  void SetGridColor(COLORREF color);
  void SetPlotColor(COLORREF color);
  void SetBackgroundColor(COLORREF color);
  void InvalidateCtrl();
  void DrawPoint();
  void Reset();

  // Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(COScopeCtrl)
  public:
  virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=NULL);
  //}}AFX_VIRTUAL

// Implementation
public:
  int m_nShiftPixels;          // amount to shift with each new point 
  int m_nYDecimals;

  CString m_strXUnitsString;
  CString m_strYUnitsString;

  COLORREF m_crBackColor;        // background color
  COLORREF m_crGridColor;        // grid color
  COLORREF m_crPlotColor;        // data color  
  
  double m_dCurrentPosition;   // current position
  double m_dPreviousPosition;  // previous position

  virtual ~COScopeCtrl();

  // Generated message map functions
protected:
  //{{AFX_MSG(COScopeCtrl)
  afx_msg void OnPaint();
  afx_msg void OnSize(UINT nType, int cx, int cy); 
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

  int m_nHalfShiftPixels;
  int m_nPlotShiftPixels;
  int m_nClientHeight;
  int m_nClientWidth;
  int m_nPlotHeight;
  int m_nPlotWidth;

  double m_dLowerLimit;        // lower bounds
  double m_dUpperLimit;        // upper bounds
  double m_dRange;
  double m_dVerticalFactor;
  
  CRect  m_rectClient;
  CRect  m_rectPlot;
  CPen   m_penPlot;
  CBrush m_brushBack;

  CDC     m_dcGrid;
  CDC     m_dcPlot;
  CBitmap *m_pbitmapOldGrid;
  CBitmap *m_pbitmapOldPlot;
  CBitmap m_bitmapGrid;
  CBitmap m_bitmapPlot;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSCOPECTRL_H__832AB65F_B7EB_4265_BD0C_6CA600975FE9__INCLUDED_)
