#include "proto.h"

BView *
Create_TEdit(BRect rct,int type)
{
	BView 		*bt;
	BScrollView	*sc;
	MyContainLv *bt1;
	bool	a = false,b = false;
	
	switch(type)
	{
		case	1:	a = false; b =true;		break;
		case	2:	a = true; b = false;	break;
		case	3:  a = b = true;			break; 
	}
	
	BRect kt = BRect(4,4,rct.IntegerWidth() - 4 - ((b) ? 14 : 0),rct.IntegerHeight() - 4 - ((a) ? 14 : 0));

	if	(bt = new BTextView(kt,"",BRect(5,5,kt.Width()-5,kt.Height()-5),B_FOLLOW_NONE,B_WILL_DRAW))
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
