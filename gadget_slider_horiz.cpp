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
	uint32 but;
	int wi,he;
	
	if (Window()->CurrentMessage()->FindInt32("buttons", (int32 *)&but) == B_NO_ERROR)
	{
		if (but & B_PRIMARY_MOUSE_BUTTON)
		{
			wi = (int)Bounds().IntegerWidth();
			he = (int)Bounds().IntegerHeight();

			SetMouseEventMask(B_POINTER_EVENTS);

			selected = (GadView *)Parent();

			offx = (int)pt.x;
			offy = (int)pt.y;

			selected->sel = true;

			selected->Draw(selected->Bounds());

			selected->resize = false;

			start = pt;

			if (offx <= 7 && offy <= 7)				selected->resize = 1;
			if (offx >= wi - 7 && offy <= 7)		selected->resize = 2;
			if (offx <= 7 && offy >= he - 7)		selected->resize = 3;
			if (offx >= wi - 7 && offy >= he - 7)	selected->resize = 4;
		}
	}	

	BView::MouseDown(pt);
}

void
MyCheckBox::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	GadView *vx;
	BPoint rt;

	uint32 but = 0;

	GetMouse(&rt,&but);

	char buf[100];
	
	sprintf(&buf[0],"%04d - %04d",(pt.x) >= 0 ? (int)pt.x : 0,(pt.y) >= 0 ? (int)pt.y : 0);
	
	Window()->SetTitle(&buf[0]);
		
	if (selected)
	{
		if (but && selected->resize)
		{
			BRect rct = Frame();
			float wi = rct.Width(),he = rct.Height();
			int diffx = pt.x - start.x;
			int diffy = pt.y - start.y;
		}
	}
	
	start = pt;	

	BCheckBox::MouseMoved(pt,tr,msg);
}

void
MyCheckBox::FrameResized(float wi,float he)
{
	BCheckBox::FrameResized(wi,he);

	Parent()->Invalidate();
}	

void
MyCheckBox::Draw(BRect rct)
{
	BCheckBox::Draw(rct);
	
	DrawGadget(this);
}
