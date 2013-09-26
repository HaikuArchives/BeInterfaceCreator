#include "proto.h"
#include "edit_tags.h"

void
ChangeColor(int id,rgb_color cl)
{
	WrkWindow		*wi;
	struct MyGadget	*gd;

	BView	*vx;

	if (wi = DefWin)
	{
		BAutolock tst(wi);

		if (gd = wi->sellist.ItemAt(0))
		{
			if (vx = (BView *)gd->pt->ChildAt(0))
			{
				goto ok;
			}
		}
			else
		{
			if (vx = (BView *)wi->bck)
			{
ok:				switch(id)
				{
					case	CHANGE_VIEWCOLOR:	vx->SetViewColor(cl);	break;	
					case	CHANGE_HIGHCOLOR:	vx->SetHighColor(cl);	break;	
					case	CHANGE_LOWCOLOR:	vx->SetLowColor(cl);	break;	
					case	CHANGE_BARCOLOR:	((BStatusBar *)vx)->SetBarColor(cl);	break;	
				}

				if (gd)
				{
					gd->pt->Invalidate();
				}
					else
				{
					vx->Invalidate();
				}	
			}	
		}
	}
}

void
EditButtonWindow::SetColorGadget(int pos)
{
	WrkWindow		*wi;
	struct MyGadget	*gd;

	ColorView		*d,*f,*h;
	EnStringView	*e,*g,*i;

	d = new ColorView(MyRect(10,pos,40,20),CHANGE_VIEWCOLOR);

	e = new EnStringView(MyRect(60,pos - 8,200,25),"",GetMessage(msg_viewcolor));

	f = new ColorView(MyRect(10,pos + 25,40,20),CHANGE_HIGHCOLOR);

	g = new EnStringView(MyRect(60,pos + 25 - 8,200,25),"",GetMessage(msg_highcolor));

	h = new ColorView(MyRect(10,pos + 50,40,20),CHANGE_LOWCOLOR);

	i = new EnStringView(MyRect(60,pos + 50 - 8,200,25),"",GetMessage(msg_lowcolor));

	if (wi = DefWin)
	{
		BAutolock tst(wi);

		if (gd = wi->sellist.ItemAt(0))
		{
			d->SetColor(gd->pt->ViewColor());		
			f->SetColor(gd->pt->HighColor());		
			h->SetColor(gd->pt->LowColor());		
		}
			else
		{
			d->SetColor(wi->bck->ViewColor());		
			f->SetColor(wi->bck->HighColor());		
			h->SetColor(wi->bck->LowColor());		
		}	
	}

	vie2->AddChild(d);
	vie2->AddChild(e);
	vie2->AddChild(f);
	vie2->AddChild(g);
	vie2->AddChild(h);
	vie2->AddChild(i);
}

void
EditButtonWindow::SetBbox(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	BTextControl	*c;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = new BMenuField(MyRect(10,10,180,25),"",GetMessage(msg_focus),menu);

	SetDivider(a,16);

	switch(gad->data.bbox.style)
	{
		case	B_PLAIN_BORDER:	tb = 0;	break;
		case	B_FANCY_BORDER:	tb = 1;	break;
		case	B_NO_BORDER:	tb = 2;	break;
	}	

	menu = CreateMenu(this,&border_bbox[0],tab_bbox_border,tb);

	b = CreateMx(MyRect(10,35,180,25),GetMessage(msg_border),menu,16);

	c = CreateString(MyRect(10,60,220,25),GetMessage(msg_label),tab_bbox_label,16);

	c->SetText(&gad->data.bbox.Label[0]);

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);

	SetColorGadget(95);
}

void
set_bbox_border(struct MyGadget *gd,int border)
{
	BBox	 	*bt;
	WrkWindow	*wi;

	border_style def;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BBox *)((GadView *)gd->pt)->ChildAt(0))
		{
			switch(border)
			{
				case	0:	def = B_PLAIN_BORDER;	break;
				case	1:	def = B_FANCY_BORDER;	break;
				case	2:	def = B_NO_BORDER;		break;
			}

			bt->SetBorder(def);
		}
	}
}

void
set_bbox_label(struct MyGadget *gd,char *txt)
{
	BBox	 	*bt;
	WrkWindow	*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BBox *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetLabel(txt);
		}
	}
}
