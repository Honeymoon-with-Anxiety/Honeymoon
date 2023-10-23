// olorPicker.cpp: implementation of the ColorPicker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mutexes.h"
#include "olorPicker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ColorPicker::ColorPicker()
{
	arColors[0] = RGB(0,0,0);
	arColors[1] = RGB(0,0,255);
	arColors[2]=	RGB(0,255,0);
	arColors[3]=	RGB(0,255,255);
	arColors[4]=	RGB(255,0,0);
	arColors[5]=	RGB(255,0,255);
	arColors[6]=	RGB(255,255,0);
	arColors[7]=	RGB(255,255,255);
	arColors[8]=	RGB(128,128,128);
	arColors[9]=	RGB(192,192,192);
}

ColorPicker::~ColorPicker()
{

}
