#include "proto.h"

const char xvirtual[] = "\tvirtual %s;";

char *
GetTitle(struct MyGadget *gd)
{
	if (prefs.code_default_name)
	{
		return(&gd->Name[0]);	
	}
		else
	{
		return "";	
	}	
}

void
generate_header_gad_all(char *name,int count,char *path,struct MyGadget *gad,char **tab)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	int64 a,nb,k;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],false));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_header_begin_creator(fi,name,count);

		nb = count_array(tab);

		a = gad->idcmp;

		for (k = 0; k < nb; k++)
		{
			if (a & (int64)(1LL << k))
			{
				sprintf(&buf[0],&xvirtual[0],tab[k]);

				xwrite_string(fi,&buf[0]);	
			}
		}

		generate_header_end_creator(fi,name,count);

		fclose(fi);

		set_sourcecode(fichier);
	}
}


void
gencode_gadget_all(FILE *fi,struct MyGadget *gad,char *str,int count,char **tab0,char **tab1)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	int64 a,nb,k;

	a = gad->idcmp;

	nb = count_array(tab0);

	for (k = 0; k < nb; k++)
	{
		if (a & (int64)(1LL << k))
		{
			char *fd,tmp[512];

			strcpy(&tmp[0],tab0[k]);

			if (fd = strchr(&tmp[0],' '))
			{
				*fd++ = '\0';

				xwrite_string(fi,&tmp[0]);

				sprintf(&buf[0],"%s%d::%s)",str,count,fd);

				buf[strlen(&buf[0]) - 1] = 0;

				xwrite_string(fi,&buf[0]);	

				if (prefs.code_default_routine)
				{
					strcpy(&tmp[0],tab1[k]);

					if (strncmp(&tmp[0],"void",4) == 0)
					{
						if (fd = strchr(&tmp[0],' '))
						{
							sprintf(&buf[0],"\t%s::%s;",str,fd + 1);
						}	
					}
						else
					{
						if (fd = strchr(&tmp[0],' '))
						{
							sprintf(&buf[0],"\treturn(%s::%s);",str,fd + 1);
						}	
					}	
				}
					else
				{
					strcpy(&buf[0],"");
				}	

				generate_crochet_code(fi,gad,&buf[0]);
			}
		}
	}
}
