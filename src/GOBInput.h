#include <windows.h>	//POINT structure defined
#include <cdxtypes.h>

typedef struct {
	POINT		MousePos;			//mouse position
	POINT		OldMousePos;		//last mouse position
	UINT8		MouseButLeft;		//state of LEFT mouse button
	UINT8		MouseButMiddle;		//state of MIDDLE mouse button
	UINT8		MouseButRight;		//state of RIGHT mouse button
	UINT8		OldMouseButLeft;	//old state of LEFT mouse button
	UINT8		OldMouseButMiddle;	//old state of MIDDLE mouse button
	UINT8		OldMouseButRight;	//old state of RIGHT mouse button
	UINT8		KeyChar;			//last keyboard character pressed
}GOBINPUT;

extern GOBINPUT GI;
