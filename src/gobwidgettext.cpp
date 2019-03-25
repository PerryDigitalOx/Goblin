#include <cdxtypes.h>
#include "GOBColor.h"			// for color management

#include "GOBWidgetText.h"


CGOBWidgetText::CGOBWidgetText()
{
	m_FontIndex = 0;
	m_pText = NULL;
	SetTextColor( GC.WHITE );
	SetShadowColor( GC.BLACK );
	SetShadowOffset( 1, 1 );

}

CGOBWidgetText::~CGOBWidgetText()
{
    DELETEARRAY(m_pText);
}


