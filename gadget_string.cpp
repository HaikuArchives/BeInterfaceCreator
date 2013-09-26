#include "proto.h"

MyString::MyString(BRect rct,char *title):BTextControl(rct,"",title,"",NULL)
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyString::~MyString(void)
{
}

void
MyString::MouseDown(BPoint pt)
{
	BView::MouseDown(pt);
}

void
MyString::Draw(BRect rct)
{
	BTextControl::Draw(rct);
}

void
MyString::DrawAfterChildren(BRect rct)
{
	BTextControl::DrawAfterChildren(rct);
}

void
MyString::AttachedToWindow(void)
{
	float a,b;

	GetPreferredSize(&a,&b);

	ResizeTo(a,b);
}
