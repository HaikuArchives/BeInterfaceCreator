#include "proto.h"
#include "prjwin.h"
#include "priwindow.h"
#include "placement.h"

BPoint startx,lastx;
struct MyGadget *wsk;

extern PriWindow *PriWin;

void
MouseDown_All(BView *vx,BPoint pt)
{
	GadView		*xt;
	WrkWindow	*wi;
	struct MyGadget *gd;

	uint32 bt;

	if (wi = (WrkWindow *)vx->Window())
	{
	    wi->CurrentMessage()->FindInt32(&buttons[0],(int32 *)&bt); 

		if (xt = (GadView *)vx->Parent())
		{
			switch(bt)
			{
				case	B_PRIMARY_MOUSE_BUTTON:
				{
					int ox,oy,diffx,diffy,x,y;
					int wid,hei;
			       	BRect rect;
					BPoint wh;

					wh = pt;

					xt->ConvertToParent(&pt);

					startx = lastx = pt;

					wsk = xt->gd;

					gd = xt->gd;

					if (modifiers() & B_SHIFT_KEY)
					{
						wi->AddGadget(xt->gd);				
					}
						else
					{
						wi->UnSelectAll();

						wi->AddGadget(xt->gd);				
					}

					ox = diffx = (int)pt.x - gd->x;
					oy = diffy = (int)pt.y - gd->y;


					if (diffx >= gd->wi - 7 && diffy < 7)
					{
						rect.SetLeftBottom(BPoint(gd->x,gd->y)); 
						rect.SetRightTop(BPoint(gd->x + gd->wi,gd->y + gd->he)); 
 					 	goto ok;
					}

					if (diffx < 7 && diffy >= gd->he - 7)
					{
						rect.SetRightTop(BPoint(gd->x,gd->y)); 
						rect.SetLeftBottom(BPoint(gd->x + gd->wi,gd->y + gd->he)); 
	 				 	goto ok;
					}

					if (diffx < 7 && diffy < 7)
					{
						rect.SetRightBottom(BPoint(gd->x,gd->y)); 
						rect.SetLeftTop(BPoint(gd->x + gd->wi,gd->y + gd->he)); 
	 				 	goto ok;
					}

					if (diffx >= gd->wi - 7 && diffy >= gd->he - 7)
					{
						rect.SetLeftTop(BPoint(gd->x,gd->y)); 
						rect.SetRightBottom(pt); 
	 				 	goto ok;
					}

					goto err;
			
ok:			    	wi->bck->BeginRectTracking(rect,B_TRACK_RECT_CORNER); 

			        do
    	   			{ 
		        	   snooze(30000); 

	    		       wi->bck->GetMouse(&pt,&bt); 

		 	        } while (bt); 
       
    			    wi->bck->EndRectTracking(); 

					rect.SetRightBottom(pt); 

					x = MIN(rect.left,rect.right);
					y = MIN(rect.top,rect.bottom);

					wid = abs(rect.IntegerWidth());
					hei = abs(rect.IntegerHeight());

					wi->MoveGadget(gd,x,y);

					wi->ResizeGadget(gd,wid - 2,hei - 2);
err:;			}
				break;
				
				case	B_SECONDARY_MOUSE_BUTTON:
				{
					BPopUpMenu* popup = new BPopUpMenu("");
					BMenuItem	*it;

					popup->SetAsyncAutoDestruct(true);
					popup->SetRadioMode(false);

					popup->AddItem(it = new BMenuItem(GetMessage(msg_creategadget),new BMessage(MENU_CREATEGADGET)));

					popup->AddSeparatorItem();

					popup->AddItem(new BMenuItem(GetMessage(msg_cut), new BMessage(MENU_CUT)));
					popup->AddItem(new BMenuItem(GetMessage(msg_copy), new BMessage(MENU_COPY)));
					popup->AddItem(new BMenuItem(GetMessage(msg_paste), new BMessage(MENU_PASTE)));
					popup->AddSeparatorItem();
					popup->AddItem(new BMenuItem(GetMessage(msg_selectnone),new BMessage(MENU_SELECT_NONE)));
					popup->AddItem(new BMenuItem(GetMessage(msg_selectall), new BMessage(MENU_SELECT_ALL)));
					popup->AddSeparatorItem();
					popup->AddItem(new BMenuItem(GetMessage(msg_delete),new BMessage(MENU_DELETE_GADGET)));

					popup->SetTargetForItems(PriWin);

					vx->ConvertToScreen(&pt); 

					popup->Go(pt,true,false,false);
				}
				break;
			}	
		}
	}
}

void
MouseUp_All(BView *vx)
{
	vx->SetEventMask(NULL);
}

extern int diffx,diffy;

void
MouseMove_All(BView *vx,BPoint pt)
{
	WrkWindow 		*wi;
	GadView			*xt;
	struct MyGadget *gd;

	int k;

	BPoint xx;
	uint32 bt;
	
	vx->GetMouse(&xx,&bt,true);

	if (bt)
	{
		if (wi = (WrkWindow *)vx->Window())
		{
			if (xt = (GadView *)vx->Parent())
			{
				if (lastx != pt)
				{
					if (xt->gd == wsk)
					{
						xt->ConvertToParent(&pt);

						for (k = 0; k < wi->sellist.CountItems(); k++)
						{
							if (gd = wi->sellist.ItemAt(k))
							{
								if (xt = (GadView *)gd->pt)
								{
									xt->MoveTo(gd->x + (pt.x - lastx.x),gd->y + (pt.y - lastx.y));

									gd->x = xt->Frame().left;
									gd->y = xt->Frame().top;
								}
							}	
						}
					}

					wi->PostInfo(true);

					if (PlaceWin)
					{
						BMessage msg(10001);
		
						msg.AddInt32("x",pt.x);		
						msg.AddInt32("y",pt.y);		
		
						PlaceWin->PostMessage(&msg);
					}

					lastx = pt;
				}
			}
		}
	}
}
