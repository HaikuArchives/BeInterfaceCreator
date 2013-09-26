#include "proto.h"

MySlider::MySlider(struct MyGadget *gd,BRect rct,orientation pos,char *title):BSlider(rct,"",title,NULL,0,15,pos)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);

	gad = gd;
}

MySlider::~MySlider(void)
{
}

void
MySlider::Draw(BRect rct)
{
	BSlider::Draw(rct);
}

void
MySlider::DrawSlider()
{
	BSlider::DrawSlider();
}
