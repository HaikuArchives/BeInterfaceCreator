#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetMx(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	SpinControl		*c;
	BTextControl	*d;
	BButton			*e;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.mx.align)
	{
		case	B_ALIGN_LEFT:	tb = 0;		break;
		case	B_ALIGN_RIGHT:	tb = 1;		break;
		case	B_ALIGN_CENTER:	tb = 2;		break;
	}

	menu = CreateMenu(this,&align[0],tab_mx_align,tb);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_alignment),menu,16);

	c = CreateSpin(MyRect(10,60,180,18),GetMessage(msg_divider),tab_mx_diviser,0,100,gad->data.mx.pixdiv,16);

	d = CreateString(MyRect(10,85,220,25),GetMessage(msg_label),tab_mx_label,16);

	d->SetText(&gad->data.mx.Label[0]);

	e = CreateButton(MyRect(240,10,120,25),GetMessage(msg_list),tab_tab_list);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);

	SetColorGadget(110);
}

void
set_mx_align(struct MyGadget *gd,int val)
{
	BMenuField	*bt;
	WrkWindow	*wi;

	alignment tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BMenuField *)((GadView *)gd->pt)->ChildAt(0))
		{
			switch(val)
			{
				case	0: tb = B_ALIGN_LEFT;		break;
				case	1: tb = B_ALIGN_RIGHT;		break;
				case	2: tb = B_ALIGN_CENTER;		break;
			}

			bt->SetAlignment(tb);

			bt->Invalidate();
		}
	}
}

void
set_mx_label(struct MyGadget *gd,char *txt)
{
	BMenuField	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BMenuField *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetLabel(txt);
		}
	}
}

void
set_mx_divider(struct MyGadget *gd,int val)
{
	BMenuField	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BMenuField *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetDivider(val);
		}
	}
}

void
set_mx_select(struct MyGadget *gd,int val)
{
	BMenuField	*bt;
	WrkWindow	*wi;

	BMenu		*mn;
	BMenuItem	*it;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BMenuField *)((GadView *)gd->pt)->ChildAt(0))
		{
			if (mn = bt->Menu())
			{
				if (it = mn->FindMarked())
				{
					it->SetMarked(false);
				}

				if (it = mn->ItemAt(val))
				{
					it->SetMarked(true);
				}
			}
		}
	}
}
