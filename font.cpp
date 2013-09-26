#include <InterfaceKit.h>
#include "proto.h"

int kFontSizeSet[] = { 8,9,10,12,14,16,18,20,24,32 };

char *choice_font[] =
{
	"Default",
	"plain font",
	"bold font",
	"fixed font",
	"choose",
	NULL
};	

class FontWindow : public BWindow
{
public:
		FontWindow(int a,int b,int c,char *c,char *d,BRect rct);
		~FontWindow(void);
		
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	FrameMoved(BPoint pt);

		BMenuField	*b0,*b1,*b2;
		BCheckBox 	*b3;
};

int
AddFontMenu(char *str,BMenu* menu, uint32 what,const BHandler* handler)//, const BLooper* looper)
{
	const int32	fontNum = count_font_families();
	font_family	fFamily;
	font_style	fStyle;
	BMenu*		styleMenu;
	BMenuItem*	styleItem;
	int tot = 0,nb = -1;

	char tmp[512];
	
	for(int32 i = 0; i < fontNum; i++)
	{
		get_font_family(i,&fFamily);

		int32 styleNum = count_font_styles(fFamily);
		for(int32 ii = 0; ii < styleNum; ii++)
		{
			get_font_style(fFamily, ii, &fStyle);

			BMessage*	msg = new BMessage(what);

			msg->AddString("f0", fFamily);
			msg->AddString("f1", fStyle);

			sprintf(&tmp[0],"%s, %s",fFamily,fStyle);	

			if (strcmp(str,&tmp[0]) == 0)
			{
				nb = tot;
			}

			tot++;

			styleItem = new BMenuItem(&tmp[0],msg);

			menu->AddItem(styleItem);
		}
	}

	return nb;
}

FontWindow::FontWindow(int a,int b,int c,char *name,char *style,BRect rct):BWindow(rct,GetMessage(msg_font),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect 	rect(Bounds());
	BView	*xt;
	BMenu	*menu;
	int nb;
	bool size = false;
	char tmp[512];

	sprintf(&tmp[0],"%s, %s",name,style);

	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));

	xt = CreateView(rect);

	menu = CreateMenu(this,&choice_font[0],5000,0);

	b0 = new BMenuField(MyRect(10,10,260,25),"","Font",menu);

	SetChoiceInMenu(b0->Menu(),a,true);

	SetDivider(b0,16);

	menu = CreateMenu(this);

	nb = AddFontMenu(&tmp[0],menu,6000,this);	

	b1 = new BMenuField(MyRect(10,35,260,25),"","Style",menu);

	SetChoiceInMenu(b1->Menu(),nb,true);

	SetDivider(b1,16);

	menu = CreateMenu(this);

	for(int32 i = 0; i < 9; i++)
	{
		if (!size && b == kFontSizeSet[i])
		{
			b = i; size = true;
		}

		sprintf(&buf[0],"%d",kFontSizeSet[i]);

		AddItemInMenu(menu,&buf[0],7000);
	}

	b2 = new BMenuField(MyRect(10,60,260,25),"","Size",menu);

	if (size)
	{
		SetChoiceInMenu(b2->Menu(),b,true);
	}
	
	SetDivider(b2,16);

	b3 = CreateCheck(MyRect(10,85,100,25),"Antiliasing",8000,false);

	b3->SetValue(c);

	xt->AddChild(b0);
	xt->AddChild(b1);
	xt->AddChild(b2);
	xt->AddChild(b3);

	AddChild(xt);
}

FontWindow::~FontWindow(void)
{
}

void
FontWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);
}

void
SetFontType(int type,int id)
{
	struct MyGadget *gad;
	WrkWindow *wi;

	if (wi = DefWin)
	{
		switch(type)
		{
			case	0:
			{
				if (gad = DefWin->sellist.ItemAt(0))
				{
					gad->FontType = id;
				}
					else
				{
					wi->FontType = id;
				}
			}
			break;

			case	1:
			{
				if (gad = DefWin->sellist.ItemAt(0))
				{
					gad->FontSize = id;
				}
					else
				{
					wi->FontSize = id;
				}
			}
			break;

			case	2:
			{
				if (gad = DefWin->sellist.ItemAt(0))
				{
					gad->FontAntiliasing = id;
				}
					else
				{
					wi->FontAntiliasing = id;
				}
			}
			break;
		}
	}
}
	
void
FontWindow::MessageReceived(BMessage *msg)
{
	int32 vl,id;

	msg->FindInt32("be:value",&vl);
	msg->FindInt32("index",&id);

	switch(msg->what)
	{
		case	5000:
		{
			SetFontType(0,id);
		}
		break;

		case	6000:
		{
			struct MyGadget *gad;
			WrkWindow *wi;
			const char *str0,*str1;

			if (wi = DefWin)
			{
				if(msg->FindString("f0",&str0) == B_OK)
				{
					if(msg->FindString("f1",&str1) == B_OK)
					{
						if (gad = DefWin->sellist.ItemAt(0))
						{
							strcpy(&gad->FontName[0],str0);
							strcpy(&gad->FontStyle[0],str1);
						}
							else
						{
							strcpy(&wi->FontName[0],str0);
							strcpy(&wi->FontStyle[0],str1);
						}
					}
				}
			}				
		}
		break;

		case	7000:
		{
			SetFontType(1,kFontSizeSet[id]);
		}
		break;

		case	8000:
		{
			SetFontType(2,id);
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
FontWindow::QuitRequested(void)
{
	return true;
}

void
font_window(int a,int b,int c,char *name,char *style)
{
	FontWindow *wi;

	wi = new FontWindow(a,b,c,name,style,MyRect(200,200,400,150));

	wi->Show();
}
