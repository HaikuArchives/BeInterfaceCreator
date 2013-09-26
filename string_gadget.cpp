#include "proto.h"

MyBox::MyBox(BRect rct,char *title):BBox(rct,"")
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);
}

MyBox::~MyBox(void)
{
}

void
MyBox::MouseDown(BPoint pt)
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
MyBox::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
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

	BBox::MouseMoved(pt,tr,msg);
}

void
MyBox::FrameResized(float wi,float he)
{
	BBox::FrameResized(wi,he);

	Parent()->Invalidate();
}	

void
DrawGadget(BView *view)
{
	GadView *vx;
	BRect rct = view->Bounds();

	if (vx = (GadView *)view->Parent())
	{
		if (vx->sel)
		{
			view->SetHighColor(255,0,0);
		}
			else
		{
			view->SetHighColor(255,255,255);
		}	
		
		view->FillRect(BRect(0,0,5,5));

		view->FillRect(BRect(rct.right - 5,0,rct.right,5));

		view->FillRect(BRect(0,rct.bottom - 5,5,rct.bottom));

		view->FillRect(BRect(rct.right - 5,rct.bottom - 5,rct.right,rct.bottom));

		view->SetHighColor(0,0,0);
	
		view->StrokeLine(BPoint(0,6),BPoint(5,6));
		view->StrokeLine(BPoint(6,0),BPoint(6,6));

		view->StrokeLine(BPoint(rct.right - 5,6),BPoint(rct.right,6));
		view->StrokeLine(BPoint(rct.right - 6,0),BPoint(rct.right - 6,6));

		view->StrokeLine(BPoint(0,rct.bottom - 6),BPoint(6,rct.bottom - 6));
		view->StrokeLine(BPoint(6,rct.bottom - 6),BPoint(6,rct.bottom));

		view->StrokeLine(BPoint(rct.right - 5,rct.bottom - 6),BPoint(rct.right,rct.bottom - 6));
		view->StrokeLine(BPoint(rct.right - 6,rct.bottom - 6),BPoint(rct.right - 6,rct.bottom));
	}
}

void
MyBox::Draw(BRect rct)
{
	BBox::Draw(rct);

	DrawGadget(this);
}
