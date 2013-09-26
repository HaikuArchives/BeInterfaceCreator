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

void
EditWinWindow::InitGui(void)
{
	BMenu 		*menu;
	SpinControl *left,*top,*width,*height;
	BMenuField	*type,*wrk,*look,*feel;
	BTextControl *title;
	char *str;

	int k = 0;

	left = new SpinControl(MyRect(10,10,130,18),"","Left",new BMessage(9000),0,100,0,10);

	SetSpinDivider(left,16);

	top = new SpinControl(MyRect(10,35,130,18),"","Top",new BMessage(9001),0,100,0,10);

	SetSpinDivider(top,16);

	width = new SpinControl(MyRect(10,60,130,18),"","Width",new BMessage(9002),0,100,0,10);

	SetSpinDivider(width,16);

	height = new SpinControl(MyRect(10,85,130,18),"","Height",new BMessage(9003),0,100,0,10);

	SetSpinDivider(height,16);

	title = new BTextControl(MyRect(10,110,120,25),"","Title","",new BMessage(9004));

	title->SetDivider(title->StringWidth(title->Label()) + 4);

	menu = CreateMenu(this,&type_win[0],9005);

	SetChoiceInMenu(menu,0,true);

	type = new BMenuField(MyRect(10,135,180,25),"","Type",menu);

	type->SetDivider(type->StringWidth(type->Label()) + 16);

	bck->AddChild(left);
	bck->AddChild(top);
	bck->AddChild(width);
	bck->AddChild(height);
	bck->AddChild(title);
	bck->AddChild(type);
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

	wi = new EditWinWindow(BRect(100,100,400,500));

	wi->Show();
}
