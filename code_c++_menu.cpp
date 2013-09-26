#include "proto.h"

void
generate_code_menu(FILE *fi,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*buf = &tmp[0];
	char ftg[B_PATH_NAME_LENGTH],*nam = &ftg[0];
	char xer[B_PATH_NAME_LENGTH],*men = &xer[0];

	struct mymenu *tx;
	int k;
	bool add = false;

	for (k = 0; k < gad->name.CountItems(); k++)
	{
		if (tx = (struct mymenu *)gad->name.ItemAt(k))
		{
			if (add)
			{
				sprintf(buf,"\t%s->AddItem(%s);",men,nam);

				xwrite_string(fi,buf);

				add = false;
			}

			switch(tx->level)
			{
				case	0:
				{
					strcpy(nam,"mn");
					strcpy(men,"menu1");

					sprintf(buf,"\tmn = new BMenu(\"%s\");",tx->name);

					xwrite_string(fi,buf);

					add = true;
				}
				break;				

				case	1:
				{
					strcpy(nam,"it");
					strcpy(men,tx->name);

					sprintf(buf,"\tit = new BMenuItem(\"%s\",NULL);",tx->name);

					xwrite_string(fi,buf);

					xwrite_string(fi,"\tmn->AddItem(it);");
				}
				break;				

				case	2:
				{
					strcpy(nam,tx->name);
					strcpy(men,tx->name);

					sprintf(buf,"\tsb = new BMenu(\"%s\");",tx->name);

					xwrite_string(fi,buf);

					add = true;
				}
				break;				
			}
		}
	}	

	if (add)
	{
		sprintf(buf,"\t%s->AddItem(%s);",men,nam);

		xwrite_string(fi,buf);
	}
}

