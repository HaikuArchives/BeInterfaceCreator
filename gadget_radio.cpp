#include "proto.h"

MyRadio::MyRadio(BRect rct,char *title):BRadioButton(rct,"",title,NULL)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyRadio::~MyRadio(void)
{
}

void
MyRadio::MouseDown(BPoint pt)
{
	BRadioButton::MouseDown(pt);
}

void
MyRadio::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BRadioButton::MouseMoved(pt,tr,msg);
}

void
MyRadio::FrameResized(float wi,float he)
{
	BRadioButton::FrameResized(wi,he);
}	

void
MyRadio::AttachedToWindow(void)
{
}

void
MyRadio::Draw(BRect rct)
{
	BRadioButton::Draw(rct);
}

void
MyRadio::DrawAfterChildren(BRect rct)
{
	BRadioButton::DrawAfterChildren(rct);
}
