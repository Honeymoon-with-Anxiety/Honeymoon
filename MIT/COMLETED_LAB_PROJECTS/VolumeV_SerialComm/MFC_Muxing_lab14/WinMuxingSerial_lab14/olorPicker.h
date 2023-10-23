// olorPicker.h: interface for the ColorPicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLORPICKER_H__5ADAE3D3_55A0_4741_8F21_09308EDF3F8A__INCLUDED_)
#define AFX_OLORPICKER_H__5ADAE3D3_55A0_4741_8F21_09308EDF3F8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ColorPicker  
{
public:
	ColorPicker();
	virtual ~ColorPicker();
	COLORREF arColors[10]; 
};

#endif // !defined(AFX_OLORPICKER_H__5ADAE3D3_55A0_4741_8F21_09308EDF3F8A__INCLUDED_)
