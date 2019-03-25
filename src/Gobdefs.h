
typedef UINT32	GOBLIN_PARAM;		// parameter

// message handler macro
#define HANDLE_GOBLIN_MSG(message, fn)    \
	case (message): return( (fn) ((GOBLIN_PARAM)(param)) )


// Return values
enum GOBLIN_RETVAL {
	GOBLIN_NOTINITIALIZED = -2, // Object not initialized
	GOBLIN_NOTIMPLEMENTED = -1,	// virtual function has no derived function implementation
	GOBLIN_SUCCESS  = 0,		// normal exit status
	GOBLIN_NOPARENT = 1,		// no parent defined. major problem
	GOBLIN_DESTROY  = 2,		// notify calling thread to destroy object
	GOBLIN_NULLPTR  = 3,		// required pointer is null
	GOBLIN_DISABLED = 4,		// notify that object is disabled
};


// Combo/Check/Radio states
enum BUTTON_STATES {
    STATE_CHECKED       =   1,  // checked, on, true
    STATE_UNCHECKED,            // unchecked, off, false
    STATE_UP,
    STATE_HOVER,
    STATE_DOWN,
    STATE_DISABLED,
};


// Widget Flags
#define WF_SOLIDBG            0x00000001		// default
#define WF_TRANSPARENTBG      0x00000002		// transparent background
#define WF_TRANSPARENTMOUSE   0x00000004		// allow mouse msgs to go through object
#define WF_MODAL              0x00000008		// modal widget, under widgets receive no mouse msgs
#define WF_PASSWORD           0x00000010		// editbox password display **** instead of text
#define WF_PARENTNOTIFY       0x00001000		// notify parent of mouse actions
#define WF_KEEPFOCUS          0x00002000		// keeps keyboard focus on enter/tab events
#define	WF_DISABLED           0x10000000		// disabled item

// Widget Image Flags
#define WF_IMAGE_NONE       0x00000000
#define WF_IMAGE_CENTER     0x00000100
#define WF_IMAGE_TILE       0x00000200
#define WF_IMAGE_ANIMATED   0x00000400
#define WF_IMAGESIZE        0x00000800		// make widget same size as image used


// Goblin Messages
enum GOBLIN_MSG {
	GM_NULL				=	0x00000000,
    GM_MOVE             =   0x00000001,
    GM_SIZE             =   0x00000002,
    GM_ACTIVATE         =   0x00000003,
    GM_DRAW             =   0x00000004,     // draw the object
    GM_PROCESS          =   0x00000005,

	GM_LBDOWN			=	0x00000020,		// mouse left click down
	GM_LBUP				=	0x00000021,		// mouse left release
	GM_RBDOWN			=	0x00000022,		// mouse right click down
	GM_RBUP				=	0x00000023,		// mouse right release
	GM_MBDOWN			=	0x00000024,		// mouse middle click down
	GM_MBUP				=	0x00000025,		// mouse middle release
	GM_DCLICK			=	0x00000026,		// double click
    GM_MOUSEMOVE        =   0x00000027,     // mouse movement happening
    GM_GOTMOUSE         =   0x00000028,     // mouse on top of object
    GM_LOSTMOUSE        =   0x00000029,     // mouse moved away from object

    GM_KEY              =   0x00000030,     // keyboard shortcut
    GM_CHAR             =   0x00000031,     // other keyboard input

    GM_WANTFOCUS        =   0x00000040,     // does object want the input focus?
    GM_GOTFOCUS         =   0x00000041,     // got the input focus
    GM_LOSTFOCUS        =   0x00000042,     // lost the input focus

	GM_SYSTEM			=	0x00001000,		// system wide message

	GM_EXTERNALEVENT	=	0x00002000,		// external event.  children can send events to other widgets.

	GM_USER				=	0x00004000,		// from here on are free...

};


// GM_SYSTEM params
#define SYS_CLOSE           0x00000001
#define SYS_MINIMIZE		0x00000002
