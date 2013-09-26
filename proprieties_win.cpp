#include "proto.h"
#include "edit_tags.h"

const rgb_color kWhite = {255,255,255,255}; 
const rgb_color kGray = {219,219,219,255}; 
const rgb_color kMedGray = {180,180,180,255}; 
const rgb_color kDarkGray = {100,100,100,255}; 
const rgb_color kBlackColor = {0,0,0,255}; 

unsigned char abmp9x9[243] ={
91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,
91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,
91,162,187,91,162,187,91,162,187,91,162,187,0x00,0x00,0x00,91,162,187,
91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,
0x00,0x00,0x00,0x00,0x00,0x00,91,162,187,91,162,187,0x00,0x00,0x00,91,162,187,
91,162,187,91,162,187,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,91,162,187,
91,162,187,0x00,0x00,0x00,0x00,0x00,0x00,91,162,187,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,91,162,187,91,162,187,91,162,187,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,91,162,187,91,162,187,91,162,187,
91,162,187,91,162,187,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,91,162,187,
91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,
0x00,0x00,0x00,91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,
91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,91,162,187,
91,162,187,91,162,187,91,162,187};

unsigned char bbmp9x9[243] ={
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
0x00,0x00,0x00,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
0x00,0x00,0x00,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,
B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT,B_TRANSPARENT_8_BIT};

//int last = -1;

CheckItemBox::CheckItemBox(char *src,bool check = false):BListItem()
{
	name = MyStringStr(src);

	checked = check;
}

CheckItemBox::~CheckItemBox()
{
	if	(name)
	{
		MyFree(name);
	}
}

void
CheckItemBox::Update(BView *vx,const BFont *ft)
{
	font_height	finfo;

	BListItem::Update(vx,ft);

	ft->GetHeight(&finfo);

	SetHeight(12 + finfo.ascent + finfo.descent + finfo.leading);
}

void CheckItemBox::DrawItem(BView *view,BRect rect,bool complete)
{
	float		offset = 16;
	BFont		font;
	char		buf[100],*str = &buf[0];
	BBitmap		*ic;
	font_height	finfo;
	
	view->GetFont(&font);

	view->GetFontHeight(&finfo);

	if (IsSelected())
	{
		view->SetHighColor(91,162,187);

		view->FillRect(rect);

		view->SetHighColor(255,0,0);
	}
		else
	{
		view->SetHighColor(255,255,255);

		view->FillRect(rect);
	}

	view->SetHighColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	if (checked)
 	{
		if (ic = new PrefilledBitmap(BRect(0,0,8,8),B_RGB32,IsSelected() ? &abmp9x9[0] : &bbmp9x9[0],0,false,false))
		{
			view->SetDrawingMode(B_OP_OVER);
			view->DrawBitmap(ic, BPoint(rect.left + 3, rect.top + 7));
			view->SetDrawingMode(B_OP_COPY);
			offset = rect.left + ic->Bounds().Width() + 8;

			delete ic;
		}
	}

	if (name)
	{
		view->SetHighColor(0,0,0);

		view->MovePenTo(offset,rect.top + ((rect.Height() - (finfo.ascent + finfo.descent + finfo.leading)) / 2) +
					(finfo.ascent + finfo.descent) - 2);
		view->DrawString(name);
	}
}

MyListView2::MyListView2(BRect rect):BListView(rect,"",B_SINGLE_SELECTION_LIST,B_FOLLOW_ALL)
{
	BFont font;

	GetFont(&font);

	font.SetSize(17);

	font.SetFlags(B_DISABLE_ANTIALIASING);

	SetFont(&font,B_FONT_FLAGS);

	mLastButton = mClickCount = 0;
}

MyListView2::~MyListView2()
{
	MakeEmpty();
}

void
MyListView2::MakeEmpty(void)
{
	BListView::MakeEmpty();
}

void
ChangeFlags(int item,bool set)
{
	WrkWindow 		*wi;
	struct MyGadget *gd;

	if (wi = OldWindow)
	{
		if (set)
		{
			wi->idcmp |= (1L << item);	
		}
			else
		{
			wi->idcmp &= ~(1L << item);
		}
	}
		else
	{
		if (wi = DefWin)
		{
			if (gd = wi->sellist.ItemAt(0))
			{
				if (set)
				{
					gd->idcmp |= (1L << item);	
				}
					else
				{
					gd->idcmp &= ~(1L << item);
				}
			}
		}
	}
}

void MyListView2::MouseDown(BPoint where)
{
	char *buf;
	CheckItemBox *it;
	BMessage* msg = Window()->CurrentMessage();

    int32 clicks = msg->FindInt32("clicks");
    int32 button = msg->FindInt32("buttons");

    if ((button == mLastButton) && (clicks > 1))
    {
        mClickCount++;
    }
    	else mClickCount = 1;

    mLastButton = button;

	int32 item = IndexOf(where);

	if ((item >= 0) && (item < CountItems())) 
	{
		switch(button)
		{
			case	B_PRIMARY_MOUSE_BUTTON:
			{
				if (it = (CheckItemBox *)ItemAt(item))
				{
					Select(IndexOf(it));

					if (mClickCount > 1)
					{
						it->checked = !it->checked;
	
						ChangeFlags(item,it->checked);

						InvalidateItem(IndexOf(it));
					}
				}
			}
			break;
			
			case	B_SECONDARY_MOUSE_BUTTON:
			{
				BPopUpMenu* popup = new BPopUpMenu("");

				popup->SetAsyncAutoDestruct(true);

				popup->SetRadioMode(false);

				popup->AddItem(new BMenuItem(GetMessage(msg_selectall), new BMessage(73500)));
				popup->AddItem(new BMenuItem(GetMessage(msg_selectnone), new BMessage(73501)));
				popup->AddSeparatorItem();
				popup->AddItem(new BMenuItem(GetMessage(msg_inverseselection), new BMessage(73502)));

				popup->SetTargetForItems(Window());

				ConvertToScreen(&where); 

				popup->Go(where,true,false,false);
			}
			break;
		}
	}
}	

MyBTabView::MyBTabView(BRect rct):BTabView(rct,"")
{
}

class MyBTab : public BTab
{
public:
		MyBTab(void);
		
		virtual void DrawTab(BView *owner,BRect frame,tab_position pos,bool full = true);
}; 		

MyBTab::MyBTab():BTab()
{
}

void
MyBTab::DrawTab(BView *owner,BRect frame,tab_position pos,bool full = true)
{
	rgb_color hi,lo;
	
	hi = owner->HighColor();
	lo = owner->LowColor();

	owner->SetHighColor(0,0,0); 
	owner->SetLowColor(219,219,219); 

	DrawLabel(owner,frame);

	owner->BeginLineArray(7); 

	if (pos != B_TAB_ANY)
	{ 
		owner->AddLine(BPoint(frame.left, frame.bottom),BPoint(frame.left+3, frame.bottom-3), kWhite); 
	} 

	owner->AddLine(BPoint(frame.left+4, frame.bottom-4),BPoint(frame.left+4, frame.top), kWhite); 

	owner->AddLine(BPoint(frame.left+5, frame.top),BPoint(frame.right-5, frame.top), kWhite); 

	owner->AddLine(BPoint(frame.right-4, frame.top),BPoint(frame.right-4, frame.bottom-4), kDarkGray); 

	owner->AddLine(BPoint(frame.right-5, frame.top),BPoint(frame.right-5, frame.bottom-4), kMedGray); 

	if (full)
	{ 
		owner->AddLine(BPoint(frame.right-3, frame.bottom-3),BPoint(frame.right, frame.bottom), kDarkGray); 
		owner->AddLine(BPoint(frame.right-4, frame.bottom-3),BPoint(frame.right-1, frame.bottom), kMedGray); 
	} 
	
	owner->EndLineArray(); 
	
	owner->SetHighColor(hi); 
	owner->SetLowColor(lo);
}

BRect old;

void
MyBTabView::Select(int32 nb)
{
	BTab *tb;

	if (tb = TabAt(Selection()))
	{
		old = tb->View()->Bounds();
	}

	BTabView::Select(nb);

	if (tb = TabAt(Selection()))
	{
		BListView *it;

		BView *vx = tb->View();
		BScrollBar *sc;

		vx->ResizeTo(old.IntegerWidth(),old.IntegerHeight());

		vx->Invalidate();
	}
}

void
change_infowin_number(int type,int val)
{
	EditButtonWindow *wi;
	
	if (wi = EditorWin)
	{
		if	(wi->Lock())
		{
			switch(type)
			{
				case	WLeft:		wi->left->SetValue(val);	break;
				case	WTop:		wi->top->SetValue(val);		break;
				case	WWidth:		wi->width->SetValue(val);	break;
				case	WHeight:	wi->height->SetValue(val);	break;
			}

			wi->Unlock();
		}	
	}
}
