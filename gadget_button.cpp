#include "proto.h"
#include "placement.h"
#include "prjwin.h"

extern bool resize,moved,drag;

extern BPoint start;
extern BPoint stx;
extern int diffx,diffy,mods;

extern	void	keydown_rtn(BView *view,char *bytes,int32 nb);
extern	void	MouseDown_All(BView *vx,BPoint pt);
extern	void	MouseUp_All(BView *vx);
extern	void	MouseMove_All(BView *vx,BPoint pt);

MyButton::MyButton(BRect rct,char *title):BButton(rct,"",title,NULL)
{
}

MyButton::~MyButton(void)
{
}

void
MyButton::MouseDown(BPoint pt)
{
	MouseDown_All(this,pt);
}

void
MyButton::MouseUp(BPoint pt)
{
	MouseUp_All(this);
}

void
MyButton::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	MouseMove_All(this,pt);
}

void
MyButton::KeyDown(const char *bytes,int32 nb)
{
	keydown_rtn(this,bytes,nb);

	BButton::KeyDown(bytes,nb);
}

void
MyButton::Draw(BRect rct)
{
	BButton::Draw(rct);

	DrawGadget(this);
}
