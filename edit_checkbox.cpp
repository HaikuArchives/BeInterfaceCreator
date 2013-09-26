#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetCheckBox(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b,*c;

	menu = CreateMenu(this,&true_false[0],12000,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_checkbox_checked,gad->data.bcheckbox.checked);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_value),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_checkbox_enabled,gad->enable);

	c = CreateMx(MyRect(10,60,180,25),GetMessage(msg_enabled),menu,16);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);

	SetColorGadget(95);
}

void
set_checkbox_checked(struct MyGadget *gd,bool def)
{
	BCheckBox 	*bt;
	WrkWindow	*wi;
	
	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BCheckBox *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetValue(def);
		}
	}
}
