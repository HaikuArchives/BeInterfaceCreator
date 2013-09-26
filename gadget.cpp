#include "proto.h"
#include <math.h>
#include <ctype.h>
#include "placement.h"
#include "prjwin.h"
#include "priwindow.h"

extern PriWindow *PriWin;

rgb_color defcolor = { 255,255,255};

bool resize = false,moved = false,drag = false;

BPoint start;
BPoint stx;
int mods;
int fucka,fuckb;

MyView::MyView(BRect b):BView(b,"",B_FOLLOW_ALL,B_FULL_UPDATE_ON_RESIZE|B_FRAME_EVENTS|B_WILL_DRAW)
{
	SetViewColor(defcolor);
}

MyView::~MyView(void)
{
}

void
MyView::MessageReceived(BMessage *msg)
{
	WrkWindow *wi = (WrkWindow *)Window();

	switch(msg->what)
	{
		case	45000:
		{
			BPoint	aPoint;
			BPoint	point;
			int32 sel;

			if (msg->FindPoint("_drop_point_",&aPoint) == B_OK)
			{
				if (msg->FindInt32("sel",&sel) == B_OK)
				{
					PrjWindow *xt;
					struct MyGadget *gd;

					point = aPoint;
					ConvertFromScreen(&point);
	
					if (gd = wi->CreateGadget(sel,(int)point.x,(int)point.y,150,50))
					{
						if (xt = PrjWin)
						{
							xt->ChooseGadget(gd);
						}
					}
				}
			}
		}
		break;
		
		default:
		{
			BView::MessageReceived(msg);
		}
		break;
	}	
}

void
keydown_rtn(BView *view,char *bytes,int32 nb)
{
	WrkWindow *wi = (WrkWindow *)view->Window();
	BPoint pt;
	uint32 but;
	BMessage *bmsg;
	int32 qual = modifiers(),key;
	struct MyGadget *gd = NULL;

	if (view->Parent())
	{
		gd = ((GadView *)view->Parent())->gd;
	}
	
	view->GetMouse(&pt,&but,false);		

	if (nb == 1)
	{
		if (bmsg = wi->CurrentMessage())
		{
			bmsg->FindInt32("modifiers",&qual);

			key = tolower(bytes[0]);

			if (key >= 'a' && key <= 'z') keypress(wi,key - 'a');

			switch(bytes[0])
			{
				case	B_FUNCTION_KEY:
				{
					if (bmsg->FindInt32("key",&key) == B_OK)
					{
						if (qual & B_CONTROL_KEY)
						{
							if (key == B_F1_KEY)
							{
								defcolor = view->ViewColor();							
							}

							if (key == B_F2_KEY)
							{
								prefs.workrect = wi->Frame();
							}
						}

						switch(key)
						{
							case	B_F1_KEY:
							case	B_F2_KEY:
							case	B_F3_KEY:
							case	B_F4_KEY:
							case	B_F5_KEY:
							case	B_F6_KEY:
							case	B_F7_KEY:
							case	B_F8_KEY:
							case	B_F9_KEY:
							case	B_F10_KEY:
							case	B_F11_KEY:
							case	B_F12_KEY:	keypress(wi,key - B_F1_KEY + 26);	break;
						}
					}
				}		
				break;	

				case	B_INSERT:
				{
					PrjWindow *xt;

					gd = wi->CheckPosition((int)pt.x,(int)pt.y);

					if (gd)
					{
						fucka = (int)gd->x;
						fuckb = (int)gd->y;

						if (gd = wi->CreateGadget(prefs.type,(int)pt.x - gd->x,(int)pt.y - gd->y,150,50,true,true))
						{
						}
					}
						else
					{
						if (gd = wi->CreateGadget(prefs.type,(int)pt.x,(int)pt.y,150,50))
						{
						}
					}
				}
				break;

				case	B_DELETE:		if (!prefs.desacdelkey)	wi->DeleteGadget();	break;
				case	B_UP_ARROW:
				{
					gd = wi->sellist.ItemAt(0);

					if (gd && (qual & B_CONTROL_KEY))
					{
						wi->MoveAll(0,-1);
						wi->ResizeGadget(gd->wi,gd->he + 1);
					}
						else
					{
						wi->MoveAll(0,-1);
					}
				}
				break;
	
				case	B_DOWN_ARROW:
				{
					gd = wi->sellist.ItemAt(0);

					if (gd && (qual & B_CONTROL_KEY))
					{
						wi->ResizeGadget(gd->wi,gd->he + 1);
					}
						else
					{
						wi->MoveAll(0,1);
					}
				}
				break;
						
				case	B_RIGHT_ARROW:
				{
					gd = wi->sellist.ItemAt(0);

					if (gd && (qual & B_CONTROL_KEY))
					{
						wi->ResizeGadget(gd->wi + 1,gd->he);
					}
						else
					{
						wi->MoveAll(1,0);
					}
				}
				break;
	
				case	B_LEFT_ARROW:
				{
					gd = wi->sellist.ItemAt(0);

					if (gd && (qual & B_CONTROL_KEY))
					{
						wi->MoveAll(-1,0);
						wi->ResizeGadget(gd->wi + 1,gd->he);
					}
						else
					{
						wi->MoveAll(-1,0);
					}
				}
				break;
			}		
		}
	}
}

void
MyView::KeyDown(const char *bytes,int32 nb)
{
	keydown_rtn(this,bytes,nb);

	BView::KeyDown(bytes,nb);
}

int	ox,oy,diffx,diffy;

void
MyView::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BView::MouseMoved(pt,tr,msg);
}

void
GadView::MouseDown(BPoint pt)
{
	BView::MouseDown(pt);
}

void
GadView::MouseMoved(BPoint pt,uint32 tr,const BMessage *msg)
{
	BView::MouseMoved(pt,tr,msg);
}

void
MyView::MouseUp(BPoint pt)
{
	BView::MouseUp(pt);
}

void
MyView::MouseDown(BPoint pt)
{
	WrkWindow *wi = (WrkWindow *)Window();
	uint32 bt;
	struct MyGadget *gd;
	BPoint where = pt;

	stx = pt;

	wi->Activate();

	mods = modifiers();

    wi->CurrentMessage()->FindInt32(&buttons[0],(int32 *)&bt); 

	resize = drag = moved = false;

	switch(bt)
	{
		case	B_PRIMARY_MOUSE_BUTTON:
		{
			start = pt;

			gd = wi->CheckPosition((int)pt.x,(int)pt.y);

			if	(!gd)
			{
				wi->UnSelectAll();

				if (prefs.autocreate)
				{
					PrjWindow *xt;

					if (gd = wi->CreateGadget(prefs.type,(int)pt.x,(int)pt.y,150,50))
					{
						if (xt = PrjWin)
						{
							xt->ChooseGadget(gd);
						}
					}
				}
			}
/*				else
			{
				int x,y;
				int wid,hei;

				ox = diffx = (int)pt.x - gd->x;
				oy = diffy = (int)pt.y - gd->y;

		       	BRect rect;

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

////OKK

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
			
				{
ok:			    	BeginRectTracking(rect,B_TRACK_RECT_CORNER); 

					resize = true;	

			        do
    	   			{ 
		        	   snooze(30000); 

	    		       GetMouse(&pt,&bt); 

		 	        } while (bt); 
       
    			    EndRectTracking(); 

					wi->Lock();

					rect.SetRightBottom(pt);

					x = MIN(rect.left,rect.right);
					y = MIN(rect.top,rect.bottom);

					wid = abs(rect.IntegerWidth());
					hei = abs(rect.IntegerHeight());

					wi->MoveAllPosition(x,y);

					wi->ResizeGadget(wid - 2,hei - 2);


					moved = drag = false;

					wi->Unlock();
				}
//					else
				{
err:				
					if	(!(mods & B_SHIFT_KEY))
					{
						wi->UnSelectAll();
					}

					if	(!(gd->flag & FLAG_SELECTED))
					{
						wi->Lock();

						wi->AddGadget(gd,true);
	
						wi->PostInfo();

						drag = true;

						wi->Unlock();
					}
				}
			}
*/		}		
		break;
		
		case	B_SECONDARY_MOUSE_BUTTON:
		{
			BPopUpMenu* popup = new BPopUpMenu("");
			BMenuItem	*it;

			popup->SetAsyncAutoDestruct(true);
			popup->SetRadioMode(false);

			drag = moved = false;

			popup->AddItem(it = new BMenuItem(GetMessage(msg_autocreate),new BMessage(MENU_AUTOCREATE)));

			it->SetMarked(prefs.autocreate);

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
			
			ConvertToScreen(&where); 

			popup->Go(where,true,false,false);
		}
		break;
	}			

	BView::MouseDown(pt);
}

rgb_color color_grid = { 0,0,0 };

void
MyView::Draw(BRect rct)
{
	BView::Draw(rct);
	int k;
	
	rct = Frame();
	WrkWindow *win;

	if (win = (WrkWindow *)Window())
	{
		if (win->grid)
		{
			int x,y;
			float wi = rct.Width(),he = rct.Height();

			SetHighColor(color_grid);

			for	(y = 0; y < he; y += win->gridx + 2 - 1)
			{
				StrokeRect(BRect(0,y,wi,y));		
			}

			for	(y = 0; y < wi; y += win->gridy + 2 - 1)
			{
				StrokeRect(BRect(y,0,y,he));		
			}	
		}
	}
}
	
GadView::GadView(struct MyGadget *gd,BRect rct,int type,char *title):BView(rct,"",B_FOLLOW_NONE,B_DRAW_ON_CHILDREN|B_WILL_DRAW)
{
	SetViewColor(255,255,255);

	gad = NULL;

	switch(type)
	{
		case	PASSWORD_KIND:
		case	FLOAT_KIND:
		case	INTEGER_KIND:
		case	STRING_KIND:			gad = new MyString(BRect(1,1,rct.Width() - 1,20),title);							break;
		case	SLIDER_HORIZ_KIND:		gad = new MySlider(gd,BRect(1,1,rct.Width() - 1,B_H_SCROLL_BAR_HEIGHT),B_HORIZONTAL,title);		break;
		case	SLIDER_VERT_KIND:		gad = new MySlider(gd,BRect(1,1,B_V_SCROLL_BAR_WIDTH,rct.Height() - 1),B_VERTICAL,title);			break;
		case	SCROLLER_HORIZ_KIND:	gad = new MyScroller(BRect(1,1,rct.Width() - 1,B_H_SCROLL_BAR_HEIGHT),B_HORIZONTAL);		break;
		case	SCROLLER_VERT_KIND:		gad = new MyScroller(BRect(1,1,B_V_SCROLL_BAR_WIDTH,rct.Height() - 1),B_VERTICAL);		break;
		case	BUTTON_KIND:			gad = new MyButton(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);			break;
		case	MENU_KIND:				gad = new MyButton(BRect(1,1,rct.Width() - 1,rct.Height() - 1),"Menu");			break;
		case	CHECKBOX_KIND:			gad = new MyCheckBox(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);			break;
		case	BOX_KIND:				gad = new MyBox(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);				break;
		case	TAB_KIND:				gad = Create_Tab(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);	break;
		case	MX_KIND:				gad = Create_Mx(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);				break;
		case	RADIO_KIND:				gad = new MyRadio(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);				break;
		case	LISTVIEW_KIND:			gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),0);	break;
		case	LISTVIEW_HORIZ_KIND:	gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),1);	break;
		case	LISTVIEW_VERT_KIND:		gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),2);	break;
		case	LISTVIEW_ALL_KIND:		gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),3);	break;
		case	OUTLISTVIEW_KIND:		gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),0);	break;
		case	OUTLISTVIEW_HORIZ_KIND:	gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),1);	break;
		case	OUTLISTVIEW_VERT_KIND:	gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),2);	break;
		case	OUTLISTVIEW_ALL_KIND:	gad = Create_Lv(BRect(1,1,rct.Width() - 1,rct.Height() - 1),3);	break;
		case	TEDIT_KIND:				gad = Create_TEdit(BRect(1,1,rct.Width() - 1,rct.Height() - 1),0);	break;
		case	TEDIT_HORIZ_KIND:		gad = Create_TEdit(BRect(1,1,rct.Width() - 1,rct.Height() - 1),1);	break;
		case	TEDIT_VERT_KIND:		gad = Create_TEdit(BRect(1,1,rct.Width() - 1,rct.Height() - 1),2);	break;
		case	TEDIT_ALL_KIND:			gad = Create_TEdit(BRect(1,1,rct.Width() - 1,rct.Height() - 1),3);	break;
		case	TEXT_KIND:				gad = new MyText(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);	break;
		case	NUMBER_KIND:			gad = new MyText(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);	break;
		case	COLOR_KIND:				gad = new MyColor(BRect(1,1,150,50));	break;
		case	STATUSBAR_KIND:			gad = new MyStatus(BRect(1,1,rct.Width() - 1,rct.Height() - 1),title);	break;
		case	VIEW_KIND:				gad = new BView(BRect(1,1,rct.Width() - 1,rct.Height() - 1),"",B_WILL_DRAW,B_FOLLOW_ALL);	break;
	}	

	if (gad)
	{
		AddChild(gad);
	}
}

void
GadView::AttachedToWindow(void)
{
}

GadView::~GadView(void)
{
}

void
GadView::DrawAfterChildren(BRect rct)
{
	WrkWindow *wi = (WrkWindow *)Window();

	BView::DrawAfterChildren(rct);

	rct = Bounds();

	SetHighColor(0,0,0);
		
	StrokeRect(BRect(0,0,7,7));

	StrokeRect(BRect(rct.right - 7,rct.bottom - 7,rct.right,rct.bottom));

	StrokeRect(BRect(0,rct.bottom - 7,7,rct.bottom));

	StrokeRect(BRect(rct.right - 7,0,rct.right,7));

	if (gd->flag & FLAG_SELECTED)
	{
		if (gd == wi->sellist.ItemAt(0))
		{
			SetHighColor(255,0,0);
		}
			else
		{
			SetHighColor(44,166,227);
		}	
		
		FillRect(BRect(1,1,6,6));

		FillRect(BRect(rct.right - 6,rct.bottom - 6,rct.right - 1,rct.bottom - 1));

		FillRect(BRect(1,rct.bottom - 6,6,rct.bottom - 1));

		FillRect(BRect(rct.right - 6,1,rct.right - 1,6));
	}
		else
	{
		SetHighColor(255,255,255);
		
		FillRect(BRect(1,1,6,6));

		FillRect(BRect(rct.right - 6,rct.bottom - 6,rct.right - 1,rct.bottom - 1));

		FillRect(BRect(1,rct.bottom - 6,6,rct.bottom - 1));

		FillRect(BRect(rct.right - 6,1,rct.right - 1,6));
	}	
}
