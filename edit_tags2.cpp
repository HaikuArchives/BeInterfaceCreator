#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::EnableRadio(bool enable)
{
	alignx->SetEnabled(enable);
	aligny->SetEnabled(enable);
}

extern void *last;

void
EditButtonWindow::SetGlobalInformation(void)
{
	WrkWindow *wi;

	if (gad)
	{
		OldWindow = NULL;

		if (gad != last)
		{
			left->SetValue(gad->x);
			top->SetValue(gad->y);
			width->SetValue(gad->wi);
			height->SetValue(gad->he);

			title->SetText(&gad->Title[0]);
			name->SetText(&gad->Name[0]);
	
			derived->SetValue(gad->derived);

			switch(gad->align)
			{
				case	FOLLOW_NONE:
				case	FOLLOW_ALL:
				{
					EnableRadio(false);
				}
				break;
			
				default:
				{
					EnableRadio(true);
				}
				break;
			}
		}

		last = gad;
	}
		else
	{
		if (wi = DefWin)
		{
			BRect rct = wi->Frame();
		
			left->SetValue((int)rct.left);
			top->SetValue((int)rct.top);
			width->SetValue(rct.IntegerWidth());
			height->SetValue(rct.IntegerHeight());

			title->SetText(&wi->WTitle[0]);
			name->SetText(&wi->Name[0]);
		}	
	}
}
