#include "proto.h"

class HGeneralSettingView1 : public BView {
public:
					HGeneralSettingView1(BRect rect);

	BMenuField		*b0;
	BCheckBox		*b1;
	BTextControl	*b2;
	BCheckBox		*b3;
	BCheckBox		*b4;
	BCheckBox		*b5;
	BCheckBox		*b6;
};

class HGeneralSettingView2 : public BView {
public:
					HGeneralSettingView2(BRect rect);

	BCheckBox		*b0,*b1,*b2;
};

class HGeneralSettingView3 : public BView {
public:
					HGeneralSettingView3(BRect rect);

	BTextControl	*b0;
	BMenuField		*b1;
	BTextControl	*b2;
	BTextControl	*b3;
	BMenuField		*b4;

	BCheckBox		*b5;
	BCheckBox		*b6;
};

class HPrefWindow : public BWindow
{
	public:
		HPrefWindow(BRect win_rect);
		~HPrefWindow();

		virtual void MessageReceived(BMessage* message);
		virtual	bool QuitRequested();
		virtual	void FrameMoved(BPoint pt);

	HGeneralSettingView1 *f1;
	HGeneralSettingView2 *f2;
	HGeneralSettingView3 *f3;
};

char *locale_lang[] =
{
	NULL,
	NULL,
	NULL
};	

char *type_opti[] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};	

char *type_app[] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};	

HGeneralSettingView2::HGeneralSettingView2(BRect rect)
:BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	b0 = CreateCheck(MyRect(10,10,200,25),GetMessage(msg_void_default),10000,prefs.code_default_void);
	b1 = CreateCheck(MyRect(10,35,200,25),GetMessage(msg_default_rtn),10001,prefs.code_default_routine);
	b2 = CreateCheck(MyRect(10,60,200,25),GetMessage(msg_write_name),10002,prefs.code_default_name);

	AddChild(b0);
	AddChild(b1);
	AddChild(b2);
}

HGeneralSettingView3::HGeneralSettingView3(BRect rect)
:BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW)
{
	int z = 0,k;

	BMenu *menu;
	
	for (k = msg_executable; k < msg_void_default; k++)
	{
		type_app[z++] = GetMessage(k);
	}

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	b0 = CreateString(MyRect(10,10,250,25),GetMessage(msg_application_name),11000,16);

	menu = CreateMenu(Window(),&type_app[0],11001,prefs.typeapp);

	b1 = CreateMx(MyRect(10,35,280,25),GetMessage(msg_application_type),menu,16);

	b2 = CreateString(MyRect(10,60,250,25),GetMessage(msg_comp_flag),11002,16);

	b3 = CreateString(MyRect(10,85,250,25),GetMessage(msg_link_flag),11003,16);

	menu = CreateMenu(Window(),&type_opti[0],11004,prefs.optiapp);

	b4 = CreateMx(MyRect(10,110,180,25),GetMessage(msg_optimisation),menu,16);

	b5 = CreateCheck(MyRect(10,135,180,25),GetMessage(msg_warning),11005,prefs.warningapp);

	b6 = CreateCheck(MyRect(10,160,180,25),GetMessage(msg_debug),11006,prefs.debugapp);

	b0->SetText(&prefs.appname[0]);
	b2->SetText(&prefs.compflag[0]);
	b3->SetText(&prefs.linkflag[0]);

	AddChild(b0);
	AddChild(b1);
	AddChild(b2);
	AddChild(b3);
	AddChild(b4);
	AddChild(b5);
	AddChild(b6);
}

HGeneralSettingView1::HGeneralSettingView1(BRect rect)
:BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW)
{
	char buf[10];
	int k,z = 0;

	BMenu *menu;
	MyFilterInteger *filter;

	for (k = msg_none; k < msg_english; k++)
	{
		type_opti[z++] = GetMessage(k);
	}

	locale_lang[0] = GetMessage(msg_english);
	locale_lang[1] = GetMessage(msg_french);

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	menu = CreateMenu(Window(),&locale_lang[0],9001,prefs.locale);

	b0 = CreateMx(MyRect(10,10,180,25),GetMessage(msg_prefs_language),menu,16);

	b1 = CreateCheck(MyRect(10,35,100,25),GetMessage(msg_prefs_saveauto),9002,prefs.autosave);

	b2 = CreateString(MyRect(140,35,120,25),GetMessage(msg_min),9000,4);

	if	(filter = new MyFilterInteger())
	{
		b2->TextView()->AddFilter((BMessageFilter *)filter);
	}

	b2->TextView()->SetMaxBytes(3);

	b3 = CreateCheck(MyRect(10,60,180,25),GetMessage(msg_prefs_openlastprojet),9003,prefs.lastprj);

	b4 = CreateCheck(MyRect(10,85,180,25),GetMessage(msg_prefs_confirmquit),9004,prefs.confquit);

	b5 = CreateCheck(MyRect(10,110,180,25),GetMessage(msg_prefs_delete),9005,prefs.confdel);

	b6 = CreateCheck(MyRect(10,135,180,25),GetMessage(msg_prefs_kill_del),9006,prefs.desacdelkey);

	sprintf(&buf[0],"%d",prefs.automin);

	b2->SetText(&buf[0]);

	AddChild(b0);
	AddChild(b1);
	AddChild(b2);
	AddChild(b3);
	AddChild(b4);
	AddChild(b5);
	AddChild(b6);
}

HPrefWindow::HPrefWindow(BRect win_rect):BWindow(win_rect,GetMessage(msg_preferences),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
{
	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));
	
	BRect rect = Bounds();
	rect.bottom -= 35;
	BTabView *tabview = new BTabView(rect,"");
	tabview->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	
	BTab *tab;
	BRect frame = tabview->Bounds();

	tab = new BTab();
	tabview->AddTab(f1 = new HGeneralSettingView1(frame),tab);
	tab->SetLabel(GetMessage(msg_prefs));

	if (ProjetType == PROJET_STANDARD)
	{
		tab = new BTab();
		tabview->AddTab(f2 = new HGeneralSettingView2(frame),tab);
		tab->SetLabel(GetMessage(msg_code));

		tab = new BTab();
		tabview->AddTab(f3 = new HGeneralSettingView3(frame),tab);
		tab->SetLabel(GetMessage(msg_makefile));
	}
	
	AddChild(tabview);
	
	BRect bgrect = Bounds();
	bgrect.top = bgrect.bottom - 35;
	BView *bgview = new BView(bgrect,"",B_FOLLOW_ALL,B_WILL_DRAW);
	bgview->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	bgrect.OffsetTo(B_ORIGIN);
	bgrect.top += 5;
	bgrect.right -= 10;
	bgrect.left = bgrect.right - 80;
	bgrect.bottom -= 5;

	BButton *button = CreateButton(bgrect,GetMessage(msg_ok),B_QUIT_REQUESTED);

	bgview->AddChild(button);
	this->AddChild(bgview);
}

HPrefWindow::~HPrefWindow()
{
	prefs.automin = atoi(f1->b2->Text());
}

void
HPrefWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);
}

void
HPrefWindow::MessageReceived(BMessage *msg)
{
	int32 id,vl;
	char *txt = "";
	BTextControl *xt = NULL;

	msg->FindInt32("be:value",&vl);
	msg->FindInt32("index",&id);

	if (msg->FindPointer("source",(void **)&xt) == B_OK)
	{
		if (is_instance_of(xt,BTextControl))
		{
			txt = xt->Text();		
		}	
	}

	switch(msg->what)
	{
		case	9001:
		{
			prefs.locale = id;	
		}
		break;

		case	9002:
		{
			prefs.autosave = vl;	
		}
		break;

		case	9003:
		{
			prefs.lastprj = vl;	
		}
		break;

		case	9004:
		{
			prefs.confquit = vl;	
		}
		break;

		case	9005:
		{
			prefs.confdel = vl;	
		}
		break;

		case	9006:
		{
			prefs.desacdelkey = vl;	
		}
		break;
		
		case	10000:
		{
			prefs.code_default_void = vl;
		}
		break;

		case	10001:
		{
			prefs.code_default_routine = vl;
		}
		break;

		case	10002:
		{
			prefs.code_default_name = vl;
		}
		break;
	
		case	11000:
		{
			strcpy(&prefs.appname[0],txt);		
		}
		break;

		case	11001:
		{
			prefs.typeapp = id;
		}
		break;

		case	11002:
		{
			strcpy(&prefs.compflag[0],txt);		
		}
		break;

		case	11003:
		{
			strcpy(&prefs.linkflag[0],txt);		
		}
		break;

		case	11004:
		{
			prefs.optiapp = id;
		}
		break;
		
		case	11005:
		{
			prefs.warningapp = vl;
		}
		break;

		case	11006:
		{
			prefs.debugapp = vl;
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
HPrefWindow::QuitRequested()
{
	return BWindow::QuitRequested();
}

void
prefs_window(void)
{
	HPrefWindow *win = new HPrefWindow(MyRect(prefs.prefspoint.x,prefs.prefspoint.y,400,400));
	win->Show();
}
