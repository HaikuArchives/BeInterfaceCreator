#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetStatus(void)
{
	BMenu 			*menu;
	BMenuField  	*a;
	BTextControl	*b,*c;
	SpinControl		*d,*e,*f;
	ColorView		*g;
	EnStringView	*h;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	b = CreateString(MyRect(10,35,220,25),GetMessage(msg_label),tab_status_label,16);

	b->SetText(&gad->data.sta.Label[0]);

	c = CreateString(MyRect(10,60,220,25),GetMessage(msg_trail),tab_status_trail,16);

	c->SetText(&gad->data.sta.Trail[0]);

	d = CreateSpin(MyRect(10,85,180,18),GetMessage(msg_value),tab_status_value,0,100,gad->data.sta.value,16);

	e = CreateSpin(MyRect(10,110,180,18),GetMessage(msg_maxvalue),tab_status_max,0,100,gad->data.sta.maxvalue,16);

	f = CreateSpin(MyRect(10,135,180,18),GetMessage(msg_barheight),tab_status_barheight,0,100,gad->data.sta.barheight,16);

	g = new ColorView(MyRect(10,170,40,20),CHANGE_BARCOLOR);

	g->SetColor(gad->data.sta.barcolor);

	h = new EnStringView(MyRect(60,170 - 8,250,25),"",GetMessage(msg_barcolor));

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);
	vie2->AddChild(f);
	vie2->AddChild(g);
	vie2->AddChild(h);

	SetColorGadget(195);
}

void
set_status_barheight(struct MyGadget *gd,int val)
{
	BStatusBar 	*bt;
	WrkWindow	*wi;
	
	int old;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStatusBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			old = bt->CurrentValue();

			bt->Reset();

			bt->SetBarHeight(val);

			bt->Update(old,&gd->data.sta.Label[0],&gd->data.sta.Trail[0]);

			bt->Invalidate();
		}
	}
}

void
set_status_barcolor(struct MyGadget *gd,int val)
{
	BStatusBar 	*bt;
	WrkWindow	*wi;

	rgb_color cl = GetRgbFromInteger(val);
	int old;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStatusBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			old = bt->CurrentValue();

			bt->Reset();

			bt->SetBarColor(cl);

			bt->Update(old,&gd->data.sta.Label[0],&gd->data.sta.Trail[0]);

			bt->Invalidate();
		}
	}
}

void
set_status_value(struct MyGadget *gd,int val)
{
	BStatusBar 	*bt;
	WrkWindow	*wi;
	
	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStatusBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->Reset();

			bt->Update(val - bt->CurrentValue(),&gd->data.sta.Label[0],&gd->data.sta.Trail[0]);

			bt->Invalidate();
		}
	}
}

void
set_status_maxvalue(struct MyGadget *gd,int val)
{
	BStatusBar 	*bt;
	WrkWindow	*wi;
	
	int old;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStatusBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			old = bt->CurrentValue();

			bt->Reset();

			bt->SetMaxValue(val);

			bt->Update(old,&gd->data.sta.Label[0],&gd->data.sta.Trail[0]);

			bt->Invalidate();
		}
	}
}

void
set_status_label(struct MyGadget *gd,char *txt)
{
	BStatusBar 	*bt;
	WrkWindow	*wi;
	
	int old;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStatusBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			old = bt->CurrentValue();

			bt->Reset();

			bt->SetText(txt);

			bt->Update(old,&gd->data.sta.Label[0],&gd->data.sta.Trail[0]);

			bt->Invalidate();
		}
	}
}

void
set_status_trail(struct MyGadget *gd,char *txt)
{
	BStatusBar 	*bt;
	WrkWindow	*wi;
	
	int old;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStatusBar *)((GadView *)gd->pt)->ChildAt(0))
		{
			old = bt->CurrentValue();

			bt->Reset();

			bt->SetTrailingText(txt);

			bt->Update(old,&gd->data.sta.Label[0],&gd->data.sta.Trail[0]);

			bt->Invalidate();
		}
	}
}
