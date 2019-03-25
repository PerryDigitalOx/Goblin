#include "GOBManager.h"
#include "GOBColor.h"
#include "GOBHProgressBar.h"


CGOBHProgressBar::CGOBHProgressBar()
{
	CGOBWidget::CGOBWidget(); //call paren't constructor
	SetRange(0, 100);
	SetValue(0);
	m_BGColor=GC.GRAY7;
	m_FrameColor=GC.BLACK;
	m_TextColor=GC.BLUE;
}


GOBLIN_RETVAL CGOBHProgressBar::OnDraw(GOBLIN_PARAM param)
{
	if (IsDisabled) 
		return GOBLIN_SUCCESS;

	CDXSurface *surf = GM.GetSurfacePtr();
	//Calculations
	float Percent = (float)(m_Value-m_nMin)/(float)(m_nMax-m_nMin);
	int   iPercent=(int)(Percent*100);
	RECT rc;
	rc.left=m_Pos.x;
	rc.top=m_Pos.y;
	rc.right=m_Pos.x+(int)(Percent*m_Size.cx);
	rc.bottom=m_Pos.y+m_Size.cy;
	SIZE TextSize;
	POINT TextPos;
	char Str5[5]=""; 
	sprintf(Str5,"%i",iPercent);
	strcat(Str5,"%");
	GM.m_Font[GetFontIndexToUse()]->GetTextSize(Str5,TextSize);
	//Draw the bar
	surf->FillRect( rc.left,rc.top,rc.right,rc.bottom,m_BGColor);
	surf->Lock();
	surf->Rect( rc.left,rc.top,rc.right,rc.bottom,m_FrameColor);
	surf->UnLock();
	//Draw the text
	TextPos.y=m_Pos.y+(m_Size.cy-TextSize.cy)/2;
	TextPos.x=m_Pos.x+((m_Size.cx-TextSize.cx)/2)*Percent;

	UINT32 SavedColor = GM.m_Font[GetFontIndexToUse()]->GetTextColor();
	GM.m_Font[GetFontIndexToUse()]->SetTextColor(m_TextColor);
	GM.m_Font[GetFontIndexToUse()]->Draw(TextPos.x,TextPos.y,Str5,surf);
	GM.m_Font[GetFontIndexToUse()]->SetTextColor(SavedColor);

    return GOBLIN_SUCCESS;
}


void CGOBHProgressBar::SetRange( INT32 nMin, INT32 nMax)
{
	if (nMin<nMax)
	{
		m_nMin = nMin;
		m_nMax = nMax;
	}
	else
	{
		m_nMax = nMin;
		m_nMin = nMax;
	}
}

void CGOBHProgressBar::SetValue(INT32 NewVal)
{
	if ((NewVal>=m_nMin) && (NewVal<=m_nMax)) m_Value=NewVal;
}


