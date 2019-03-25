#include "GOBManager.h"
#include "GOBStaticPic.h"


GOBLIN_RETVAL CGOBStaticPic::OnDraw(GOBLIN_PARAM param)
{
	CDXSprite *pImage = GetImagePtr();
	if(!pImage)
		return GOBLIN_NULLPTR;

	pImage->SetFrame(0);
	pImage->SetPos(m_Pos.x, m_Pos.y);
//	pImage->m_Tile->SetDest(m_Pos.x, m_Pos.y, m_Pos.y+m_Size.cy, m_Pos.x+m_Size.cx);
//	pImage->GetTile()->SetDest(m_Pos.x, m_Pos.y, m_Pos.y+m_Size.cy, m_Pos.x+m_Size.cx);

	pImage->Draw( GM.GetSurfacePtr(), 0, 0, GetBltType());	//call CDXSprite draw

    return GOBLIN_SUCCESS;
}
