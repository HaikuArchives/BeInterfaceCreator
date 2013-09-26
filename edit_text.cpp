#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetText(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	BTextControl	*c;

	char tmp[200],*buf = &tmp[0];

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.txt.align)
	{
		case	B_ALIGN_LEFT:	tb = 0;		break;
		case	B_ALIGN_RIGHT:	tb = 1;		break;
		case	B_ALIGN_CENTER:	tb = 2;		break;
	}
	
	menu = CreateMenu(this,&align[0],tab_text_align,tb);

	b = CreateMx(MyRect(10,35,250,25),GetMessage(msg_alignment),menu,16);

	c = CreateString(MyRect(10,60,220,25),GetMessage(msg_label),tab_text_label,16);

	c->SetText(&gad->data.txt.Label[0]);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);

	SetColorGadget(85);
}

void
EditButtonWindow::SetNumber(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	BTextControl	*c;
	MyFilterInteger	*fi;

	char tmp[200],*buf = &tmp[0];

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.num.align)
	{
		case	B_ALIGN_LEFT:	tb = 0;		break;
		case	B_ALIGN_RIGHT:	tb = 1;		break;
		case	B_ALIGN_CENTER:	tb = 2;		break;
	}

	menu = CreateMenu(this,&align[0],tab_number_align,tb);

	b = CreateMx(MyRect(10,35,250,25),GetMessage(msg_alignment),menu,16);

	c = CreateString(MyRect(10,60,220,25),GetMessage(msg_number),tab_number_number,16);

	c->SetText(&gad->data.num.Label[0]);

	if	(fi = new MyFilterInteger())
	{
		c->TextView()->AddFilter((BMessageFilter *)fi);
	}

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);

	SetColorGadget(85);
}

void
set_text_align(struct MyGadget *gd,int val)
{
	BStringView	*bt;
	WrkWindow	*wi;

	alignment tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStringView *)((GadView *)gd->pt)->ChildAt(0))
		{
			switch(val)
			{
				case	0: tb = B_ALIGN_LEFT;	break;
				case	1: tb = B_ALIGN_RIGHT;	break;
				case	2: tb = B_ALIGN_CENTER;	break;
			}

			bt->SetAlignment(tb);
		}
	}
}

void
set_number_value(struct MyGadget *gd,int val)
{
	BStringView	*bt;
	WrkWindow	*wi;

	char tmp[200],*buf = &tmp[0];

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStringView *)((GadView *)gd->pt)->ChildAt(0))
		{
			sprintf(buf,"%d",val);

			bt->SetText(buf);
		}
	}
}

void
set_text_text(struct MyGadget *gd,char *txt)
{
	BStringView	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BStringView *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetText(txt);
		}
	}
}

