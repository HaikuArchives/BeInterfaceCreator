#include "proto.h"
#include "priwindow.h"

extern PriWindow *PriWin;

class MyListView4 : public BListView
{
public:
	MyListView4(BRect rct);
	virtual	void	MouseDown(BPoint pt);
};

class SearchItem : public BStringItem
{
public:

		 SearchItem(char *str,WrkWindow *wi,struct MyGadget *gd);
		 ~SearchItem();

	WrkWindow 		*win;
	struct MyGadget *gad;
};

class SearchWindow : public BWindow
{
public:
		SearchWindow(BRect rct);
		~SearchWindow(void);
		
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	Search(char *txt);
		void	SearchType(int32 nb);
		void	RemoveGadget(struct MyGadget *gad);

		BTextControl 	*b0;
		BMenuField		*b1;
		BButton			*b2;
		MyListView4		*b3;	
};

int32 index = 0;

MyListView4::MyListView4(BRect rect):BListView(rect,"",B_SINGLE_SELECTION_LIST,B_FOLLOW_ALL)
{
	BFont font;

	GetFont(&font);

	font.SetSize(18);

	font.SetFlags(B_DISABLE_ANTIALIASING);

	SetFont(&font,B_FONT_FLAGS);
}

void MyListView4::MouseDown(BPoint where)
{
	BMessage* msg = Window()->CurrentMessage();

    int32 clicks = msg->FindInt32("clicks");
    int32 button = msg->FindInt32("buttons");

	int32 item = IndexOf(where);

	if ((item >= 0) && (item < CountItems())) 
	{
		switch(button)
		{
			case	B_SECONDARY_MOUSE_BUTTON:
			{
				BPopUpMenu* popup = new BPopUpMenu("");

				popup->SetAsyncAutoDestruct(true);

				popup->SetRadioMode(false);

				popup->AddItem(new BMenuItem(GetMessage(msg_cut), new BMessage(MENU_CUT)));
				popup->AddItem(new BMenuItem(GetMessage(msg_copy), new BMessage(MENU_COPY)));
				popup->AddItem(new BMenuItem(GetMessage(msg_paste), new BMessage(MENU_PASTE)));
				popup->AddSeparatorItem();
				popup->AddItem(new BMenuItem(GetMessage(msg_delete),new BMessage(MENU_DELETE_GADGET)));

				popup->SetTargetForItems(PriWin);

				ConvertToScreen(&where); 

				popup->Go(where,true,false,false);

				return;
			}
			break;
		}
	}

	BListView::MouseDown(where);
}	

SearchItem::SearchItem(char *str,WrkWindow *wi,struct MyGadget *gd):BStringItem(str)
{
	win = wi;
	gad = gd;
}

SearchItem::~SearchItem()
{
}

SearchWindow::SearchWindow(BRect rct):BWindow(rct,GetMessage(msg_search),B_TITLED_WINDOW_LOOK,B_NORMAL_WINDOW_FEEL,B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect 	rect(Bounds());
	BView	*xt;
	BMenu *menu;

	menu = CreateMenu(this,&search_type[0],9001,index);

	xt = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);

	xt->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	b0 = CreateString(MyRect(5,5,120,25),GetMessage(msg_name),9000,4);

	b0->SetModificationMessage(new BMessage(9007));

	b0->SetEnabled(true);

	b1 = CreateMx(MyRect(130,3,180,30),"",menu,0);

	b2 = CreateButton(MyRect(234,4,80,19),GetMessage(msg_search),9003);

	rect.right -= B_V_SCROLL_BAR_WIDTH;

	b3 = new MyListView4(BRect(5,35,rect.right - 5,rect.bottom - 5));

	BScrollView *sc = new BScrollView("",b3,B_FOLLOW_ALL,B_FULL_UPDATE_ON_RESIZE,false,true);

	b3->SetSelectionMessage(new BMessage(9005));

	xt->AddChild(b0);
	xt->AddChild(b1);
	xt->AddChild(b2);
	xt->AddChild(sc);

	AddChild(xt);
}

SearchWindow::~SearchWindow(void)
{
}

void
SearchWindow::Search(char *txt)
{
	int i,k;
	WrkWindow *wi;
	struct MyGadget *gd;
	char buf[100];
	bool found = false;

	b3->MakeEmpty();

	for (k = 0; k < projet.CountItems(); k++)
	{
		if (wi = (WrkWindow *)projet.ItemAt(k))
		{
			for (i = 0; i < wi->list.CountItems(); i++)
			{
				if	(gd = wi->list.ItemAt(i))
				{
					if (strcmp(&gd->Name[0],txt) == 0)
					{
						sprintf(&buf[0],"%s - %s",&gd->Name[0],&wi->Name[0]);
						
						b3->AddItem(new SearchItem(&buf[0],wi,gd));	

						found = true;
					}
				}
			}	
		}
	}

	if (!found)
	{
		beep();
	}
}

void
Update_SearchWindow(struct MyGadget *gad)
{
	if (SearchWin)
	{
		BAutolock win(SearchWin);

		SearchWin->RemoveGadget(gad);	
	}
}

void
SearchWindow::RemoveGadget(struct MyGadget *gad)
{
	int k;
	SearchItem	*it;
	
	for (k = 0; k < b3->CountItems(); k++)
	{
		if (it = (SearchItem *)b3->ItemAt(k))
		{
			if (it->gad == gad)
			{
				b3->RemoveItem(it);

				delete it;
			}		
		}
	}
}

void
SearchWindow::SearchType(int32 idx)
{
	int i,k;
	WrkWindow *wi;
	struct MyGadget *gd;
	char buf[100];
	bool found = false;

	b3->MakeEmpty();

	for (k = 0; k < projet.CountItems(); k++)
	{
		if (wi = (WrkWindow *)projet.ItemAt(k))
		{
			for (i = 0; i < wi->list.CountItems(); i++)
			{
				if	(gd = wi->list.ItemAt(i))
				{
					if (gd->type == idx)
					{
						sprintf(&buf[0],"%s - %s",&gd->Name[0],&wi->Name[0]);
						
						b3->AddItem(new SearchItem(&buf[0],wi,gd));	

						found = true;
					}
				}
			}	
		}
	}

	if (!found)
	{
		beep();
	}
}

void
SearchWindow::MessageReceived(BMessage *msg)
{
	switch(msg->what)
	{
		case	9000:
		{
txt:		Search((char *)b0->Text());	
		}
		break;

		case	9001:
		{
			msg->FindInt32("index",&index); 

			b0->SetEnabled((index) ? false : true);
		}
		break;

		case	9003:
		{
			if (!index)
			{
				goto txt;
			}
				else
			{
				SearchType(index - 1);	
			}
		}
		break;

		case	9005:
		{
			SearchItem *it;

			msg->FindInt32("index",&index); 

			if (index >= 0)
			{
				if (it = (SearchItem *)b3->ItemAt(index))
				{
					it->win->Lock();
					it->win->UnSelectAll();
					it->win->AddGadget(it->gad);
					it->win->Unlock();
				}							
			}
		}
		break;

		case	9007:
		{
		}
		break;
		
		default:	BWindow::MessageReceived(msg);	break;
	}	
}

bool
SearchWindow::QuitRequested(void)
{
	SearchWin = NULL;

	return true;
}

void
SearchWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);

	prefs.searchrect = Frame();
}

void
SearchWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	prefs.searchrect = Frame();
}

void
search_window(void)
{
	if (!SearchWin)
	{
		SearchWin = new SearchWindow(prefs.searchrect);

		SearchWin->Show();
	}
		else
	{
		SearchWin->Show();

		SearchWin->Activate();
	}
}		