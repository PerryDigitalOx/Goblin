#include "GOBManager.h"
#include "GOBInput.h"
#include "GOBTextBox.h"

CGOBTextBox::CGOBTextBox() : CGOBWidgetParent()
{
	m_NormalSurface=m_OnMouseSurface=m_OnClickSurface=m_DisabledSurface=NULL;
	m_IsDown = FALSE;
	m_IsHover = FALSE;
	m_HoverFrames=0;
	m_NormalColor=m_OnMouseColor=m_OnClickColor=m_DisabledColor=0;
	m_LineVSize=0;
	ResetLines();
	m_FirstY=0;
	m_Timer = new AnimObj();
	m_Timer->SetInfo(0,0,200);
	m_Timer->ResetTime();
}

void CGOBTextBox::SetText(char * newtext )
{
	DivideLines(newtext);
}


GOBLIN_RETVAL CGOBTextBox::OnLostMouse(GOBLIN_PARAM param)
{
	m_IsDown = FALSE;
	m_IsHover = FALSE;
	m_HoverFrames=0;
	
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBTextBox::OnGotMouse(GOBLIN_PARAM param)
{
	//this fixes, if mouse button goes down, move off of item, then back on, its back to down.
	if(GI.MouseButLeft & 1)
	{
		//hover must have been set prior.
		if(m_IsHover)		//this fixes bug where button is down, roll over other buttons, they do down.
			m_IsDown = TRUE;
	}
	
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBTextBox::OnMouseMove(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;
	
	//if button is down
	if(m_IsDown)
	{
		// and mouse button isnt down
		if(!(GI.MouseButLeft & 1))
		{
			// we change button to up state
			m_IsDown = FALSE;
		}
		//turn off hover state
		m_IsHover = FALSE;
		m_HoverFrames=0;
	}
	else
	{
		//if the mouse button isn't down, then we hover
		if(!(GI.MouseButLeft & 1))
		{
			m_IsHover = TRUE;
			if (m_HoverFrames<15) m_HoverFrames++;
		}
	}
	
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBTextBox::OnLBDown(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;
	
	m_IsDown = TRUE;
	
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBTextBox::OnLBUp(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;
	
	m_IsDown = FALSE;
	
	GM.SetEvent(GetID());
	
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBTextBox::OnDraw(GOBLIN_PARAM param)
{
	if(m_NormalSurface) //Or any surface, for that matter
	{
		if (m_Timer->Execute())
		{
			m_Timer->ResetTime();
			if (m_IsHover)
			{
				if (m_HoverFrames==15) 
				{
					if ( (m_FirstY+m_Size.cy)<(m_NormalSurface->GetHeight()) ) m_FirstY++;
				}
			}
			else
			{
				if  (m_FirstY>5) m_FirstY-=5; else m_FirstY=0;
			}
		}
		
		RECT ClippingRect;
		ClippingRect.left=0;
		ClippingRect.right=m_Size.cx;
		ClippingRect.top=m_FirstY;
		ClippingRect.bottom=m_FirstY+m_Size.cy;
		if (m_FirstY+m_Size.cy>m_NormalSurface->GetHeight()) 
		{
			ClippingRect.bottom=m_NormalSurface->GetHeight();
			ClippingRect.top=ClippingRect.bottom-m_Size.cy;
		}
		//m_TextSurface->DrawClipped(m_Pos.x,m_Pos.y,GM.GetSurfacePtr(),&ClippingRect);
		CDXSurface*    DrawingSurface = m_NormalSurface;
		if (m_IsHover) DrawingSurface = m_OnMouseSurface;
		if (m_IsDown)  DrawingSurface = m_OnClickSurface;
		DrawingSurface->DrawDDBlk(GM.GetSurfacePtr(), m_Pos.x, m_Pos.y,&ClippingRect);
		DrawingSurface=NULL;
	}
	SendMsgToChildren( GM_DRAW );
    return GOBLIN_SUCCESS;
}

void CGOBTextBox::AddLine(char* Line)
{
	if (m_LinesNum<100)
	{
		m_LinesNum++;
		memset(m_Lines[m_LinesNum-1],0,100); //First, ensure that it's blank
		memcpy(&m_Lines[m_LinesNum-1][0],Line,strlen(Line));
	}
}

UINT32 CGOBTextBox::DivideLines(char* Input, BOOL SurfaceCreation)
{
	ResetLines();
	char* StrPtr=Input;
	char TempLine[255]=""; 
	UINT32 TempLineLength=0;
	SIZE Tempm_Linesize;

	while ((*StrPtr)!=0) //Add word-by-word to the m_Lines list
	{
		char Word[100]="";
		UINT32 WordLength=0;
		char C=*StrPtr;
		while ( (C!=0) && (C!=32) )
		{
			Word[WordLength]=*(StrPtr+WordLength);
			WordLength++;
			C=*(StrPtr+WordLength);
		}
		if (TempLineLength!=0)
		{
			TempLine[TempLineLength]=32;
			TempLine[TempLineLength+1]=0;
			TempLineLength+=1;
		}
		memcpy(&TempLine[TempLineLength],Word,WordLength);
		TempLineLength+=WordLength;
		TempLine[TempLineLength]=0;
		GM.m_Font[m_FontIndex]->GetTextSize((char*)TempLine,Tempm_Linesize);
		if (Tempm_Linesize.cx>m_Size.cx)
		{
			//StrPtr-=WordLength;
			TempLine[TempLineLength-WordLength-1]=0;
			AddLine(TempLine);
			TempLine[0]=0;TempLineLength=0;
			if (m_LineVSize<Tempm_Linesize.cy) m_LineVSize=Tempm_Linesize.cy;
		}
		else 
		{
			StrPtr+=WordLength;
			if ((*StrPtr)==32) StrPtr++;
			if((*StrPtr)==0) AddLine(TempLine);
		}
	}
	if (SurfaceCreation) CreateSurfaces();
	return m_LinesNum;
}

void CGOBTextBox::CreateSurfaces()
{
	if (m_NormalSurface!=NULL) 		delete m_NormalSurface;
	if (m_OnMouseSurface!=NULL) 	delete m_OnMouseSurface;
	if (m_OnClickSurface!=NULL)		delete m_OnClickSurface;
	m_NormalSurface = new CDXSurface();
	m_OnMouseSurface = new CDXSurface();
	m_OnClickSurface = new CDXSurface();
	if (!((m_NormalSurface) && (m_OnMouseSurface) && (m_OnClickSurface)))
	{
		if (m_NormalSurface!=NULL)   	delete m_NormalSurface;
		if (m_OnMouseSurface!=NULL)		delete m_OnMouseSurface;
		if (m_OnClickSurface!=NULL)		delete m_OnClickSurface;
		m_NormalSurface=m_OnMouseSurface=m_OnClickSurface=NULL;	
		return; //Can't create them.
	}
	UINT32 SurfaceHeight=m_LineVSize*m_LinesNum;
	if (SurfaceHeight<m_Size.cy) SurfaceHeight=m_Size.cy;
	m_NormalSurface->Create(GM.GetScreenPtr(),m_Size.cx,SurfaceHeight,CDXMEM_SYSTEMONLY);
	m_NormalSurface->Fill(0); //Change to the desired background color
	m_OnMouseSurface->Create(GM.GetScreenPtr(),m_Size.cx,SurfaceHeight,CDXMEM_SYSTEMONLY);
	m_OnMouseSurface->Fill(0);
	m_OnClickSurface->Create(GM.GetScreenPtr(),m_Size.cx,SurfaceHeight,CDXMEM_SYSTEMONLY);
	m_OnClickSurface->Fill(0);
	//Disabled mode not supported nor implemented in the Draw function
	
	UINT32 SavedColor=GM.m_Font[m_FontIndex]->GetTextColor();
	
	UINT32 i;
	for (i=0;i<=m_LinesNum-1;i++)
	{
		UINT32 tx=0;         //Default alignment is to the left
		if (!m_Alignment) //Align to the right
		{
			SIZE TextSize;
			GM.m_Font[m_FontIndex]->GetTextSize(&m_Lines[i][0],TextSize);
			tx=m_Size.cx-TextSize.cx;
		}
		GM.m_Font[m_FontIndex]->SetTextColor(m_NormalColor);
		GM.m_Font[m_FontIndex]->Draw(tx,m_LineVSize*i,&m_Lines[i][0],m_NormalSurface);
		GM.m_Font[m_FontIndex]->SetTextColor(m_OnMouseColor);
		GM.m_Font[m_FontIndex]->Draw(tx,m_LineVSize*i,&m_Lines[i][0],m_OnMouseSurface);
		GM.m_Font[m_FontIndex]->SetTextColor(m_OnClickColor);
		GM.m_Font[m_FontIndex]->Draw(tx,m_LineVSize*i,&m_Lines[i][0],m_OnClickSurface);
	}
	GM.m_Font[m_FontIndex]->SetTextColor(SavedColor);
}

void CGOBTextBox::ResetLines()
{
	memset(&m_Lines[0][0],0,10000);
	m_LinesNum=0;
}

void CGOBTextBox::SetColors(UINT32 NormalColor,UINT32 OnMouseColor,UINT32 OnClickColor,UINT32 DisabledColor)
{
	m_NormalColor = NormalColor;
	m_OnMouseColor = OnMouseColor;
	m_OnClickColor = OnClickColor;
	m_DisabledColor = DisabledColor;
	CreateSurfaces();
}
