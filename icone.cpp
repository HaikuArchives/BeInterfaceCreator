#include "proto.h"

char *
GetFlagView(int nb)
{
	int k = 0;
	static char tmp[500] = {0},*buf = &tmp[0],**tab = &msg_gadviewflags[0],*str;

	*buf = '\0';

	while (str = tab[k])
	{
		if (nb & (1L << k))
		{
			strcat(buf,str);

			strcat(buf,"|");		
		}

		k++;
	}

	if (buf[strlen(buf) - 1] == '|')
	{
		buf[strlen(buf) - 1] = 0;
	}

	return buf;
}

char *
GetAlign(struct MyGadget *gd)
{
	static char tmp[500] = {0},*buf = &tmp[0];

	switch(gd->align)
	{
		case	0:	return(align_select[0]);	break;
		case	1:	return(align_select[1]);	break;
		case	2:
		{
			sprintf(buf,"%s|%s",alignx_select[gd->alignx],aligny_select[gd->aligny]);		
		}
	}

	return buf;
}		
			
