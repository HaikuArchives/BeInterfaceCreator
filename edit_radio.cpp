#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetRadio(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b,*c;
	BButton			*d;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_radio_value,gad->data.rad.val);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_value),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_radio_enable,gad->enable);

	c = CreateMx(MyRect(10,60,180,25),GetMessage(msg_enabled),menu,16);

	d = CreateButton(MyRect(240,10,120,25),GetMessage(msg_list),tab_tab_list);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);

	SetColorGadget(95);
}

void
set_radio_checked(struct MyGadget *gd,int tb)
{
	BRadioButton	*bt;
	WrkWindow		*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BRadioButton *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetValue(tb);
		}
	}
}

void
set_radio_enabled(struct MyGadget *gd,int tb)
{
	BRadioButton	*bt;
	WrkWindow		*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BRadioButton *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetEnabled(tb);
		}
	}
}
