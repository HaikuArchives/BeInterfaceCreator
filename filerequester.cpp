#include "proto.h"

class	MyFilter : public BRefFilter
{
public:
	MyFilter(char *str);
	~MyFilter();
	
	virtual bool Filter(const entry_ref *ref,BNode *node,struct stat *st,const char *filetype);

	char *dat;
};	

class	MyFilter2 : public BRefFilter
{
public:
	MyFilter2();
	
	virtual bool Filter(const entry_ref *ref,BNode *node,struct stat *st,const char *filetype);

	char *dat;
};	

MyFilter::MyFilter(char *str)
{
	if (str && *str)
	{
		dat = MyStringStr(str);
	}
}

MyFilter::~MyFilter(void)
{
	if 	(dat)
	{
		free(dat);	
	}
}

bool
MyFilter::Filter(const entry_ref *ref,BNode *node,struct stat *st,const char *filetype)
{
	if	(dat)
	{
		if (S_ISDIR(st->st_mode))
		{
			return true;
		}

		if (S_ISLNK(st->st_mode))
		{
			return true;
		}

		if	(!strstr(filetype,dat))
		{
			return(false);
		}
	}

	return(true);
}

MyFilter2::MyFilter2()
{
	dat = NULL;
}

bool
MyFilter2::Filter(const entry_ref *ref,BNode *node,struct stat *st,const char *filetype)
{
	if (S_ISDIR(st->st_mode))
	{
		return true;
	}

	if (S_ISLNK(st->st_mode))
	{
		return true;
	}

	return(false);
}

extern char buf[];

BRect freq(100,100,480,500);

char
*OpenFileReq(char *title,char *pathname,char *type = "a",char *mime = NULL,int xtype = B_OPEN_PANEL)
{
	BFilePanel 	*fi;
	BWindow		*wi;
	BMessenger	k;
	BButton	*la,*sa,*ca,*za;
	MyFilter *fl = 0;
	uint32 node = 0;

	entry_ref ref,mdir;
	BEntry ent;
	BPath path;
	status_t rt;
	bool off = false;

	if (strcmp(type,"d") == 0) { off = true;	node = B_DIRECTORY_NODE + B_SYMLINK_NODE; }
	if (strcmp(type,"l") == 0) { off = true; node = B_SYMLINK_NODE;}

	char *str = &buf[0];

	if	(fi = new BFilePanel((file_panel_mode)xtype,NULL,NULL,node,false,NULL,NULL,true,true))
	{
		if (wi = fi->Window())
		{
			if (off)
			{
				if	(fl = (MyFilter *)new MyFilter2())
				{
					fi->SetRefFilter(fl);
				}
			}
				else
			{
				if (mime && *mime)
				{
					if	(fl = new MyFilter(mime))
					{
						fi->SetRefFilter(fl);
					}
				}
			}
				
			wi->SetTitle(title);		
		
			fi->SetPanelDirectory(pathname);

			wi->MoveTo(freq.left,freq.top);

 			wi->ResizeTo(freq.Width(),freq.Height());

			fi->Show();					

			fi->SetTarget(k);

			while (fi->IsShowing())
			{
				BWindow *xd;
				int z = 0;
			
				while (xd = be_app->WindowAt(z++))
				{
					if (xd != wi) xd->UpdateIfNeeded();			
				}

				snooze(50000);
			}
		
			ca = (BButton *)wi->FindView("cancel button");
			sa = (BButton *)wi->FindView("default button");
			za = (BButton *)wi->FindView("PoseView");
	
			la = (BButton *)wi->LastMouseMovedView();

			freq = wi->Frame();

			if ((la == sa || la == za) && sa->IsEnabled())
			{
				fi->Rewind();
			
				if ((rt = fi->GetNextSelectedRef(&ref)) == B_NO_ERROR)
				{
					fi->GetPanelDirectory(&mdir);

					if (ent.SetTo(&mdir) == B_NO_ERROR)
					{
						if (ent.GetPath(&path) == B_NO_ERROR)
						{
							sprintf(str,"%s/%s",path.Path(),ref.name);

							if (fl)
							{
								fi->SetRefFilter(NULL);

								delete fl;
							}
							
							delete fi;

							return(str);
						}
					}	
				}
			}

			fi->SetRefFilter(NULL);

			if (fl) delete fl;
		}	

		delete fi;
	}
	
	return(NULL);
}

char
*SaveFileReq(char *title,char *name,char *pathname,char *mime = NULL)
{
	BFilePanel 	*fi;
	BWindow		*wi;
	BButton	*la,*sa,*ca,*za;
	MyFilter *fl = NULL;
	BMessenger	k;

	entry_ref ref,mdir;
	BEntry ent;
	BPath path;
	status_t rt;
	char *str = &buf[0];

	if	(fi = new BFilePanel(B_SAVE_PANEL,&be_app_messenger,NULL,7,false,NULL,NULL,true,true))
	{
		if (wi = fi->Window())
		{
			if (mime && *mime)
			{
				if	(fl = new MyFilter(mime))
				{
					fi->SetRefFilter(fl);
				}
			}

			wi->SetTitle(title);		
		
			fi->SetPanelDirectory(pathname);

			fi->SetSaveText(name);

			fi->Show();					
		
			wi->MoveTo(freq.left,freq.top);

 			wi->ResizeTo(freq.Width(),freq.Height());

			fi->SetTarget(k);

			while (fi->IsShowing())
			{
				BWindow *xd;
				int z = 0;
			
				while (xd = be_app->WindowAt(z++))
				{
					if (xd != wi) xd->UpdateIfNeeded();			
				}

				snooze(50000);
			}
		
			freq = wi->Frame();

			ca = (BButton *)wi->FindView("cancel button");
			sa = (BButton *)wi->FindView("default button");
			za = (BButton *)wi->FindView("PoseView");
	
			la = (BButton *)wi->LastMouseMovedView();

			if ((la == sa || la == za) && sa->IsEnabled())
			{
				fi->GetPanelDirectory(&mdir);

				if (ent.SetTo(&mdir) == B_NO_ERROR)
				{
					if (ent.GetPath(&path) == B_NO_ERROR)
					{
						wi->Lock();

						BView *background = wi->ChildAt(0);
						BTextControl *files = (BTextControl *)background->FindView("text view");

						sprintf(str,"%s/%s",path.Path(),files->Text());

						wi->Unlock();
						
						if (fl)
						{
							fi->SetRefFilter(NULL);

							 delete fl;
						}
						
						delete fi;

						return(str);
					}	
				}
			}

			fi->SetRefFilter(NULL);

			if (fl) delete fl;
		}	

		delete fi;
	}
	
	return("");
}
