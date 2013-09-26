#include "proto.h"

MyColor::MyColor(BRect rct):BColorControl(BPoint(rct.left,rct.top),B_CELLS_32x8,8,"",NULL)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyColor::~MyColor(void)
{
}

void
MyColor::MouseDown(BPoint pt)
{
	BColorControl::MouseDown(pt);
}

void
MyColor::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BColorControl::MouseMoved(pt,tr,msg);
}

void
MyColor::FrameResized(float wi,float he)
{
	BColorControl::FrameResized(wi,he);
}	

void
MyColor::Draw(BRect rct)
{
	BColorControl::Draw(rct);
}

void
MyColor::DrawAfterChildren(BRect rct)
{
	BColorControl::DrawAfterChildren(rct);
}

void
MyColor::AttachedToWindow(void)
{
	float a,b;

	GetPreferredSize(&a,&b);

	ResizeTo(a,b);
}
