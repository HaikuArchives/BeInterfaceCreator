#include "proto.h"
#include "menu.h"

static CMenuItem *sel;
static BList	list;
BList *lsgad;

BRect menueditrect(100,100,600,510);

CMenuItem::CMenuItem(bool men,char *a,char c,int d,bool e,bool f,bool g,uint32 level = 0):BStringItem(a,level)
{
	menu  	= men;
	name 	= MyStringStr(a);
	car  	= c;
	msg 	= d;
	enable  = e;
	checked = f;
	radio  	= g;
}

CMenuItem::~CMenuItem()
{
	if (name)
	{
		free(name);
	}
}

MyLv2::MyLv2(BRect rct):BOutlineListView(rct,"",B_SINGLE_SELECTION_LIST,B_FOLLOW_ALL)
{
}

MyLv2::~MyLv2(void)
{
}

void
MyLv2::SelectionChanged(void)
{
	int nb;
	CMenuItem 	*it;
	MenuWindow 	*wi = (MenuWindow *)Window();

	BOutlineListView::SelectionChanged();

	if ((nb = CurrentSelection()) >= 0)
	{
		char tmp[6];

		if (it = (CMenuItem *)ItemAt(nb))
		{
			sel = it;

			wi->b3->SetEnabled(true);	
			wi->b8->SetEnabled(true);	
			wi->b6->SetEnabled(true);	

			wi->b4->SetText(it->name);

			wi->b6->SetValue(it->enable);

			if (!it->OutlineLevel())
			{
				wi->b5->SetText("");

				wi->b1->SetEnabled(true);	
				wi->b2->SetEnabled(true);	

				wi->b5->SetEnabled(false);	
				wi->b7->SetEnabled(false);	
				wi->b9->SetEnabled(true);	

				wi->b7->SetValue(0);

				wi->b9->SetValue(it->radio);
			}
				else
			{
				wi->b9->SetEnabled(false);	

				wi->b9->SetValue(0);

				wi->b1->SetEnabled(true);	
				wi->b2->SetEnabled(true);	
				wi->b5->SetEnabled(true);	
				wi->b7->SetEnabled(true);	

				wi->b7->SetValue(it->checked);

				sprintf(&tmp[0],"%c",it->car);

				wi->b5->SetText(&tmp[0]);
			}			

			sprintf(&tmp[0],"%d",it->msg);

			wi->b8->SetText(&tmp[0]);
		}
	}
		else
	{
		sel = 0;

		wi->b6->SetValue(0);
		wi->b7->SetValue(0);
		wi->b9->SetValue(0);

		wi->b1->SetEnabled(true);	
		wi->b8->SetEnabled(true);	
		wi->b6->SetEnabled(true);	
		wi->b9->SetEnabled(true);	

		wi->b2->SetEnabled(false);	
		wi->b3->SetEnabled(false);	
		wi->b5->SetEnabled(false);	
		wi->b7->SetEnabled(false);	

		wi->b4->SetText("");
		wi->b5->SetText("");
		wi->b8->SetText("");
	}	
}

MenuWindow::MenuWindow(BRect rct)
:BWindow(rct,GetMessage(msg_create_menu),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,B_ASYNCHRONOUS_CONTROLS|B_NOT_ZOOMABLE)
{
	BRect 	rect(Bounds());

	xt = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);

	xt->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	b0 = new MyLv2(BRect(5,5,400,300));

	BScrollView *scroll = new BScrollView("",b0,B_FOLLOW_ALL,0,true,true);

	b4 = CreateString(MyRect(5,320,150,25),GetMessage(msg_label),9004,4);
	b5 = CreateString(MyRect(5,350,70,25),GetMessage(msg_raccourci),9005,4);
	b8 = CreateString(MyRect(5,380,90,25),GetMessage(msg_message),9008,4);

	b1 = CreateButton(MyRect(420,3,85,25),GetMessage(msg_addmenu),9001);
	b2 = CreateButton(MyRect(420,33,85,25),GetMessage(msg_additem),9002);
	b3 = CreateButton(MyRect(420,63,85,25),GetMessage(msg_delete),9003);

	b6 = new BCheckBox(MyRect(190,320,150,25),"",GetMessage(msg_actived),new BMessage(9006));
	b7 = new BCheckBox(MyRect(190,350,150,25),"",GetMessage(msg_checked),new BMessage(9007));
	b9 = new BCheckBox(MyRect(190,380,150,25),"",GetMessage(msg_radiomode),new BMessage(9009));

	SetStringLen(b5,1);
	SetStringLen(b8,4);

	b2->SetEnabled(false);
	b3->SetEnabled(false);

	b5->SetEnabled(false);
	b7->SetEnabled(false);

	xt->AddChild(scroll);

	xt->AddChild(b4);
	xt->AddChild(b5);
	xt->AddChild(b8);

	xt->AddChild(b1);
	xt->AddChild(b2);
	xt->AddChild(b3);
	xt->AddChild(b6);
	xt->AddChild(b7);
	xt->AddChild(b9);

	AddChild(xt);

	Show();
}

MenuWindow::~MenuWindow(void)
{
}

void
MenuWindow::LoadInfo(void)
{
	int k;
	CMenuItem *Current,*it;
	struct mymenu *tx;

	Lock();

	for (k = 0; k < list.CountItems(); k++)
	{
		if (tx = (struct mymenu *)list.ItemAt(k))
		{
			CMenuItem *it;

			if (!tx->level)
			{
				b0->AddItem(it = new CMenuItem(tx->menu,tx->name,tx->car,tx->msg,tx->enable,tx->checked,tx->radio));

				Current = it;
			}
				else
			{
				switch(tx->level)
				{
					case	1:
					{
						int32 level = Current->OutlineLevel() + 1;
						int32 index = b0->FullListIndexOf(Current)
						+ b0->CountItemsUnder(Current, false) + 1;
	
						b0->AddItem(it = new CMenuItem(tx->menu,tx->name,tx->car,tx->msg,tx->enable,tx->checked,tx->radio,level),index);
					}
					break;
					
					case	2:
					{
						int32 level = Current->OutlineLevel() + 1;
						int32 index = b0->FullListIndexOf(Current)
						+ b0->CountItemsUnder(Current, false) + 1;
	
						b0->AddItem(it = new CMenuItem(tx->menu,tx->name,tx->car,tx->msg,tx->enable,tx->checked,tx->radio,level),index);

						Current = it;
					}
					break;
				}
			}	
		}
	}

	b0->Invalidate();	

	Unlock();
}

void
MenuWindow::StoreInList(bool men,char *str,int nb,int car,int msg,bool enable,bool checked,bool radio)
{
	struct mymenu *tx;

	if (tx = MyAlloc(sizeof(struct mymenu)))
	{
		if (tx->name = MyStringStr(str))
		{
			tx->menu    = men;
			tx->level   = nb;
			tx->msg     = msg;
			tx->car     = car;
			tx->radio   = radio;
			tx->enable  = enable;
			tx->checked = checked;

			lsgad->AddItem(tx);
		}
	}
}

void
MenuWindow::BuildMenuItems(BMenu* pMenu, BListItem* pSuperitem,BOutlineListView* pView)
{
	if ((! pSuperitem) || (! pView)) {
		return;
	}
	
	int32 len = pView->CountItemsUnder(pSuperitem, true);
	
	for (int32 i=0; i<len; i++) {
		BStringItem* pItem = dynamic_cast<BStringItem*>
			(pView->ItemUnderAt(pSuperitem, true, i));
		if (pItem > 0) {

				CMenuItem *it = (CMenuItem *)pItem;

			if (pView->CountItemsUnder(pItem, true) > 0)
			 {
				StoreInList(it->menu,(char *)it->Text(),2,it->car,it->msg,it->enable,it->checked,it->radio);	

				BuildMenuItems(NULL, pItem, pView);
			} else 
			{
				StoreInList(it->menu,(char *)it->Text(),1,it->car,it->msg,it->enable,it->checked,it->radio);	
			}
		}
	}
}

void
MenuWindow::StoreInfo(void)
{
	int k;
	CMenuItem *it;
	static struct mymenu *tx;

	list.MakeEmpty();

	lsgad->MakeEmpty();

	for (k = 0; k < b0->CountItems(); k++)
	{
		if (it = (CMenuItem *)b0->ItemAt(k))
		{
			if (!it->OutlineLevel())
			{
				StoreInList(it->menu,(char *)it->Text(),0,it->car,it->msg,it->enable,it->checked,it->radio);	

				BListItem* pListItem = b0->ItemUnderAt(NULL, true,k);
	
				BuildMenuItems(NULL,pListItem,b0);
			}
		}
	}
}

void
MenuWindow::InfoShow(void)
{
	int k;
	CMenuItem *it;

	return;

	for (k = 0; k < b0->CountItems(); k++)
	{
		if (it = (CMenuItem *)b0->ItemAt(k))
		{
		}
	}
}

void
MenuWindow::MessageReceived(BMessage *msg)
{
	int32 nb,vl;
	char *st;

	msg->FindInt32("be:value",&vl);

	switch(msg->what)
	{
		case	9001:	AddMenu();	break;
		case	9002:	AddItem();	break;
		case	9003:	Delete();	break;

		case	9010:	InfoShow();		break;

		case	9004:
		{
			if (sel)
			{
				if (strlen(b4->Text()))
				{
					if (st = MyStringStr(b4->Text()))
					{
						MyFree(sel->name);					

						sel->name = st;

						sel->SetText(st);

						b0->InvalidateItem(b0->IndexOf(sel));
					}
				}			
			}
		}
		break;

		case	9005:
		{
			if (sel)
			{
				if (strlen(b5->Text()))
				{
					if (st = b5->Text())
					{
						sel->car = st[0];
					}
				}			
					else
				{
					sel->car = 0;
				}	
			}
		}
		break;

		case	9008:
		{
			if (sel)
			{
				if (strlen(b8->Text()))
				{
					if (st = b8->Text())
					{
						if ((nb = atoi(st)) > 0)
						{
							sel->msg = nb;
						}
					}
				}			
			}
		}
		break;

		case	9006:
		{
			if (sel)
			{
				sel->enable = vl;
			}			
		}
		break;

		case	9007:
		{
			if (sel)
			{
				sel->checked = vl;
			}			
		}
		break;

		case	9009:
		{
			if (sel)
			{
				sel->radio = vl;
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
MenuWindow::AddMenu(void)
{
	CMenuItem *it;
	char *xt,*st;
	int nb;
	
	if (xt = b4->Text())
	{
		if (*xt)
		{
			if (st = b8->Text())
			{
				if ((nb = atoi(st)) > 0)
				{
					if (!sel)
					{
						goto ok;
					}

					if (!sel->OutlineLevel())
					{
ok:						b0->AddItem(it = new CMenuItem(true,xt,0,nb,b6->Value(),false,false));
					}
						else
					{
						int32 selected = b0->CurrentSelection();
						if (selected >= 0)
						{
							CMenuItem* pSelItem = (CMenuItem *)b0->ItemAt(selected);
	
							if (pSelItem)
							{		
								int32 level = pSelItem->OutlineLevel() + 1;
								int32 index = b0->FullListIndexOf(pSelItem)
									+ b0->CountItemsUnder(pSelItem, false);
	
								b0->AddUnder(it = new CMenuItem(true,xt,0,nb,b6->Value(),false,false,level),pSelItem);
							}
						}
					}
				
					b0->Invalidate();	// outline view doesn't

					b0->Select(b0->IndexOf(it));
				}
			}	
		}
	}
}

void
MenuWindow::AddItem(void)
{
	CMenuItem *it;
	char *xt,*st;
	int car,nb;
	
	if (xt = b4->Text())
	{
		if (*xt)
		{
			st = b5->Text();

			car = st[0];

			if (st = b8->Text())
			{
				if ((nb = atoi(st)) > 0)
				{
					if (sel)
					{
						int32 selected = b0->CurrentSelection();
						if (selected >= 0)
						{
							CMenuItem* pSelItem = (CMenuItem *)b0->ItemAt(selected);
	
							if (pSelItem)
							{		
								int32 level = pSelItem->OutlineLevel() + 1;
								int32 index = b0->FullListIndexOf(pSelItem)
									+ b0->CountItemsUnder(pSelItem, false) + 1;
	
								b0->AddItem(it = new CMenuItem(false,xt,car,nb,b6->Value(),b7->Value(),b9->Value(),(!pSelItem->OutlineLevel()) ? level : level - 1),index);

								b0->Invalidate();	// outline view doesn't

								b0->Select(b0->IndexOf(it));
							}
						}
					}
				}
			}	
		}
	}
}

void
MenuWindow::Delete(void)
{
	if (sel)
	{
		CMenuItem* pSuperitem = dynamic_cast<CMenuItem*>(b0->Superitem(sel));

		b0->RemoveItem(sel);	

		if (pSuperitem)
		{
			if (!b0->CountItemsUnder(pSuperitem,true))
			{
				int32 index = b0->FullListIndexOf(pSuperitem);
				b0->RemoveItem(pSuperitem);
				CMenuItem* pCloneItem = new CMenuItem(pSuperitem->menu,(char *)pSuperitem->Text(),pSuperitem->car,pSuperitem->msg,pSuperitem->enable,pSuperitem->checked,pSuperitem->radio,pSuperitem->OutlineLevel());
				b0->AddItem(pCloneItem, index);
				delete pSuperitem;
			}
		}

		delete sel;

		sel = 0;
	}
}

bool
MenuWindow::QuitRequested(void)
{
	StoreInfo();

	return true;
}

void
MenuWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);

	menueditrect = Frame();
}

void
MenuWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	menueditrect = Frame();
}

void
window_menu(BList *ls)
{
	int k;
	struct mymenu *tx;

	sel = 0;

	MenuWindow *wi;
	
	wi = new MenuWindow(menueditrect);

	list.MakeEmpty();

	lsgad = ls;

	for (k = 0; k < ls->CountItems(); k++)
	{
		if (tx = (struct mymenu *)ls->ItemAt(k))
		{
			list.AddItem(tx);
		}
	}	

	wi->LoadInfo();
}
	
	
