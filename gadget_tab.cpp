#include "proto.h"

BView *
Create_Tab(BRect rct,char *title)
{
	BTabView	*bt;
	BTab		*b0;
	BView		*xt;
	int	k;

	if	(bt = new BTabView(rct,""))
	{
		if	(b0 = new BTab())
		{
			BRect rct = bt->Bounds();

			rct.InsetBy(5,5);
			rct.bottom -= bt->TabHeight();	

			if	(xt = new BView(rct,"",B_FOLLOW_ALL,B_WILL_DRAW))
			{
				xt->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

				bt->AddTab(xt,b0);
				
				b0->SetLabel(title);

				return(bt);
			}

			delete b0;
		}

		delete bt;
	}		

	return(NULL);	
}

void
change_gadget_list(struct MyGadget *gd)
{
	char *it;
	int k;

	BAutolock tst(gd->pt->Window());

	switch(gd->type)
	{
		case	MX_KIND:
		{
			BMenuField 	*bt;
			BMenuItem	*ft;
			BMenu		*mn;

			if (bt = (BMenuField *)gd->pt->ChildAt(0))
			{
				if (mn = bt->Menu())
				{
					while (ft = mn->ItemAt(0))
					{
						mn->RemoveItem(ft);
					}

					for (k = 0; k < gd->name.CountItems(); k++)
					{
						if (it = (char *)gd->name.ItemAt(k))
						{
							mn->AddItem(new BMenuItem(it,NULL));
						}
					}
				}

				bt->Invalidate();
			}			
		}
		break;

		case	TAB_KIND:
		{
			MyBTabView 	*bt;
			BTab		*xt;	
			BView		*vx;	

			WrkWindow *wi = (WrkWindow *)gd->pt->Window();

			if (bt = (MyBTabView *)gd->pt->ChildAt(0))
			{
				while (xt = bt->RemoveTab(0));

				for (k = 0; k < gd->name.CountItems(); k++)
				{
					if (it = (char *)gd->name.ItemAt(k))
					{
						if	(xt = new BTab())
						{
							BRect rct = bt->Bounds();

							if	(vx = new BView(rct,"",B_FOLLOW_ALL,B_WILL_DRAW))
							{
								vx->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

								bt->AddTab(vx,xt);
				
								xt->SetLabel(it);
							}
						}
					}	
				}

				bt->Invalidate();
			}
		}
		break;			
	}	
}

