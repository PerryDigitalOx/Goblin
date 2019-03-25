#define KEYDOWN(a)		(GetKeyState(a) & 0x1000)


#if defined(USE_DIRECTINPUT)

#define KB_RETURN	DIK_RETURN
#define KB_UP		DIK_UP
#define KB_DOWN		DIK_DOWN
#define KB_ESCAPE	DIK_ESCAPE

#else

#define KB_RETURN	VK_RETURN
#define KB_UP		VK_UP
#define KB_DOWN		VK_DOWN
#define KB_ESCAPE	VK_ESCAPE
#define KB_LEFT		VK_LEFT
#define KB_RIGHT	VK_RIGHT
#define KB_HOME     VK_HOME
#define KB_END      VK_END

#define KB_F10		VK_F10

#endif