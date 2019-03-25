#ifndef CGOBSYSBUTTONS_H
#define CGOBSYSBUTTONS_H

#include "GOBButton.h"

class CGOBSysClose : public CGOBButton
{
public:
	CGOBSysClose();
	~CGOBSysClose();

	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);

};

class CGOBSysMinimize : public CGOBButton
{
public:
	CGOBSysMinimize();
	~CGOBSysMinimize();

	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);

};



#endif
