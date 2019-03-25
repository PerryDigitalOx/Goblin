#include "GOBManager.h"
#include "GOBMenu.h"


GOBLIN_RETVAL CGOBMenu::OnDraw(GOBLIN_PARAM param)
{
	if(m_pBGImage)
	{
//		if(IsFlagSet(WF_TRANSPARENTBG))
//			m_pBGImage->DrawTrans(m_Pos.x, m_Pos.y, GM.GetSurfacePtr());
//			m_pBGImage->DrawTrans(GM.GetSurfacePtr(), m_Pos.x, m_Pos.y, );
//		else
//			m_pBGImage->DrawFast(m_Pos.x, m_Pos.y, GM.GetSurfacePtr());
//			m_pBGImage->DrawTrans(GM.GetSurfacePtr(), m_Pos.x, m_Pos.y, );
	}

	SendMsgToChildren(GM_DRAW);

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBMenu::OnLBUp(GOBLIN_PARAM param)
{
    return GOBLIN_SUCCESS;
}


void CGOBMenu::BringToFront(void)
{
    GM.RemoveChild(this);
    GM.AddChild(this);
}

GOBLIN_RETVAL CGOBMenu::OnProcess(GOBLIN_PARAM param)
{
	CGOBWidget *pWidget = NULL;

	if((pWidget = m_ActiveList.GetLast()))
	{
		do
		{
			SendMsg(pWidget, GM_PROCESS, 0);
		}while((pWidget = m_ActiveList.Prev(pWidget)));
	}

	return GOBLIN_SUCCESS;
}
