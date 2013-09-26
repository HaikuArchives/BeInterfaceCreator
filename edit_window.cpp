#include "proto.h"
#include "edit_tags.h"

void
SetSpinDivider(SpinControl *ct,int nb)
{
	ct->SetDivider(ct->StringWidth(ct->Label()) + nb);
}

void
SetDivider(BTextControl *ct,int nb)
{
	ct->SetDivider(ct->StringWidth(ct->Label()) + nb);
}

void
SetDivider(BMenuField *ct,int nb)
{
	ct->SetDivider(ct->StringWidth(ct->Label()) + nb);
}

void
EditButtonWindow::SetWindow(void)
{
	BMenu 		*menu;
	SpinControl *minw,*minh,*maxw,*maxh;
	BMenuField	*look,*feel;
	WrkWindow *wi;
	char **tab,*str;
	BButton	*font;

	int k;

	if (wi = DefWin)
	{
		menu = CreateMenu(this,&look_win[0],window_look,wi->look);

		look = CreateMx(MyRect(10,10,180,25),GetMessage(msg_look),menu,16);
	
		menu = CreateMenu(this,&feel_win[0],window_feel,wi->feel);

		feel = CreateMx(MyRect(10,35,180,25),GetMessage(msg_feel),menu,16);

		minw = CreateSpin(MyRect(220,10,180,18),GetMessage(msg_minhoriz),window_minw,0,100000,wi->minw,16);

		maxw = CreateSpin(MyRect(220,35,180,18),GetMessage(msg_maxhoriz),window_maxw,0,100000,wi->maxh,16);

		minh = CreateSpin(MyRect(220,60,180,18),GetMessage(msg_minvert),window_minh,0,100000,wi->minh,16);

		maxh = CreateSpin(MyRect(220,85,180,18),GetMessage(msg_maxvert),window_maxh,0,100000,wi->maxh,16);

		font = CreateButton(MyRect(9,60,90,20),GetMessage(msg_changefont),tab_font);

		vie2->AddChild(look);
		vie2->AddChild(feel);
		vie2->AddChild(minw);
		vie2->AddChild(maxw);
		vie2->AddChild(minh);
		vie2->AddChild(maxh);
		vie2->AddChild(font);

		SetColorGadget(95);

		idcmp->MakeEmpty();

		tab = (ProjetType == PROJET_BCC) ? &msg_winevents_basic[0] : &msg_winevents_ccplus[0];

		k = 0;

		while (str = tab[k])
		{
			idcmp->AddItem(new CheckItemBox(str,(wi->idcmp & (1l << k++)) ? true : false));	
		}

		if (ProjetType == PROJET_STANDARD)
		{
			k = 0;
		
			while (str = msg_windowflags[k])
			{
				lv->AddItem(new CheckItemBox(str,(wi->flag & (1l << k++)) ? true : false));	
			}
		}
	}
}

void
ChangeWindowType(WrkWindow *wi,int type)
{
	switch(type)
	{
		case	0:	wi->SetLook(B_TITLED_WINDOW_LOOK);		break;
		case	1:	wi->SetLook(B_MODAL_WINDOW_LOOK);		break;
		case	2:	wi->SetLook(B_DOCUMENT_WINDOW_LOOK);	break;
		case	3:	wi->SetLook(B_BORDERED_WINDOW_LOOK);	break;
		case	4:	wi->SetLook(B_FLOATING_WINDOW_LOOK);	break;
	}
}

