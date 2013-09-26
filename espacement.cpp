#include "proto.h"

static a,b;

class SpaceWindow : public BWindow
{
public:
		SpaceWindow(BRect rct);
		~SpaceWindow(void);
		
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	FrameMoved(BPoint pt);

		BTextControl *b0,*b1;
		BButton	*b3,*b4;
};

SpaceWindow::SpaceWindow(BRect rct):BWindow(rct,GetMessage(msg_espacement),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect 	rect(Bounds());
	BView	*xt;

	xt = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);

	xt->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	b0 = CreateInteger(MyRect(5,5,120,25),GetMessage(msg_spacex),9000,4);

	SetStringLen(b0,3);

	b1 = CreateInteger(MyRect(5,30,120,25),GetMessage(msg_spacey),9001,4);

	SetStringLen(b1,3);

	b3 = CreateButton(MyRect(140,5,70,25),GetMessage(msg_ok),9003);
	b4 = CreateButton(MyRect(140,35,70,25),GetMessage(msg_cancel),9004);

	xt->AddChild(b0);
	xt->AddChild(b1);
	xt->AddChild(b3);
	xt->AddChild(b4);

	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));

	if (DefWin)
	{
		char buf[6];
		
		a = DefWin->spacex;
		b = DefWin->spacey;
		
		sprintf(&buf[0],"%d",a);
		
		b0->SetText(&buf[0]);		

		sprintf(&buf[0],"%d",b);
		
		b1->SetText(&buf[0]);		
	}

	AddChild(xt);
}

SpaceWindow::~SpaceWindow(void)
{
	SpaceWin = NULL;
}

void
SpaceWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);
}

void
SpaceWindow::MessageReceived(BMessage *msg)
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

				wi->spacex = atoi(b0->Text());
				wi->spacey = atoi(b1->Text());

				wi->Unlock();
			}		
		}
		break;

		case	9004:
		{
			if	(wi = DefWin)
			{
				wi->Lock();

				wi->spacex 	= a;
				wi->spacey 	= b;

				wi->Unlock();
			}		
		}
		break;

		default:	BWindow::MessageReceived(msg);	break;
	}	
}

bool
SpaceWindow::QuitRequested(void)
{
	return true;
}

void
spacement_window(void)
{
	if (!SpaceWin)
	{
		SpaceWin = new SpaceWindow(MyRect(prefs.grillepoint.x,prefs.grillepoint.y,220,90));

		SpaceWin->Show();
	}
		else
	{
		SpaceWin->Show();
	
		SpaceWin->Activate();
	}	
}
