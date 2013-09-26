#include "proto.h"

BView *
Create_Mx(BRect rct,char *title)
{
	BPopUpMenu 	*pt;
	BMenuField 	*vx;
	BMenu		*mn;
	BMenuItem	*it;

	if	(pt = new BPopUpMenu(""))
	{
		pt->AddItem(new BMenuItem(title,NULL));

		if	(vx = new BMenuField(rct,"","",pt))
		{
			float a,b;
			
			vx->GetPreferredSize(&a,&b);

			vx->ResizeTo(a,b);

			vx->SetLabel(title);
		
			return(vx);
		}

		delete pt;
	}

	return(NULL);
}
