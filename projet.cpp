#include "proto.h"

BPoint projetpoint(100,100);

class ProjetWindow : public BWindow
{
	public:
		ProjetWindow(BRect win_rect);
		~ProjetWindow();

		virtual void MessageReceived(BMessage* message);
		virtual	bool QuitRequested();
		virtual void FrameMoved(BPoint pt);

	BView			*f0;
	BBox 			*f1;
	BTextControl 	*f2,*f3;
	BMenuField	 	*f4;
	BButton		  	*f5,*f6,*f7;
};

char *bcc_api[] = 
{
	"Bcc API",
#ifndef BIC_BCC
	"Standard API",
#endif
	NULL
};	

ProjetWindow::ProjetWindow(BRect win_rect)
	:BWindow(win_rect,GetMessage(msg_newprojet),B_TITLED_WINDOW_LOOK,B_MODAL_APP_WINDOW_FEEL,
		B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BMenu *menu;

	ProjetType = 0;

	this->AddShortcut('W',0,new BMessage(B_QUIT_REQUESTED));
	
	f0 = new BView(Bounds(),"",B_FOLLOW_ALL,B_WILL_DRAW);

	f0->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	f1 = new BBox(MyRect(5,5,410,80));

	f1->SetLabel(GetMessage(msg_information));

	f2 = CreateString(MyRect(5,15,350,25),GetMessage(msg_nameprj),9000,16);

	f2->TextView()->SetMaxBytes(100);

	f3 = CreateString(MyRect(5,40,350,25),GetMessage(msg_directory),9001,16);

	f3->SetText("/boot/home");

	f3->TextView()->SetMaxBytes(B_PATH_NAME_LENGTH);

	f7 = CreateButton(MyRect(365,44,20,25),"...",9004);

	f7->ResizeTo(40,18);

#ifdef BIC_BCC
	menu = CreateMenu(this,&bcc_api[0],9003,0);
#else
	menu = CreateMenu(this,&bcc_api[0],9003,1);
#endif

	f4 = CreateMx(MyRect(10,90,180,25),GetMessage(msg_typeprj),menu,16);

	f5 = CreateButton(MyRect(240,90,70,25),GetMessage(msg_cancel),B_QUIT_REQUESTED);
	f6 = CreateButton(MyRect(320,90,70,25),GetMessage(msg_ok),9002);

	f1->AddChild(f2);
	f1->AddChild(f3);
	f0->AddChild(f7);

	f0->AddChild(f1);
	f0->AddChild(f4);
	f0->AddChild(f5);
	f0->AddChild(f6);

	AddChild(f0);

	f2->MakeFocus(true);
}

ProjetWindow::~ProjetWindow()
{
}

void
ProjetWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	projetpoint = pt;
}

void
ProjetWindow::MessageReceived(BMessage *msg)
{
	int32 vl;

	switch(msg->what)
	{
		case	9003:
		{
			msg->FindInt32("index",&vl);

			ProjetType = vl;
		}
		break;

		case	9002:
		{
			if (ProjetType == PROJET_BCC)
			{
				if (prefs.type == VIEW_KIND)
				{
					prefs.type = BUTTON_KIND;		
				}
			}	

			strcpy(&ProjetName[0],f2->Text());

			if (strcmp(&ProjetName[0],"") == 0)
			{
				strcpy(&ProjetName[0],GetMessage(msg_untitled));
			}

			sprintf(&ProjetPath[0],"%s/%s",f3->Text(),&ProjetName[0]);

			create_window();		

			if (prefs.gad) 		create_gadget_window();

			PostMessage(B_QUIT_REQUESTED);
		}
		break;
		
		case	9004:
		{
			char *str;

			if (str = OpenFileReq(GetMessage(msg_choosedir),f3->Text(),"d"))
			{
				f3->SetText(str);				
			}
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
ProjetWindow::QuitRequested()
{
	return BWindow::QuitRequested();
}

void
new_projet(void)
{
	int k;
	WrkWindow *wk;
	
	if (projet.CountItems())
	{
		switch(SysAlert(GetMessage(msg_quitprogsave),GetMessage(msg_savecancel)))
		{
			case	0:
			{
				save_files();
			}
			break;
			
			case	2:
			{
				return;
			}
			break;
		}
			
		for (k = 0; k < projet.CountItems(); k++)
		{
			if (wk = (WrkWindow *)projet.ItemAt(k))
			{
				wk->Lock();
				wk->Quit();
			}
		}
		
		projet.MakeEmpty();	
	}	
	
	strcpy(&ProjetPath[0],"");
	strcpy(&ProjetName[0],"");
	strcpy(&ProjetFile[0],"");

	ProjetWindow *win = new ProjetWindow(MyRect(projetpoint.x,projetpoint.y,420,130));
	win->Show();
}	
