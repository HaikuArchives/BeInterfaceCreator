#include "proto.h"

BRect editlistrect(MyRect(50,50,435,365));

enum Messages
{
	MSG_AJOUTER_TEXTE,
	MSG_SUPPRIMER_TEXTE,
	MSG_CONTROLE_TEXTE_AJOUTER_TEXTE
		
};

class MyLv_t0 : public BListView
{
public:
		MyLv_t0(BRect rct);
		
		virtual void SelectionChanged(void);	
};

class AppListWindow : public BWindow
{
	public:
		AppListWindow(BRect surface);
		~AppListWindow();

		void Init(void);
		
		virtual bool QuitRequested(); 
		virtual void MessageReceived(BMessage * message);
		virtual void FrameResized(float wi,float he);
		virtual void FrameMoved(BPoint pt);

		void	AddString(char *str);

	struct MyGadget *gad;

	MyLv_t0 		*xt;
	BScrollView		*sc;
	BTextControl	*tx;
	BButton			*dl;	
};

AppListWindow::AppListWindow(BRect surface)
	:BWindow(surface,GetMessage(msg_editor),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,B_ASYNCHRONOUS_CONTROLS|B_NOT_ZOOMABLE)
{
	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));

	Init();

	Show();
}

bool AppListWindow::QuitRequested()
{
	int k;
	BStringItem *it;

	gad->name.MakeEmpty();

	for (k = 0; k < xt->CountItems(); k++)
	{
		if (it = (BStringItem *)xt->ItemAt(k))
		{
			gad->name.AddItem(MyStringStr(it->Text()));
		}
	}	

	change_gadget_list(gad);

	return(true);
	
}
AppListWindow::~AppListWindow()
{
}

void
AppListWindow::FrameResized(float wi,float he)
{
	BScrollBar *xi;

	BWindow::FrameResized(wi,he);

	if (xi = sc->ScrollBar(B_HORIZONTAL))
	{
		xi->Invalidate();
	}

	if (xi = sc->ScrollBar(B_VERTICAL))
	{
		xi->Invalidate();
	}

	editlistrect = Frame();
}

void
AppListWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	editlistrect = Frame();
}

MyLv_t0::MyLv_t0(BRect rct):BListView(rct,"")
{
}

void
MyLv_t0::SelectionChanged(void)
{
	AppListWindow *wi = (AppListWindow *)Window();
	int nb;
	BStringItem *it;

	BListView::SelectionChanged();

	if ((nb = CurrentSelection()) != -1)
	{
		wi->dl->SetEnabled(true);

		if (it = (BStringItem *)ItemAt(nb))
		{
			wi->tx->TextView()->SetText(it->Text());
		}
	}
		else
	{
		wi->tx->SetText("");

		wi->dl->SetEnabled(false);
	}	
}

void
AppListWindow::Init(void)
{
	BRect 	rect(Bounds());
	BView	*bk;

	bk = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW|B_FULL_UPDATE_ON_RESIZE);

	bk->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	tx = CreateString(MyRect(10,10,300,25),"",9000,0);

	dl = CreateButton(MyRect(320,10,90,20),GetMessage(msg_delete),9001);

	dl->SetEnabled(false);

	xt = new MyLv_t0(MyRect(10,50,400,290));

	sc = new BScrollView("",xt,B_FOLLOW_ALL,0,true,true);

	bk->AddChild(tx);
	bk->AddChild(dl);
	bk->AddChild(sc);

	AddChild(bk);
}

void
AppListWindow::AddString(char *str)
{
	Lock();

	xt->AddItem(new BStringItem(str));	

	Unlock();
}

void 
AppListWindow::MessageReceived(BMessage *msg)
{
	char 		*str;
	BStringItem	*it;

	int32 nb;

	switch(msg->what)
	{
		case	9000:
		{
			if (str = tx->Text())
			{
				if (*str)
				{
					if ((nb = xt->CurrentSelection()) >= 0)
					{
						if (it = (BStringItem *)xt->ItemAt(nb))
						{
							it->SetText(str);

							xt->InvalidateItem(nb);
						}
					}
						else
					{
						AddString(str);

						tx->SetText("");
					}
				}
			}
		}
		break;

		case	9001:
		{
			if (gad->type == TAB_KIND || gad->type == RADIO_KIND)
			{
				if (xt->CountItems() == 1)			
				{
					beep();
					return;					
				}
			}

			if ((nb = xt->CurrentSelection()) >= 0)
			{
				if (it = (BStringItem *)xt->ItemAt(nb))
				{
					xt->RemoveItem(it);					

					delete it;
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

void
AddListWindow(struct MyGadget *gd)
{
	char *tx;
	int k;

	AppListWindow *wi;

	wi = new AppListWindow(editlistrect);

	wi->gad = gd;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (tx = (char *)gd->name.ItemAt(k))
		{
			wi->AddString(tx);
		}
	}	
}
