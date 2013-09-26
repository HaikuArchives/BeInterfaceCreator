#include "proto.h"
#include <ctype.h>

int tabkey[40];

char *key_command[] =
{
	"selectall",
	"unselectall",
	"inverseselection",
	"selectnext",
	"selectpred",
	"allisderived",
	"allisnotderived",
	"fontdefault",
	"create",
	"delete",
	"cut",
	"copy",
	"paste",
	"centerwidth",
	"centerheight",
	"centerall",
	"spacewidth",
	"spaceheight",
	"spaceall",
	"uniformwidth",
	"uniformheight",
	"uniformall",
	"aligntop",
	"alignright",
	"aligntop",
	"alignbottom",
	"undelete",
	"gridon",
	"gridoff",
	"lockx",
	"locky",
	"lockw",
	"lockh",
	"unlockx",
	"unlocky",
	"unlockw",
	"unlockh",
	NULL
};		

enum cmlist 
{
	SELECTALL = 0,
	UNSELECTALL,
	INVERSESELECTION,
	SELECTNEXT,
	SELECTPRED,
	ALLISDERIVED,
	ALLISNOTDERIVED,
	FONTDEFAULT,
	CREATE,
	DELETE,
	CUT,
	COPY,
	PASTE,
	CENTERWIDTH,
	CENTERHEIGHT,
	CENTERALL,
	SPACEWIDTH,
	SPACEHEIGHT,
	SPACEALL,
	UNIFORMWIDTH,
	UNIFORMEIGHT,
	UNIFORMALL,
	ALIGNLEFT,
	ALIGNRIGHT,
	ALIGNTOP,
	ALIGNBOTTOM,
	UNDELETE,
	GRIDON,
	GRIDOFF,
	ONLOCKX,
	ONLOCKY,
	ONLOCKW,
	ONLOCKH,
	OFFLOCKX,
	OFFLOCKY,
	OFFLOCKW,
	OFFLOCKH,
};	

char *key_valid[] =
{
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	NULL
};		

void
docommand(WrkWindow *wi,int cmd)
{
	switch(cmd)
	{
		case	CUT:				wi->Cut();							break;
		case	COPY:				wi->Copy();							break;
		case	PASTE:				wi->Paste();						break;
		case	SELECTALL:			wi->SelectAll();					break;
		case	UNSELECTALL:		wi->UnSelectAll();					break;
		case	INVERSESELECTION:	wi->InverseSelection();				break;
		case	ALLISDERIVED:		wi->AllDerived(true);				break;	
		case	ALLISNOTDERIVED:	wi->AllDerived(false);				break;	
		case	CENTERWIDTH:		wi->CenterInForm(CENTER_WIDTH);		break;
		case	CENTERHEIGHT:		wi->CenterInForm(CENTER_HEIGHT);	break;
		case	CENTERALL:			wi->CenterInForm(CENTER_ALL);		break;
		case	SPACEWIDTH:			wi->SpaceInForm(SPACING_WIDTH);		break;
		case	SPACEHEIGHT:		wi->SpaceInForm(SPACING_HEIGHT);	break;
		case	SPACEALL:			wi->SpaceInForm(SPACING_ALL);		break;
		case	UNIFORMWIDTH:		wi->UniForm(UNIFORM_WIDTH);			break;
		case	UNIFORMEIGHT:		wi->UniForm(UNIFORM_HEIGHT);		break;
		case	UNIFORMALL:			wi->UniForm(UNIFORM_ALL);			break;
		case	ALIGNLEFT:			wi->AlignRtn(ALIGN_LEFT);			break;
		case	ALIGNRIGHT:			wi->AlignRtn(ALIGN_RIGHT);			break;
		case	ALIGNTOP:			wi->AlignRtn(ALIGN_TOP);			break;
		case	ALIGNBOTTOM:		wi->AlignRtn(ALIGN_BOTTOM);			break;
		case	UNDELETE:			wi->UnDelete();						break;
		case	GRIDON:				wi->SetGrid(true);					break;
		case	GRIDOFF:			wi->SetGrid(false);					break;
		case	ONLOCKX:			wi->LockGadget(0,true);				break;
		case	ONLOCKY:			wi->LockGadget(1,true);				break;
		case	ONLOCKW:			wi->LockGadget(2,true);				break;
		case	ONLOCKH:			wi->LockGadget(3,true);				break;
		case	OFFLOCKX:			wi->LockGadget(0,false);			break;
		case	OFFLOCKY:			wi->LockGadget(1,false);			break;
		case	OFFLOCKW:			wi->LockGadget(2,false);			break;
		case	OFFLOCKH:			wi->LockGadget(3,false);			break;
	}
}

void
keypress(WrkWindow *wi,int key)
{
	int nb;

	if (key < 0 || key > 37)
	{
		return;
	}

	if ((nb = tabkey[key]) != -1)
	{
		docommand(wi,nb);
	}
}

void
set_lower(char *p)
{
	while(*p) { *p = tolower(*p); p++; }
}

int
isvalidcom(char *buf)
{
	char *str;
	int k = 0;
	
	while (str = key_command[k++])
	{
		if (strcmp(str,buf) == 0)
		{
			return(k - 1);
		}	
	}
	
	return -1;
}

int
isvalidkey(char *buf)
{
	char *str;
	int k = 0;
	
	while (str = key_valid[k++])
	{
		if (strcmp(str,buf) == 0)
		{
			return(k - 1);
		}	
	}
	
	return -1;
}

void
load_keypress(void)
{
	char tmp[300],*fd,*buf = &tmp[0];
	int a,b;
	FILE *fi;

	for (a = 0; a < 40; a++)
	{
		tabkey[a] = -1;	
	}

	if (fi = fopen("/boot/home/Bic.Key","r+"))
	{
		while (fgets(buf,256,fi))
		{
			buf[strlen(buf) - 1] = 0;
	
			if (buf[0] != '#')
			{
				if (fd = strchr(buf,'='))
				{
					*fd++ = 0;

					set_lower(buf);
					set_lower(fd);

					a = isvalidcom(fd);
					b = isvalidkey(buf);
					
					if (a >=0 && b >=0)
					{
						tabkey[b] = a;
					}
				}
			}		
		}

		fclose(fi);
	}
}
