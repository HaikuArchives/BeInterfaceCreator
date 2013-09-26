#include "proto.h"

BList files;

#define BIC_RECENTNAME "/boot/home/config/settings/Bic_Recent"

bool
IsFileExists(char *name)
{
	BEntry *fi;
	
	if (fi = new BEntry(name,false))
	{
		if (fi->InitCheck() == B_OK)
		{
			if (fi->Exists() == true)
			{
				delete fi;
			
				return(true);
			}
		}

		delete fi;
	}		
	
	return(false);
}

void
clear_recent(void)
{
	char *st;
	int k;

	for (k = 0; k < files.CountItems(); k++)
	{
		if (st = files.ItemAt(k))
		{
			free(st);
		}
	}		

	files.MakeEmpty();
}

void
addmenu_recent(BMenu *mn)
{
	int 	k;
	char 	*st,dat[1050],*buf = &dat[0];
	FILE	*fi;
	bool add = false;

	if (fi = fopen(BIC_RECENTNAME,"r"))
	{
		for (k = 0; k < 20; k++)
		{
			if (fgets(buf,1024,fi) != NULL)
			{
				buf[strlen(buf) - 1] = 0;

				if (*buf)
				{		
					if (IsFileExists(buf))
					{
						Store_Path_Files(buf);

						mn->AddItem(new BMenuItem(buf,new BMessage(7777),0,B_COMMAND_KEY));

						add = true;
					}
				}
			}	
		}

		fclose(fi);
	}

	if (!add)
	{
		mn->AddItem(new BMenuItem(GetMessage(msg_empty),new BMessage(7778),0,B_COMMAND_KEY));
	}	
}

bool
is_not_in_list(char *str)
{
	char *st;
	int k;

	for (k = 0; k < files.CountItems(); k++)
	{
		if (st = files.ItemAt(k))
		{
			if (strcmp(st,str) == 0)
			{
				return(true);
			}
		}
	}	

	return(false);
}

void
Store_Path_Files(char *chemin)
{
	char *mn,*st;
	
	if (st = strdup(chemin))
	{
		if (!is_not_in_list(chemin))
		{
			if (files.CountItems() < 20)
			{
				files.AddItem(st);
			}
				else
			{
				if (mn = (char *)files.RemoveItem((int32)0))
				{
					MyFree(mn);

					files.AddItem(st);
				}
			}
		}	
	}
}

void
Save_Path_Files(void)
{
	int 	k;
	char 	*st,dat[1050],*buf = &dat[0];
	BFile	*fi;

	if (fi = new BFile(BIC_RECENTNAME,B_CREATE_FILE|B_WRITE_ONLY|B_ERASE_FILE))
	{
		for (k = 0; k < files.CountItems(); k++)
		{
			if (st = files.ItemAt(k))
			{
				sprintf(buf,"%s\n",st);

				fi->Write(buf,strlen(buf));
			}	
		}

		delete fi;
	}	
}
