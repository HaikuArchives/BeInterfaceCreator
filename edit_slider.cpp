#include "proto.h"
#include "edit_tags.h"

char *slider_style[] =
{
	"B_BLOCK_THUMB",
	"B_TRIANGLE_THUMB",
	NULL
};	

void
EditButtonWindow::SetSlider(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b,*c;
	SpinControl		*d,*e,*f,*g,*h,*i;
	BTextControl	*j,*k,*r,*s;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.bslider.hashtype)
	{
		case	B_HASH_MARKS_NONE:		tb = 0;	break;
		case	B_HASH_MARKS_TOP:		tb = 1;	break;
		case	B_HASH_MARKS_BOTTOM:	tb = 2;	break;
		case	B_HASH_MARKS_BOTH:		tb = 3;	break;
	}

	menu = CreateMenu(this,&hashmarks[0],tab_slider_hashtype,tb);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_hashmarks),menu,16);

	switch(gad->data.bslider.style)
	{
		case	B_BLOCK_THUMB:		tb = 0;	break;
		case	B_TRIANGLE_THUMB:	tb = 1;	break;
	}

	menu = CreateMenu(this,&slider_style[0],tab_slider_style,tb);

	c = CreateMx(MyRect(10,60,180,25),GetMessage(msg_style),menu,16);

	d = CreateSpin(MyRect(10,90,180,18),GetMessage(msg_min),tab_slider_min,0,100,gad->data.bslider.min,16);

	e = CreateSpin(MyRect(10,110,180,18),GetMessage(msg_max),tab_slider_max,0,100,gad->data.bslider.max,16);

	f = CreateSpin(MyRect(10,130,180,18),GetMessage(msg_thickness),tab_slider_thickness,0,100,gad->data.bslider.thickness,16);

	g = CreateSpin(MyRect(10,150,180,18),GetMessage(msg_hashcount),tab_slider_hashcount,0,100,gad->data.bslider.hashcount,16);

	h = CreateSpin(MyRect(10,170,180,18),GetMessage(msg_keyinc),tab_slider_keyinc,0,100,gad->data.bslider.keyinc,16);

	i = CreateSpin(MyRect(10,190,180,18),GetMessage(msg_value),tab_slider_value,0,100,gad->data.bslider.pos,16);

//	r = CreateString(MyRect(240,10,220,25),GetMessage(msg_label),tab_slider_label,16);

//	s = CreateString(MyRect(240,35,220,25),GetMessage(msg_message),tab_slider_message,16);

	j = CreateString(MyRect(240,60,220,25),GetMessage(msg_minlabel),tab_slider_minlabel,16);

	k = CreateString(MyRect(240,85,220,25),GetMessage(msg_maxlabel),tab_slider_maxlabel,16);

//	r->SetText(&gad->data.bslider.Label[0]);
	j->SetText(&gad->data.bslider.MinLabel[0]);
	k->SetText(&gad->data.bslider.MaxLabel[0]);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);
	vie2->AddChild(f);
	vie2->AddChild(g);
	vie2->AddChild(h);
	vie2->AddChild(i);
	vie2->AddChild(j);
	vie2->AddChild(k);

	SetColorGadget(215);
}

void
invalidate_slider(BSlider *vx)
{
	vx->Invalidate();
}

void
set_slider_value(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetValue(val);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_style(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	thumb_style tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			switch(val)
			{
				case	0: tb = B_BLOCK_THUMB;		break;
				case	1: tb = B_TRIANGLE_THUMB;	break;
			}

			bt->SetStyle(tb);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_keyinc(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetKeyIncrementValue(val);
		}
	}
}

void
set_slider_thickness(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetBarThickness(val);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_hashcount(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetHashMarkCount(val);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_hashtype(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	hash_mark_location tb;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			switch(val)
			{
				case	0: tb = B_HASH_MARKS_NONE;		break;
				case	1: tb = B_HASH_MARKS_TOP;		break;
				case	2: tb = B_HASH_MARKS_BOTTOM;	break;
				case	3: tb = B_HASH_MARKS_BOTH;		break;
			}

			bt->SetHashMarks(tb);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_barcolor(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	rgb_color cl = GetRgbFromInteger(val);

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetBarColor(cl);
		}
	}
}

void
set_slider_fillcolor(struct MyGadget *gd,int val)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	rgb_color cl = GetRgbFromInteger(val);

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->UseFillColor(true,&cl);
		}
	}
}

void
set_slider_minlabel(struct MyGadget *gd,char *txt)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetLimitLabels(txt,&gd->data.bslider.MaxLabel[0]);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_label(struct MyGadget *gd,char *txt)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetLabel(txt);

			invalidate_slider(bt);
		}
	}
}

void
set_slider_maxlabel(struct MyGadget *gd,char *txt)
{
	BSlider	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BSlider *)((GadView *)gd->pt))
		{
			bt->SetLimitLabels(&gd->data.bslider.MinLabel[0],txt);

			invalidate_slider(bt);
		}
	}
}

