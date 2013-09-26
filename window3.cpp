#include "proto.h"
#include "placement.h"
#include "prjwin.h"

void
WrkWindow::ChangeFont(int font)
{
	struct 	MyGadget *gd;
	int		nb,k;
	
	if	((nb = sellist.CountItems()) > 1)
	{
		for (k = 0; k < nb; k++)
		{
			if	(gd = sellist.ItemAt(k))
			{


			}
		}
	}
}

void
WrkWindow::AllDerived(bool deriv)
{
	struct 	MyGadget *gd;
	int		nb,k;
	
	if	((nb = sellist.CountItems()) > 1)
	{
		for (k = 0; k < nb; k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				gd->derived = deriv;
			}
		}
	}
}

void
WrkWindow::SetGrid(bool setgrid)
{
	grid = setgrid;

	bck->Invalidate();
}

void
WrkWindow::LockGadget(int nbx,bool lock)
{
	struct 	MyGadget *gd;
	int		nb,k;
	
	if	((nb = sellist.CountItems()) > 1)
	{
		for (k = 0; k < nb; k++)
		{
			if	(gd = sellist.ItemAt(k))
			{
				switch(nbx)
				{
					case	0:
					{
						if (lock)
						{
							gd->flag |= FLAG_LOCKX;
						}
							else
						{
							gd->flag &= ~FLAG_LOCKX;
						}	
					}
					break;

					case	1:
					{
						if (lock)
						{
							gd->flag |= FLAG_LOCKY;
						}
							else
						{
							gd->flag &= ~FLAG_LOCKY;
						}	
					}
					break;

					case	2:
					{
						if (lock)
						{
							gd->flag |= FLAG_LOCKW;
						}
							else
						{
							gd->flag &= ~FLAG_LOCKW;
						}	
					}
					break;

					case	3:
					{
						if (lock)
						{
							gd->flag |= FLAG_LOCKH;
						}
							else
						{
							gd->flag &= ~FLAG_LOCKH;
						}	
					}
					break;
				}
			}
		}
	}
}


			