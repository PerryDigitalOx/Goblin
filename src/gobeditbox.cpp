
#include "GOBManager.h"
#include "GOBEditBox.h"
#include "GOBColor.h"			// for color management
#include "CDXFontBase.h"

CGOBEditBox::CGOBEditBox()
{
	m_IsDown = FALSE;
	m_CharCount = 0;
	m_CursorAnimObj.SetInfo(0,0,400);
	m_CursorAnimObj.Stop();
	m_IsCursorOn = FALSE;
}

void CGOBEditBox::SetText( const char * newtext )
{
	if(!m_pText)
	{
	    m_pText = new char[127 + 1];
		strcpy(m_pText, newtext);
		m_CharCount = strlen(m_pText);
	}
	else
	{
		strcpy(m_pText, newtext);
		m_CharCount = strlen(m_pText);
	}
}

GOBLIN_RETVAL CGOBEditBox::OnLostFocus(GOBLIN_PARAM param)
{
	if(m_IsDown)
	{
		m_IsDown=FALSE;
	}
	m_CursorAnimObj.Stop();
	m_CursorAnimObj.ResetTime();
	m_IsCursorOn = FALSE;

	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBEditBox::OnGotFocus(GOBLIN_PARAM param)
{
	m_CursorAnimObj.Start();

	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBEditBox::OnLBUp(GOBLIN_PARAM param)
{
	if(!m_IsDown)
	{
		m_IsDown = TRUE;
	}
	else
	{
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBEditBox::OnDraw(GOBLIN_PARAM param)
{
	CDXSurface *surf = GM.GetSurfacePtr();

	RECT rc,rc2;

	rc.top = m_Pos.y;
	rc.bottom = m_Pos.y+m_Size.cy;
	rc.left = m_Pos.x;
	rc.right = m_Pos.x+m_Size.cx;

	rc2 = rc;

	rc2.top++;
	rc2.bottom--;
	rc2.left++;
	rc2.right--;

	UINT32 col = GWC.ButtonTextNormal;
	if(!m_IsDown)
		col = GWC.ButtonTextHover;

	CDXFontBase *font = GM.m_Font[m_FontIndex];

	if(!IsFlagSet(WF_TRANSPARENTBG))
	{
		surf->Rect(rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonFace);

		surf->Lock();
		surf->HLine(rc.left, rc.right, rc.top, GWC.ButtonShadow);
		surf->VLine(rc.top, rc.bottom, rc.left, GWC.ButtonShadow);
		surf->HLine(rc.left, rc.right, rc.bottom, GWC.ButtonHilight);
		surf->VLine(rc.top, rc.bottom, rc.right, GWC.ButtonHilight);
		surf->UnLock();
	}

	SIZE szText;
	INT32 curpos = m_Pos.x;
	char TempString[255]; //Whatever.. can be changed to char* and then change it.
	strcpy(TempString,m_pText);
	if (IsFlagSet(WF_PASSWORD)) {
		memset(TempString, '*', strlen(m_pText));
//		UINT8 t;
//		UINT8 len = strlen(m_pText);
//		for(t=0; t<len; t++) {
//			TempString[t]='*';
//		}
	}
	
	if(TempString != NULL) {
		if(!IsDisabled) {
			font->Draw(m_Pos.x+2, m_Pos.y+3, TempString, GM.GetSurfacePtr());
		} else {
			font->Draw(1+m_Pos.x+(m_Size.cx/2), 1+m_Pos.y+2, TempString, GM.GetSurfacePtr());
		}

		font->GetTextSize(TempString, szText);
		curpos+=szText.cx+2;
	}

	if(m_CursorAnimObj.Execute()) {
		m_IsCursorOn = !m_IsCursorOn;
	}
	if(m_IsCursorOn) {
		surf->Rect(curpos, rc.top+2, curpos+4, rc.bottom-2, GWC.ButtonFace);
	}

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBEditBox::OnChar(GOBLIN_PARAM param)
{
	if(!m_pText)
	{
		m_pText = new char[127];
		memset(m_pText, 0, 127);
		m_CharCount = 0;
	}

	CDXFontBase *font = GM.m_Font[m_FontIndex];

	if(m_CharCount<127-1)
	{
		switch((char)param)
		{
		case 0x08:		//backspace
			if(m_CharCount>0)
				m_CharCount--;
			m_pText[m_CharCount] = '\0';
			break;

		case 0x0D:		//enter
			GM.SetEvent(GetID());
		case 0x09:		//tab
			if(!IsFlagSet(WF_KEEPFOCUS))
			{
				OnLostFocus(0);
				GM.m_pFocusObject = NULL;
				GM.m_pKeyboardObject = NULL;
			}
			return GOBLIN_SUCCESS;
			break;

		default:
			{
				SIZE sz;
				font->GetTextSize(m_pText, sz);
				SIZE charsz;
				font->GetTextSize("W", charsz);

				if(sz.cx < m_Size.cx-charsz.cx)
				{
					m_pText[m_CharCount] = (char)param;
					m_CharCount++;
					m_pText[m_CharCount] = '\0';
				}

			}
			break;
		}

		//since a key is pressed, reset flashing timer and turn cursor on
		m_CursorAnimObj.ResetTime();
		m_IsCursorOn = TRUE;
	}

	return GOBLIN_SUCCESS;
}
