#ifndef CGOBHPROGRESSBAR_H
#define CGOBHPROGRESSBAR_H

#include "GOBWidget.h"

class CGOBHProgressBar: public CGOBWidget
{
public:
	// Set default values
	CGOBHProgressBar();

	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);

	// Sets the range of values of progressbar.
	void SetRange( INT32 nMin, INT32 nMax );
	void SetValue( INT32 NewVal );
	INT32 GetValue() {return m_Value;}
	void SetBGColor(UINT32 Color) {m_BGColor=Color;}
	void SetFrameColor(UINT32 Color) {m_FrameColor=Color;}
	UINT32 GetBGColor() {return m_BGColor;}
	UINT32 GetFrameColor() {return m_FrameColor;}

private:
	INT32	m_nMin, m_nMax, m_Value;
	UINT32 m_BGColor,m_FrameColor;
};

#endif
