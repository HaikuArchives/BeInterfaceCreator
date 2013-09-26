#include "proto.h"

MyScroller::MyScroller(BRect rct,orientation pos):BScrollBar(rct,"",NULL,0,0,pos)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);

	SetRange(0,0);
}

MyScroller::~MyScroller(void)
{
}

void
MyScroller::MouseDown(BPoint pt)
{
	BScrollBar::MouseDown(pt);
}

void
MyScroller::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BScrollBar::MouseMoved(pt,tr,msg);
}

void
MyScroller::FrameResized(float wi,float he)
{
	BScrollBar::FrameResized(wi,he);

	float a,b;

	GetPreferredSize(&a,&b);

	ResizeTo(a,b);
}	

void
MyScroller::Draw(BRect rct)
{
	BScrollBar::Draw(rct);
}

void
MyScroller::DrawAfterChildren(BRect rct)
{
	BScrollBar::DrawAfterChildren(rct);
}
