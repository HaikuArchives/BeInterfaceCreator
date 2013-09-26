#include "proto.h"

MyContainLv::MyContainLv(BRect rct):BView(rct,"",B_FOLLOW_NONE,B_DRAW_ON_CHILDREN|B_WILL_DRAW)
{
}

void
MyContainLv::AttachedToWindow(void)
{
}

void
MyContainLv::Draw(BRect rct)
{
	BView::Draw(rct);
}

void
MyContainLv::DrawAfterChildren(BRect rct)
{
	BView::DrawAfterChildren(rct);
}

BView *
Create_Lv(BRect rct,int type)
{
	BView 		*bt;
	MyContainLv *bt1;
	BScrollView	*sc;
	bool	a = false,b = false;
	
	switch(type)
	{
		case	1:	a = false; b =true;		break;
		case	2:	a = true; b = false;	break;
		case	3:  a = b = true;			break; 
	}
	
	if	(bt = new BListView(BRect(4,4,rct.IntegerWidth() - 4 - ((b) ? 14 : 0),rct.IntegerHeight() - 4 - ((a) ? 14 : 0)),""))
	{
		if (sc = new BScrollView("",bt,B_FOLLOW_ALL,0,a,b))
		{
			if	(a)
			{
				BScrollBar *xi;
				
				if (xi = sc->ScrollBar(B_HORIZONTAL))
				{
					xi->SetRange(0,0);
				}
			}

			if (bt1 = new MyContainLv(rct))
			{
				bt1->AddChild(sc);

				return(bt1);
			}
		}
	}
		
	return(NULL);
}
