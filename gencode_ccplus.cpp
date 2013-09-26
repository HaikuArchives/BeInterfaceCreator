#include "proto.h"

extern FILE *xfi;

void
xwrite_string(FILE *fi,char *str,bool cr = true)
{
	BString kk(str);

	if (!prefs.code_default_void)
	{
		kk = kk.ReplaceAll((const char *)"(void)",(const char *)"()");
	}
	
	fwrite(kk.String(),1,strlen(kk.String()),fi);
	
	if (cr)
	{
		fwrite("\n",1,1,fi);
	}
}

void
xwrite_cr(FILE *fi)
{
	fwrite("\n",1,1,fi);
}

void
generate_copyright_include(FILE *fi)
{
	xwrite_string(fi,"/*");
	xwrite_string(fi,"\tFile generated with Bic");
	xwrite_string(fi,"\tCopyright 2001 Devulder Jpaul rgb@free.fr");
	xwrite_string(fi,"*/");

	xwrite_cr(fi);
	xwrite_cr(fi);

	xwrite_string(fi,"#include <AppKit.h>");	
	xwrite_string(fi,"#include <InterfaceKit.h>");	

	xwrite_cr(fi);
	xwrite_cr(fi);
}

WrkWindow *defwin;

void
gen_ccplus_window(char *path,WrkWindow *wi)
{
	int t;
	struct MyGadget *gad;

	if (wi->idcmp)
	{
		generate_header_ccplus_window(path,wi);

		generate_code_ccplus_window(path,wi);

		defwin = wi;

		for (t = 0; t < wi->list.CountItems(); t++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(t))
			{
				if (gad->derived)
				{
					switch(gad->type)
					{
						case	VIEW_KIND:				gen_ccplus_gad_view(path,gad);			break;
						case	BUTTON_KIND:			gen_ccplus_gad_button(path,gad);		break;
						case	MX_KIND:				gen_ccplus_gad_mx(path,gad);			break;
						case	TAB_KIND:				gen_ccplus_gad_tab(path,gad);			break;
						case	CHECKBOX_KIND:			gen_ccplus_gad_checkbox(path,gad);		break;
						case	RADIO_KIND:				gen_ccplus_gad_radio(path,gad);			break;
						case	COLOR_KIND:				gen_ccplus_gad_color(path,gad);			break;
						case	SLIDER_HORIZ_KIND:
						case	SLIDER_VERT_KIND:		gen_ccplus_gad_slider(path,gad);		break;
						case	SCROLLER_HORIZ_KIND:	
						case	SCROLLER_VERT_KIND:		gen_ccplus_gad_scroller(path,gad);		break;
						case	STRING_KIND:			
						case	INTEGER_KIND:		
						case	PASSWORD_KIND:				
						case	FLOAT_KIND:				gen_ccplus_gad_string(path,gad);		break;
						case	BOX_KIND:				gen_ccplus_gad_box(path,gad);			break;
						case	NUMBER_KIND:
						case	TEXT_KIND:				gen_ccplus_gad_text(path,gad);			break;
						case	STATUSBAR_KIND:			gen_ccplus_gad_statusbar(path,gad);		break;
						case	LISTVIEW_KIND:
						case	LISTVIEW_HORIZ_KIND:
						case	LISTVIEW_VERT_KIND:
						case	LISTVIEW_ALL_KIND:		gen_ccplus_gad_listview(path,gad);		break;
						case	OUTLISTVIEW_KIND:
						case	OUTLISTVIEW_HORIZ_KIND:
						case	OUTLISTVIEW_VERT_KIND:
						case	OUTLISTVIEW_ALL_KIND:	gen_ccplus_gad_outlistview(path,gad);	break;
						case	TEDIT_KIND:
						case	TEDIT_HORIZ_KIND:
						case	TEDIT_VERT_KIND:
						case	TEDIT_ALL_KIND:			gen_ccplus_gad_tedit(path,gad);			break;
					}
				}
			}
		}	
	}
}

void
gencode_ccplus(char *path,char *fichier,WrkWindow *wi)
{
	char a00[B_PATH_NAME_LENGTH],*f00 = &a00[0];

	strcpy(a00,path);

	count_button 		= 0;
	count_tab 			= 0;
	count_box 			= 0;
	count_slider 		= 0;
	count_scroller	 	= 0;
	count_text 			= 0;
	count_number 		= 0;
	count_listview 		= 0;
	count_outlistview 	= 0;
	count_checkbox 		= 0;
	count_string 		= 0;
	count_tedit 		= 0;
	count_color 		= 0;
	count_statusbar 	= 0;
	count_mx 			= 0;
	count_radio 		= 0;

	gen_ccplus_window(a00,wi);
}
