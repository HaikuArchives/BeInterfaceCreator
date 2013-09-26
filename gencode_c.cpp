#include "proto.h"

extern FILE *xfi;

char *array_msg_ccplus[] = 
{
	"active(void)",
	"inactive(void)",
	"minimize(int x)",
	"moved(int x, int y)",
	"zoom(void)",
	"hide(void)",
	"show(void)",
	"paint(int x)",
	"resized(int x,int y)",
	"screen(int x)",
	"wkactived(int x,int y)",
	"wkchanged(int x,int y)",
	"closed(void)",
	"key(int x,int y)",
	"mousedown(int x,int y,int w,int z)",
	"mousemove(int x,int y)",
	"timer(void)",
	"menu(int x)",
	"begin(void)",
	"watchdevices(int x)",
	"watchdir(char *x,char *y,int z)",
	"dropped(int x,char **tab)",
	"watchapp(int x,char *name)",
	"message(char *appas,char *mess)",
	NULL
};	

char *array2_msg_ccplus[] = 
{
	"active",
	"inactive",
	"minimize",
	"moved",
	"zoom",
	"hide",
	"show",
	"paint",
	"resized",
	"screen",
	"wkactived",
	"wkchanged",
	"closed",
	"key",
	"mousedown",
	"mousemove",
	"timer",
	"menu",
	"begin",
	"watchdevices",
	"watchdir",
	"dropped",
	"appevents",
	"message",
	NULL
};	

char *message_gadget_ccplus[] =
{
	"clicked",
	"keydown",
	"selected",
	"keyfilter",
	"keyenter",
	"doubleclick",
	"dropped",
	"dragicon",	
	NULL
};	

char *message_gadget0_ccplus[] =
{
	"clicked(void)",
	"keydown(int x,int y)",
	"selected(int x)",
	"keyfilter(int x)",
	"keyenter(char *x)",
	"doubleclick(int x)",
	"dropped(int x,char **y)",
	"dragicon(int a,int b,int c,int d)",	
	NULL
};	

char *array_type_ccplus[] =
{
	"button",
	"checkbox",
	"string",
	"integer",
	"float",
	"password",
	"tab",
	"box",
	"radio",
	"mx",
	"stext",
	"number",
	"statusbar",
	"color",
	"listview",
	"listview1",
	"listview2",
	"listview3",
	"outlistview",
	"outlistview1",
	"outlistview2",
	"outlistview3",
	"hslider",
	"vslider",
	"hscroller",
	"vscroller",
	"tedit",
	"tedit1",
	"tedit2",
	"tedit3",
	"menu",	
	NULL
};

void
gencode_checkbox_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.bcheckbox.checked)
	{
		sprintf(buf,"SetChecked(%s,true);",&gd->Name[0]);

		xwrite_string(buf);
	}
}

void
gencode_text_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetAlignment(%s,%d);",&gd->Name[0],gd->align);
		xwrite_string(buf);
	}
	
/*	if (gd->data.txt.txt)
	{
		sprintf(buf,"SetTextString(%s,\"%s\");",&gd->Name[0],gd->data.txt.txt);
		xwrite_string(buf);
	}
*/
}

void
gencode_number_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetAlignment(%s,%d);",&gd->Name[0],gd->align);
		xwrite_string(buf);
	}
	
	if (gd->data.num.val != 0)
	{
		sprintf(buf,"SetNumberString(%s,%d);",&gd->Name[0],gd->data.num.val);
		xwrite_string(buf);
	}
}

void
gencode_color_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.col.cellsize != 6)
	{
		sprintf(buf,"SetCellSize(%s,%d);",&gd->Name[0],gd->data.col.cellsize);
		xwrite_string(buf);
	}
	
	if (gd->data.col.layout != 1)
	{
		sprintf(buf,"SetLayout(%s,%d);",&gd->Name[0],gd->data.col.layout << 2);
		xwrite_string(buf);
	}
}

void
gencode_box_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.bbox.style != B_FANCY_BORDER)
	{
		sprintf(buf,"SetBorder %s,%d",&gd->Name[0],gd->data.bbox.style);
		xwrite_string(buf);
	}
}

void
gencode_tab_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*str,*buf = &tmp[0];
	int k = 0;

	sprintf(buf,"AddTab(g%s,\"%s\");",&gd->Name[0],&gd->Name[0]);

	xwrite_string(buf);

	return;

	if (gd->data.tab.sel != 0)
	{
		sprintf(buf,"TabSelect(%s,\"%s\");",&gd->Name[0],gd->data.tab.sel);
		xwrite_string(buf);
	}

	if (gd->data.tab.tabwidth != 0)
	{
		sprintf(buf,"SetTabWidth(%s,%d);",&gd->Name[0],gd->data.tab.tabwidth);
		xwrite_string(buf);
	}

	if (gd->data.tab.tabheight != 19)
	{
		sprintf(buf,"SetTabHeight(%s,%d);",&gd->Name[0],gd->data.tab.tabheight);
		xwrite_string(buf);
	}
}

void
gencode_listview_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.lv.multi)
	{
		sprintf(buf,"SetMultiSelect(%s,true);",&gd->Name[0]);
		xwrite_string(buf);
	}
	
	if (gd->data.lv.sel != -1)
	{
		sprintf(buf,"SetSelectEntry(%s,%d);",&gd->Name[0],gd->data.lv.sel);
		xwrite_string(buf);
	}
}

void
gencode_outlistview_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.olv.multi)
	{
		sprintf(buf,"SetMultiSelect(%s,true);",&gd->Name[0]);
		xwrite_string(buf);
	}
	
	if (gd->data.olv.sel != -1)
	{
		sprintf(buf,"SetSelectEntry(%s,%d);",&gd->Name[0],gd->data.olv.sel);
		xwrite_string(buf);
	}
}

void
gencode_radio_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*str,*dat,*buf = &tmp[0];
	int k = 0;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (str = (char *)gd->name.ItemAt(k))
		{
			sprintf(buf,"ArrayStr(%d) = \"%s\";",k,str);

			xwrite_string(buf);
		}
	}	

	sprintf(buf,"ArrayStr(%d) = \"\";",k);

	xwrite_string(buf);

	if (gd->data.rad.sel != -1)
	{
		sprintf(buf,"RadSelected %s,%d",&gd->Name[0],gd->data.rad.sel);
		xwrite_string(buf);
	}
}

void
gencode_mx_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*str,*dat,*buf = &tmp[0];
	int k = 0;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (str = (char *)gd->name.ItemAt(k))
		{
			sprintf(buf,"ArrayStr(%d) = \"%s\";",k,str);

			xwrite_string(buf);
		}
	}	

	sprintf(buf,"ArrayStr(%d) = \"\";",k);

	xwrite_string(buf);

/*	if (gd->data.mx.sel != -1)
	{
		sprintf(buf,"MxSelected(%s,%d);",&gd->Name[0],gd->data.mx.sel);
		xwrite_string(buf);
	}
*/
}

void
gencode_slider_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];
	rgb_color blk = { 0,0,0};
	rgb_color cyg = { 80,80,80};

	if (gd->data.bslider.pos != 0)
	{
		sprintf(buf,"SetSliderPosition(%s,%d);",&gd->Name[0],gd->data.bslider.pos);
		xwrite_string(buf);
	}

	if (gd->data.bslider.style)
	{
		sprintf(buf,"SetStyle(%s,true);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.bslider.hashtype)
	{
		sprintf(buf,"SetHashType(%s,%d);",&gd->Name[0],gd->data.bslider.hashtype);
		xwrite_string(buf);
	}

	if (gd->data.bslider.hashcount)
	{
		sprintf(buf,"SetHashType(%s,%d);",&gd->Name[0],gd->data.bslider.hashcount);
		xwrite_string(buf);
	}

/*	if (gd->data.bslider.minlabel || gd->data.bslider.maxlabel)
	{
		sprintf(buf,"SetLimitsLabel(%s,\"%s\",\"%s\");",&gd->Name[0],(gd->data.bslider.minlabel) ? gd->data.bslider.minlabel : "",(gd->data.bslider.maxlabel) ? gd->data.bslider.maxlabel : "");
		xwrite_string(buf);
	}
*/
	if (!IsSameColor(&gd->data.bslider.fillcolor,&blk))
	{
		sprintf(buf,"SetFillColor(%s,&h%x);",&gd->Name[0],(gd->data.bslider.fillcolor.red << 24) + (gd->data.bslider.fillcolor.green << 16) + (gd->data.bslider.fillcolor.blue << 8));
		xwrite_string(buf);
	}

	if (!IsSameColor(&gd->data.bslider.barcolor,&cyg))
	{
		sprintf(buf,"SetBarColor(%s,&h%x);",&gd->Name[0],(gd->data.bslider.barcolor.red << 24) + (gd->data.bslider.barcolor.green << 16) + (gd->data.bslider.barcolor.blue << 8));
		xwrite_string(buf);
	}
}

void
gencode_scroller_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.bscroller.minrange != 0 || gd->data.bscroller.maxrange != 15)
	{
		sprintf(buf,"SetRange(%s,%d,%d);",&gd->Name[0],gd->data.bscroller.minrange,gd->data.bscroller.maxrange);
		xwrite_string(buf);
	}

	if (gd->data.bscroller.pos != 0)
	{
		sprintf(buf,"SetValue(%s,%d);",&gd->Name[0],gd->data.bscroller.pos);
		xwrite_string(buf);
	}

	if (gd->data.bscroller.setprop != 0)
	{
		sprintf(buf,"SetProportion(%s,%d);",&gd->Name[0],gd->data.bscroller.setprop);
		xwrite_string(buf);
	}

	if (gd->data.bscroller.minstep != 1 || gd->data.bscroller.maxstep != 5)
	{
		sprintf(buf,"SetSteps(%s,%d,%d);",&gd->Name[0],gd->data.bscroller.minstep,gd->data.bscroller.maxstep);
		xwrite_string(buf);
	}
}

void
gencode_string_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetAlignment(%s,%d);",&gd->Name[0],gd->align);
		xwrite_string(buf);
	}

	if (gd->data.string.maxchars != 15)
	{
		sprintf(buf,"SetInteger(%s,%d);",&gd->Name[0],gd->data.string.maxchars);
		xwrite_string(buf);
	}

	if (!gd->data.string.editable)
	{
		sprintf(buf,"MakeEditable(%s,false);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (!gd->data.string.selectable)
	{
		sprintf(buf,"MakeSelectable(%s,false);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.string.pixdiv != gd->data.string.pixdeb)
	{
		sprintf(buf,"SetDiviser(%s,%d);",&gd->Name[0],gd->data.string.pixdiv);
		xwrite_string(buf);
	}

	switch(gd->type)
	{
		case	STRING_KIND:			
		{
/*			if (gd->data.string.txt)
			{
				sprintf(buf,"SetString(%s,\"%s\");",&gd->Name[0],gd->data.string.txt);
				xwrite_string(buf);
			}
*/		}
		break;

		case	INTEGER_KIND:			
		{
			if (gd->data.string.value != 0)
			{
				sprintf(buf,"SetInteger(%s,%d);",&gd->Name[0],gd->data.string.value);
				xwrite_string(buf);
			}
		}
		break;

		case	PASSWORD_KIND:			
		{
/*			if (gd->data.string.txt)
			{
				sprintf(buf,"SetString(%s,\"%s\");",&gd->Name[0],gd->data.string.txt);
				xwrite_string(buf);
			}
*/		}
		break;
	}
}

void
gencode_tedit_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetAlignment(%s,%d);",&gd->Name[0],gd->align);
		xwrite_string(buf);
	}

	if (!gd->data.edi.selectable)
	{
		sprintf(buf,"TEditMakeSelectable(%s,false);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (!gd->data.edi.editable)
	{
		sprintf(buf,"TEditMakeEditable(%s,false);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (!gd->data.edi.wordwrap)
	{
		sprintf(buf,"TEditWordWrap(%s,false);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.edi.autoident)
	{
		sprintf(buf,"TEditAutoIdent(%s,true);",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.edi.tabwidth != ((BTextView *)gd->pt)->TabWidth())
	{
		sprintf(buf,"TEditSetTabWidth(%s,%d);",&gd->Name[0],gd->data.edi.tabwidth);
		xwrite_string(buf);
	}

	if (gd->data.edi.maxchars != ((BTextView *)gd->pt)->MaxBytes())
	{
		sprintf(buf,"TEditSetMaxSize(%s,%d);",&gd->Name[0],gd->data.edi.maxchars);
		xwrite_string(buf);
	}
}

void
gencode_statusbar_ccplus(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];
	rgb_color blk = { 50,150,255};

	if (gd->data.sta.barheight != 17)
	{
		sprintf(buf,"SetStatusBarHeight(%s,%d);",&gd->Name[0],gd->data.sta.barheight);
		xwrite_string(buf);
	}

	if (gd->data.sta.maxvalue != 100)
	{
		sprintf(buf,"SetStatusMaxValue(%s,%d);",&gd->Name[0],gd->data.sta.maxvalue);
		xwrite_string(buf);
	}

	if (gd->data.sta.value != 0)
	{
		sprintf(buf,"SetStatusValue(%s,%d);",&gd->Name[0],gd->data.sta.value);
		xwrite_string(buf);
	}

	if (&gd->data.sta.barcolor != &blk)
	{
		sprintf(buf,"SetStatusBarColor(%s,&h%x);",&gd->Name[0],(gd->data.sta.barcolor.red << 24) + (gd->data.sta.barcolor.green << 16) + (gd->data.sta.barcolor.blue << 8));
		xwrite_string(buf);
	}
	
/*	if (gd->data.sta.label)
	{
		sprintf(buf,"SetStatusLabel(%s,\"%s\");",&gd->Name[0],gd->data.sta.label);
		xwrite_string(buf);
	}

	if (gd->data.sta.trail)
	{
		sprintf(buf,"SetStatusTrail(%s,\"%s\");",&gd->Name[0],gd->data.sta.trail);
		xwrite_string(buf);
	}
*/
}

void
gencode_c(char *fichier,WrkWindow *wi)
{
	struct MyGadget *gad;
	struct MyProject *xt;
	int t,tt,k;
	char tmp[500],name[128],*title = &name[0],*buf = &tmp[0];
	BRect rct;
	bool have_mx_or_rad = false;

	rgb_color col,cox,backcol = { 216,216,216},forcol = {0,0,0};

	sprintf(title,"form%d",projet.IndexOf(wi) + 1);

	if (xfi = fopen(fichier,"w+"))
	{
		for (tt = 0; tt< wi->list.CountItems(); tt++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(tt))
			{
				if (gad->type == MX_KIND || gad->type == RADIO_KIND)
				{
					have_mx_or_rad = true;
				}				
			}
		}						

		if (have_mx_or_rad)
		{
			sprintf(buf,"char *ArrayStr[50];");

			xwrite_string(buf);
		}

		sprintf(buf,"int %s",title);

		xwrite_string(buf);

		for (tt = 0; tt< wi->list.CountItems(); tt++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(tt))
			{
				sprintf(buf,"int g%s;",&gad->Name[0]);

				xwrite_string(buf);
			}	
		}

		xwrite_cr();

		for (t = 0; t < OnEnd; t++)
		{
			if (wi->idcmp & (1L << t))
			{
				char *str;
				
				if (str = array_msg_ccplus[t])
				{
					bool paren = false;

					if (strchr(str,'('))
					{
						paren = true;				
					}

					sprintf(buf,"%s %s_%s%s\n{",(t == OnClosed) ? "bool" : "void",title,str,(paren) ? "" : "(void)");

					xwrite_string(buf);

					if (t == OnClosed)
					{
						strcpy(buf,"\treturn true;");
	
						xwrite_string(buf);
					}

					sprintf(buf,"}");

					xwrite_string(buf);

					xwrite_cr();
				}
			}
		}	

		rct = wi->Frame();

		sprintf(buf,"%s = OpenWindow(%d,%d,%d,%d);",title,(int)rct.left,(int)rct.top,rct.IntegerWidth(),rct.IntegerHeight());

		xwrite_string(buf);

		for (t = 0; t < OnEnd; t++)
		{
			if (wi->idcmp & (1L << t))
			{
				sprintf(buf,"SetHandlerWindow(%s,%d,&%s_%s);",title,t + 1,title,array2_msg_ccplus[t]);

				xwrite_string(buf);
			}
		}	

/*		if (!wi->Zoomable)
		{
			sprintf(buf,"WindowZoomable(%s,false);",title);
			xwrite_string(buf);
		}

		if (!wi->Resizable)
		{
			sprintf(buf,"WindowResizable(%s,false);",title);
			xwrite_string(buf);
		}

		if (!wi->Minimizable)
		{
			sprintf(buf,"WindowMinimizable(%s,false);",title);
			xwrite_string(buf);
		}

		if (!wi->Visible)
		{
			sprintf(buf,"HideWindow(%s);",title);
			xwrite_string(buf);
		}

		if (!wi->Movable)
		{
			sprintf(buf,"WindowMovable(%s,false);",title);
			xwrite_string(buf);
		}
					
		if (!wi->Resizable)
		{
			sprintf(buf,"WindowResizable(%s,false);",title);
			xwrite_string(buf);
		}

		if (wi->ResizeMode)
		{
			sprintf(buf,"WindowResizeMode(%s,true);",title);
			xwrite_string(buf);
		}

		if (wi->Style)
		{
			sprintf(buf,"SetWindowLook(%s,%d);",title,wi->Style);
			xwrite_string(buf);
		}

		wi->Lock();

		col = wi->bck->ViewColor();

		if (col.red != backcol.red || col.green != backcol.green || col.blue != backcol.blue)
		{
			sprintf(buf,"SetBackColor(%s,&h%x);",title,(col.red << 24) + (col.green << 16) + (col.blue << 8));
			xwrite_string(buf);
			sprintf(buf,"Clear(%s);",title);
			xwrite_string(buf);
		}	

		col = wi->bck->HighColor();
		cox = wi->bck->LowColor();

		if (col.red != forcol.red || col.green != forcol.green || col.blue != forcol.blue)
		{
			sprintf(buf,"SetForeColor(%s,&h%x,&h%x);",title,(col.red << 24) + (col.green << 16) + (col.blue << 8),(cox.red << 24) + (cox.green << 16) + (cox.blue << 8));
			xwrite_string(buf);
		}	

		wi->Unlock();
*/
		for (t = 0; t < wi->list.CountItems(); t++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(t))
			{
				for (k = 0; k < OnGadEnd; k++)
				{
					if (gad->flag & (1L << k))
					{
						if (t == 0 || t == 3 || tt == 4)
						{
							sprintf(buf,"void\ng%s_%s",&gad->Name[0],message_gadget0_ccplus[t]);
						}
							else
						{
							sprintf(buf,"void\ng%s_%s",&gad->Name[0],message_gadget0_ccplus[t]);
						}

						xwrite_string(buf);
							
						xwrite_string("{");

						sprintf(buf,"}");

						xwrite_string(buf);

						xwrite_cr();
					}
				}	
			}
		}	

		for (t = 0; t < wi->list.CountItems(); t++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(t))
			{
				int val = 0;
				
				if (gad->type == MENU_KIND)
				{
					goto next;
				}

				if (gad->type == SLIDER_HORIZ_KIND || gad->type == SLIDER_VERT_KIND)
				{
					val = gad->data.bslider.max;				
				}
		
				if (gad->type == RADIO_KIND || gad->type == MX_KIND)
				{
					switch(gad->type)
					{
						case	MX_KIND:	gencode_mx_ccplus(gad,xfi);	break;
						case	RADIO_KIND:	gencode_radio_ccplus(gad,xfi);	break;
					}	

					sprintf(buf,"%s = CreateGadget(%gs,%s,%d,%d,%d,%d,&ArrayStr[0],0);",&gad->Name[0],array_type_ccplus[gad->type],title,gad->x,gad->y,gad->wi,gad->he);
				}
					else
				{
					char *name = &gad->Title[0];

					switch(gad->type)
					{
						case	TAB_KIND:
						case	COLOR_KIND:
						case	SCROLLER_HORIZ_KIND:
						case	SCROLLER_VERT_KIND:
						case	LISTVIEW_KIND:
						case	LISTVIEW_HORIZ_KIND:
						case	LISTVIEW_VERT_KIND:
						case	LISTVIEW_ALL_KIND:
						case	OUTLISTVIEW_KIND:
						case	OUTLISTVIEW_HORIZ_KIND:
						case	OUTLISTVIEW_VERT_KIND:
						case	OUTLISTVIEW_ALL_KIND:
						case	TEDIT_KIND:
						case	TEDIT_HORIZ_KIND:
						case	TEDIT_VERT_KIND:
						case	TEDIT_ALL_KIND:	name = ""; break;
					}

					sprintf(buf,"%s = CreateGadget(%gs,%s,%d,%d,%d,%d,\"%s\",%d);",&gad->Name[0],array_type_ccplus[gad->type],title,gad->x,gad->y,gad->wi,gad->he,name,val);
				}
				
				xwrite_string(buf);

				if (!gad->enable)
				{
					sprintf(buf,"SetEnabled(%gs,false);",&gad->Name[0]);
					xwrite_string(buf);
				}

				if (gad->flag & IS_FONTLEASING)
				{
					sprintf(buf,"SetAntiliasingGadget(%gs,false);",&gad->Name[0]);
					xwrite_string(buf);
				}

				switch(gad->type)
				{
					case	TAB_KIND:				gencode_tab_ccplus(gad,xfi);	break;
/*					case	CHECKBOX_KIND:			gencode_checkbox_ccplus(gad,xfi);	break;
					case	COLOR_KIND:				gencode_color_ccplus(gad,xfi);	break;
					case	SLIDER_HORIZ_KIND:
					case	SLIDER_VERT_KIND:		gencode_slider_ccplus(gad,xfi);	break;
					case	SCROLLER_HORIZ_KIND:	
					case	SCROLLER_VERT_KIND:		gencode_scroller_ccplus(gad,xfi);	break;
					case	STRING_KIND:			
					case	INTEGER_KIND:		
					case	PASSWORD_KIND:				
					case	FLOAT_KIND:				gencode_string_ccplus(gad,xfi);	break;
					case	BOX_KIND:				gencode_box_ccplus(gad,xfi);	break;
					case	TEXT_KIND:				gencode_text_ccplus(gad,xfi);	break;
					case	NUMBER_KIND:			gencode_number_ccplus(gad,xfi);	break;
					case	STATUSBAR_KIND:			gencode_statusbar_ccplus(gad,xfi);	break;
					case	LISTVIEW_KIND:
					case	LISTVIEW_HORIZ_KIND:
					case	LISTVIEW_VERT_KIND:
					case	LISTVIEW_ALL_KIND:		gencode_listview_ccplus(gad,xfi);	break;
					case	OUTLISTVIEW_KIND:
					case	OUTLISTVIEW_HORIZ_KIND:
					case	OUTLISTVIEW_VERT_KIND:
					case	OUTLISTVIEW_ALL_KIND:	gencode_outlistview_ccplus(gad,xfi);	break;
					case	TEDIT_KIND:
					case	TEDIT_HORIZ_KIND:
					case	TEDIT_VERT_KIND:
					case	TEDIT_ALL_KIND:			gencode_tedit_ccplus(gad,xfi);	break;
*/				}
next:;		}
		}

		for (t = 0; t < wi->list.CountItems(); t++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(t))
			{
				for (k = 0; k < OnGadEnd; k++)
				{
					if (gad->flag & (1L << k))
					{
						sprintf(buf,"SetHandlerGadget(%gs,%d,&g%s_%s);",&gad->Name[0],t + 1,&gad->Name[0],message_gadget_ccplus[t]);

						xwrite_string(buf);
					}
				}
			}
		}			

		fclose(xfi);

		set_sourcecode(fichier);
	}
}
