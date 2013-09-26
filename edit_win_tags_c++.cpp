#include "proto.h"

#include "SpinButton.h"
#include "SpinControl.h"

using namespace BeUnited;

class EditWinWindow : public BWindow
{
public:
		EditWinWindow(BRect rct);
		~EditWinWindow(void);
		
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	InitGui(void);

	BView	*bck;
	
};

EditWinWindow::EditWinWindow(BRect rct):BWindow(rct,"Editeur fenetre",B_TITLED_WINDOW,B_WILL_ACCEPT_FIRST_CLICK|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect rect(Bounds());

	bck = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);

	bck->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	InitGui();

	AddChild(bck);
}

EditWinWindow::~EditWinWindow(void)
{
}

void
SetSpinDivider(SpinControl *ct,int nb)
{
	ct->SetDivider(ct->StringWidth(ct->Label()) + nb);
}

void
SetDivider(BTextControl *ct,int nb)
{
	ct->SetDivider(ct->StringWidth(ct->Label()) + nb);
}

void
SetDivider(BMenuField *ct,int nb)
{
	ct->SetDivider(ct->StringWidth(ct->Label()) + nb);
}

char *type_win[] =
{
	"B_TITLED_WINDOW",
	"B_DOCUMENT_WINDOW",
	"B_MODAL_WINDOW",
	"B_FLOATING_WINDOW",
	"B_BORDERED_WINDOW",
	NULL
};	

char *wrk_win[] =
{
	"B_CURRENT_WORKSPACE",
	"B_ALL_WORKSPACE",
	NULL
};	

char *look_win[] =
{
	"B_TITLED_WINDOW_LOOK",
	"B_DOCUMENT_WINDOW_LOOK",
	"B_MODAL_WINDOW_LOOK",
	"B_FLOATING_WINDOW_LOOK",
	"B_BORDERED_WINDOW_LOOK",
	"B_NO_BORDERED_WINDOW_LOOK",
	NULL
};

char *feel_win[] =
{
	"B_NORMAL_WINDOW_FEEL",
	"B_MODAL_SUBSET_WINDOW_FEEL",
	"B_MODAL_APP_WINDOW_FEEL",
	"B_MODAL_ALL_WINDOW_FEEL",
	"B_FLOATING_SUBSET_WINDOW_FEEL",
	"B_FLOATING_APP_WINDOW_FEEL",
	"B_FLOATING_ALL_WINDOW_FEEL",
	NULL
};	

void
EditWinWindow::InitGui(void)
{
	BMenu 		*menu;
	SpinControl *left,*top,*width,*height;
	SpinControl *minw,*minh,*maxw,*maxh;

	BMenuField	*type,*wrk,*look,*feel;
	BTextControl *title;

	MyListView2 *f0,*f1;
	BScrollView	*s0,*s1;

	char *str;

	int k = 0;

	left = CreateSpin(MyRect(10,10,130,18),"*******Left",9000,0,100,0,16);
	
	top = CreateSpin(MyRect(10,35,130,18),"Top",9001,0,100,0,16);

	width = CreateSpin(MyRect(10,60,130,18),"Right",9002,0,100,0,16);

	height = CreateSpin(MyRect(10,85,130,18),"Bottom",9003,0,100,0,16);

	title = CreateString(MyRect(10,110,120,25),"Title",9004,16);

	menu = CreateMenu(this,&type_win[0],9005,0);

	type = CreateMx(MyRect(10,135,180,25),"Type",menu,16);

	menu = CreateMenu(this,&wrk_win[0],9006,0);

	wrk = CreateMx(MyRect(10,160,180,25),"Workspace",menu,16);

	menu = CreateMenu(this,&look_win[0],9007,0);

	look = CreateMx(MyRect(10,185,180,25),"Look",menu,16);

	menu = CreateMenu(this,&feel_win[0],9008,0);

	feel = CreateMx(MyRect(10,210,180,25),"Feel",menu,16);

	minw = CreateSpin(MyRect(10,235,180,18),"Min horizontal",9009,0,100,0,16);

	maxw = CreateSpin(MyRect(10,260,180,18),"Max horizontal",9010,0,100,0,16);

	minh = CreateSpin(MyRect(10,285,180,18),"Min vertical",9011,0,100,0,16);

	maxh = CreateSpin(MyRect(10,310,180,18),"Max vertical",9012,0,100,0,16);

	f0 = new MyListView2(MyRect(210,10,240,150));

	s0 = new BScrollView("",f0,B_FOLLOW_ALL,0,false,true);

	f1 = new MyListView2(MyRect(210,170,240,150));

	s1 = new BScrollView("",f1,B_FOLLOW_ALL,0,false,true);

	bck->AddChild(left);
	bck->AddChild(top);
	bck->AddChild(width);
	bck->AddChild(height);
	bck->AddChild(title);
	bck->AddChild(type);
	bck->AddChild(wrk);
	bck->AddChild(look);
	bck->AddChild(feel);
	bck->AddChild(minw);
	bck->AddChild(maxw);
	bck->AddChild(minh);
	bck->AddChild(maxh);
	bck->AddChild(s0);
	bck->AddChild(s1);
}

bool
EditWinWindow::QuitRequested(void)
{
	return true;
}

void
EditWinWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);
}

void
EditWinWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);
}

void
EditWinWindow::MessageReceived(BMessage *msg)
{
	BWindow::MessageReceived(msg);
}

void
edit_win_tags(WrkWindow *edit)
{
	EditWinWindow *wi;

	wi = new EditWinWindow(MyRect(440,454,504,342));

	wi->Show();
}
