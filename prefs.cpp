#include "proto.h"

void
load_prefs(void)
{
	BDirectory 	dir;
	BEntry		entry;
	BPath		path;
	BFile		*fi;
	off_t		size;
	char		*dat;
	bool		ok = false;
	int			nb;

	find_directory(B_USER_SETTINGS_DIRECTORY, &path, true);

	dir.SetTo(path.Path());

	if (dir.FindEntry(PREFS_FILE,&entry) == B_NO_ERROR)
	{
		if (fi = new BFile(&entry,O_RDWR))
		{
			if (fi->InitCheck() == B_NO_ERROR)
			{
				if (fi->GetSize(&size) == B_OK)
				{
					nb = (int)size;

					if (nb == sizeof(struct myprefs))
					{
						if (fi->Read(&prefs,sizeof(struct myprefs)) == sizeof(struct myprefs))
						{
							ok = true;
						}
					}	
				}
			}

			delete fi;
		}
	}

	if (!ok)
	{
		default_prefs();
	}
}

void
default_prefs(void)
{
	register struct myprefs *pf = &prefs;

	memset(pf,0,sizeof(struct myprefs));

	pf->prirect.Set(200,200,500,15);
	pf->gadrect.Set(50,300,400,400);
	pf->projrect.Set(75,150,175,450);
	pf->workrect.Set(300,300,700,700);
	pf->placerect.Set(200,200,200 + 100,200 + 200);
	pf->searchrect.Set(200,200,200 + 320,200 + 90);
	pf->editrect.Set(300,300,700,700);
	pf->tipsrect = MyRect(-1000,-1000,425,135);
	pf->editorwinrect.Set(440,454,440 + 504,454 + 400);

	strcpy(&pf->appname[0],"BeApp");

	pf->grillepoint.x = 200; 
	pf->grillepoint.y = 200; 

	pf->autocreate = true;

	pf->code_default_void = true;
	pf->code_default_routine = true;
	
	pf->prefspoint.x = 300; 
	pf->prefspoint.y = 200; 

	pf->automin = 5;

	pf->showstartup = true;

	pf->type = BUTTON_KIND;
}

void
save_prefs(void)
{
	BDirectory 	dir;
	BEntry		entry;
	BPath		path;
	BFile		*fi;
	bool ok = false;
	char *str;

	find_directory(B_USER_SETTINGS_DIRECTORY, &path, true);

	path.Append(PREFS_FILE);

	if (fi = new BFile(path.Path(),B_CREATE_FILE|B_ERASE_FILE|B_WRITE_ONLY))
	{
		if (fi->InitCheck() == B_NO_ERROR)
		{
			prefs.gad    = (GadWin) 	? true : false;
			prefs.prj    = (PrjWin) 	? true : false;
			prefs.edit   = (EditorWin) 	? true : false;
			prefs.place  = (PlaceWin) 	? true : false;

			if (fi->Write(&prefs,sizeof(struct myprefs)) != sizeof(struct myprefs))
			{
				(new BAlert(B_EMPTY_STRING,GetMessage(msg_errorwriting),GetMessage(msg_ok)))->Go();
			}			
		}

		delete fi;
	}
}
