#ifndef GOBCOLOR_H
#define GOBCOLOR_H

// color management
class CGOBManager;
extern CGOBManager GM;

#define GOBColor( col )		GM.GetScreenPtr()->MakeColor( col, GM.GetSurfacePtr() )

typedef struct {
	UINT32   BLACK;			//RGB 0, 0, 0
	UINT32	WHITE;			//RGB 255,255,255
	UINT32	GRAY7;			//RGB 200, 200, 200
	UINT32	GRAY247;		//RGB 160, 160, 160
	UINT32	GRAY248;		//RGB 128, 128, 128
	UINT32	DARKGRAY;		//RGB 51, 51, 51
	UINT32	RED;			//RGB 255, 0, 0
	UINT32	DARKRED;		//RGB 102, 0, 0
	UINT32	BLUE;			//RGB 0, 0, 255
	UINT32	DARKBLUE;		//RGB 0, 0, 128
	UINT32	ORANGE;			//RGB 255, 51, 0
	UINT32	GREEN;			//RGB 0, 255, 0
	UINT32	DARKGREEN;		//RGB 0, 128, 0
	UINT32	YELLOW;			//RGB 255, 255, 0
	UINT32	DARKYELLOW;		//RGB 128, 128, 0
	UINT32	PURPLE;			//RGB 102, 0, 102
	UINT32	BROWN;			//RGB 115, 75, 35
	UINT32	LIGHTBROWN;		//RGB 175, 107, 59
	UINT32	TEAL;			//RGB 0, 255, 255
	UINT32	PEACH;			//RGB 255, 255, 102
	UINT32	PINK;			//RGB 255, 51, 204
}GOBCOLORS;

typedef struct {
	UINT32	ActiveTitleBarFace;		//BLUE
	UINT32	InActiveTitleBarFace;	//BROWN
	UINT32	ActiveWindowFace;		//GRAY247
	UINT32	InActiveWindowFace;		//GRAY247
	UINT32	ActiveWindowHilight;	//GRAY7
	UINT32	ActiveWindowShadow;		//DARKGRAY
	UINT32	InActiveWindowHilight;	//LIGHTBROWN
	UINT32	InActiveWindowShadow;	//BROWN
	UINT32	ButtonFace;				//GRAY7
	UINT32	ButtonHilight;			//WHITE
	UINT32	ButtonShadow;			//GRAY248
	UINT32	ButtonHoverHilight;		//GREEN
	UINT32	ButtonHoverShadow;		//DARKGREEN
	UINT32	ButtonTextHover;		//RED
	UINT32	ButtonTextNormal;		//BLACK
	UINT32	ButtonTextShadow;		//DARKRED
	UINT32	ButtonTextSelect;		//GRAY248
	UINT32	ButtonTextDisabled;		//GRAY248
	UINT32	ButtonHilightDisabled;	//GRAY247
	UINT32	ButtonFaceDisabled;		//GRAY7
}GOBWIDGETCOLORS;


extern GOBCOLORS		GC;
extern GOBWIDGETCOLORS	GWC;


#endif