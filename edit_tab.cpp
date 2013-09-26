#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetTab(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	SpinControl		*c,*d;
	BButton			*e;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.tab.tabwidth)
	{
		case	B_WIDTH_FROM_WIDEST:	tb = 0;		break;
		case	B_WIDTH_AS_USUAL:		tb = 1;		break;
		case	B_WIDTH_FROM_LABEL:		tb = 2;		break;
	}

	menu = CreateMenu(this,&mtab_width[0],tab_tab_width,tb);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_tabwidth),menu,16);

	c = CreateSpin(MyRect(10,60,180,18),GetMessage(msg_tabheight),tab_tab_height,0,100,gad->data.tab.tabheight,16);

	d = CreateSpin(MyRect(10,85,180,18),GetMessage(msg_selected),tab_tab_selected,0,100,gad->data.tab.sel,16);

	e = CreateButton(MyRect(240,10,120,25),GetMessage(msg_list),tab_tab_list);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);

	SetColorGadget(110);
}

void
set_tab_width(struct MyGadget *gd,int val)
{
	BTabView	*bt;
	WrkWindow	*wi;

	button_width tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTabView *)((GadView *)gd->pt)->ChildAt(0))
		{
			switch(val)
			{
				case	0:	tb = B_WIDTH_FROM_WIDEST;	break;
				case	1:	tb = B_WIDTH_AS_USUAL;		break;
				case	2:	tb = B_WIDTH_FROM_LABEL;	break;
			}			

			bt->SetTabWidth(tb);			

			bt->Invalidate();

			gd->pt->Invalidate();
		}
	}
}

void
set_tab_height(struct MyGadget *gd,int tb)
{
	BTabView	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTabView *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetTabHeight(tb);			

			gd->pt->Invalidate();
		}
	}
}

void
set_tab_select(struct MyGadget *gd,int tb)
{
	BTabView	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTabView *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->Select(tb);			

			gd->pt->Invalidate();
		}
	}
}
