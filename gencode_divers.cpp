#include "proto.h"

BPath *
create_path(char *path)
{
	BPath *pt;
	
	if	((pt = new BPath(path)))
	{
		if	(pt->InitCheck() == B_NO_ERROR)	
		{
			return(pt);
		}
		
		delete pt;
	}

	return(NULL);
}			

BDirectory *
create_mydir(char *str)
{
	BDirectory *dir;
	
	if ((dir = new BDirectory(str)))
	{
		if (dir->InitCheck() == B_OK)
		{
			return(dir);
		}

		delete dir;
	}	
			
	return(NULL);	
}

void
delete_directory_path(char *path,bool recur)
{
	BDirectory 	*dir;
	BPath		*pat,pt;
	BEntry		*ent;

	if ((pat = create_path(path)))
	{
		if	((dir = create_mydir((char *)pat->Path())))
		{
			if	(dir->Rewind() == B_OK)
			{
				if	((ent = new BEntry()))
				{
					while (dir->GetNextEntry(ent,false) == B_NO_ERROR)
					{
						if (ent->GetPath(&pt) == B_NO_ERROR)
						{
							if (recur)
							{
								if	(ent->IsDirectory())
								{
									delete_directory_path((char *)pt.Path(),recur);
								}
							}
						}

						ent->Remove();
					}

					delete ent;
				}
			}

			delete dir;
		}

		delete pat;
	}
}

void
RemoveDir(char *app)
{
	delete_directory_path(app,true);
}

