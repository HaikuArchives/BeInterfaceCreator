#include "proto.h"
#include "priwindow.h"
#include "edit_tags.h"

extern PriWindow *PriWin;

void
arrange_showall(bool show)
{
	int k;
	BWindow *wi;

	for (k = 0; k < be_app->CountWindows(); k++)
	{
		if (wi = (BWindow *)be_app->WindowAt(k))
		{
			if (is_instance_of(wi,WrkWindow))
			{
				if (show)
				{
					wi->Minimize(false);				
					wi->Show();				
				}
					else
				{
					wi->Minimize(true);				
					wi->Hide();				
				}	
			}
		}
	}

	PriWin->Activate();
}

void
arrange_win0(void)
{
	int	startx = 5,starty = 21,k,nb;

	if	((nb = projet.CountItems()) > 1)
	{
		for (k = 0; k < nb; k++)
		{
			WrkWindow *wi;

			if (wi = projet.ItemAt(k))
			{
				wi->MoveTo(startx,starty);

				startx += 30;
				starty += 30;
			}
		}	
	}

	PriWin->Activate();
}

void
arrange_win1(void)
{
	int	startx = 5,starty = 21,k,h,nb;
	BScreen *sc;

	if	((nb = projet.CountItems()) > 1)
	{
		if	(sc = new BScreen(B_MAIN_SCREEN_ID))
		{
			if (sc->IsValid())
			{
				h = (sc->Frame().IntegerHeight() - ((nb - 1) * 28)) / nb;

				for (k = 0; k < nb; k++)
				{
					WrkWindow *wi;
		
					if (wi = projet.ItemAt(k))
					{
						wi->MoveTo(startx,starty);
						wi->ResizeTo(wi->Frame().IntegerWidth(),h - 6);

						starty += h + 22;
					}
				}	
			}

			delete sc;
		}	
	}

	PriWin->Activate();
}

void
arrange_win2(void)
{
	int	startx = 5,starty = 21,w,k,nb;
	BScreen *sc;

	if	((nb = projet.CountItems()) > 1)
	{
		if	(sc = new BScreen(B_MAIN_SCREEN_ID))
		{
			if (sc->IsValid())
			{
				w = (sc->Frame().IntegerWidth() - ((nb - 1) * 10)) / nb;

				for (k = 0; k < nb; k++)
				{
					WrkWindow *wi;
		
					if (wi = projet.ItemAt(k))
					{
						wi->MoveTo(startx,starty);
						wi->ResizeTo(w - 4,wi->Frame().IntegerHeight());

						startx += w + 8;
					}
				}	
			}

			delete sc;
		}	
	}

	PriWin->Activate();
}
