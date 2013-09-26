#include "proto.h"

BFile *fi;

extern char bbcbuilder_mime[];

char last_load[B_PATH_NAME_LENGTH] = "/boot/home";

void
load_files(void)
{
	char *tb,*str;
	
	if (str = OpenFileReq(GetMessage(msg_loading),&last_load[0],"a",&bbcbuilder_mime[0]))
	{
		BPath pt(str);
		
		if (tb = pt.Path())
		{
			strcpy(&last_load[0],tb);

			last_load[pt.Leaf() - tb] = 0;
		}
		
		load_file(str);
	}
}

void
save_files(void)
{
	char *str;
	
	if (strcmp(&ProjetFile[0],"") == 0)
	{
		if (str = SaveFileReq(GetMessage(msg_saving),"","/boot/home",NULL))
		{
			save_file(str);

			strcpy(&ProjetFile[0],str);
		}
	}
		else
	{
		save_file(&ProjetFile[0]);	
	}		
}

void
save_as_files(void)
{
	char *str = "";
	
	if (str = SaveFileReq(GetMessage(msg_savingas),"","/boot/home",NULL))
	{
		save_file(str);
	}
}

void
sauve_window(WrkWindow *wi)
{
	struct MyGadget *gd;
	int i;

	BRect rct = wi->Frame();

	write_integer((int)rct.left);
	write_integer((int)rct.top);
	write_integer((int)rct.IntegerWidth());
	write_integer((int)rct.IntegerHeight());

	write_integer(wi->flag);

	write_long(wi->idcmp);

	write_integer(wi->grid);
	write_integer(wi->gridx);
	write_integer(wi->gridy);
	write_integer(wi->spacex);
	write_integer(wi->spacey);
	write_integer(wi->Style);
	write_integer(wi->feel);
	write_integer(wi->look);
	write_integer(wi->wrk);
	write_integer(wi->typewin);
	write_integer(wi->minw);
	write_integer(wi->minh);
	write_integer(wi->maxh);
	write_integer(wi->maxw);

	write_string(&wi->Name[0]);
	write_string(&wi->WTitle[0]);

	write_integer(wi->list.CountItems());

	for (i = 0; i < wi->list.CountItems(); i++)
	{
		if	(gd = wi->list.ItemAt(i))
		{
			sauve_gadget(gd);
		}
	}		
}

void
sauve_textlist(BList *ls)
{
	char *tx;
	int k;
	
	write_integer(ls->CountItems());

	for (k = 0; k < ls->CountItems(); k++)
	{
		if (tx = (char *)ls->ItemAt(k))
		{
			write_string(tx);
		}	
	}
}

void
sauve_menu(BList *ls)
{
	int k;
	struct mymenu *tx;
	
	write_integer(ls->CountItems());

	for (k = 0; k < ls->CountItems(); k++)
	{
		if (tx = (struct mymenu *)ls->ItemAt(k))
		{
			write_string(tx->name);
			
			write_integer(tx->menu);
			write_integer(tx->enable);
			write_integer(tx->checked);
			write_integer(tx->radio);

			write_integer(tx->car);
			write_integer(tx->msg);
			write_integer(tx->level);
		}
	}	
}

void
sauve_gadget(struct MyGadget *gd)
{
	write_integer(gd->x);
	write_integer(gd->y);
	write_integer(gd->wi);
	write_integer(gd->he);
	write_integer(gd->type);


	write_integer(gd->derived);
	write_integer(gd->align);
	write_integer(gd->alignx);
	write_integer(gd->aligny);
	write_integer(gd->enable);

	gd->flag &= ~FLAG_SELECTED;

	write_integer(gd->flag);
	write_long(gd->idcmp);
	write_integer(gd->view);
	write_integer(gd->msg);
	write_integer(gd->focus);

	write_string(&gd->Name[0]);
	write_string(&gd->Title[0]);

	switch(gd->type)
	{
		case	BUTTON_KIND:			SaveButton(gd);		break;
		case	CHECKBOX_KIND:			SaveCheckBox(gd);	break;
		case	BOX_KIND:				SaveBbox(gd);		break;
		case	COLOR_KIND:				SaveColor(gd);		break;
		case	SLIDER_VERT_KIND:
		case	SLIDER_HORIZ_KIND:		SaveSlider(gd);		break;
		case	INTEGER_KIND:
		case	PASSWORD_KIND:
		case	FLOAT_KIND:
		case	STRING_KIND:			SaveString(gd);		break;
		case	MX_KIND:				SaveMx(gd);			break;
		case	RADIO_KIND:				SaveRadio(gd);		break;
		case	SCROLLER_VERT_KIND:
		case	SCROLLER_HORIZ_KIND:	SaveScroller(gd);	break;
		case	STATUSBAR_KIND:			SaveStatus(gd);		break;
		case	TEXT_KIND:				SaveText(gd);		break;
		case	TAB_KIND:				SaveTab(gd);		break;
		case	NUMBER_KIND:			SaveNumber(gd);		break;
		case	TEDIT_KIND:
		case	TEDIT_HORIZ_KIND:
		case	TEDIT_VERT_KIND:
		case	TEDIT_ALL_KIND:			SaveEdit(gd);		break;
		case	LISTVIEW_KIND:
		case	LISTVIEW_HORIZ_KIND:
		case	LISTVIEW_VERT_KIND:
		case	LISTVIEW_ALL_KIND:		SaveLv(gd);			break;
		case	OUTLISTVIEW_KIND:
		case	OUTLISTVIEW_HORIZ_KIND:
		case	OUTLISTVIEW_VERT_KIND:
		case	OUTLISTVIEW_ALL_KIND:	SaveOLv(gd);		break;
	}
	
	switch(gd->type)
	{
		case	MENU_KIND:
		{
			sauve_menu(&gd->name);	
		}
		break;

		case	TAB_KIND:
		case	MX_KIND:
		case	RADIO_KIND:
		{
			sauve_textlist(&gd->name);		
		}
		break;
	}
}

void
save_file(char *txt)
{
	WrkWindow *wi;
	int k;

	busy_cursor(true);

	Store_Path_Files(txt);

	strcpy(&prefs.lastprjname[0],txt);
	
	if	(fi = new BFile(txt,B_CREATE_FILE|B_READ_WRITE|B_ERASE_FILE))
	{
		if	(fi->InitCheck() == B_NO_ERROR)
		{
			write_integer(MAGIC_HEADER_FORM);

			write_integer(0);

			write_integer(ProjetType);

			write_integer(projet.CountItems());

			write_string(&ProjetName[0]);

			write_string(&ProjetPath[0]);

			for (k = 0; k < projet.CountItems(); k++)
			{
				if (wi = (WrkWindow *)projet.ItemAt(k))
				{
					sauve_window(wi);
				}
			}

			k = get_file_len();

			seek_file(SEEK_SET,4);

			write_integer(k);
		}
			
		delete fi;
	}	

	set_mimefile(&prefs.lastprjname[0],"text/plain");

	busy_cursor(false);
}

bool
write_data(void *pt,int nb)
{
	if	(fi->Write(pt,nb) == nb)
	{
		return(true);	
	}

	return(false);
}

bool
read_data(void *pt,int nb)
{
	if	(fi->Read(pt,nb) == nb)
	{
		return(true);	
	}

	return(false);
}

bool
write_double(double val)
{
	if	(fi->Write(&val,sizeof(double)) == sizeof(double))
	{
		return(true);	
	}

	return(false);
}

double
read_double(void)
{
	double ret;

	if	(fi->Read(&ret,sizeof(double)) == sizeof(double))
	{
		return(ret);	
	}

	return false;
}

bool
write_integer(int nb)
{
	if	(fi->Write(&nb,sizeof(int)) == sizeof(int))
	{
		return(true);	
	}

	return(false);
}			

int
read_integer(void)
{
	int ret;

	if	(fi->Read(&ret,sizeof(int)) == sizeof(int))
	{
		return(ret);	
	}

	return(false);
}

bool
write_long(int64 nb)
{
	if	(fi->Write(&nb,sizeof(int64)) == sizeof(int64))
	{
		return(true);	
	}

	return(false);
}			

int64
read_long(void)
{
	int64 ret;

	if	(fi->Read(&ret,sizeof(int64)) == sizeof(int64))
	{
		return(ret);	
	}

	return(false);
}

bool
write_short(short nb)
{
	if	(fi->Write(&nb,sizeof(short)) == sizeof(short))
	{
		return(true);	
	}

	return(false);
}			

short
read_short(void)
{
	short nb;

	if	(fi->Read(&nb,sizeof(short)) == sizeof(short))
	{
		return(nb);	
	}

	return false;
}

bool
write_string(char *str,bool addcr = false)
{
	char *tp;
	int   lg;

	if	(str && str[0])
	{
		lg = strlen(str);

		if	(tp = (char *)MyAlloc(lg + 2))
		{
			lg = sprintf(tp,"%s",str);

			if (write_integer(lg))
			{
				if (fi->Write(tp,lg) == lg)
				{
					MyFree(tp);

					return(true);
				}
			}

			MyFree(tp);
		}			
	}
		else
	{
		if (write_integer(0))
		{
			return(true);
		}
	}		

	return(false);
}

bool
read_string(char *str)
{
	char tmp[257] = {0},*buf = &tmp[0];
	int k;

	if ((k = read_integer()) >= 0)
	{
		str[0] = '\0';

		if (fi->Read(buf,k) == k)
		{
			strcpy(str,buf);			

			return(true);
		}
	}
	
	return(false);
}

bool
seek_file(int type,int nb)
{
	if	(fi->Seek(nb,type) != B_ERROR)
	{
		return(true);
	}
	
	return(false);
}

int
get_file_len(void)
{
	off_t size;

	if	(fi->GetSize(&size) != B_ERROR)
	{
		return(size);
	}
	
	return(false);
}
