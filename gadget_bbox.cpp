#include "proto.h"

MyBox::MyBox(BRect rct,char *title):BBox(rct,"")
{
	SetFlags(B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW);

	SetLabel(title);
}

MyBox::~MyBox(void)
{
}

void
MyBox::MouseDown(BPoint pt)
{
	BView::MouseDown(pt);
}

void
MyBox::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BBox::MouseMoved(pt,tr,msg);
}

void
MyBox::FrameResized(float wi,float he)
{
	BBox::FrameResized(wi,he);
}	

void
MyBox::AttachedToWindow(void)
{
}

void
DrawGadget(BView *view)
{
	WrkWindow *wi = (WrkWindow *)view->Window();
	GadView *vx;
	BRect rct = view->Frame();

	if (vx = (GadView *)view->Parent())
	{
		if (vx->gd->flag & FLAG_SELECTED)
		{
			if (vx->gd == wi->sellist.ItemAt(0))
			{
				view->SetHighColor(255,0,0);
			}
				else
			{
				view->SetHighColor(44,166,227);
			}	
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
}
