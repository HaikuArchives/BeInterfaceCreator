#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetButton(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b,*c;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_button_default,gad->data.button.defaut);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_default),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_button_enabled,gad->enable);

	c = CreateMx(MyRect(10,60,180,25),GetMessage(msg_enabled),menu,16);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);

	SetColorGadget(95);
}

void
set_button_defaut(struct MyGadget *gd,bool def)
{
	BButton 	*bt;
	WrkWindow	*wi;
	
	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BButton *)((GadView *)gd->pt)->ChildAt(0))
		{
			wi->SetDefaultButton((def) ? bt : NULL);
		}
	}
}

void
set_button_enable(struct MyGadget *gd,bool def)
{
	BButton 	*bt;
	WrkWindow	*wi;
	
	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BButton *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetEnabled(def);
		}
	}
}

void
set_button_label(struct MyGadget *gd,char *def)
{
	BButton 	*bt;
	WrkWindow	*wi;
	
	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);
	
		if (bt = (BButton *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetLabel(def);
		}
	}
}
