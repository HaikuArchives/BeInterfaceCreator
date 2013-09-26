#include "proto.h"
#include "edit_tags.h"

WrkWindow *OldWindow = NULL;

MyListView3::MyListView3(BRect rect):BListView(rect,"",B_SINGLE_SELECTION_LIST,B_FOLLOW_ALL)
{
	BFont font;

	GetFont(&font);

	font.SetSize(18);

	font.SetFlags(B_DISABLE_ANTIALIASING);

	SetFont(&font,B_FONT_FLAGS);

	mLastButton = mClickCount = 0;
}

MyListView3::~MyListView3()
{
	MakeEmpty();
}

void
MyListView3::MakeEmpty(void)
{
	BListView::MakeEmpty();
}

void
ChangeView(int item,bool set)
{
	WrkWindow 		*wi;
	struct MyGadget *gd;

	if (wi = DefWin)
	{
		if (gd = wi->sellist.ItemAt(0))
		{
			if (set)
			{
				gd->view |= (1L << item);	
			}
				else
			{	
				gd->view &= ~(1L << item);
			}
		}
			else
		{
			if (set)
			{
				wi->flag |= (1L << item);	
			}
				else
			{	
				wi->flag &= ~(1L << item);
			}
		}	
	}
}

void MyListView3::MouseDown(BPoint where)
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
	
						ChangeView(item,it->checked);

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

				popup->AddItem(new BMenuItem(GetMessage(msg_selectall), new BMessage(73600)));
				popup->AddItem(new BMenuItem(GetMessage(msg_selectnone),new BMessage(73601)));
				popup->AddSeparatorItem();
				popup->AddItem(new BMenuItem(GetMessage(msg_inverseselection),new BMessage(73602)));

				popup->SetTargetForItems(Window());

				ConvertToScreen(&where); 

				popup->Go(where,true,false,false);
			}
			break;
		}
	}
}	

ColorView::ColorView( BRect frame,int id )
			   : BView( frame,"Color_view",B_FOLLOW_NONE,B_WILL_DRAW){

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	color.red = color.green = color.blue = 255;
	lowcolor.red = lowcolor.blue = 222;
	lowcolor.green = 219;
	enabled = true;
	cid = id;
}

ColorView::~ColorView() {
}

void ColorView::Draw( BRect updateRect ) {

	SetLowColor( lowcolor );
	SetHighColor(color);
	FillRect( Bounds(),enabled ? B_SOLID_HIGH : B_MIXED_COLORS );
	if( enabled )
		SetHighColor(0,0,0);
	else
		SetHighColor(169,166,169);
	StrokeRect(Bounds());
}

void ColorView::SetColor( rgb_color col ) {
	color = col;
	if( Window() )
		Invalidate();
}

void ColorView::SetColor( int32 r,int32 g,int32 b ) {
	color.red = r;
	color.green = g;
	color.blue = b;
	if( Window() )
		Invalidate();
}

rgb_color ColorView::GetColor() {
	return color;
}

void ColorView::SetEnabled( bool en ) {
	enabled = en;
}

void ColorView::MouseDown( BPoint point ) {
	
	if( enabled && Window() && cid != -1 ) {
		BMessage* msg = new BMessage(2200);
		msg->AddData( "color",B_RGB_COLOR_TYPE,&color,sizeof(rgb_color) );
		msg->AddPointer("pt",this);
		msg->AddInt32( "cid",(int32)cid );
		Window()->PostMessage( msg );	
	}
	BView::MouseDown(point);
}


EnStringView::EnStringView( BRect frame,const char* name,const char* text )
			: BStringView( frame,name,text )
{
	enabled = true;	
}

void EnStringView::SetEnabled( bool en ) {
	enabled = en;
}


void EnStringView::Draw(BRect updateRect) {

	if( enabled )
		SetHighColor(0,0,0);
	else
		SetHighColor(132,130,132);

	BStringView::Draw(updateRect);
}

EditButtonWindow::EditButtonWindow(BRect rct,struct MyGadget *ee):BWindow(rct,"",B_TITLED_WINDOW,B_WILL_ACCEPT_FIRST_CLICK|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	gad = ee;

	lv = idcmp = 0;

	InitGui();
}

EditButtonWindow::~EditButtonWindow(void)
{
}

void
remove_all_gadget(BView *vx)
{
	BView *bt;

	while (bt = (BView *)vx->ChildAt(0))
	{ 
		vx->RemoveChild(bt);
		
		delete bt;
	}
}

void *last = -5;

void
EditButtonWindow::ChangeGui(struct MyGadget *gd)
{
	BScrollView		*sc;

	char **tab,*str;
	int k;

	gad = gd;

	Lock();

	if (gd != last)
	{
		remove_all_gadget(vie1);
		remove_all_gadget(vie2);
		remove_all_gadget(vie3);

		left = CreateSpin(MyRect(10,10,130,18),GetMessage(msg_left),9000,-5000,5000,0,16);

		top = CreateSpin(MyRect(10,35,130,18),GetMessage(msg_top),9001,-5000,5000,0,16);

		width = CreateSpin(MyRect(10,60,130,18),GetMessage(msg_width),9002,0,5000,0,16);

		height = CreateSpin(MyRect(10,85,130,18),GetMessage(msg_height),9003,0,5000,0,16);

		name = CreateString(MyRect(160,10,220,25),GetMessage(msg_name),9004,16);

//		name->SetModificationMessage(new BMessage(9004));

		title = CreateString(MyRect(160,35,220,25),GetMessage(msg_title),9005,16);

		vie1->AddChild(left);
		vie1->AddChild(top);
		vie1->AddChild(width);
		vie1->AddChild(height);
		vie1->AddChild(name);
		vie1->AddChild(title);

		if (gad)
		{
			left->SetValue(gad->x);
			top->SetValue(gad->y);
			width->SetValue(gad->wi);
			height->SetValue(gad->he);

			title->SetText(&gad->Title[0]);
			name->SetText(&gad->Name[0]);

			SetTitle(GetMessage(msg_editeur_gadget));

			bbox = new BBox(MyRect(10,120,265,120));

			menu = CreateMenu(this,&align_select[0],align_type,gad->align);

			alig = CreateMx(MyRect(10,210,180,25),GetMessage(msg_alignment),menu,4);

			bbox->SetLabel(alig);

			menu = CreateMenu(this,&alignx_select[0],align_x,gad->alignx);

			alignx = CreateMx(MyRect(10,30,280,25),GetMessage(msg_alignment_x),menu,16);

			menu = CreateMenu(this,&aligny_select[0],align_y,gad->aligny);

			aligny = CreateMx(MyRect(10,60,280,25),GetMessage(msg_alignment_y),menu,16);

			if (gd->align != 2)
			{
				alignx->SetEnabled(false);
				aligny->SetEnabled(false);
			}

			bbox->AddChild(alignx);
			bbox->AddChild(aligny);

			vie1->AddChild(bbox);

			if (ProjetType == PROJET_STANDARD)
			{
				derived = new BCheckBox(MyRect(160,90,100,25),"",GetMessage(msg_derived),new BMessage(gad_derived));

				derived->SetValue(gad->derived);

				vie1->AddChild(derived);
			}
		}
			else
		{
			BMenu 		*menu;
			BMenuField	*type,*wrk;

			SetTitle(GetMessage(msg_editeur_window));

			menu = CreateMenu(this,&type_win[0],window_type,DefWin->typewin);

			type = CreateMx(MyRect(10,110,180,25),GetMessage(msg_type),menu,16);

			menu = CreateMenu(this,&wrk_win[0],window_workspace,DefWin->wrk);

			wrk = CreateMx(MyRect(10,135,180,25),GetMessage(msg_workspace),menu,16);

			vie1->AddChild(type);
			vie1->AddChild(wrk);
		}

		idcmp = new MyListView2(MyRect(10,10,400,300));

		sc = new BScrollView("",idcmp,B_FOLLOW_NONE,0,false,true);

		vie3->AddChild(sc);

		if (ProjetType == PROJET_STANDARD)
		{
			lv = (MyListView2 *)new MyListView3(MyRect(285,88,190,150));

			sc = new BScrollView("",lv,B_FOLLOW_NONE,0,false,true);
	
			k = 0;

			if (gad)
			{
				tab = &msg_gadviewflags[0];

				while (str = tab[k])
				{
					lv->AddItem(new CheckItemBox(str,(gad->view & (1l << k++)) ? true : false));
				}
			}
				else
			{
				tab = &msg_windowflags[0];

				while (str = tab[k])
				{
					lv->AddItem(new CheckItemBox(str,(DefWin->flag & (1l << k++)) ? true : false));
				}	
			}

			vie1->AddChild(sc);
		
			if (gd)
			{
				char buf[8];

				msg = CreateInteger(MyRect(160,60,220,25),GetMessage(msg_message),9006,16);

				SetStringLen(msg,4);

				if (gd->msg != 0)
				{
					sprintf(&buf[0],"%d",gd->msg);
			
					msg->TextView()->SetText(&buf[0]);
				}

				vie1->AddChild(msg);
			}
		}
	
		if (gad)
		{
			switch(gad->type)
			{
				case	VIEW_KIND:				tab = &msg_gadevents_view[0];						break;
				case	BUTTON_KIND:			tab = &msg_gadevents_button[0];		SetButton();	break;
				case	CHECKBOX_KIND:			tab = &msg_gadevents_checkbox[0];	SetCheckBox();	break;
				case	BOX_KIND:				tab = &msg_gadevents_box[0];		SetBbox();		break;
				case	COLOR_KIND:				tab = &msg_gadevents_color[0];		SetColor();		break;
				case	MENU_KIND:				tab = &msg_gadevents_menu[0];		SetMenu();		break;
				case	SLIDER_VERT_KIND:
				case	SLIDER_HORIZ_KIND:		tab = &msg_gadevents_slider[0];		SetSlider();	break;
				case	INTEGER_KIND:
				case	PASSWORD_KIND:
				case	FLOAT_KIND:
				case	STRING_KIND:			tab = &msg_gadevents_string[0];		SetString();	break;
				case	MX_KIND:				tab = &msg_gadevents_mx[0];			SetMx();		break;
				case	RADIO_KIND:				tab = &msg_gadevents_radio[0];		SetRadio();		break;
				case	SCROLLER_VERT_KIND:
				case	SCROLLER_HORIZ_KIND:	tab = &msg_gadevents_scroller[0];	SetScroller();	break;
				case	STATUSBAR_KIND:			tab = &msg_gadevents_status[0];		SetStatus();	break;
				case	TEXT_KIND:				tab = &msg_gadevents_text[0];		SetText();		break;
				case	TAB_KIND:				tab = &msg_gadevents_tab[0];		SetTab();		break;
				case	NUMBER_KIND:			tab = &msg_gadevents_button[0];		SetNumber();	break;
				case	TEDIT_KIND:
				case	TEDIT_HORIZ_KIND:
				case	TEDIT_VERT_KIND:
				case	TEDIT_ALL_KIND:			tab = &msg_gadevents_edit[0];		SetEdit();		break;
				case	LISTVIEW_KIND:
				case	LISTVIEW_HORIZ_KIND:
				case	LISTVIEW_VERT_KIND:
				case	LISTVIEW_ALL_KIND:		tab = &msg_gadevents_lv[0];			SetLv();		break;
				case	OUTLISTVIEW_KIND:
				case	OUTLISTVIEW_HORIZ_KIND:
				case	OUTLISTVIEW_VERT_KIND:
				case	OUTLISTVIEW_ALL_KIND:	tab = &msg_gadevents_olv[0];		SetOLv();		break;
			}	

			int k = 0;
	
			idcmp->MakeEmpty();

			if (ProjetType == PROJET_STANDARD)
			{
				while (str = tab[k])
				{
					idcmp->AddItem(new CheckItemBox(str,(gad->idcmp & (1l << k++)) ? true : false));
				}
			}
				else
			{
				switch(gad->type)
				{
					case	BUTTON_KIND:
					{
						idcmp->AddItem(new CheckItemBox(msg_gadevents_basic[0],(gad->idcmp & (1l << 0)) ? true : false));
					}
					break;
					
					case	BOX_KIND:
					case	TEXT_KIND:
					case	NUMBER_KIND:
					case	STATUSBAR_KIND:	break;
					
					default:
					{
						if (gad->type != MENU_KIND)
						{
							tab = &msg_gadevents_basic[0];

							while (str = tab[k])
							{
								idcmp->AddItem(new CheckItemBox(str,(gad->idcmp & (1l << k++)) ? true : false));

								if (k > 2)
								{
									if (!(gad->type == FLOAT_KIND || gad->type == INTEGER_KIND || gad->type == STRING_KIND || gad->type == PASSWORD_KIND))
									{
										goto exit;						
									}
								}
							}
exit:;					}
							else
						{
							idcmp->AddItem(new CheckItemBox(msg_gadevents_basic[1],(gad->idcmp & (1l << 1)) ? true : false));
						}	
					}
					break;
				}	
			}
		}
			else
		{
			SetWindow();
		}	

		last = gd;

		SetGlobalInformation();
	}
		else
	{
		SetGlobalInformation();
	}		
	
	Unlock();
}

class MyVx : public BView
{
public:

		MyVx(BRect rct);
		~MyVx();
		
		virtual void MouseDown(BPoint pt);
};

MyVx::MyVx(BRect rct):BView(rct,"",B_FOLLOW_NONE,B_WILL_DRAW)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}

MyVx::~MyVx()
{
}

void
MyVx::MouseDown(BPoint pt)
{
	BView::MouseDown(pt);
	
	Window()->Activate();
}

void
EditButtonWindow::InitGui(void)
{
	char *str;

	int k = 0;

	BRect frame,rect = Bounds();

	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));

	BTabView 	*tabview = new BTabView(rect,"");
	BTab 		*tab;

	tabview->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	frame = tabview->Bounds();

	tab1 = new BTab();
	tabview->AddTab(vie1 = new MyVx(frame),tab1);
	tab1->SetLabel(GetMessage(msg_constructor));

	tab2 = new BTab();
	tabview->AddTab(vie2 = new MyVx(frame),tab2);
	tab2->SetLabel(GetMessage(msg_proprieties));

	tab3 = new BTab();
	tabview->AddTab(vie3 = new MyVx(frame),tab3);
	tab3->SetLabel(GetMessage(msg_events));

	ChangeGui(gad);
	
	AddChild(tabview);

	tabview->SetTabWidth(B_WIDTH_FROM_WIDEST);
}

bool
EditButtonWindow::QuitRequested(void)
{
	EditorWin = NULL;

	last = -5;

	return true;
}
