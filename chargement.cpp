#include "proto.h"
#include "prjwin.h"

extern BFile *fi;

void
error_loading(int err)
{
	char tmp[512],*buf = &tmp[0];

	sprintf(buf,GetMessage(msg_error_number),err);

	(new BAlert(B_EMPTY_STRING,buf,GetMessage(msg_ok)))->Go();

	exit(0);
}

void
load_menu(BList *ls)
{
	int a,k;
	struct mymenu *tx;
	char tmp[512],*st,*buf = &tmp[0];

	a = read_integer();
	
	for (k = 0; k < a; k++)
	{
		if (tx = MyAlloc(sizeof(struct mymenu)))
		{
			read_string(buf);

			if (st = MyStringStr(buf))
			{
				tx->name = st;	
	
				tx->menu    = read_integer();
				tx->enable  = read_integer();
				tx->checked = read_integer();
				tx->radio   = read_integer();
				tx->car     = read_integer();
				tx->msg     = read_integer();
				tx->level   = read_integer();

				if (!ls->AddItem(tx))
				{
					error_loading(600);
				}
			}	
		}
	}
}

void
load_string(int nb,struct MyGadget *gd)
{
	char tmp[512],*st,*buf = &tmp[0];
	int k;

	for (k = 0; k < nb; k++)
	{
		read_string(buf);

		if (st = MyStringStr(buf))
		{
			if (!gd->name.AddItem(st))
			{
				error_loading(15);
			}
		}
	}
}

struct MyGadget *
load_gadget(WrkWindow *wi)
{
	char tmp[512],*buf = &tmp[0];
	struct MyGadget *gd;
	int a,b,c,d,e;

	a = read_integer();
	b = read_integer();
	c = read_integer();
	d = read_integer();
	e = read_integer();
	
	if (gd = wi->CreateGadget(e,a,b,c,d))
	{
		gd->derived	= read_integer();
		gd->align 	= read_integer();
		gd->alignx 	= read_integer();
		gd->aligny 	= read_integer();
		gd->enable 	= read_integer();
		gd->flag 	= read_integer();
		gd->idcmp 	= read_long();
		gd->view 	= read_integer();
		gd->msg	 	= read_integer();
		gd->focus 	= read_integer();

		read_string(buf);

		strcpy(&gd->Name[0],buf);

		read_string(buf);

		strcpy(&gd->Title[0],buf);

		switch(gd->type)
		{
			case	BUTTON_KIND:			LoadButton(gd);		break;
			case	CHECKBOX_KIND:			LoadCheckBox(gd);	break;
			case	BOX_KIND:				LoadBbox(gd);		break;
			case	COLOR_KIND:				LoadColor(gd);		break;
			case	SLIDER_VERT_KIND:
			case	SLIDER_HORIZ_KIND:		LoadSlider(gd);		break;
			case	INTEGER_KIND:
			case	PASSWORD_KIND:
			case	FLOAT_KIND:
			case	STRING_KIND:			LoadString(gd);		break;
			case	MX_KIND:				LoadMx(gd);			break;
			case	RADIO_KIND:				LoadRadio(gd);		break;
			case	SCROLLER_VERT_KIND:
			case	SCROLLER_HORIZ_KIND:	LoadScroller(gd);	break;
			case	STATUSBAR_KIND:			LoadStatus(gd);		break;
			case	TEXT_KIND:				LoadText(gd);		break;
			case	TAB_KIND:				LoadTab(gd);		break;
			case	NUMBER_KIND:			LoadNumber(gd);		break;
			case	TEDIT_KIND:
			case	TEDIT_HORIZ_KIND:
			case	TEDIT_VERT_KIND:
			case	TEDIT_ALL_KIND:			LoadEdit(gd);		break;
			case	LISTVIEW_KIND:
			case	LISTVIEW_HORIZ_KIND:
			case	LISTVIEW_VERT_KIND:
			case	LISTVIEW_ALL_KIND:		LoadLv(gd);			break;
			case	OUTLISTVIEW_KIND:
			case	OUTLISTVIEW_HORIZ_KIND:
			case	OUTLISTVIEW_VERT_KIND:
			case	OUTLISTVIEW_ALL_KIND:	LoadOLv(gd);		break;
			case	MENU_KIND:				load_menu(&gd->name);	break;
		}

		return gd;	
	}

	return NULL;
}

WrkWindow *
load_window(void)
{
	WrkWindow *wi;
	struct MyGadget *gd;
	int i,a,b,c,d;
	
	a = read_integer();
	b = read_integer();
	c = read_integer();
	d = read_integer();

	if (wi = new WrkWindow(BRect(a,b,a + c,b + d),GetTitle_Form()))
	{
		wi->flag 	= read_integer();
		wi->idcmp   = read_long();
		wi->grid 	= read_integer();
		wi->gridx 	= read_integer();
		wi->gridy 	= read_integer();
		wi->spacex  = read_integer();
		wi->spacey  = read_integer();
		wi->Style   = read_integer();
		wi->feel    = read_integer();
		wi->look    = read_integer();
		wi->wrk     = read_integer();
		wi->typewin = read_integer();
		wi->minw    = read_integer();
		wi->minh    = read_integer();
		wi->maxh    = read_integer();
		wi->maxw    = read_integer();

		read_string(buf);

		strcpy(&wi->Name[0],buf);

		read_string(buf);

		strcpy(&wi->WTitle[0],buf);

		a = read_integer();

		for (i = 0; i < a; i++)
		{
			if (!(gd = load_gadget(wi)))
			{
				error_loading(7);
			}	
		}

		if (!projet.AddItem(wi))
		{
			error_loading(8);	
		}

		ChangeWindowType(wi,wi->typewin);

		wi->UnSelectAll();

		wi->Lock();

		wi->bck->Invalidate();

		wi->Unlock();

		return wi;		
	}

	return NULL;
}

void
set_projet_update(void)
{
	char tmp[B_PATH_NAME_LENGTH],*buf = &tmp[0];

	int nb,e,k;
	WrkWindow	*wk;
	PrjWindow	*prj;
	struct MyGadget *gd;
	char *str = "";

	if (prj = PrjWin)
	{
		prj->Lock();

		int nb_button = 0;
		int nb_tab = 0;
		int nb_checkbox = 0;
		int nb_radio = 0;
		int nb_color = 0;
		int nb_mx = 0;
		int nb_slider = 0;
		int nb_scroller = 0;
		int nb_string = 0;
		int nb_box = 0;
		int nb_text = 0;
		int nb_status = 0;
		int nb_listview = 0;
		int nb_outlistview = 0;
		int nb_tedit = 0;
		int nb_menu = 0;

		for (k = 0; k < projet.CountItems(); k++)
		{
			if (wk = (WrkWindow *)projet.ItemAt(k))
			{
				prj->AddWindow(wk,&wk->Name[0]);

				for (e = 0; e < wk->list.CountItems(); e++)
				{
					if (gd = (struct MyGadget *)wk->list.ItemAt(e))
					{
						switch(gd->type)
						{
							case	MENU_KIND:					++nb_menu;		nb = nb_menu;	str = "Menu";			break;
							case	BUTTON_KIND:				++nb_button;	nb = nb_button;	str = "Button";			break;
							case	MX_KIND:					++nb_mx;		nb = nb_mx;	str = "Mx";					break;
							case	TAB_KIND:					++nb_tab;		nb = nb_tab;	str = "Tab";			break;
							case	CHECKBOX_KIND:				++nb_checkbox;	nb = nb_checkbox;	str = "CheckBox";	break;
							case	RADIO_KIND:					++nb_radio;		nb = nb_radio;	str = "Radio";			break;
							case	COLOR_KIND:
							{
								SetTagsColor(gd);
								++nb_color;		nb = nb_color;	str = "Color";
							}
							break;

							case	SLIDER_HORIZ_KIND:
							case	SLIDER_VERT_KIND:
							{
								SetTagsSlider(gd);
								++nb_slider;	nb = nb_slider;	str = "Slider";
							}
							break;
							case	SCROLLER_HORIZ_KIND:	
							case	SCROLLER_VERT_KIND:			++nb_scroller;	nb = nb_scroller;	str = "Scroller";	break;
							case	STRING_KIND:			
							case	INTEGER_KIND:		
							case	PASSWORD_KIND:				
							case	FLOAT_KIND:					++nb_string;	nb = nb_string;	str = "String";		break;
							case	BOX_KIND:					++nb_box;		nb = nb_box;	str = "Box";		break;
							case	NUMBER_KIND:
							case	TEXT_KIND:					++nb_text;		nb = nb_text;	str = "Text";		break;
							case	STATUSBAR_KIND:				++nb_status;	nb = nb_status;	str = "Status";		break;
							case	LISTVIEW_KIND:
							case	LISTVIEW_HORIZ_KIND:
							case	LISTVIEW_VERT_KIND:
							case	LISTVIEW_ALL_KIND:			++nb_listview;	nb = nb_listview;	str = "ListView";	break;
							case	OUTLISTVIEW_KIND:
							case	OUTLISTVIEW_HORIZ_KIND:
							case	OUTLISTVIEW_VERT_KIND:
							case	OUTLISTVIEW_ALL_KIND:		++nb_outlistview; nb = nb_outlistview;	str = "OutListView";	break;
							case	TEDIT_KIND:
							case	TEDIT_HORIZ_KIND:
							case	TEDIT_VERT_KIND:
							case	TEDIT_ALL_KIND:				++nb_tedit;	nb = nb_tedit;		str = "TEdit";	break;
						}

						sprintf(buf,"%s%d",ToLower(str),nb);	

						prj->AddGadget(wk,gd,buf,gd->type);
					}
				}
			}
		}			

		prj->Unlock();
	}
}

void
load_file(char *name)
{
	char tmp[512],*buf = &tmp[0];
	off_t off;
	int a,b,c,d;
	WrkWindow	*wk;

	if	(fi = new BFile(name,B_READ_ONLY))
	{
		if	(fi->InitCheck() == B_NO_ERROR)
		{
			if (fi->GetSize(&off) == B_OK)
			{
				a = read_integer();
				b = read_integer();
				c = read_integer();
				d = read_integer();

				if (a != MAGIC_HEADER_FORM)
				{
					error_loading(4);
				}

				if (b != off)
				{
					error_loading(5);
				}
			
				ProjetType = c;

				read_string(buf);
	
				strcpy(&ProjetName[0],buf);

				read_string(buf);
	
				strcpy(&ProjetPath[0],buf);

				for (a = 0; a < d; a++)
				{
					if (!(wk = load_window()))
					{
						error_loading(25);
					}	

					wk->ChangeTitleWindow();

					wk->Show();
				}

				set_projet_update();

				strcpy(&ProjetFile[0],name);
			}
		}

		delete fi;
	}
}

