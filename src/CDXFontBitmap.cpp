#include "GOBManager.h"
#include "GOBColor.h"
#include "CDXFontBitmap.h"


CDXFontBitmap::CDXFontBitmap()
{
	m_pSurface = NULL;
}

CDXFontBitmap::~CDXFontBitmap()
{
	SAFEDELETE(m_pSurface);
}


CDXFontBitmap::Create( CDXScreen *pScreen, const char *szFileName, UINT32 BlockWidth, UINT32 BlockHeight, UINT16 nBlocks )
{
	m_pScreen = pScreen;

	m_pSurface = new CDXSprite;
	if(m_pSurface==NULL)
		return S_FALSE;

	m_pSurface->Create(pScreen, szFileName, BlockWidth, BlockHeight, nBlocks, CDXMEM_VIDTHENSYS);
	m_pSurface->SetColorKey();

	CalculateKerning();

	return S_OK;
}


HRESULT CDXFontBitmap::Draw( INT32 xPos, INT32 yPos, char * pText, CDXSurface * lpDDest, INT16 nTextLength )
{
	if(m_pSurface==NULL)
		return S_FALSE;

	INT16 len = strlen(pText);
	INT32 offset = 0;

/*
    int i;
    for(i=0; i<len; i++)
	{
		m_pSurface->SetFrame( pText[i]-32 );
		m_pSurface->SetPos(xPos+offset, yPos);
		m_pSurface->Draw(lpDDest, 0, 0, CDXBLT_TRANS);
		offset += m_pSurface->m_Tile->m_BlockWidth;
	}
*/

	INT32 TilesInWidth;
	INT32 SpriteSrcX, SpriteSrcY;
	RECT SpriteSrcRect;

	// Get the number of tiles in the sprite tile surface width
	TilesInWidth = m_pSurface->GetTile()->GetWidth() / m_pSurface->GetTile()->m_BlockWidth;


	m_pSurface->Lock();
	lpDDest->Lock();

	INT32 x,y;
	UINT32 src;
//	double weight;
//	UINT8 dR, dG, dB, sR, sG, sB;
    INT16 i;
    for(i=0; i<len; i++)
	{
		m_pSurface->SetFrame( toupper(pText[i])-32 );
		m_pSurface->SetPos(xPos+offset, yPos);

		// Calc the upper left corner of the current frame of animation
		SpriteSrcX = (m_pSurface->GetFrame() % TilesInWidth) * m_pSurface->GetTile()->m_BlockWidth;
		SpriteSrcY = (m_pSurface->GetFrame() / TilesInWidth) * m_pSurface->GetTile()->m_BlockHeight;

		// Define the source RECT for the BLT.
		SpriteSrcRect.top = SpriteSrcY;
		SpriteSrcRect.left = SpriteSrcX;
		SpriteSrcRect.bottom = SpriteSrcY + m_pSurface->GetTile()->m_BlockHeight;
		SpriteSrcRect.right = SpriteSrcX + m_pSurface->GetTile()->m_BlockWidth;

		for(y=0; y<SpriteSrcRect.bottom-SpriteSrcRect.top; y++)
		{
			for(x=0; x<SpriteSrcRect.right-SpriteSrcRect.left; x++)
			{
				src = m_pSurface->GetTile()->GetPixel(x+SpriteSrcRect.left, y+SpriteSrcRect.top);
/*
//				if(src!=RGB(0,0,0))
				{
					sR = GetRValue(src);
					sG = GetGValue(src);
					sB = GetBValue(src);

					//WORD alpha = ((GetRValue(src)+GetGValue(src)+GetBValue(src)) / 3);
					//WORD alpha = GetRValue(src);
					UINT32 dst = lpDDest->GetPixel(xPos+x+offset, yPos+y);
					//alpha -= GetRValue(dst);
					//if(alpha<0)
						//alpha = 0;

					weight = (float)(sR + sG + sB) / 3.0;
					weight = (weight + 128.0) / (384.0);

					dR = GetRValue(dst);
					dG = GetGValue(dst);
					dB = GetBValue(dst);

					dR = (UINT8)(((float)dR * (1.0 - weight)) + ((float)sR * weight));
					dG = (UINT8)(((float)dG * (1.0 - weight)) + ((float)sG * weight));
					dB = (UINT8)(((float)dB * (1.0 - weight)) + ((float)sB * weight));

					//src = RGB(255,255,255)-src;	//negate colors

					//lpDDest->PutAAPixel( xPos+x+offset, yPos+y, src, alpha);
					//lpDDest->PutPixel( xPos+x+offset, yPos+y, GOBColor(RGB(dR, dG, dB)));
					lpDDest->PutPixel( xPos+x+offset, yPos+y, RGB(dR, dG, dB));
				}
*/
				if(src!=RGB(0,0,0))
					lpDDest->PutPixel( xPos+x+offset, yPos+y, src);
			}
		}

		//m_pSurface->Draw(lpDDest, 0, 0, CDXBLT_TRANS);
		offset += m_pSurface->GetTile()->m_BlockWidth;
	}

	m_pSurface->UnLock();
	lpDDest->UnLock();

	return S_OK;
}


BOOL CDXFontBitmap::GetTextSize(char *szText, SIZE &sz)
{
	sz.cy = m_pSurface->GetTile()->m_BlockHeight;
	sz.cx = m_pSurface->GetTile()->m_BlockWidth * strlen(szText);

	return TRUE;
}


void CDXFontBitmap::CalculateKerning()
{

}
