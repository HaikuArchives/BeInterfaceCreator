#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetScroller(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	SpinControl		*c,*d,*e,*f,*g;
	SpinControl		*h,*i;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	h = CreateSpin(MyRect(10,60,180,18),"Min",tab_scroller_min,0,100,gad->data.bscroller.min,16);

	i = CreateSpin(MyRect(10,60,180,18),"Max",tab_scroller_max,0,100,gad->data.bscroller.max,16);

	c = CreateSpin(MyRect(10,85,180,18),GetMessage(msg_focus),tab_scroller_value,0,100,gad->data.bscroller.pos,16);

	d = CreateSpin(MyRect(10,110,180,18),GetMessage(msg_minrange),tab_scroller_minrange,0,100,gad->data.bscroller.minrange,16);

	e = CreateSpin(MyRect(10,135,180,18),GetMessage(msg_maxrange),tab_scroller_maxrange,0,100,gad->data.bscroller.maxrange,16);

	f = CreateSpin(MyRect(10,160,180,18),GetMessage(msg_minstep),tab_scroller_minstep,0,100,gad->data.bscroller.minstep,16);

	g = CreateSpin(MyRect(10,185,180,18),GetMessage(msg_maxstep),tab_scroller_maxstep,0,100,gad->data.bscroller.maxstep,16);

	vie2->AddChild(a);
	vie2->AddChild(h);
	vie2->AddChild(i);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);
	vie2->AddChild(f);
	vie2->AddChild(g);

	SetColorGadget(185);
}

void
set_scroller_value(struct MyGadget *gd,int val)
{
	BScrollBar	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BScrollBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetValue(val);
		}
	}
}

void
set_scroller_minstep(struct MyGadget *gd,int val)
{
	BScrollBar	*bt;
	WrkWindow	*wi;

	float a,b;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BScrollBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->GetSteps(&a,&b);

			bt->SetSteps(val,b);
		}
	}
}

void
set_scroller_maxstep(struct MyGadget *gd,int val)
{
	BScrollBar	*bt;
	WrkWindow	*wi;

	float a,b;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BScrollBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->GetSteps(&a,&b);

			bt->SetSteps(a,val);
		}
	}
}

void
set_scroller_minrange(struct MyGadget *gd,int val)
{
	BScrollBar	*bt;
	WrkWindow	*wi;

	float a,b;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BScrollBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->GetRange(&a,&b);

			bt->SetRange(val,b);
		}
	}
}

void
set_scroller_maxrange(struct MyGadget *gd,int val)
{
	BScrollBar	*bt;
	WrkWindow	*wi;

	float a,b;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BScrollBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->GetRange(&a,&b);

			bt->SetRange(a,val);
		}
	}
}
