#include "proto.h"
#include "priwindow.h"
#include "edit_tags.h"

PriWindow::PriWindow(BRect rct):BWindow(rct,"Be Interface Candidate Release 2",B_TITLED_WINDOW,B_NOT_V_RESIZABLE|B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	AddMenu();
	InitGUI();
}

void
PriWindow::InitGUI(void)
{
}

PriWindow::~PriWindow(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
}

void
PriWindow::Minimize(bool mini)
{
	int k;
	BWindow *wi;

	BWindow::Minimize(mini);

	if (mini)
	{
		for (k = 0; k < be_app->CountWindows(); k++)
		{
			if (wi = (BWindow *)be_app->WindowAt(k))
			{
				if (wi != this)
				{
					wi->Minimize(true);
				}
			}
		}
	}
}

void
PriWindow::MessageReceived(BMessage *msg)
{
	WrkWindow *win = (WrkWindow *)DefWin;

	switch(msg->what)
	{
		case	7777:
		{
			BMenuItem *it;
			
			if (msg->FindPointer("source",(void **)&it) == B_OK)
			{
				load_file(it->Label());
			}
		}
		break;

		case	17000:
		{
			WrkWindow *wi;
			
			if (msg->FindPointer("pt",(void **)&wi) == B_OK)
			{
				wi->Show();			
				wi->Activate();			
			}
		}
		break;

		case	MENU_AUTOCREATE:
		{
			prefs.autocreate = !prefs.autocreate;
		}		
		break;

		case	B_ABOUT_REQUESTED:	About();			break;	

		case	MENU_NEW:		new_projet();			break;
		case	MENU_OPEN:		load_files();			break;
		case	MENU_SAVE:		save_files();			break;
		case	MENU_SAVE_AS:	save_as_files();		break;
		case	MENU_CLEAR_RECENT:	clear_recent();		break;

		case	MENU_PROJET:	create_projet_window();	break;
		case	MENU_GADGET:	create_gadget_window();	break;
		case	MENU_GRID:		grid_window();			break;
		case	MENU_SEARCH:	search_window();		break;	
		case	MENU_PLACEMENT:	placement_win();		break;
		case	MENU_PREFSWINDOW: prefs_window();		break;
		case	MENU_TAGEDITOR:	Editor_Win();			break;

		case	MENU_GEN_BASIC:		generate_code();	break;

		case	MENU_UNDELETE:	if (win)	win->UnDelete();	break;
		case	MENU_CUT:		if (win)	win->Cut();			break;
		case	MENU_COPY:		if (win)	win->Copy();		break;
		case	MENU_PASTE:		if (win)	win->Paste();		break;

		case	MENU_ALIGN_LEFT:	if (win)	win->AlignRtn(ALIGN_LEFT);		break;
		case	MENU_ALIGN_RIGHT:	if (win)	win->AlignRtn(ALIGN_RIGHT);		break;
		case	MENU_ALIGN_TOP:		if (win)	win->AlignRtn(ALIGN_TOP);		break;
		case	MENU_ALIGN_BOTTOM:	if (win)	win->AlignRtn(ALIGN_BOTTOM);		break;

		case	MENU_SELECT_ALL:	if (win)	win->SelectAll();				break;
		case	MENU_SELECT_NONE:	if (win)	win->UnSelectAll();				break;
		case	MENU_DELETE_GADGET:	if (win)	win->DeleteGadget();				break;

		case	MENU_CENTER_WIDTH:	if (win)	win->CenterInForm(CENTER_WIDTH);	break;
		case	MENU_CENTER_HEIGHT:	if (win)	win->CenterInForm(CENTER_HEIGHT);break;
		case	MENU_CENTER_ALL:	if (win)	win->CenterInForm(CENTER_ALL);	break;

		case	MENU_UNIFORM_WIDTH:		if (win)	win->UniForm(UNIFORM_WIDTH);	break;
		case	MENU_UNIFORM_HEIGHT:	if (win)	win->UniForm(UNIFORM_HEIGHT);break;
		case	MENU_UNIFORM_ALL:		if (win)	win->UniForm(UNIFORM_ALL);	break;

		case	MENU_SPACE_WIDTH:	if (win)	win->SpaceInForm(SPACING_WIDTH);	break;
		case	MENU_SPACE_HEIGHT:	if (win)	win->SpaceInForm(SPACING_HEIGHT);break;
		case	MENU_SPACE_ALL:		if (win)	win->SpaceInForm(SPACING_ALL);	break;

		case	MENU_ADDFORM:		create_window();	break;
		case	MENU_SHOWALL:		arrange_showall(true);	break;		
		case	MENU_HIDEALL:		arrange_showall(false);	break;		
		case	MENU_ARRANGE_WIN0:	arrange_win0();	break;
		case	MENU_ARRANGE_WIN1:	arrange_win1();	break;
		case	MENU_ARRANGE_WIN2:	arrange_win2();	break;

		case	MENU_HELP:			show_help();	break;
		case	MENU_ASTUCE:		startup_tips();	break;

		default:	BWindow::MessageReceived(msg);		break;
	}
}

void
PriWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);

	prefs.prirect = Frame();
}

void
PriWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	prefs.prirect = Frame();
}

bool
PriWindow::QuitRequested(void)
{
	if (prefs.confquit)
	{
		if	(SysAlert(GetMessage(msg_confirmquit),GetMessage(msg_yesno)))
		{
			return false;
		}	
	}

	if (projet.CountItems())
	{
		if (SysAlert(GetMessage(msg_confirmsave),GetMessage(msg_noyes)))
		{
			save_files();
		}
	}
	
	if (EditorWin)
	{
		EditorWin->Lock();
		EditorWin->Quit();

		EditorWin = NULL;
	}

	save_prefs();

	return true;
}

BMenuItem *
PriWindow::SetItemMenu(int men,int nb,bool enable)
{
	BMenuItem *mn,*it;
	BMenu *xt;

	if	(mn = (BMenuItem *)br->ItemAt(men))
	{
		if (xt = mn->Submenu())
		{
			if (it = xt->FindItem(nb))
			{
				it->SetEnabled(enable);

				return it;
			}
		}
	}	

	return NULL;
}

void
PriWindow::MenusBeginning(void)
{
	WrkWindow *wi = (WrkWindow *)DefWin;
	BMenuItem *mn,*it,*it0,*it1,*it2;
	BMenu *xt;
	bool multi = projet.CountItems() ? true : false;

	SetItemMenu(MN_FICHIER,MENU_SAVE,multi);
	SetItemMenu(MN_FICHIER,MENU_SAVE_AS,multi);
	SetItemMenu(MN_FICHIER,MENU_GEN_BASIC,multi);

	SetItemMenu(MN_EDITION,MENU_UNDELETE,(wi && wi->undelete) ? true : false);
	SetItemMenu(MN_EDITION,MENU_CUT,(wi && wi->sellist.CountItems()) ? true : false);

	SetItemMenu(MN_EDITION,MENU_SELECT_ALL,(multi) ? true : false);
	SetItemMenu(MN_EDITION,MENU_SELECT_NONE,(multi) ? true : false);

	SetItemMenu(MN_EDITION,MENU_DELETE_GADGET,(wi && wi->sellist.CountItems()) ? true : false);
	SetItemMenu(MN_EDITION,MENU_COPY,(wi && wi->sellist.CountItems()) ? true : false);
	SetItemMenu(MN_EDITION,MENU_PASTE,(wi && cliplist.CountItems()) ? true : false);

	if (it = SetItemMenu(MN_EDITION,MENU_ALIGN_LEFT,(wi && wi->sellist.CountItems() > 1) ? true : false))
	{
		if (xt = it->Menu())
		{
			xt->SetEnabled((wi && wi->sellist.CountItems() > 1) ? true : false);		
		}
	}	

	if (it = SetItemMenu(MN_EDITION,MENU_UNIFORM_WIDTH,(wi && wi->sellist.CountItems() > 1) ? true : false))
	{
		if (xt = it->Menu())
		{
			xt->SetEnabled((wi && wi->sellist.CountItems() > 1) ? true : false);		
		}
	}	

	if (it = SetItemMenu(MN_EDITION,MENU_CENTER_WIDTH,(wi) ? true : false))
	{
		if (xt = it->Menu())
		{
			xt->SetEnabled((wi && wi->sellist.CountItems()) ? true : false);		
		}
	}	

	if (it = SetItemMenu(MN_EDITION,MENU_SPACE_WIDTH,(wi) ? true : false))
	{
		if (xt = it->Menu())
		{
			xt->SetEnabled((wi && wi->sellist.CountItems()) ? true : false);		
		}
	}	

	SetItemMenu(MN_OUTILS,MENU_GRID,(wi) ? true : false);
	SetItemMenu(MN_OUTILS,MENU_TAGEDITOR,(wi) ? true : false);
	SetItemMenu(MN_OUTILS,MENU_GADGET,(wi) ? true : false);

	if	(mn = (BMenuItem *)br->ItemAt(MN_FENETRE))
	{
		if (xt = mn->Submenu())
		{
			xt->RemoveItems(0,xt->CountItems());

			xt->AddItem(it = new BMenuItem(GetMessage(msg_addform),new BMessage(MENU_ADDFORM),'F',B_COMMAND_KEY));

			xt->AddSeparatorItem();

			xt->AddItem(it0 = new BMenuItem(GetMessage(msg_showall),new BMessage(MENU_SHOWALL),'0',B_COMMAND_KEY));
			xt->AddItem(it1 = new BMenuItem(GetMessage(msg_hideall),new BMessage(MENU_HIDEALL),'1',B_COMMAND_KEY));

			if (projet.CountItems() < 2)
			{
				it0->SetEnabled(false);
				it1->SetEnabled(false);
			}	

			xt->AddSeparatorItem();

			xt->AddItem(it0 = new BMenuItem(GetMessage(msg_cascade),new BMessage(MENU_ARRANGE_WIN0),'2',B_COMMAND_KEY));
			xt->AddItem(it1 = new BMenuItem(GetMessage(msg_vertical),new BMessage(MENU_ARRANGE_WIN1),'3',B_COMMAND_KEY));
			xt->AddItem(it2 = new BMenuItem(GetMessage(msg_horizontal),new BMessage(MENU_ARRANGE_WIN2),'4',B_COMMAND_KEY));
		
			if (projet.CountItems() < 2)
			{
				it0->SetEnabled(false);
				it1->SetEnabled(false);
				it2->SetEnabled(false);
			}	

			if (!multi)
			{
				it->SetEnabled(false);
			}
				else
			{
				int k;
				WrkWindow *wk;
				BMenuItem *it;

				xt->AddItem(new BSeparatorItem());

				for (k = 0; k < projet.CountItems(); k++)
				{
					if (wk = (WrkWindow *)projet.ItemAt(k))
					{
						BMessage *msg = new BMessage(17000);
						
						msg->AddPointer("pt",wk);

						if (it = new BMenuItem(wk->Title(),msg,0,0))	
						{
							xt->AddItem(it);
						}
					}
				}
			}					
		}
	}	
}

void
PriWindow::AddMenu(void)
{
	BRect rct(0,0,Bounds().right - 1,15);

	BMenu 		*sub,*mn;
	BMenuItem	*it;
	
	br = new BMenuBar(rct,"");

	mn = new BMenu(GetMessage(msg_file));
	mn->AddItem(new BMenuItem(GetMessage(msg_new),new BMessage(MENU_NEW),'N',B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_open),new BMessage(MENU_OPEN),'O',B_COMMAND_KEY));

	sub = new BMenu(GetMessage(msg_openrecent));

	addmenu_recent(sub);

	mn->AddItem(sub);

	mn->AddItem(new BMenuItem("Clear recent",new BMessage(MENU_CLEAR_RECENT),0,0));
	mn->AddItem(new BMenuItem(GetMessage(msg_save),new BMessage(MENU_SAVE),'S',B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_saveas),new BMessage(MENU_SAVE_AS),'S',B_SHIFT_KEY + B_COMMAND_KEY));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem("Generate Code",new BMessage(MENU_GEN_BASIC),'G',B_COMMAND_KEY));
	mn->AddSeparatorItem();

	mn->AddItem(new BMenuItem(GetMessage(msg_information),new BMessage(B_ABOUT_REQUESTED),'?',0));
	mn->AddItem(new BMenuItem(GetMessage(msg_preferences),new BMessage(MENU_PREFSWINDOW)));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem(GetMessage(msg_quit),new BMessage(B_QUIT_REQUESTED)));

	br->AddItem(mn);

	mn = new BMenu(GetMessage(msg_edition));
	mn->AddItem(new BMenuItem(GetMessage(msg_undelete),new BMessage(MENU_UNDELETE),0,B_COMMAND_KEY));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem(GetMessage(msg_cut),new BMessage(MENU_CUT),0,B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_copy),new BMessage(MENU_COPY),0,B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_paste),new BMessage(MENU_PASTE),0,B_COMMAND_KEY));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem(GetMessage(msg_selectall),new BMessage(MENU_SELECT_ALL),0,B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_selectnone),new BMessage(MENU_SELECT_NONE),0,B_COMMAND_KEY));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem(GetMessage(msg_delete),new BMessage(MENU_DELETE_GADGET),0,B_COMMAND_KEY));
	mn->AddSeparatorItem();

	sub = new BMenu(GetMessage(msg_alignment));

	sub->AddItem(new BMenuItem(GetMessage(msg_right),new BMessage(MENU_ALIGN_LEFT),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_left),new BMessage(MENU_ALIGN_RIGHT),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_up),new BMessage(MENU_ALIGN_TOP),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_down),new BMessage(MENU_ALIGN_BOTTOM),0,B_COMMAND_KEY));

	mn->AddItem(sub);

	sub = new BMenu(GetMessage(msg_center));

	sub->AddItem(new BMenuItem(GetMessage(msg_width),new BMessage(MENU_CENTER_WIDTH),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_height),new BMessage(MENU_CENTER_HEIGHT),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_all),new BMessage(MENU_CENTER_ALL),0,B_COMMAND_KEY));

	mn->AddItem(sub);

	sub = new BMenu(GetMessage(msg_uniform));

	sub->AddItem(new BMenuItem(GetMessage(msg_width),new BMessage(MENU_UNIFORM_WIDTH),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_height),new BMessage(MENU_UNIFORM_HEIGHT),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_all),new BMessage(MENU_UNIFORM_ALL),0,B_COMMAND_KEY));

	mn->AddItem(sub);

	sub = new BMenu(GetMessage(msg_spacement));

	sub->AddItem(new BMenuItem(GetMessage(msg_width),new BMessage(MENU_SPACE_WIDTH),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_height),new BMessage(MENU_SPACE_HEIGHT),0,B_COMMAND_KEY));
	sub->AddItem(new BMenuItem(GetMessage(msg_all),new BMessage(MENU_SPACE_ALL),0,B_COMMAND_KEY));

	mn->AddItem(sub);

	br->AddItem(mn);

	mn = new BMenu(GetMessage(msg_tools));
	mn->AddItem(new BMenuItem(GetMessage(msg_list_projet),new BMessage(MENU_PROJET),'0',B_CONTROL_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_list_gadget),new BMessage(MENU_GADGET),'1',B_CONTROL_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_list_placement),new BMessage(MENU_PLACEMENT),'2',B_CONTROL_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_list_search),new BMessage(MENU_SEARCH),'3',B_CONTROL_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_list_proprietes),new BMessage(MENU_TAGEDITOR),'4',B_CONTROL_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_list_grid),new BMessage(MENU_GRID),'5',B_CONTROL_KEY));

	br->AddItem(mn);

	mn = new BMenu(GetMessage(msg_window));
	mn->AddItem(new BMenuItem(GetMessage(msg_addform),new BMessage(MENU_ADDFORM),'F',B_COMMAND_KEY));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem(GetMessage(msg_showall),new BMessage(MENU_SHOWALL),'0',B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_hideall),new BMessage(MENU_HIDEALL),'1',B_COMMAND_KEY));
	mn->AddSeparatorItem();
	mn->AddItem(new BMenuItem(GetMessage(msg_cascade),new BMessage(MENU_ARRANGE_WIN0),'2',B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_vertical),new BMessage(MENU_ARRANGE_WIN1),'3',B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_horizontal),new BMessage(MENU_ARRANGE_WIN2),'4',B_COMMAND_KEY));

	br->AddItem(mn);

	mn = new BMenu(GetMessage(msg_help));

	mn->AddItem(new BMenuItem(GetMessage(msg_html),new BMessage(MENU_HELP),'H',B_COMMAND_KEY));
	mn->AddItem(new BMenuItem(GetMessage(msg_tips),new BMessage(MENU_ASTUCE),'T',B_COMMAND_KEY));

	br->AddItem(mn);

	AddChild(br);
}

extern PriWindow *PriWin;

void
open_priwin(void)
{
	PriWin = new PriWindow(prefs.prirect);

	PriWin->Show();

	if (prefs.prj) 		create_projet_window();
	if (prefs.edit) 	Editor_Win();
	if (prefs.place) 	placement_win();

	if (prefs.showstartup)
	{
		startup_tips();
	}

	if (prefs.lastprj)
	{
		if (!(modifiers() & B_CONTROL_KEY))
		{
			load_file(&prefs.lastprjname[0]);
		}
	}
}
