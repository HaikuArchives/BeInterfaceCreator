#include "proto.h"
#include "placement.h"
#include "prjwin.h"

extern void Update_SearchWindow(struct MyGadget *gad);

void
WrkWindow::Cut(void)
{
	int nb,k;
	struct MyGadget *gd;
	BList	*xt;
	BView	*vx;

	if (nb = sellist.CountItems())
	{
		Lock();

		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				gd->flag &= ~FLAG_SELECTED;

				if (vx = (BView *)gd->pt)
				{
					RemoveChild(vx);
				}

				list.RemoveItem(gd);

				if (PrjWin)
				{
					PrjWin->RemoveGadget(this,gd);
				}

				cliplist.AddItem(gd);
			}
		}

		sellist.MakeEmpty();

		Unlock();
	}
}

void
WrkWindow::Copy(void)
{
	int nb,k;
	struct MyGadget *fr,*gd;
	BList	*xt;
	BView	*vx;

	if (nb = sellist.CountItems())
	{
		Lock();

		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				if (fr = (struct MyGadget *)CreateGadget(gd->type,gd->x,gd->y,gd->wi,gd->he,false,false,false,&gd->Title[0]))
				{
					gd->flag &= ~FLAG_SELECTED;

					cliplist.AddItem(fr);
				}
			}
		}

		sellist.MakeEmpty();

		Unlock();
	}
}

void
WrkWindow::Paste(void)
{
	PrjWindow *wi;
	struct MyGadget *gd;
	int	tot,k;

	if (tot = cliplist.CountItems())
	{
		for (k = 0; k < tot; k++)
		{
			if	(gd = cliplist.ItemAt(k))
			{
				if (!list.HasItem(gd))
				{
					gd->flag &= ~FLAG_SELECTED;

					list.AddItem(gd);

					AddChild(gd->pt);

					if (wi = PrjWin)
					{
						wi->AddGadget(this,gd,&gd->Title[0],gd->type);
					}
				}
			}
		}

		cliplist.MakeEmpty();

		Lock();

		bck->Invalidate();

		Unlock();
	}
}

void
WrkWindow::AddGadget(struct MyGadget *gd,bool draw = true,bool update = true)
{
	PrjWindow *wi;

	if (!(gd->flag & FLAG_SELECTED))
	{
		gd->flag |= FLAG_SELECTED;
			
		sellist.AddItem(gd);

		if ((wi = PrjWin) && update)
		{
			wi->ChooseGadget(gd);
		}

		if (draw)
		{
			if (gd->pt && gd->pt->ChildAt(0))
			{
				gd->pt->ChildAt(0)->Invalidate();
			}
		}

		PostInfo();
	}
}

void
WrkWindow::SelectPrevGadget(void)
{
	int t,k;
	struct MyGadget *gd;

	if (list.CountItems())
	{
		if	((k = CountSelected(0,0)) < 2)
		{
			if (!k)
			{
				if (gd = list.ItemAt(0))
				{
					UnSelectAll();

					AddGadget(gd);
				}	
			}
				else
			{
				if (gd = sellist.ItemAt(0))
				{
					t = list.IndexOf(gd);
					
					if (gd = list.ItemAt(t - 1))
					{
						UnSelectAll();

						AddGadget(gd);
					}
						else
					{
						if (gd = list.LastItem())
						{
							UnSelectAll();

							AddGadget(gd);
						}	
					}	
				}
			}			
		}
	}

	PostInfo();
}

void
WrkWindow::SelectNextGadget(void)
{
	int t,k;
	struct MyGadget *gd;

	if (list.CountItems())
	{
		if	((k = CountSelected(0,0)) < 2)
		{
			if (!k)
			{
				if (gd = list.FirstItem())
				{
					UnSelectAll();

					AddGadget(gd);
				}	
			}
				else
			{
				if (gd = sellist.FirstItem())
				{
					t = list.IndexOf(gd);
					
					if (gd = list.ItemAt(t + 1))
					{
						UnSelectAll();

						AddGadget(gd);
					}
						else
					{
						if (gd = list.FirstItem())
						{
							UnSelectAll();

							AddGadget(gd);
						}	
					}	
				}
			}			
		}
	}

	PostInfo();
}

struct MyGadget *
WrkWindow::CheckPosition(int x,int y,bool add = true)
{
	int z,k;
	struct MyGadget *dp,*gd,*first = NULL,*enf = NULL;
	GadView	*xt;

	for (k = 0; k < list.CountItems(); k++)
	{
		if	(gd = list.ItemAt(k))
		{
			if (x >= gd->x && y >= gd->y && x <= gd->x + gd->wi && y <= gd->y + gd->he)
			{
				if (gd->pt->ChildAt(0))
				{
					for (z = 0; z < list.CountItems(); z++)
					{
						if	(dp = list.ItemAt(z))
						{
							if (dp->pt->Parent() == gd->pt->ChildAt(0))
							{
								if (xt = (GadView *)dp->pt)
								{
									if (x >= xt->gd->x && y >= xt->gd->y && x <= xt->gd->x + xt->gd->wi && y <= xt->gd->y + xt->gd->he)
									{
										first = dp;
	
										if (add) AddGadget(dp);

										goto end;
									}								
								}
							}
						}
					}

					first = gd;
	
					if (add) AddGadget(gd);
				}
					else
				{
					first = gd;
				}
	
				if (add) AddGadget(gd);
			}
		}
	}
end:
	if (!first && enf) first = enf;

	return(first);
}

extern int mods;

void
WrkWindow::SelectAll(void)
{
	int k;
	struct MyGadget *gd;

	Lock();

	for (k = 0; k < list.CountItems(); k++)
	{
		mods = -1;

		if	(gd = list.ItemAt(k))
		{
			AddGadget(gd);
		}
	}

	PostInfo();

	Unlock();
}

void
WrkWindow::InverseSelection(void)
{
	int k;
	struct MyGadget *gd;
	PrjWindow *wi;
	BView	*vx;

	Lock();

	for (k = 0; k < list.CountItems(); k++)
	{
		mods = -1;

		if	(gd = list.ItemAt(k))
		{
			if (gd->flag & FLAG_SELECTED)
			{
				gd->flag &= ~FLAG_SELECTED;

				sellist.RemoveItem(gd);

				if (vx = (BView *)gd->pt)
				{
					vx->Invalidate();
				}
			}
				else
			{
				AddGadget(gd);
			}	
		}
	}

	if (wi = PrjWin)
	{
		wi->ChooseGadget(NULL);
	}

	PostInfo();

	Unlock();
}

void
WrkWindow::UnSelectAll(bool update = true)
{
	int k;
	PrjWindow *wi;
	struct MyGadget *gd;
	BList	*xt;
	BView	*vx;

	Lock();

	for (k = 0; k < sellist.CountItems(); k++)
	{
		if	(gd = sellist.ItemAt(k))
		{
			if (gd->flag & FLAG_SELECTED)
			{
				gd->flag &= ~FLAG_SELECTED;

				if (vx = (BView *)gd->pt)
				{
					vx->Invalidate();
				}
			}
		}
	}
	
	if ((wi = PrjWin) && update)
	{
		wi->ChooseGadget(NULL);
	}

	sellist.MakeEmpty();

	PostInfo();

	Unlock();
}

void
WrkWindow::MoveAll(int x,int y)
{
	int z,k;
	struct MyGadget *gd;
	BList	*xt;
	BView	*tp,*vx;
	GadView	*gad;

	if (x != 0 || y != 0)
	{
		Lock();

		if (sellist.CountItems())
		{
			for (k = 0; k < sellist.CountItems(); k++)
			{
				if	(gd = sellist.ItemAt(k))
				{
					if (gd->flag & FLAG_SELECTED)
					{
						if (vx = (BView *)gd->pt)
						{
							if (!(gd->flag & FLAG_LOCKX))
							{
								vx->MoveBy(x,0);
					
								gd->x += x;
							}

							if (!(gd->flag & FLAG_LOCKY))
							{
								vx->MoveBy(0,y);
					
								gd->y += y;
							}

							for (z = 0; z < vx->ChildAt(0)->CountChildren(); z++)
							{
								if (gad = (GadView *)vx->ChildAt(0)->ChildAt(z))
								{
									if (is_instance_of(gad,GadView))
									{
										if (!(gd->flag & FLAG_LOCKX))
										{
											gad->gd->x += x;
										}

										if (!(gd->flag & FLAG_LOCKY))
										{
											gad->gd->y += y;
										}
									}
								}
							}	
						}
					}
				}
			}
		}
			else
		{
			if (!(flag & FLAG_LOCKX))
			{
				MoveBy(x,0);
			}

			if (!(flag & FLAG_LOCKY))
			{
				MoveBy(0,y);
			}
		}	
			
		Unlock();
	}

	PostInfo(true);

	if (gd)
	{
		change_infowin_number(but_Left,gd->x);
		change_infowin_number(but_Top,gd->y);
	}
}

void
WrkWindow::ResizeGadget(struct MyGadget *gd,int wi,int he)
{
	BView	*vx;
	bool  refresh = false;

	if (wi > 10 && he > 10)
	{
		Lock();

		if ((gd->flag & FLAG_SELECTED) && gd->type != MENU_KIND)
		{
			if (vx = (BView *)gd->pt)
			{
				if (gd->wi != wi)
				{
					if (!(gd->flag & FLAG_LOCKW))
					{
						vx->ResizeTo(wi,gd->he);
		
						vx->ChildAt(0)->ResizeTo(wi,gd->he);

						gd->wi = wi;

						refresh = true;
					}
				}

				if (gd->he != he)
				{
					if (!(gd->flag & FLAG_LOCKH))
					{
						vx->ResizeTo(gd->wi,he);

						vx->ChildAt(0)->ResizeTo(gd->wi,he);
					
						gd->he = he;

						refresh = true;
					}
				}
				
				if (refresh)
				{
					vx->Invalidate();
				}
			}
		}

		Unlock();
	}
}

void
WrkWindow::MoveGadget(struct MyGadget *gd,int x,int y)
{
	BView	*vx;
	Lock();

	if (gd->flag & FLAG_SELECTED)
	{
		if (vx = (BView *)gd->pt)
		{
			if (gd->x != x)
			{
				if (!(gd->flag & FLAG_LOCKX))
				{
					vx->MoveTo(x,gd->y);
					
					gd->x = x;
				}
			}
						
			if (gd->y != y)
			{
				if (!(gd->flag & FLAG_LOCKY))
				{
					vx->MoveTo(gd->x,y);
					
					gd->y = y;
				}
			}
		}
	}

	Unlock();
}

void
WrkWindow::MoveAllPosition(int x,int y)
{
	int k;
	struct MyGadget *gd = 0;
	BList	*xt;
	BView	*vx;

	if (x != 0 || y != 0)
	{
		Lock();

		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				if (gd->flag & FLAG_SELECTED)
				{
					if (vx = (BView *)gd->pt)
					{
						if (gd->x != x)
						{
							if (!(gd->flag & FLAG_LOCKX))
							{
								vx->MoveTo(x,gd->y);
					
								gd->x = x;
							}
						}
						
						if (gd->y != y)
						{
							if (!(gd->flag & FLAG_LOCKY))
							{
								vx->MoveTo(gd->x,y);
					
								gd->y = y;
							}
						}
					}
				}
			}
		}
		
		Unlock();
	}

	PostInfo(true);

	if (gd)
	{
		change_infowin_number(but_Left,gd->x);
		change_infowin_number(but_Top,gd->y);
	}
}

extern bool drag,moved;

void
WrkWindow::ChangeSize(int flag,int wi,int he)
{
	int k;
	struct MyGadget *gd;
	BList	*xt;
	BView	*vx;
	bool refresh = false;

	Lock();

	for (k = 0; k < sellist.CountItems(); k++)
	{
		if	(gd = sellist.ItemAt(k))
		{
			if (gd->flag & FLAG_SELECTED)
			{
				if (vx = (BView *)gd->pt)
				{
					if (!(gd->flag & FLAG_LOCKW))
					{
						if (flag & CHANGE_WIDTH)
						{
							vx->ResizeTo(wi,vx->Frame().Height());

							vx->ChildAt(0)->ResizeTo(wi,vx->Frame().Height());
					
							gd->wi = wi;

							refresh = true;
						}
					}

					if (!(gd->flag & FLAG_LOCKH))
					{
						if (flag & CHANGE_HEIGHT)
						{
							vx->ResizeTo(vx->Frame().Width(),he);

							vx->ChildAt(0)->ResizeTo(vx->Frame().Width(),he);
					
							gd->he = he;

							refresh = true;
						}
					}
					
					if (refresh)
					{
						vx->Invalidate();
					}
				}
			}
		}
	}
	
	PostInfo(true);

	change_infowin_number(but_Width,wi);
	change_infowin_number(but_Height,he);

	Unlock();
}

void
WrkWindow::ResizeGadget(int wi,int he)
{
	int k;
	struct MyGadget *gd;
	BList	*xt;
	BView	*vx;
	bool  refresh = false;

	if (wi > 10 && he > 10)
	{
		Lock();

		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				if ((gd->flag & FLAG_SELECTED) && gd->type != MENU_KIND)
				{
					if (vx = (BView *)gd->pt)
					{
						if (!(gd->flag & FLAG_LOCKW))
						{
							vx->ResizeTo(wi,gd->he);
					
							vx->ChildAt(0)->ResizeTo(wi,gd->he);

							gd->wi = wi;

							refresh = true;
						}

						if (!(gd->flag & FLAG_LOCKH))
						{
							vx->ResizeTo(gd->wi,he);

							vx->ChildAt(0)->ResizeTo(gd->wi,he);
					
							gd->he = he;

							refresh = true;
						}

						if (refresh)
						{
							vx->Invalidate();
						}
					}
				}
			}
		}
	
		PostInfo(true);

		change_infowin_number(but_Width,wi);
		change_infowin_number(but_Height,he);

		drag = moved = false;

		Unlock();
	}
}

bool
WrkWindow::DeleteGadget(void)
{
	int nb,k;
	struct MyGadget *gd;
	BList	*xt;
	BView	*vx;

	if (nb = sellist.CountItems())
	{
		if (prefs.confdel)
		{
			char	tmp[100],*str = &tmp[0];
		
			sprintf(str,"Confirm delete %s %d gadget%c ?",(nb > 1) ? "des" : "du",nb,(nb > 1) ? 's' : 0);
	
			if	(SysAlert(str,"Yes|No"))
			{
				return false;
			}	
		}
		
		Lock();

		undelete = true;

		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				gd->flag &= ~FLAG_SELECTED;

				if (vx = (BView *)gd->pt)
				{
					if (!vx->Parent())
					{
						RemoveChild(vx);
					}
						else
					{
						vx->Parent()->RemoveChild(vx);
					}	
				}

				if (PrjWin)
				{
					PrjWin->RemoveGadget(this,gd);
				}

				list.RemoveItem(gd);

				dellist.AddItem(gd);

				Update_SearchWindow(gd);
			}
		}

		Activate();

		sellist.MakeEmpty();

		Unlock();
	}

	return true;
}

void
WrkWindow::UnDelete(void)
{
	PrjWindow *wi;
	struct MyGadget *gd;
	int	tot,k;

	if (tot = dellist.CountItems())
	{
		for (k = 0; k < tot; k++)
		{
			if	(gd = dellist.ItemAt(k))
			{
				gd->flag &= ~FLAG_SELECTED;

				list.AddItem(gd);

				AddChild(gd->pt);

				if (wi = PrjWin)
				{
					wi->AddGadget(this,gd,&gd->Title[0],gd->type);
				}
			}
		}

		undelete = false;
	
		dellist.MakeEmpty();
		sellist.MakeEmpty();

		Lock();

		bck->Invalidate();

		Unlock();
	}
}

void
WrkWindow::UniForm(int type)
{
	struct MyGadget *gd;
	int	wi,nb,he,k,val;
	
	if	((nb = sellist.CountItems()) > 1)
	{
		Lock();

		DisableUpdates();

		gd = (struct MyGadget *)sellist.ItemAt(0);
			
		wi = gd->wi;
		he = gd->he;

		for (k = 0; k < nb; k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				switch(type)
				{
					case	UNIFORM_WIDTH:
					{
						gd->wi = wi;			
						he = gd->he;
					}
					break;

					case	UNIFORM_HEIGHT:
					{
						gd->he = he;			
						wi = gd->wi;
					}
					break;

					case	UNIFORM_ALL:
					{
						gd->he = he;			
						gd->wi = wi;			
					}
					break;
				}

				gd->pt->ResizeTo(gd->wi,gd->he);
			}
		}

		EnableUpdates();

		UpdateIfNeeded();

		Unlock();
	}
}

void
WrkWindow::SpaceInForm(int type)
{
	struct MyGadget *top,*gd;
	int	nb,deb,k;
	int spacex = 10,spacey = 10;

	if	((nb = sellist.CountItems()) > 1)
	{
		Lock();

		DisableUpdates();

		top = sellist.ItemAt(0);

		for (k = 1; k < nb; k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				switch(type)
				{
					case	SPACING_WIDTH:
					{
						gd->x = top->x + top->wi + spacex - 1;
					}
					break;

					case	SPACING_HEIGHT:
					{
						gd->y = top->y + top->he + spacey - 1;
					}
					break;

					case	SPACING_ALL:
					{
						gd->x = top->x + top->wi + spacex - 1;
						gd->y = top->y + top->he + spacey - 1;
					}
					break;
				}
										
				gd->pt->MoveTo(gd->x,gd->y);

				top = gd;
			}
		}							

		EnableUpdates();

		UpdateIfNeeded();

		Unlock();
	}
}

void
WrkWindow::CenterInForm(int type)
{
	struct MyGadget *gd;
	int	nb,wi,he,k;

	if	(nb = sellist.CountItems())
	{
		Lock();

		DisableUpdates();

		wi = this->Bounds().IntegerWidth();
		he = this->Bounds().IntegerHeight();

		for (k = 0; k < nb; k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				switch(type)
				{
					case	CENTER_WIDTH:
					{
						gd->x = (wi - gd->wi) / 2;
					}
					break;

					case	CENTER_HEIGHT:
					{
						gd->y = (he - gd->he) / 2;			
					}
						break;

					case	CENTER_ALL:
					{
						gd->x = (wi - gd->wi) / 2;
						gd->y = (he - gd->he) / 2;			
					}
					break;
				}

				gd->pt->MoveTo(gd->x,gd->y);
			}
		}							

		EnableUpdates();

		UpdateIfNeeded();

		Unlock();
	}
}

void
WrkWindow::ChangeTitleWindow(void)
{
	sprintf(&buf[0],"%s - %s [%s]",&ProjetName[0],&Name[0],&WTitle[0]);
	
	SetTitle(&buf[0]);
}	

void
WrkWindow::AlignRtn(int alig)
{
	int	k,val;
	struct MyGadget *gd;
	
	if	((k = CountSelected(alig,&val)) > 1)
	{
		Lock();

		DisableUpdates();

		for (k = 0; k < sellist.CountItems(); k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				switch(alig)
				{
					case	ALIGN_LEFT:
					{
						gd->x = val - gd->wi;			
					}
					break;

					case	ALIGN_RIGHT:
					{
						gd->x = val;			
					}
					break;

					case	ALIGN_TOP:
					{
						gd->y = val;			
					}
					break;

					case	ALIGN_BOTTOM:
					{
						gd->y = val - gd->he;					
					}
				}				

				gd->pt->MoveTo(gd->x,gd->y);
			}
		}

		EnableUpdates();

		UpdateIfNeeded();

		Unlock();
	}
}

int
WrkWindow::CountSelected(int alig,int *val)
{
	int ret,nb = 0,k;
	struct MyGadget *gd;
	bool	start = false;

	if	(gd = sellist.ItemAt(0))
	{
		switch(alig)
		{
			case	ALIGN_LEFT:
			{
				ret = gd->x + gd->wi;
			}
			break;

			case	ALIGN_RIGHT:
			{
				ret = gd->x;
			}
			break;

			case	ALIGN_TOP:
			{
				ret = gd->y;
			}
			break;

			case	ALIGN_BOTTOM:
			{
				ret = gd->y + gd->he;
			}
			break;
		}
	}

	if (val)
	{
		*val = ret;
	}
	
	return(sellist.CountItems());
}

char *
GetTitle_Form(void)
{
	sprintf(&buf[0],"%s - form%d",&ProjetName[0],projet.CountItems() + 1);
	
	return(&buf[0]);
}	

void
create_window(void)
{
	WrkWindow *wi;

	if (wi = new WrkWindow(prefs.workrect,GetTitle_Form()))
	{
		if (!projet.AddItem(wi))
		{
			error_loading(144);
		}
	
		if (!DefWin)
		{
			DefWin = wi;
		}	

		wi->ChangeTitleWindow();

		wi->Show();

		if (PrjWin)
		{
			PrjWin->AddWindow(wi,&wi->Name[0]);
		}
	}
}
