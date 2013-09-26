#include "proto.h"

static a,b,c;

class GridWindow : public BWindow
{
public:
		GridWindow(BRect rct);
		~GridWindow(void);
		
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	FrameMoved(BPoint pt);

		BTextControl *b0,*b1;
		BCheckBox *b2;
		BButton	*b3,*b4;
};

GridWindow::GridWindow(BRect rct):BWindow(rct,GetMessage(msg_grid),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect 	rect(Bounds());
	BView	*xt;

	xt = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);

	xt->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	b0 = CreateInteger(MyRect(5,5,120,25),GetMessage(msg_espacex),9000,4);

	SetStringLen(b0,3);

	b1 = CreateInteger(MyRect(5,30,120,25),GetMessage(msg_espacey),9001,4);

	SetStringLen(b1,3);

	b2 = new BCheckBox(MyRect(5,55,150,25),"",GetMessage(msg_usegrid),new BMessage(9002));

	b3 = CreateButton(MyRect(140,5,70,25),GetMessage(msg_ok),9003);
	b4 = CreateButton(MyRect(140,35,70,25),GetMessage(msg_cancel),9004);

	xt->AddChild(b0);
	xt->AddChild(b1);
	xt->AddChild(b2);
	xt->AddChild(b3);
	xt->AddChild(b4);

	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));

	if (DefWin)
	{
		char buf[6];
		
		a = DefWin->gridx;
		b = DefWin->gridy;
		c = DefWin->grid;
		
		sprintf(&buf[0],"%d",a);
		
		b0->SetText(&buf[0]);		

		sprintf(&buf[0],"%d",b);
		
		b1->SetText(&buf[0]);		
	
		b2->SetValue(c);
	}

	AddChild(xt);
}

GridWindow::~GridWindow(void)
{
	GridWin = NULL;
}

void
GridWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	prefs.grillepoint = pt;
}

void
GridWindow::MessageReceived(BMessage *msg)
{
	WrkWindow *wi;
	BMessage mymsg(51000);
	int32 vl;

	switch(msg->what)
	{
		case	9003:
		{
			if	(wi = DefWin)
			{
				wi->Lock();

				wi->gridx = atoi(b0->Text());
				wi->gridy = atoi(b1->Text());

				wi->grid = b2->Value();

				wi->bck->Invalidate();

				PostMessage(B_QUIT_REQUESTED);

				wi->Unlock();
			}		
		}
		break;

		case	9004:
		{
			if	(wi = DefWin)
			{
				wi->Lock();

				wi->gridx 	= a;
				wi->gridy 	= b;
				wi->grid 	= c;

				wi->bck->Invalidate();

				wi->Unlock();
			}		
		}
		break;

		default:	BWindow::MessageReceived(msg);	break;
	}	
}

bool
GridWindow::QuitRequested(void)
{
	return true;
}

void
grid_window(void)
{
	if (!GridWin)
	{
		GridWin = new GridWindow(MyRect(prefs.grillepoint.x,prefs.grillepoint.y,220,90));

		GridWin->Show();
	}
		else
	{
		GridWin->Show();
	
		GridWin->Activate();
	}	
}

void
create_mmxmenu(void)
{
	struct MyGadget *gd;

	if (DefWin)
	{
		if (gd = DefWin->sellist.FirstItem())
		{
			if (gd->type == MENU_KIND)
			{
				window_menu(&gd->name);
			}
		}
	}
}
