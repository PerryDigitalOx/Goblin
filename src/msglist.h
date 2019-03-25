///////////////////////////////////////////////////////////////////////////////
//
//	CGOBMsgList class constructor
//		CGOBMsgList()
//			Nullify and zero out all member variables.
//
//	CGOBMsgList class destructor
//		~CGOBMsgList()
//
//
//	Functions:
//		void Init(CDXSurface *surface, PT pixelCoord, int listSize, int verticalSpace, int lifeSpan)
//			No return.
//			Expects a pointer to a CDXSurface, a PT, an int, an int and another int.
//			Initializes the list to be drawn on the surface at the pixelCoord.
//			It also sets the list to be of size listSize.
//			Sets the spacing between lines to be at verticalSpace
//			Sets the length of time a line exists to lifeSpan
//
//		void Add(const char *text, ...)
//			No return.
//			Expects a pointer to a string, and any number of variables.
//			Adds the string to the list.
//
//		void ChangeFont(const char *FontName, int Width, int Height, int Attributes = FW_NORMAL)
//			No return.
//			Expects a stiring, an int, an int, and an optional int.
//			Sets the font in the list to the FontName.
//			Sets the font width to the Width and the height to the Height.
//			If a valid Attribute is passed, that attribute is set as well.
//
//		void Update()
//			No return.
//			No arguments.
//			Draws and makes changes to the list if any apply.
//
///////////////////////////////////////////////////////////////////////////////
//
//Usage:
//	CGOBMsgList lst;
//
//	//inits the list to be drawn on pDDBSurface @ point. 5 lines long, 10 pixels between each line.
//	//Each line has a 2 second lifespan
//	lst.Init(pDDBSurface, point, 5, 10, 2000)
//
//	//sets the font to Avalon Quest at 8 wide an 16 high
//	lst.ChangeFont("Avalon Quest", 8, 16);
//
//	//adds a simple line
//	lst.Add("First Line");
//
//	//adds a line with a variable
//	lst.Add("Line %d", count);
//
//	//draws the list
//	lst.Update();
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(_GOBMSGLIST_H_)
#define _GOBMSGLIST_H_

#include <cdx.h>
#include <cdxsurface.h>

class CGOBMsgList
{
public:
	CGOBMsgList();
	virtual ~CGOBMsgList();
	void Init(CDXSurface *surface, int x, int y, int listSize, int verticalSpace, int lifeSpan);
	void Add(const char *text, ...);
	void Add(COLORREF color, const char *text, ...);
	void ChangeFont(const char *FontName, int Width, int Height, int Attributes = FW_NORMAL) { if(m_pSurface) m_pSurface->ChangeFont(FontName, Width, Height, Attributes); m_iFontHeight = Height; }
	void Update();

private:
	CDXSurface *m_pSurface;	//dd surface
	COLORREF *m_LineColor;	//the color of each line
	int m_iCurrentSize;		//number of text items currently in the list
	int m_iMaxSize;			//maximum number of lines
	UINT32 m_iMaxLife;			//life in milliseconds
	POINT m_Coordinate;		//pixel coord of where the first line will be displayed
	char **m_szLine;		//an array of char* 's
	int m_iVerticalSpace;	//how far apart vertically lines should be
	int m_iFontHeight;		//current font's pixel height
	UINT32 m_dwStartTime;
};

#endif
