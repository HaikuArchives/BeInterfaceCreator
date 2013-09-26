#include <InterfaceKit.h>

#include "proto.h"
#include "placement.h"
#include "prjwin.h"
#include "edit_tags.h"

extern char *array_type[];

WrkWindow::WrkWindow(BRect rct,char *title):BWindow(rct,title,B_TITLED_WINDOW,B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BFont font;
	font_family a;
	font_style  b;

	_Init();

	AddShortcut('m',B_RIGHT_CONTROL_KEY,new BMessage(B_QUIT_REQUESTED));

	sprintf(&Name[0],"form%d",projet.CountItems() + 1);

	bck = new MyView(Bounds());
	
	AddChild(bck);

	bck->GetFont(&font);

	font.GetFamilyAndStyle(&a,&b);

	strcpy(&FontName[0],a);
	strcpy(&FontStyle[0],b);

	FontSize = (int)font.Size();

	PostInfo();
}

void
WrkWindow::_Init(void)
{
	float a,b,c,d;
	int res = 0,nb;

	GetSizeLimits(&a,&b,&c,&d);

	minw  = (int)a;
	maxw  = (int)b;
	minh  = (int)c;
	maxh  = (int)d;

	strcpy(&WTitle[0],"");

	feel = look = typewin = wrk = flag = Style = 0;
	
	FontType = 0;

	Visible = Closable = Movable = Resizable = true;

	idcmp = WIN_EVENTS12;

	FontAntiliasing = grid = undelete = false;
	
	gridx = gridy = spacex = spacey = 5;

	nb = (int)Flags();
				
	if (nb & B_NOT_MOVABLE)					res |= (1L << 0);
	if (nb & B_NOT_CLOSABLE)				res |= (1L << 1);
	if (nb & B_NOT_ZOOMABLE)				res |= (1L << 2);
	if (nb & B_NOT_MINIMIZABLE)				res |= (1L << 3);
	if (nb & B_NOT_H_RESIZABLE)				res |= (1L << 4);
	if (nb & B_NOT_V_RESIZABLE)				res |= (1L << 5);
	if (nb & B_NOT_RESIZABLE)				res |= (1L << 6);
	if (nb & B_OUTLINE_RESIZE)				res |= (1L << 7);
	if (nb & B_WILL_ACCEPT_FIRST_CLICK)		res |= (1L << 8);
	if (nb & B_AVOID_FRONT)					res |= (1L << 9);
	if (nb & B_AVOID_FOCUS)					res |= (1L << 10);
	if (nb & B_NO_WORKSPACE_ACTIVATION)		res |= (1L << 11);
	if (nb & B_NOT_ANCHORED_ON_ACTIVATE)	res |= (1L << 12);
	if (nb & B_ASYNCHRONOUS_CONTROLS)		res |= (1L << 13);

	flag = res;
}

void
WrkWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);

	bck->LockLooper();

	bck->ResizeTo(wi,he);

	bck->Invalidate();

	bck->UnlockLooper();

	PostInfo(true);

	change_infowin_number(WWidth,(int)wi);
	change_infowin_number(WHeight,(int)he);
}

void
WrkWindow::FrameMoved(BPoint pt)
{
//	BMessage msg(52000);

	BWindow::FrameMoved(pt);

/*	msg.AddInt32("x",(int)pt.x);
	msg.AddInt32("y",(int)pt.y);

	PostMessage(&msg);
*/
	PostInfo(true);

	change_infowin_number(WLeft,(int)pt.x);
	change_infowin_number(WTop,(int)pt.y);
}

void
WrkWindow::PostInfo(bool empty = false)
{
	BRect rct = Frame();
	struct MyGadget *gd;
	int nb;

	BMessage msg(51000);
	
	if (PlaceWin)
	{
		if (!(nb = sellist.CountItems()))
		{
			msg.AddInt32("x",(DefWin) ? (int)rct.left : -55555);	
			msg.AddInt32("y",(DefWin) ? (int)rct.top : -55555);	
			msg.AddInt32("w",(DefWin) ? (int)rct.IntegerWidth() : -55555);	
			msg.AddInt32("h",(DefWin) ? (int)rct.IntegerHeight() : -55555);	
			msg.AddInt32("f",(DefWin) ? flag : -55555);	
		}
			else
		{
			if (gd = (struct MyGadget *)sellist.ItemAt(0))
			{
				msg.AddInt32("x",gd->x);	
				msg.AddInt32("y",gd->y);	
				msg.AddInt32("w",gd->wi);	
				msg.AddInt32("h",gd->he);	
				msg.AddInt32("f",gd->flag);	
			}
		}	
		
		PlaceWin->PostMessage(&msg);

		{
			BMessage msg(10002);
		
			msg.AddInt32("nb",sellist.CountItems());		
		
			PlaceWin->PostMessage(&msg);
		}

		{
			BMessage msg(10003);
		
			msg.AddInt32("type",prefs.type);		
		
			PlaceWin->PostMessage(&msg);
		}
	}	

	if (EditorWin && !empty)
	{
		EditorWin->ChangeGui((struct MyGadget *)sellist.ItemAt(0));	
	}	
}

WrkWindow::~WrkWindow(void)
{
}

void
WrkWindow::RemoveProjet(void)
{
	projet.RemoveItem(this);

	if (PrjWin)
	{
		PrjWin->RemoveWindow(this);
	}
}

void
WrkWindow::WindowActivated(bool act)
{
	struct MyGadget *gd;
	int k;

	BWindow::WindowActivated(act);

	if (act)
	{
		DefWin = this;

		bck->MakeFocus(true);
	}

	if (EditorWin && act)
	{
		EditorWin->ChangeGui((struct MyGadget *)sellist.ItemAt(0));	
	}	

	for (k = 0; k < list.CountItems(); k++)
	{
		if (gd = (struct MyGadget *)list.ItemAt(k))
		{
			if (gd->type == SCROLLER_HORIZ_KIND || gd->type == SCROLLER_VERT_KIND)
			{
				gd->pt->Invalidate();			
			}
		}
	}
	
	PostInfo();
}

void
WrkWindow::MySetFlags(bool vl,int nb)
{
	int k;
	struct MyGadget *gd;

	if (!sellist.CountItems())
	{
		switch(nb)
		{
			case	9004:
			{
				if (vl)
				{
					flag |= FLAG_LOCKX;

					SetFlags(Flags() | B_NOT_MOVABLE);
				}
					else
				{
					flag &= ~FLAG_LOCKX;

					SetFlags(Flags() & ~B_NOT_MOVABLE);
				}	
			}
			break;

			case	9005:
			{
				if (vl)
				{
					flag |= FLAG_LOCKY;

					SetFlags(Flags() | B_NOT_MOVABLE);
				}
					else
				{
					flag &= ~FLAG_LOCKY;

					SetFlags(Flags() & ~B_NOT_MOVABLE);
				}	
			}
			break;

			case	9006:
			{
				if (vl)
				{
					flag |= FLAG_LOCKW;

					SetFlags(Flags() | B_NOT_H_RESIZABLE);
				}
					else
				{
					flag &= ~FLAG_LOCKW;

					SetFlags(Flags() & ~B_NOT_H_RESIZABLE);
				}	
			}
			break;

			case	9007:
			{
				if (vl)
				{
					flag |= FLAG_LOCKH;

					SetFlags(Flags() | B_NOT_V_RESIZABLE);
				}
					else
				{
					flag &= ~FLAG_LOCKH;

					SetFlags(Flags() & ~B_NOT_V_RESIZABLE);
				}	
			}
			break;
		}
	}
		else
	{
		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				if (gd->flag & FLAG_SELECTED)
				{
					switch(nb)
					{
						case	9004:
						{
							if (vl)
							{
								gd->flag |= FLAG_LOCKX;
							}
								else
							{
								gd->flag &= ~FLAG_LOCKX;
							}	
						}
						break;

						case	9005:
						{
							if (vl)
							{
								gd->flag |= FLAG_LOCKY;
							}
								else
							{
								gd->flag &= ~FLAG_LOCKY;
							}	
						}
						break;

						case	9006:
						{
							if (vl)
							{
								gd->flag |= FLAG_LOCKW;
							}
								else
							{
								gd->flag &= ~FLAG_LOCKW;
							}	
						}
						break;

						case	9007:
						{
							if (vl)
							{
								gd->flag |= FLAG_LOCKH;
							}
								else
							{
								gd->flag &= ~FLAG_LOCKH;
							}	
						}
						break;
					}
				}
			}
		}				
	}
}

void
WrkWindow::MessageReceived(BMessage *msg)
{
	int k;
	struct MyGadget *gd;
	int32 a;

	switch(msg->what)
	{
		case	MENU_AUTOCREATE:
		{
			prefs.autocreate = !prefs.autocreate;
		}		
		break;
		case	MENU_CUT:	Cut();		break;
		case	MENU_COPY:	Copy();		break;
		case	MENU_PASTE:	Paste();	break;

		case	MENU_DELETE_GADGET:
		{
			DeleteGadget();
		}
		break;

		case	51000:
		{
			if (!sellist.CountItems())
			{
				if (!(flag & FLAG_LOCKX))
				{
					if (msg->FindInt32("x",&a) == B_OK)
					{
						MoveTo(a,Frame().top);
					}		
				}
				
				if (!(flag & FLAG_LOCKY))
				{
					if (msg->FindInt32("y",&a) == B_OK)
					{
						MoveTo(Frame().left,a);
					}		
				}
				
				if (!(flag & FLAG_LOCKW))
				{
					if (msg->FindInt32("w",&a) == B_OK)
					{
						ResizeTo(a,Frame().Height());
					}		
				}
				
				if (!(flag & FLAG_LOCKH))
				{
					if (msg->FindInt32("h",&a) == B_OK)
					{
						ResizeTo(Frame().Width(),a);
					}		
				}
				
				if (msg->FindInt32("f",&a) == B_OK)
				{
					flag = a;
				}		
			}
				else
			{
				for (k = 0; k < sellist.CountItems(); k++)
				{
					if	(gd = sellist.ItemAt(k))
					{
						if (gd->flag & FLAG_SELECTED)
						{
							BView *vx = (BView *)gd->pt;

							if (msg->FindInt32("x",&a) == B_OK)
							{
								if (!(gd->flag & FLAG_LOCKX))
								{
									vx->MoveTo(a,gd->y);
					
									gd->x = a;

									change_infowin_number(but_Left,a);
								}
							}
							
							if (msg->FindInt32("y",&a) == B_OK)
							{
								if (!(gd->flag & FLAG_LOCKY))
								{
									vx->MoveTo(gd->x,a);
					
									gd->y = a;

									change_infowin_number(but_Top,a);
								}
							}		

							if (msg->FindInt32("w",&a) == B_OK)
							{
								ChangeSize(CHANGE_WIDTH,a,gd->he);
							}		

							if (msg->FindInt32("h",&a) == B_OK)
							{
								ChangeSize(CHANGE_HEIGHT,gd->wi,a);
							}		

							if (msg->FindInt32("f",&a) == B_OK)
							{
								gd->flag = a;
							}		
						}
					}
				}
			}			
		}
		break;

		default:
		{
			BWindow::MessageReceived(msg);
		}
		break;
	}		
}	

bool
WrkWindow::AcceptMsg(int nb)
{
	if (!sellist.CountItems())
	{
		switch(nb)
		{
			case	0:
			{
				if (flag & FLAG_LOCKX)
				{
					return(false);
				}			
			}
			break;

			case	1:
			{
				if (flag & FLAG_LOCKY)
				{
					return(false);
				}			
			}
			break;

			case	2:
			{
				if (flag & FLAG_LOCKW)
				{
					return(false);
				}			
			}
			break;

			case	3:
			{
				if (flag & FLAG_LOCKH)
				{
					return(false);
				}			
			}
			break;
		}
	}

	return(true);
}

bool
WrkWindow::QuitRequested(void)
{
	if	(SysAlert(GetMessage(msg_killwindow),GetMessage(msg_yesno)))
	{
		return false;
	}	

	RemoveProjet();

	if (DefWin == this)
	{
		DefWin = NULL;
	
		PostInfo();
	}

	return true;
}

bool
WrkWindow::ExistsMenu(void)
{
	int k;
	struct MyGadget *gd;

	for (k = 0; k < list.CountItems(); k++)
	{
		if	(gd = list.ItemAt(k))
		{
			if (gd->type == MENU_KIND)
			{
				return(true);
			}
		}
	}	

	return(false);
}

char *array_type_ccplus[] =
{
	"button",
	"checkbox",
	"string",
	"integer",
	"float",
	"password",
	"tab",
	"box",
	"radio",
	"mx",
	"stext",
	"number",
	"statusbar",
	"color",
	"listview",
	"listview",
	"listview",
	"listview",
	"outlistview",
	"outlistview",
	"outlistview",
	"outlistview",
	"hslider",
	"vslider",
	"hscroller",
	"vscroller",
	"tedit",
	"tedit",
	"tedit",
	"tedit",
	"menu",	
	"view",
	NULL
};

char *
WrkWindow::GetTitle_Gadget(int type)
{
	int nb = 0,k;
	struct MyGadget *gd;

	for (k = 0; k < list.CountItems(); k++)
	{
		if	(gd = list.ItemAt(k))
		{
			switch(type)
			{
				case	LISTVIEW_KIND:
				case	LISTVIEW_HORIZ_KIND:
				case	LISTVIEW_VERT_KIND:
				case	LISTVIEW_ALL_KIND:
				{
					if (gd->type >= LISTVIEW_KIND && gd->type <= LISTVIEW_ALL_KIND)
					{
						nb++;
					}
				}
				break;
				
				case	OUTLISTVIEW_KIND:
				case	OUTLISTVIEW_HORIZ_KIND:
				case	OUTLISTVIEW_VERT_KIND:
				case	OUTLISTVIEW_ALL_KIND:
				{
					if (gd->type >= OUTLISTVIEW_KIND && gd->type <= OUTLISTVIEW_ALL_KIND)
					{
						nb++;
					}
				}
				break;
				
				case	TEDIT_KIND:
				case	TEDIT_HORIZ_KIND:
				case	TEDIT_VERT_KIND:
				case	TEDIT_ALL_KIND:
				{
					if (gd->type >= TEDIT_KIND && gd->type <= TEDIT_ALL_KIND)
					{
						nb++;
					}
				}
				break;
			
				default:
				{
					if (gd->type == type)
					{
						nb++;
					}
				}	
				break;
			}
		}
	}			

	if (ProjetType == PROJET_BCC)
	{
		sprintf(&buf[0],"%s%d",array_type[type],nb + 1);
	}
		else
	{
		sprintf(&buf[0],"%s%d",array_type_ccplus[type],nb + 1);
	}		

	return(&buf[0]);
}	

extern int fucka,fuckb;

struct MyGadget *
WrkWindow::CreateGadget(int type,int x,int y,int wi,int he,bool add = true,bool relative = false,bool check = true,bool attach = true,char *title = NULL)
{
	struct MyGadget *gd;
	GadView	*k;
	
	if (gd = (struct MyGadget *)MyAlloc(sizeof(struct MyGadget)))
	{
		strcpy(&gd->FontName[0],&FontName[0]);
		strcpy(&gd->FontStyle[0],&FontStyle[0]);
		
		gd->FontSize = FontSize;

		gd->FontType = 0;

		if (type == MX_KIND)
		{
			he = 25;		
		}

		if (type == MENU_KIND)
		{
			if (check && ExistsMenu())
			{
				SysAlert(GetMessage(msg_onemenu),GetMessage(msg_ok));

				return(NULL);	
			}

			wi = 30;		
			he = 20;		
		}

		strcpy(&gd->Name[0],GetTitle_Gadget(type));
		strcpy(&gd->Title[0],GetTitle_Gadget(type));

		gd->align = (ProjetType == PROJET_BCC) ? 0 : 2;

		gd->idcmp = 0;

		gd->enable = true;

		if (k = new GadView(gd,MyRect(x,y,wi,he),type,(title) ? title : &gd->Title[0]))
		{
			float aa,bb;
			BView *cd;

			if (!relative)
			{
				gd->x = x;
				gd->y = y;
			}
				else
			{
				gd->x = x + fucka;
				gd->y = y + fuckb;
			}
			
			gd->wi = wi;
			gd->he = he;
			gd->type = type;

			k->gd = gd;

			gd->pt = k;

			if (attach && (cd = k->ChildAt(0)))
			{
				int nb,res = 0;

				((BView *)cd)->GetPreferredSize(&aa,&bb);	

				gd->ColHigh = cd->HighColor();
				gd->ColLow  = cd->LowColor();
				gd->ColView = cd->ViewColor();

				nb = (int)cd->Flags();
				
				if (nb & B_WILL_DRAW)				res |= (1L << 0);
				if (nb & B_FULL_UPDATE_ON_RESIZE)	res |= (1L << 1);
				if (nb & B_FRAME_EVENTS)			res |= (1L << 2);
				if (nb & B_PULSE_NEEDED)			res |= (1L << 3);
				if (nb & B_NAVIGABLE)				res |= (1L << 4);
				if (nb & B_NAVIGABLE_JUMP)			res |= (1L << 5);

				gd->view = res;

				gd->alignx = 0;
				gd->aligny = 0;
			}

			if (type == TAB_KIND || type == RADIO_KIND || type == MX_KIND)
			{
				gd->name.AddItem(MyStringStr(&gd->Name[0]));
			}			
			
			switch(type)
			{
				case	CHECKBOX_KIND:
				case	COLOR_KIND:
				case	RADIO_KIND:
				case	SCROLLER_HORIZ_KIND:
				case	SCROLLER_VERT_KIND:
				case	SLIDER_HORIZ_KIND:
				case	SLIDER_VERT_KIND:
				case	STRING_KIND:
				case	INTEGER_KIND:
				case	PASSWORD_KIND:
				case	FLOAT_KIND:
				{
					k->ResizeTo(aa,bb);
	
					gd->wi = (int)aa;
					gd->he = (int)bb;
				}		
				break;

				case	MX_KIND:
				{
					gd->data.mx.pixdiv = (int)(((BMenuField *)cd)->Divider());

					k->ResizeTo(aa,bb);

					gd->wi = (int)aa;
					gd->he = (int)bb;
				}		
				break;
			}

			switch(type)
			{
				case	TAB_KIND:
				{
					gd->data.tab.sel = 0;
					gd->data.tab.tabwidth  = (int)(((BTabView *)cd)->TabWidth());
					gd->data.tab.tabheight = (int)(((BTabView *)cd)->TabHeight());
				};
				break;
		
				case	RADIO_KIND:
				{
					gd->data.rad.val = 0;
					gd->data.rad.sel = -1;
				}
				break;

				case	MX_KIND:
				{
					BView *cd;

					cd = k->ChildAt(0);	

					((BMenuField *)cd)->SetLabel(&gd->Name[0]);

					strcpy(&gd->data.mx.Label[0],&gd->Name[0]);

					gd->data.mx.pixdiv = (int)(((BMenuField *)cd)->Divider());
					gd->align = B_ALIGN_LEFT;
				}
				break;

				case	BOX_KIND:
				{
					strcpy(&gd->data.bbox.Label[0],&gd->Name[0]);

					gd->data.bbox.style = (int)((BBox *)cd)->Border();
				}
				break;

				case	SLIDER_HORIZ_KIND:
				case	SLIDER_VERT_KIND:
				{
					BSlider *dt = (BSlider *)k;

					gd->data.bslider.min = 0;
					gd->data.bslider.max = 15;
					gd->data.bslider.pos = (int)dt->Position();
					gd->data.bslider.style = (int)dt->Style();
					gd->data.bslider.hashtype = (int)dt->HashMarks();
					gd->data.bslider.hashcount = (int)dt->HashMarkCount();
					gd->data.bslider.keyinc = (int)dt->KeyIncrementValue();
					gd->data.bslider.thickness = (int)dt->BarThickness();
					gd->data.bslider.fillall = true;

					strcpy(&gd->data.bslider.Label[0],&gd->Name[0]);
					strcpy(&gd->data.bslider.MinLabel[0],"");
					strcpy(&gd->data.bslider.MaxLabel[0],"");
					dt->FillColor(&gd->data.bslider.fillcolor);
					gd->data.bslider.barcolor =dt->BarColor();
				}
				break;
				
				case	SCROLLER_HORIZ_KIND:
				case	SCROLLER_VERT_KIND:
				{
					float a,b;

					BScrollBar *dt = (BScrollBar *)cd;
					
					dt->GetRange(&a,&b);	

					gd->data.bscroller.minrange = (int)a;
					gd->data.bscroller.maxrange = (int)b;
					gd->data.bscroller.pos = (int)dt->Value();

					dt->GetSteps(&a,&b);	

					gd->data.bscroller.setprop = 0;
					gd->data.bscroller.minstep = (int)a;
					gd->data.bscroller.maxstep = (int)b;
				}
				break;

				case	CHECKBOX_KIND:
				{
					gd->data.bcheckbox.checked = false;
				}
				break;

				case	INTEGER_KIND:
				{
					BTextControl *xt = (BTextControl *)cd;

					strcpy(&gd->data.string.Text[0],&gd->Name[0]);	

					gd->data.string.value = 0;
					gd->data.string.maxchars = 15;
					gd->align = B_ALIGN_LEFT;
					gd->data.string.pixdiv = gd->data.string.pixdeb =(int)xt->Divider();
					gd->data.string.negvalue = true;
					gd->data.string.editable = true;
					gd->data.string.selectable = true;
				}
				break;

				case	STRING_KIND:
				{
					BTextControl *xt = (BTextControl *)cd;

					strcpy(&gd->data.string.Text[0],&gd->Name[0]);	

					gd->data.string.maxchars = 15;
					gd->align = B_ALIGN_LEFT;
					gd->data.string.pixdiv = gd->data.string.pixdeb =(int)xt->Divider();
					gd->data.string.editable = true;
					gd->data.string.selectable = true;
				}
				break;

				case	FLOAT_KIND:
				{
					BTextControl *xt = (BTextControl *)cd;

					strcpy(&gd->data.string.Text[0],&gd->Name[0]);	

					gd->data.string.value = 0;
					gd->data.string.maxchars = 15;
					gd->align = B_ALIGN_LEFT;
					gd->data.string.pixdiv = gd->data.string.pixdeb =(int)xt->Divider();
					gd->data.string.acceptvir = false;
					gd->data.string.negvalue = true;
					gd->data.string.editable = true;
					gd->data.string.selectable = true;
				}
				break;

				case	PASSWORD_KIND:
				{
					BTextControl *xt = (BTextControl *)cd;

					strcpy(&gd->data.string.Text[0],&gd->Name[0]);	

					gd->data.string.maxchars = 15;
					gd->align = B_ALIGN_LEFT;
					gd->data.string.pixdiv = gd->data.string.pixdeb =(int)xt->Divider();
					gd->data.string.editable = true;
					gd->data.string.selectable = true;
					gd->data.string.car = '*';
				}
				break;

				case	TEXT_KIND:
				{
					strcpy(&gd->data.txt.Label[0],&gd->Name[0]);
				}
				break;

				case	NUMBER_KIND:
				{
					strcpy(&gd->data.num.Label[0],&gd->Name[0]);

					gd->data.num.val = 0;
				}
				break;

				case	COLOR_KIND:
				{
					BColorControl *xt = (BColorControl *)cd;

					gd->data.col.cellsize = (int)xt->CellSize();
					gd->data.col.layout = (int)xt->Layout();
					gd->data.col.value = xt->ValueAsColor();
					gd->data.col.redrawbuffer = false;
				}
				break;

				case	STATUSBAR_KIND:
				{
					strcpy(&gd->data.sta.Label[0],&gd->Name[0]);
					strcpy(&gd->data.sta.Trail[0],"");

					gd->data.sta.barcolor = ((BStatusBar *)cd)->BarColor();
					gd->data.sta.barheight = (int)(((BStatusBar *)cd)->BarHeight());
					gd->data.sta.maxvalue = (int)(((BStatusBar *)cd)->MaxValue());
					gd->data.sta.value = (int)(((BStatusBar *)cd)->CurrentValue());
				}
				break;

				case	LISTVIEW_KIND:
				case	LISTVIEW_HORIZ_KIND:
				case	LISTVIEW_VERT_KIND:
				case	LISTVIEW_ALL_KIND:
				{
					gd->data.lv.multi = false;
					gd->data.lv.sel = -1;
				}
				break;

				case	OUTLISTVIEW_KIND:
				case	OUTLISTVIEW_HORIZ_KIND:
				case	OUTLISTVIEW_VERT_KIND:
				case	OUTLISTVIEW_ALL_KIND:
				{
					gd->data.olv.multi = false;
					gd->data.olv.sel = -1;
				}
				break;

				case	TEDIT_KIND:
				case	TEDIT_HORIZ_KIND:
				case	TEDIT_VERT_KIND:
				case	TEDIT_ALL_KIND:
				{
					BTextControl *ct = (BTextControl *)cd->ChildAt(0)->ChildAt(0);
					BTextView	*vt = ct->TextView();	

					gd->data.edi.selectable = (int)vt->IsSelectable();
					gd->data.edi.editable = (int)vt->IsEditable();
					gd->data.edi.stylable = (int)vt->IsStylable();
					gd->data.edi.tabwidth = (int)vt->TabWidth();
					gd->data.edi.wordwrap = (int)vt->DoesWordWrap();
					gd->data.edi.autoident = (int)vt->DoesAutoindent();
					gd->data.edi.maxchars = (int)vt->MaxBytes();
				}
				break;
			}	 

fin:		if (attach)
			{
				struct MyGadget *x0 = NULL;
				BView	*vx;

				if (x0 = sellist.ItemAt(0))
				{
					if (vx = (BView *)x0->pt->ChildAt(0))
					{
						vx->AddChild(k);

						gd->parent = x0;
					}
				}
					else
				{
					bck->AddChild(k);
				}
							
				list.AddItem(gd);

				if (add && PrjWin)
				{
					PrjWin->AddGadget(this,gd,&gd->Title[0],type,x0);
				}

				UnSelectAll(false);

//				AddGadget(gd);

			}

			return gd;
		}

		MyFree(gd);
	}

	return NULL;
}
