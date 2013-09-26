#include "proto.h"
#include "edit_tags.h"
void
EditButtonWindow::SetLv(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	menu = CreateMenu(this,&selection_lv[0],tab_lv_multi,gad->data.lv.multi);

	b = CreateMx(MyRect(10,35,250,25),GetMessage(msg_selection),menu,16);

	vie2->AddChild(a);
	vie2->AddChild(b);

	SetColorGadget(60);
}

void
EditButtonWindow::SetOLv(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	menu = CreateMenu(this,&selection_lv[0],tab_lv_multi,gad->data.olv.multi);

	b = CreateMx(MyRect(10,35,250,25),GetMessage(msg_selection),menu,16);

	vie2->AddChild(a);
	vie2->AddChild(b);

	SetColorGadget(60);
}
