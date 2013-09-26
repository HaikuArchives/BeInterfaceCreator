#include "proto.h"

MyText::MyText(BRect rct,char *title):BStringView(rct,"",title,B_FOLLOW_NONE,B_WILL_DRAW)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyText::~MyText(void)
{
}

void
MyText::MouseDown(BPoint pt)
{
	BStringView::MouseDown(pt);
}

void
MyText::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BStringView::MouseMoved(pt,tr,msg);
}

void
MyText::FrameResized(float wi,float he)
{
	BStringView::FrameResized(wi,he);
}	

void
MyText::AttachedToWindow(void)
{
}

void
MyText::Draw(BRect rct)
{
	BStringView::Draw(rct);
}

void
MyText::DrawAfterChildren(BRect rct)
{
	BStringView::DrawAfterChildren(rct);
}
