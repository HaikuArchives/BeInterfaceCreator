#include "proto.h"
#include "placement.h"
#include "icone.h"

#include <ClassInfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class MyLv0 : public BListView
{
public:
	MyLv0(BRect rct);

	virtual void SelectionChanged(void);
	virtual void FrameResized(float wi,float he);
	virtual bool InitiateDrag(BPoint  point,int32 index,bool wasSelected);
};

class GadWindow : public BWindow
{
public:
		GadWindow(BRect rct);
		~GadWindow(void);
		
	virtual void	FrameMoved(BPoint pt);
	virtual void	FrameResized(float wi,float he);
	virtual	void	WindowActivated(bool act);
	virtual	bool	QuitRequested(void);

	MyLv0 *xt;
	BScrollView *scroll;
};

MyLv0::MyLv0(BRect rct):BListView(rct,"",B_SINGLE_SELECTION_LIST,B_FOLLOW_ALL)
{
	BFont font;

	GetFont(&font);

	font.SetFlags(B_DISABLE_ANTIALIASING);

	SetFont(&font,B_FONT_FLAGS);
}

void
MyLv0::SelectionChanged(void)
{
	BListView::SelectionChanged();

	prefs.type = CurrentSelection();

	if (PlaceWin && DefWin)
	{
		BMessage msg(10003);
		
		msg.AddInt32("type",prefs.type);		
		
		PlaceWin->PostMessage(&msg);
	}
}

void
MyLv0::FrameResized(float wi,float he)
{
	int nb;

	BListView::FrameResized(wi,he);

	if ((nb = CurrentSelection()) >= 0)
	{
		InvalidateItem(nb);
	}
}

bool
MyLv0::InitiateDrag(BPoint  point,int32 index,bool wasSelected)
{
	if (wasSelected) 
	{
		BMessage msg(45000);
		TListItem0 *item = cast_as(ItemAt(index),TListItem0);
		if(item == NULL)
			return false;

		msg.AddInt32("sel",index);
		const char *subject = item->name;
		BRect	theRect = this->ItemFrame(index);
		theRect.OffsetTo(B_ORIGIN);
		theRect.right = theRect.left + StringWidth(subject) + 20;
		BBitmap *bitmap = new BBitmap(theRect,B_RGBA32,true);
		BView *view = new BView(theRect,"",B_FOLLOW_NONE,0);
		const BBitmap *icon = item->icon;

		bitmap->AddChild(view);
		bitmap->Lock();
		view->SetHighColor(0,0,0,0);
		view->FillRect(view->Bounds());
		
		view->SetDrawingMode(B_OP_ALPHA);
		view->SetHighColor(0,0,0,128);
		view->SetBlendingMode(B_CONSTANT_ALPHA,B_ALPHA_COMPOSITE);
		if(icon)
			view->DrawBitmap(icon);
		
		bitmap->Unlock();
		
		DragMessage(&msg, bitmap, B_OP_ALPHA,
				BPoint(bitmap->Bounds().Width()/2,bitmap->Bounds().Height()/2));
	}

	return wasSelected;
}

GadWindow::GadWindow(BRect rct):BWindow(rct,GetMessage(msg_listegadget),B_TITLED_WINDOW,B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect rect(Bounds());

	TListItem0 *it;
	BBitmap *ic;
	int k = 0;
	char **tab,*str;

	rect.right -= B_V_SCROLL_BAR_WIDTH;

	xt = new MyLv0(rect);

	tab = (ProjetType == PROJET_BCC) ? &gad_name_basic[0] : &gad_name_ccplus[0];

	while (str = tab[k])
	{
		void *dat;

		switch(k++)
		{
			case	TEDIT_KIND:
			case	TEDIT_HORIZ_KIND:
			case	TEDIT_VERT_KIND:
			case	TEDIT_ALL_KIND:			dat = &tedit_icon[0];	break;
			case	LISTVIEW_KIND:
			case	LISTVIEW_HORIZ_KIND:
			case	LISTVIEW_VERT_KIND:
			case	LISTVIEW_ALL_KIND:		dat = &listview_icon[0];	break;
			case	OUTLISTVIEW_KIND:
			case	OUTLISTVIEW_HORIZ_KIND:
			case	OUTLISTVIEW_VERT_KIND:
			case	OUTLISTVIEW_ALL_KIND:	dat = &outlistview_icon[0];	break;
			case	BUTTON_KIND:			dat = &button_icon[0];		break;
			case	CHECKBOX_KIND:			dat = &checkbox_icon[0];	break;
			case	BOX_KIND:				dat = &box_icon[0];			break;
			case	COLOR_KIND:				dat = &color_icon[0];		break;
			case	MENU_KIND:				dat = &menu_icon[0];		break;
			case	MX_KIND:				dat = &mx_icon[0];			break;
			case	RADIO_KIND:				dat = &radio_icon[0];		break;
			case	STATUSBAR_KIND:			dat = &status_icon[0];		break;
			case	SLIDER_VERT_KIND:
			case	SLIDER_HORIZ_KIND:		dat = &slider_icon[0];		break;
			case	SCROLLER_HORIZ_KIND:
			case	SCROLLER_VERT_KIND:		dat = &scroller_icon[0];	break;
			case	TAB_KIND:				dat = &tab_icon[0];			break;
			case	NUMBER_KIND:
			case	TEXT_KIND:				dat = &text_icon[0];		break;
			case	PASSWORD_KIND:
			case	INTEGER_KIND:
			case	FLOAT_KIND:
			case	STRING_KIND:			dat = &string_icon[0];		break;
			default:						dat = &color_icon[0];		break;
		}
					
		ic = new PrefilledBitmap(BRect(0,0,31,23),B_RGB32,dat,0,false,false);

		xt->AddItem(it = new TListItem0(ic,str));
	}
	
	scroll = new BScrollView("",xt,B_FOLLOW_ALL,0,true,true);

	AddChild(scroll);

	xt->Select(prefs.type);

	xt->ScrollToSelection();
}

GadWindow::~GadWindow(void)
{
	GadWin = NULL;
}

void
GadWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);

	prefs.gadrect = Frame();
}

void
GadWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	prefs.gadrect = Frame();
}

void
GadWindow::WindowActivated(bool act)
{
	BWindow::WindowActivated(act);

	if (act)
	{
		xt->MakeFocus(true);
	}
}

bool
GadWindow::QuitRequested(void)
{
	return true;
}

TListItem0::TListItem0(BBitmap *ic,char *str):BListItem()
{
	icon = ic;
	name = MyStringStr(str);
}

TListItem0::~TListItem0()
{
	if (icon)
	{
		delete icon;
	}

	if (name)
	{
		free(name);
	}
}

void TListItem0::DrawItem(BView *view, BRect rect,bool complete)
{
	float		offset = 20;
	BFont		font;
	font_height	finfo;

	view->GetFont(&font);

	if (IsSelected())
	{
		view->SetHighColor(91,162,187);

		view->FillRect(rect);

		view->SetHighColor(255,0,0);

		view->StrokeRect(rect);
	}
		else
	{
		view->SetHighColor(255,255,255);

		view->FillRect(rect);
	}

	if (icon)
	{
		view->SetDrawingMode(B_OP_OVER);
		view->DrawBitmap(icon, BPoint(rect.left + 3, rect.top + 3));
		view->SetDrawingMode(B_OP_COPY);
		offset = rect.left + icon->Bounds().Width() + 8;
	}

	font.GetHeight(&finfo);

	view->SetHighColor(0,0,0);

	view->MovePenTo(offset,
		rect.top + ((rect.Height() - (finfo.ascent + finfo.descent + finfo.leading)) / 2) +
					(finfo.ascent + finfo.descent) - 2);
	view->DrawString(name);
}

void TListItem0::Update(BView *owner, const BFont *finfo)
{
	BListItem::Update(owner, finfo);

	SetHeight(29);
}

void
create_gadget_window(void)
{
	if (!GadWin)
	{
		GadWin = new GadWindow(prefs.gadrect);

		GadWin->Show();
	}
		else
	{
		GadWin->Show();

		GadWin->Activate();
	}
}

