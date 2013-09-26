#include "proto.h"

MyStatus::MyStatus(BRect rct,char *title):BStatusBar(rct,"",title)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyStatus::~MyStatus(void)
{
}

void
MyStatus::MouseDown(BPoint pt)
{
	BStatusBar::MouseDown(pt);
}

void
MyStatus::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BStatusBar::MouseMoved(pt,tr,msg);
}

void
MyStatus::AttachedToWindow(void)
{
}

void
MyStatus::FrameResized(float wi,float he)
{
	BStatusBar::FrameResized(wi,he);
}	

void
MyStatus::Draw(BRect rct)
{
	BStatusBar::Draw(rct);
}

void
MyStatus::DrawAfterChildren(BRect rct)
{
	BStatusBar::DrawAfterChildren(rct);
}
