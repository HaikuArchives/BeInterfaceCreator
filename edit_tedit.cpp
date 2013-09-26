#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetEdit(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b,*c,*d,*e,*f,*g;
	SpinControl		*h,*i;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.edi.align)
	{
		case	B_ALIGN_LEFT:	tb = 0;		break;
		case	B_ALIGN_RIGHT:	tb = 1;		break;
		case	B_ALIGN_CENTER:	tb = 2;		break;
	}

	menu = CreateMenu(this,&align[0],tab_tedit_align,tb);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_alignment),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_tedit_selectable,gad->data.edi.selectable);

	c = CreateMx(MyRect(10,60,180,25),GetMessage(msg_selectable),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_tedit_editable,gad->data.edi.editable);

	d = CreateMx(MyRect(10,85,180,25),GetMessage(msg_editable),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_tedit_wordwrap,gad->data.edi.wordwrap);

	e = CreateMx(MyRect(10,110,180,25),GetMessage(msg_wordwrap),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_tedit_setstylable,gad->data.edi.stylable);

	f = CreateMx(MyRect(10,135,180,25),GetMessage(msg_setstylable),menu,16);

	menu = CreateMenu(this,&true_false[0],tab_tedit_autoident,gad->data.edi.autoident);

	g = CreateMx(MyRect(10,160,180,25),GetMessage(msg_autoindent),menu,16);

	h = CreateSpin(MyRect(10,185,180,18),GetMessage(msg_tabwidth),tab_tedit_tabwidth,0,100,gad->data.edi.tabwidth,16);

	i = CreateSpin(MyRect(10,210,180,18),GetMessage(msg_maxbytes),tab_tedit_maxbytes,0,100,gad->data.edi.maxchars,16);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);
	vie2->AddChild(f);
	vie2->AddChild(g);
	vie2->AddChild(h);
	vie2->AddChild(i);

	SetColorGadget(225);
}
