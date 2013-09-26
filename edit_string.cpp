#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetString(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*c,*d;
	BTextControl	*k;
	SpinControl		*b;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	b = CreateSpin(MyRect(10,35,180,18),GetMessage(msg_divider),tab_string_diviser,0,100,gad->data.string.pixdiv,16);

	switch(gad->data.string.alignlab)
	{
		case	B_ALIGN_LEFT:	tb = 0;		break;
		case	B_ALIGN_RIGHT:	tb = 1;		break;
		case	B_ALIGN_CENTER:	tb = 2;		break;
	}

	menu = CreateMenu(this,&align[0],tab_string_alignlab,tb);

	c = CreateMx(MyRect(10,55,180,25),GetMessage(msg_align_label),menu,16);

	switch(gad->data.string.aligntxt)
	{
		case	B_ALIGN_LEFT:	tb = 0;		break;
		case	B_ALIGN_RIGHT:	tb = 1;		break;
		case	B_ALIGN_CENTER:	tb = 2;		break;
	}

	menu = CreateMenu(this,&align[0],tab_string_aligntxt,tb);

	k = CreateString(MyRect(240,10,220,25),GetMessage(msg_label),tab_string_label,16);

	k->SetText(&gad->data.string.Text[0]);

	d = CreateMx(MyRect(10,80,180,25),GetMessage(msg_align_text),menu,16);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);

	SetColorGadget(105);
}

void
set_string_alignment_text(struct MyGadget *gd,int val)
{
	BTextControl	*bt;
	WrkWindow		*wi;

	alignment xt,tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTextControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->GetAlignment(&xt,&tb);

			switch(val)
			{
				case	B_ALIGN_LEFT:	tb = 0;		break;
				case	B_ALIGN_RIGHT:	tb = 1;		break;
				case	B_ALIGN_CENTER:	tb = 2;		break;
			}
			
			bt->SetAlignment(xt,tb);
		}
	}
}

void
set_string_alignment_label(struct MyGadget *gd,int val)
{
	BTextControl	*bt;
	WrkWindow		*wi;

	alignment xt,tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTextControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->GetAlignment(&tb,&xt);

			switch(val)
			{
				case	B_ALIGN_LEFT:	tb = 0;		break;
				case	B_ALIGN_RIGHT:	tb = 1;		break;
				case	B_ALIGN_CENTER:	tb = 2;		break;
			}
			
			bt->SetAlignment(tb,xt);
		}
	}
}

void
set_string_divider(struct MyGadget *gd,int val)
{
	BTextControl	*bt;
	WrkWindow		*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTextControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetDivider(val);
		}
	}
}

void
set_string_label(struct MyGadget *gd,char *txt)
{
	BTextControl	*bt;
	WrkWindow		*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BTextControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetLabel(txt);
		}
	}
}
