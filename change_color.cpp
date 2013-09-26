#include "proto.h"

const uint32 BEAIM_CP_COLOR_CHANGED = 'nee!';
const uint32 BEAIM_NEW_COLOR_PICKED = 'nCLR';
const uint32 BEAIM_COLORVIEW_CLICKED = 'c&CK';

char *array_color[] =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};	

int array_rgbcolor[] = 
{
	(255 << 24) + (255 << 16) + (255 << 8),//white
	(0 << 24) + (0 << 16) + (0 << 8),//black
	(255 << 24) + (0 << 16) + (0 << 8),//red
	(0 << 24) + (0 << 16) + (255 << 8),//blue
	(190 << 24) + (190 << 16) + (190 << 8),//Grey
	(0 << 24) + (255 << 16) + (0 << 8),//Green
	(64 << 24) + (224 << 16) + (208 << 8),//Turqoise
	(0 << 24) + (255 << 16) + (255 << 8),//Cyan
};

class MyColor2 : public BColorControl
{
public: 

		MyColor2(BPoint rct);
		~MyColor2();
};		

MyColor2::MyColor2(BPoint rct):BColorControl(rct,B_CELLS_32x8,7,"",new BMessage(BEAIM_CP_COLOR_CHANGED))
{
}

MyColor2::~MyColor2()
{
}

ColorPickerWindow::ColorPickerWindow( BRect frame,const char* title,int id,BWindow* own,void *pt)
	 				: BWindow(frame,title,B_TITLED_WINDOW,
	 				  B_NOT_ZOOMABLE | B_NOT_RESIZABLE )
{
	int nb = 0,k;

	for (k = msg_white; k <= msg_cyan; k++)
	{
		array_color[nb++] = GetMessage(k);
	}

	BRect aRect( Bounds() );
	genView = new ColorPickerView(this,aRect );
	AddChild( genView );
	
	// other stuff

	SetFeel(B_MODAL_ALL_WINDOW_FEEL );

	Activate();

	ptr = pt;
	owner = own;
	cid = id;
}

//-------------------------------------------------------------------------

ColorPickerWindow::~ColorPickerWindow() {
}

//-------------------------------------------------------------------------

bool ColorPickerWindow::QuitRequested()
{
	//be_app->PostMessage( new BMessage(B_QUIT_REQUESTED) );
	return(true);
}

//-------------------------------------------------------------------------

void ColorPickerWindow::MessageReceived(BMessage* message)
{
	int32 id;

	switch(message->what)
	{
		case	5000:
		{
			message->FindInt32("index",&id);

			rgb_color cl = {0};
			int val = array_rgbcolor[id];

			cl.red 	 = (val >> 24);
			cl.green = (val >> 16);
			cl.blue  = (val >> 8);

			genView->colPick->SetColor(cl);
			genView->picker->SetValue(val);
		}
		break;

		case BEAIM_CP_COLOR_CHANGED:
			genView->colPick->SetColor( genView->picker->ValueAsColor() );
			break;
			
		case B_OK:
			if( owner ) {
				rgb_color color = genView->picker->ValueAsColor();
				BMessage* msg = new BMessage(BEAIM_NEW_COLOR_PICKED);
				msg->AddInt32( "cid",(int32)cid );
				msg->AddPointer("pt",ptr);
				msg->AddData( "color",B_RGB_COLOR_TYPE,&color,sizeof(rgb_color) );
				owner->PostMessage( msg );
			}
			PostMessage( new BMessage(B_QUIT_REQUESTED) );
			break;
	
		default:
			BWindow::MessageReceived(message);
	}
}

//-------------------------------------------------------------------------

// the cancel function
void ColorPickerWindow::DispatchMessage( BMessage* msg,BHandler* handler )
{
	if( msg->what == B_KEY_DOWN )
		if( msg->FindString("bytes")[0] == B_ESCAPE ) {
			PostMessage( new BMessage(B_QUIT_REQUESTED) );
			return;
		}
	
	BWindow::DispatchMessage( msg,handler );
}

//-------------------------------------------------------------------------

void ColorPickerWindow::SetTheColor( rgb_color clr ) {

	genView->picker->SetValue( clr );
	genView->colPick->SetColor( clr );
}

ColorPickerView::ColorPickerView(BWindow *wi,BRect rect )
	   	   : BView(rect,"",B_FOLLOW_ALL_SIDES,B_WILL_DRAW)
{
	BMenu 			*menu;
	BMenuField  	*a;

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	menu = CreateMenu(wi,&array_color[0],5000,-1);

	picker = new MyColor2(BPoint(7,7));
	AddChild( picker );

	// Set up the view rectangles
	BRect textframe = BRect( 7,23,265,136 );
	textframe.right -= B_V_SCROLL_BAR_WIDTH;
	
	// make the colorview
	colPick = new ColorView( BRect( 8,75,38,103 ),-1 );
	AddChild( colPick );

	a = new BMenuField(MyRect(60,75,180,25),"","Color",menu);

	SetDivider(a,16);

	AddChild(a);

	BRect buttonrect = BRect( 195,79,245,0 );
	btnSave = new BButton(buttonrect,"",GetMessage(msg_save),new BMessage(B_OK),B_FOLLOW_BOTTOM | B_FOLLOW_RIGHT,B_NAVIGABLE | B_NAVIGABLE_JUMP | B_WILL_DRAW );

	AddChild( btnSave );

	buttonrect = BRect( 255,79,305,0 );
	btnCancel = new BButton(buttonrect,"",GetMessage(msg_cancel),new BMessage(B_QUIT_REQUESTED),B_FOLLOW_BOTTOM | B_FOLLOW_RIGHT,B_NAVIGABLE | B_WILL_DRAW);
	AddChild( btnCancel );
}
