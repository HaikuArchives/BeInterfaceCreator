#include "proto.h"

extern FILE *xfi;

void
generate_header_gad_button(struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	int k;

	sprintf(fichier,"/boot/home/Button%d.h",count_button);
	
	if (fi = fopen(fichier,"w+"))
	{
		sprintf(fichier,"#ifndef __Button%d",count_button);

		xwrite_string(fi,fichier);	

		xwrite_cr(fi);

		sprintf(fichier,"class Button%d : public BButton",count_button);

		xwrite_string(fi,fichier);	

		xwrite_string(fi,"{\npublic:\n");	

		sprintf(fichier,"\tButton%d(void);",count_button);

		xwrite_string(fi,fichier);	

		sprintf(fichier,"\t~Button%d(void);",count_button);

		xwrite_string(fi,fichier);	

		xwrite_cr(fi);

		for (k = 0; k < 51; k++)
		{
			if (gad->idcmp & (1L << k))
			{
				sprintf(fichier,"\tvirtual %s;",msg_gadevents_code_ccplus_button[k]);

				xwrite_string(fi,fichier);	
			}
		}

		xwrite_string(fi,"};");

		xwrite_cr(fi);

		sprintf(fichier,"#define __Button%d",count_button);

		xwrite_string(fi,fichier);	

		xwrite_string(fi,"#endif");	

		fclose(fi);
	}
}

void
generate_code_ccplus_gad_button(struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	int k;

	sprintf(fichier,"/boot/home/Button%d.cpp",count_button);
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(fichier,"#include \"Button%d.h\"",count_button);

		xwrite_string(fi,fichier);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(fichier,"Button%d::Button%d(void):BButton(BRect(%d,%d,%d,%d),\"%s\",\"%s\",new BMessage((uint32)%d),%s)",count_button,count_button,gad->x,gad->y,gad->x + gad->wi,gad->y + gad->he,&gad->Name[0],&gad->Title[0],gad->msg,"B_WILL_DRAW");

		xwrite_string(fi,fichier);

		xwrite_string(fi,"{");
		xwrite_string(fi,"}");

		xwrite_cr(fi);

		sprintf(fichier,"Button%d::~Button%d(void)\n{\n}\n",count_button,count_button);

		for (k = 0; k < 51; k++)
		{
			if (gad->idcmp & (1L << k))
			{
				char *fd,tmp[512];
				
				strcpy(&tmp[0],msg_gadevents_code_ccplus_button[k]);

				if (fd = strchr(&tmp[0],' '))
				{
					*fd++ = '\0';

					xwrite_string(fi,&tmp[0]);

					sprintf(fichier,"Button%d::%s)",count_button,fd);

					fichier[strlen(fichier) - 1] = 0;

					xwrite_string(fi,fichier);	

					xwrite_string(fi,"{");
					xwrite_string(fi,"}");

					xwrite_cr(fi);
				}
			}
		}

		fclose(fi);
	}
}

void
gen_ccplus_gad_button(struct MyGadget *gad)
{
	++count_button;

	generate_header_gad_button(gad);

	generate_code_ccplus_gad_button(gad);
}
