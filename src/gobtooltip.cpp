
#include "GOBManager.h"
#include "GOBToolTip.h"
#include "GOBColor.h"			// for color management

CGOBToolTip::CGOBToolTip()
{
}

CGOBToolTip::~CGOBToolTip()
{
	m_pToolTipText = NULL;
}


GOBLIN_RETVAL CGOBToolTip::OnDraw(GOBLIN_PARAM param)
{
	CDXSurface *surf = GM.GetSurfacePtr();

	if(m_pToolTipText)
	{
		SIZE sz = {0,0};
		GM.m_Font[m_FontIndex]->GetTextSize(m_pToolTipText, sz);
		sz.cx+=4;
		sz.cy+=4;
		m_Size = sz;

		RECT rc;
		rc.left = m_Pos.x;
		rc.right = m_Pos.x+m_Size.cx;
		rc.top = m_Pos.y;
		rc.bottom = m_Pos.y+m_Size.cy;

		if(!IsFlagSet(WF_TRANSPARENTBG))
		{
			surf->Rect( rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonFace );

			surf->Lock();
			surf->HLine(rc.left, rc.right, rc.top, GWC.ButtonHilight);
			surf->VLine(rc.top, rc.bottom, rc.left, GWC.ButtonHilight);
			surf->HLine(rc.left, rc.right, rc.bottom, GWC.ButtonShadow);
			surf->VLine(rc.top, rc.bottom, rc.right, GWC.ButtonShadow);
			surf->UnLock();
		}

//		GM.m_Font[m_FontIndex]->DrawTransColor(m_Pos.x+2, m_Pos.y, m_pToolTipText, GM.GetSurfacePtr(), GOBColor(GetTextColor()));
		GM.m_Font[m_FontIndex]->Draw(m_Pos.x+2, m_Pos.y, m_pToolTipText, GM.GetSurfacePtr());
	}
    return GOBLIN_SUCCESS;
}
