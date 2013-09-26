#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetColor(void)
{
	BMenu 			*menu;
	BMenuField  	*a,*b;
	SpinControl		*c;
	BCheckBox		*d;
	ColorView		*e;
	EnStringView	*f;
	BTextControl	*g;

	int tb;

	menu = CreateMenu(this,&true_false[0],tab_focus,gad->focus);

	a = CreateMx(MyRect(10,10,180,25),GetMessage(msg_focus),menu,16);

	switch(gad->data.col.layout)
	{
		case	B_CELLS_4x64:	tb = 0;		break;
		case	B_CELLS_8x32:	tb = 1;		break;
		case	B_CELLS_16x16:	tb = 2;		break;
		case	B_CELLS_32x8:	tb = 3;		break;
		case	B_CELLS_64x4:	tb = 4;		break;
	}

	menu = CreateMenu(this,&layout_color[0],tab_color_layout,tb);

	b = CreateMx(MyRect(10,35,250,25),GetMessage(msg_layout),menu,16);

	g = CreateString(MyRect(10,60,220,25),GetMessage(msg_message),tab_color_message,16);

	c = CreateSpin(MyRect(10,85,180,18),GetMessage(msg_cellsize),tab_color_cellsize,0,100,gad->data.col.cellsize,16);

	d = CreateCheck(MyRect(5,110,150,25),GetMessage(msg_buffereddraw),tab_color_drawbuffered,gad->data.col.redrawbuffer);

	e = new ColorView(MyRect(10,135,40,20),0);

	e->SetColor(gad->data.col.value);

	f = new EnStringView(MyRect(60,135 - 8,250,25),"",GetMessage(msg_setvalue));

	vie2->AddChild(a);
	vie2->AddChild(b);
	vie2->AddChild(c);
	vie2->AddChild(d);
	vie2->AddChild(e);
	vie2->AddChild(f);

	SetColorGadget(160);
}

void
set_color_layout(struct MyGadget *gd,int val)
{
	BColorControl 	*bt;
	WrkWindow		*wi;

	float a,b;

	color_control_layout col;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BColorControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			switch(val)
			{
				case	0:	col = B_CELLS_4x64;		break;
				case	1:	col = B_CELLS_8x32;		break;
				case	2:	col = B_CELLS_16x16;	break;
				case	3:	col = B_CELLS_32x8;		break;
				case	4:	col = B_CELLS_64x4;		break;
			}
			
			bt->SetLayout(col);

			bt->GetPreferredSize(&a,&b);

			gd->pt->ResizeTo(a,b);

			bt->ResizeTo(a,b);

			gd->pt->Invalidate();
		}
	}
}

void
set_color_cellsize(struct MyGadget *gd,int val)
{
	BColorControl 	*bt;
	WrkWindow		*wi;

	float a,b;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BColorControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetCellSize(val);

			bt->GetPreferredSize(&a,&b);

			gd->pt->ResizeTo(a,b);

			bt->ResizeTo(a,b);

			gd->pt->Invalidate();
		}
	}
}

void
set_color_value(struct MyGadget *gd,int val)
{
	BColorControl 	*bt;
	WrkWindow		*wi;

	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BColorControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			bt->SetValue(val);
		}
	}
}

