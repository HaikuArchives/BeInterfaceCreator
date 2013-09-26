#include "proto.h"

MyCheckBox::MyCheckBox(BRect rct,char *title):BCheckBox(rct,"",title,NULL,B_FOLLOW_ALL)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyCheckBox::~MyCheckBox(void)
{
}

void
MyCheckBox::MouseDown(BPoint pt)
{
	BView::MouseDown(pt);
}

void
MyCheckBox::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BCheckBox::MouseMoved(pt,tr,msg);
}

void
MyCheckBox::FrameResized(float wi,float he)
{
	BCheckBox::FrameResized(wi,he);
}	

void
MyCheckBox::Draw(BRect rct)
{
	BCheckBox::Draw(rct);
}

void
MyCheckBox::AttachedToWindow(void)
{
}
