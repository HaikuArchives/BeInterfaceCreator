#include "proto.h"

FILE *xfi;

extern	void	RemoveDir(char *app);

char *array_msg[] = 
{
	"active",
	"inactive",
	"minimize(x As Integer)",
	"moved(x As Integer,y As Integer)",
	"zoom",
	"hide",
	"show",
	"paint(x As Integer)",
	"resized(x As Integer,y As Integer)",
	"screen(x As Integer)",
	"wkactived(x As Integer,y As Integer)",
	"wkchanged(x As Integer,y As Integer)",
	"closed",
	"key(x As Integer,y As Integer)",
	"mousedown(x As Integer,y As Integer,w As Integer,z As Integer)",
	"mousemove(x As Integer,y As Integer)",
	"timer",
	"menu(x As Integer)",
	"begin",
	"watchdevices(x As Integer)",
	"watchdir(x As String,y As String,z As Integer)",
	"dropped(x As Integer,y As ArrayString)",
	"appevents(x As Integer,name As String)",
	"message(app As String,mess As String)",
	NULL
};	

char *array2_msg[] = 
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

char *message_gadget[] =
{
	"clicked",
	"selected",
	"keydown",
	"doubleclick",
	"dropped",
	"dragicon",	
	"keyfilter",
	"keyenter",
	NULL
};	

char *message_gadget0[] =
{
	"clicked",
	"selected(num As Integer)",
	"keydown(key As Integer,qualifier As Integer)",
	"doubleclick(num As Integer)",
	"dropped(num As Integer,tab As ArrayString)",
	"dragicon(a As Integer,b As Integer,c As Integer,d As Integer)",	
	"keyfilter(car As Integer)",
	"keyenter(str As String)",
	NULL
};	

char *array_type[] =
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
xwrite_string(char *str,bool cr = true)
{
	BString kk(str);

	if (!prefs.code_default_void)
	{
		kk = kk.ReplaceAll((const char *)"(void)",(const char *)"()");
	}
	
	fwrite(kk.String(),1,strlen(kk.String()),xfi);
	
	if (cr)
	{
		fwrite("\n",1,1,xfi);
	}
}

void
xwrite_cr(void)
{
	fwrite("\n",1,1,xfi);
}

void
gencode_menu(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];
	struct mymenu *tx;
	int k;
	bool	sub = false;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (tx = (struct mymenu *)gd->name.ItemAt(k))
		{
			switch(tx->level)
			{
				case	0:
				{
					sub = false;

					sprintf(buf,"ArrayStr(%d) = \"t*1000%4d%s\"",k,tx->msg,tx->name);

					xwrite_string(buf);
				}
				break;

				case	1:
				{
					if (strcmp(tx->name,"---") == 0)
					{
						sprintf(buf,"ArrayStr(%d) = \"-\"",k);
					}
						else
					{
						if (sub)
						{
							sprintf(buf,"ArrayStr(%d) = \"e*1000%4d%s\"",k,tx->msg,tx->name);
						}
							else
						{
							sprintf(buf,"ArrayStr(%d) = \"i*1000%4d%s\"",k,tx->msg,tx->name);
						}	
					}

					xwrite_string(buf);
				}
				break;

				case	2:
				{
					sub = true;

					sprintf(buf,"ArrayStr(%d) = \"x*1000%4d%s\"",k,tx->msg,tx->name);

					xwrite_string(buf);
				}
				break;
			}
		}
	}			

	sprintf(buf,"ArrayStr(%d) = \"q\"",k);

	xwrite_string(buf);
}

void
gencode_checkbox(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.bcheckbox.checked)
	{
		sprintf(buf,"SetChecked g%s,true",&gd->Name[0]);
		xwrite_string(buf);
	}
}

void
gencode_text(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.txt.align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetTags g%s,alignment_gadget,%d",&gd->Name[0],gd->data.txt.align);
		xwrite_string(buf);
	}
}

void
gencode_number(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.num.align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetTags g%s,alignment_gadget,%d",&gd->Name[0],gd->data.num.align);
		xwrite_string(buf);
	}
}

void
gencode_color(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.col.cellsize != 6)
	{
		sprintf(buf,"SetTags g%s,cellsize_gadget,%d",&gd->Name[0],gd->data.col.cellsize);
		xwrite_string(buf);
	}
	
	if (gd->data.col.layout != 1)
	{
		sprintf(buf,"SetTags g%s,layout_gadget,%d",&gd->Name[0],gd->data.col.layout << 2);
		xwrite_string(buf);
	}
}

void
gencode_box(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.bbox.style != B_FANCY_BORDER)
	{
		sprintf(buf,"SetTags g%s,border_gadget,%d",&gd->Name[0],gd->data.bbox.style);
		xwrite_string(buf);
	}
}

void
gencode_tab(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*str,*buf = &tmp[0];
	int k = 0;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (str = (char *)gd->name.ItemAt(k))
		{
			sprintf(buf,"AddTab g%s,\"%s\"",&gd->Name[0],str);

			xwrite_string(buf);
		}
	}	

	if (gd->data.tab.sel != 0)
	{
		sprintf(buf,"SetTags g%s,tabselect_gadget,%d",&gd->Name[0],gd->data.tab.sel);
		xwrite_string(buf);
	}

	if (gd->data.tab.tabwidth != 0)
	{
		sprintf(buf,"SetTags g%s,tabwidth_gadget,%d",&gd->Name[0],gd->data.tab.tabwidth);
		xwrite_string(buf);
	}

	if (gd->data.tab.tabheight != 19)
	{
		sprintf(buf,"SetTags g%s,tabheight_gadget,%d",&gd->Name[0],gd->data.tab.tabheight);
		xwrite_string(buf);
	}
}

void
gencode_listview(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.lv.multi)
	{
		sprintf(buf,"SetTags g%s,lvmultiselect_gadget,true",&gd->Name[0]);
		xwrite_string(buf);
	}
	
	if (gd->data.lv.sel != -1)
	{
		sprintf(buf,"SetTags g%s,lvselect_gadget,%d",&gd->Name[0],gd->data.lv.sel);
		xwrite_string(buf);
	}
}

void
gencode_outlistview(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.olv.multi)
	{
		sprintf(buf,"SetTags g%s,lvmultiselect_gadget,true",&gd->Name[0]);
		xwrite_string(buf);
	}
	
	if (gd->data.olv.sel != -1)
	{
		sprintf(buf,"SetTags g%s,lvselect_gadget,%d",&gd->Name[0],gd->data.olv.sel);
		xwrite_string(buf);
	}
}

void
gencode_radio(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*str,*dat,*buf = &tmp[0];
	int k = 0;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (str = (char *)gd->name.ItemAt(k))
		{
			sprintf(buf,"ArrayStr(%d) = \"%s\"",k,str);

			xwrite_string(buf);
		}
	}	

	sprintf(buf,"ArrayStr(%d) = \"\"",k);

	xwrite_string(buf);

	if (gd->data.rad.sel != -1)
	{
		sprintf(buf,"SetTags g%s,radio_gadget,%d",&gd->Name[0],gd->data.rad.sel);
		xwrite_string(buf);
	}
}

void
gencode_mx(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*str,*dat,*buf = &tmp[0];
	int k = 0;

	for (k = 0; k < gd->name.CountItems(); k++)
	{
		if (str = (char *)gd->name.ItemAt(k))
		{
			sprintf(buf,"ArrayStr(%d) = \"%s\"",k,str);

			xwrite_string(buf);
		}
	}	

	sprintf(buf,"ArrayStr(%d) = \"\"",k);

	xwrite_string(buf);

	if (gd->data.mx.sel != -1)
	{
		sprintf(buf,"SetTags g%s,mx_gadget,%d",&gd->Name[0],gd->data.mx.sel);
		xwrite_string(buf);
	}
}

bool
IsSameColor(rgb_color *a,rgb_color *b)
{
	if (a->red == b->red && a->green == b->green && a->blue == b->blue)
	{
		return(true);
	}

	return(false);
}	

void
gencode_slider(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];
	rgb_color blk = { 0,0,0};
	rgb_color cyg = { 80,80,80};

	if (gd->data.bslider.pos != 0)
	{
		sprintf(buf,"SetTags g%s,sliderpos_gadget,%d",&gd->Name[0],gd->data.bslider.pos);
		xwrite_string(buf);
	}

	if (gd->data.bslider.style)
	{
		sprintf(buf,"SetTags g%s,sliderstyle_gadget,true",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.bslider.hashtype)
	{
		sprintf(buf,"SetTags g%s,sliderhash_gadget,%d",&gd->Name[0],gd->data.bslider.hashtype);
		xwrite_string(buf);
	}

	if (gd->data.bslider.hashcount)
	{
		sprintf(buf,"SetTags g%s,slidercount_gadget,%d",&gd->Name[0],gd->data.bslider.hashcount);
		xwrite_string(buf);
	}

	if (!IsSameColor(&gd->data.bslider.fillcolor,&blk))
	{
		sprintf(buf,"SetTags g%s,sliderfilcol_gadget,&h%x",&gd->Name[0],(gd->data.bslider.fillcolor.red << 24) + (gd->data.bslider.fillcolor.green << 16) + (gd->data.bslider.fillcolor.blue << 8));
		xwrite_string(buf);
	}

	if (!IsSameColor(&gd->data.bslider.barcolor,&cyg))
	{
		sprintf(buf,"SetTags g%s,sliderbarcol_gadget,&h%x",&gd->Name[0],(gd->data.bslider.barcolor.red << 24) + (gd->data.bslider.barcolor.green << 16) + (gd->data.bslider.barcolor.blue << 8));
		xwrite_string(buf);
	}

	if (strcmp(&gd->data.bslider.MinLabel[0],"") != 0)
	{
		sprintf(buf,"SetTagsString g%s,sliderminlabel_gadget,\"%s\"",&gd->Name[0],&gd->data.bslider.MinLabel[0]);
		xwrite_string(buf);
	}

	if (strcmp(&gd->data.bslider.MaxLabel[0],"") != 0)
	{
		sprintf(buf,"SetTagsString g%s,slidermaxlabel_gadget,\"%s\"",&gd->Name[0],&gd->data.bslider.MaxLabel[0]);
		xwrite_string(buf);
	}
}

void
gencode_scroller(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->data.bscroller.minrange != 0 || gd->data.bscroller.maxrange != 15)
	{
		sprintf(buf,"SetRange g%s,%d,%d",&gd->Name[0],gd->data.bscroller.minrange,gd->data.bscroller.maxrange);
		xwrite_string(buf);
	}

	if (gd->data.bscroller.pos != 0)
	{
		sprintf(buf,"SetValue g%s,%d",&gd->Name[0],gd->data.bscroller.pos);
		xwrite_string(buf);
	}

	if (gd->data.bscroller.setprop != 0)
	{
		sprintf(buf,"SetProportion g%s,%d",&gd->Name[0],gd->data.bscroller.setprop);
		xwrite_string(buf);
	}

	if (gd->data.bscroller.minstep != 1 || gd->data.bscroller.maxstep != 5)
	{
		sprintf(buf,"SetSteps g%s,%d,%d",&gd->Name[0],gd->data.bscroller.minstep,gd->data.bscroller.maxstep);
		xwrite_string(buf);
	}
}

void
gencode_string(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetTags g%s,alignment_gadget,%d",&gd->Name[0],gd->align);
		xwrite_string(buf);
	}

	if (gd->data.string.maxchars != 15)
	{
		sprintf(buf,"SetTags g%s,setinteger_gadget,%d",&gd->Name[0],gd->data.string.maxchars);
		xwrite_string(buf);
	}

	if (!gd->data.string.editable)
	{
		sprintf(buf,"SetTags g%s,editable_gadget,false",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (!gd->data.string.selectable)
	{
		sprintf(buf,"SetTags g%s,selectable_gadget,false",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.string.pixdiv != gd->data.string.pixdeb)
	{
		sprintf(buf,"SetTags g%s,setdivider_gadget,%d",&gd->Name[0],gd->data.string.pixdiv);
		xwrite_string(buf);
	}
}

void
gencode_tedit(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];

	if (gd->align != B_ALIGN_LEFT)
	{
		sprintf(buf,"SetTags g%s,alignment_gadget,%d",&gd->Name[0],gd->align);
		xwrite_string(buf);
	}

	if (!gd->data.edi.selectable)
	{
		sprintf(buf,"SetTags g%s,teditselectable_gadget,false",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (!gd->data.edi.editable)
	{
		sprintf(buf,"SetTags g%s,teditable_gadget,false",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (!gd->data.edi.wordwrap)
	{
		sprintf(buf,"SetTags g%s,teditwordwrap_gadget,false",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.edi.autoident)
	{
		sprintf(buf,"SetTags g%s,teditautoident_gadget,true",&gd->Name[0]);
		xwrite_string(buf);
	}

	if (gd->data.edi.tabwidth != ((BTextView *)gd->pt)->TabWidth())
	{
		sprintf(buf,"SetTags g%s,tedittabwidth_gadget,%d",&gd->Name[0],gd->data.edi.tabwidth);
		xwrite_string(buf);
	}

	if (gd->data.edi.maxchars != ((BTextView *)gd->pt)->MaxBytes())
	{
		sprintf(buf,"SetTags g%s,teditmaxsize_gadget,%d",&gd->Name[0],gd->data.edi.maxchars);
		xwrite_string(buf);
	}
}

void
gencode_statusbar(struct MyGadget *gd,FILE *fi)
{
	char tmp[500],*buf = &tmp[0];
	rgb_color blk = { 50,150,255};

	if (gd->data.sta.barheight != 17)
	{
		sprintf(buf,"SetTags g%s,statusheight_gadget,%d",&gd->Name[0],gd->data.sta.barheight);
		xwrite_string(buf);
	}

	if (gd->data.sta.maxvalue != 100)
	{
		sprintf(buf,"SetTags g%s,statusmax_gadget,%d",&gd->Name[0],gd->data.sta.maxvalue);
		xwrite_string(buf);
	}

	if (gd->data.sta.value != 0)
	{
		sprintf(buf,"SetTags g%s,statusval_gadget,%d",&gd->Name[0],gd->data.sta.value);
		xwrite_string(buf);
	}

	if (&gd->data.sta.barcolor != &blk)
	{
		sprintf(buf,"SetTags g%s,statuscolor_gadget,&h%x",&gd->Name[0],(gd->data.sta.barcolor.red << 24) + (gd->data.sta.barcolor.green << 16) + (gd->data.sta.barcolor.blue << 8));
		xwrite_string(buf);
	}
}

void
gencode_basic(char *fichier,WrkWindow *wi)
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
		for (tt = 0; tt < wi->list.CountItems(); tt++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(tt))
			{
				if (gad->type == MX_KIND || gad->type == MENU_KIND || gad->type == RADIO_KIND)
				{
					have_mx_or_rad = true;
				}				
			}
		}						

		if (have_mx_or_rad)
		{
			sprintf(buf,"Dim ArrayStr(50) As String");

			xwrite_string(buf);
		}

		sprintf(buf,"Dim %s",title);

		xwrite_string(buf);

		for (tt = 0; tt< wi->list.CountItems(); tt++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(tt))
			{
				sprintf(buf,"Dim g%s",&gad->Name[0]);

				xwrite_string(buf);
			}	
		}

		xwrite_cr();

		for (t = 0; t < OnEnd; t++)
		{
			if (wi->idcmp & (1L << t))
			{
				char *str;
				
				if (str = array_msg[t])
				{
					bool paren = false;

					if (strchr(str,'('))
					{
						paren = true;				
					}

					sprintf(buf,"%s %s_%s%s %s",(t == OnClosed) ? "Function" : "Sub",title,str,(paren) ? "" : "()",(t == OnClosed) ? "As Boolean" : "");

					xwrite_string(buf);

					if (t == OnClosed)
					{
						strcpy(buf,"\tReturn true");
	
						xwrite_string(buf);
					}

					sprintf(buf,"End %s",(t == OnClosed) ? "Function" : "Sub");

					xwrite_string(buf);

					xwrite_cr();
				}
			}
		}	

		rct = wi->Frame();

		sprintf(buf,"%s = OpenWindow %d,%d,%d,%d",title,(int)rct.left,(int)rct.top,rct.IntegerWidth(),rct.IntegerHeight());

		xwrite_string(buf);

		wi->Lock();

		rgb_color a = wi->bck->ViewColor(),b = ui_color(B_PANEL_BACKGROUND_COLOR);

		wi->Unlock();

		if (!IsSameColor(&a,&b))
		{
			sprintf(buf,"SetBackColor %s,&h%x",title,(a.red << 24) + (a.green << 16) + (a.blue << 8));

			xwrite_string(buf);

			sprintf(buf,"Clear %s",title);

			xwrite_string(buf);
		}

		if (strcmp(&wi->WTitle[0],"") != 0)
		{
			sprintf(buf,"SetTagsString %s,title_window,\"%s\"",title,&wi->WTitle[0]);

			xwrite_string(buf);
		}

		for (t = 0; t < OnEnd; t++)
		{
			if (wi->idcmp & (1L << t))
			{
				sprintf(buf,"SetHandlerWindow %s msg_%s %s_%s",title,array2_msg[t],title,array2_msg[t]);

				xwrite_string(buf);
			}
		}	

		for (t = 0; t < wi->list.CountItems(); t++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(t))
			{
				for (k = 0; k < OnGadEnd; k++)
				{
					if (gad->idcmp & (1L << k))
					{
						switch(k)
						{
							case	0:
							{
								sprintf(buf,"Sub g%s_%s()",&gad->Name[0],message_gadget0[k]);
							}
							break;
							
							case	6:
							{
								sprintf(buf,"Function g%s_%s As Integer",&gad->Name[0],message_gadget0[k]);
							}
							break;
							
							default:
							{
								sprintf(buf,"Sub g%s_%s",&gad->Name[0],message_gadget0[k]);
							}
							break;
						}
							
						xwrite_string(buf);

						if (k != 6)
						{
							sprintf(buf,"End Sub");
						}
							else
						{
							sprintf(buf,"End Function");
						}	

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
				
				if (gad->type == SLIDER_HORIZ_KIND || gad->type == SLIDER_VERT_KIND)
				{
					val = gad->data.bslider.max;				
				}
		
				if (gad->type == MENU_KIND || gad->type == RADIO_KIND || gad->type == MX_KIND)
				{
					switch(gad->type)
					{
						case	MX_KIND:	gencode_mx(gad,xfi);	break;
						case	RADIO_KIND:	gencode_radio(gad,xfi);	break;
						case	MENU_KIND:	gencode_menu(gad,xfi);	break;
					}	

					if (gad->type == RADIO_KIND || gad->type == MX_KIND)
					{
						sprintf(buf,"g%s = CreateGadget %s,%s,%d,%d,%d,%d,ArrayStr,0",&gad->Name[0],array_type[gad->type],title,gad->x,gad->y,gad->wi,gad->he);
					}
						else
					{
						sprintf(buf,"g%s = CreateMenu ArrayStr",&gad->Name[0]);

						xwrite_string(buf);

						sprintf(buf,"AttachMenuToWindow %s,g%s",title,&gad->Name[0]);

						xwrite_string(buf);

						goto next;
					}	
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

					sprintf(buf,"g%s = CreateGadget %s,%s,%d,%d,%d,%d,\"%s\",%d",&gad->Name[0],array_type[gad->type],title,gad->x,gad->y,gad->wi,gad->he,name,val);
				}
				
				xwrite_string(buf);

				if (!gad->enable)
				{
					sprintf(buf,"SetEnabled g%s,false",&gad->Name[0]);

					xwrite_string(buf);
				}

				if (gad->flag & IS_FONTLEASING)
				{
					sprintf(buf,"SetAntiliasingGadget g%s,false",&gad->Name[0]);
					xwrite_string(buf);
				}

				switch(gad->type)
				{
					case	TAB_KIND:				gencode_tab(gad,xfi);	break;
					case	CHECKBOX_KIND:			gencode_checkbox(gad,xfi);	break;
					case	COLOR_KIND:				gencode_color(gad,xfi);	break;
					case	SLIDER_HORIZ_KIND:
					case	SLIDER_VERT_KIND:		gencode_slider(gad,xfi);	break;
					case	SCROLLER_HORIZ_KIND:	
					case	SCROLLER_VERT_KIND:		gencode_scroller(gad,xfi);	break;
					case	STRING_KIND:			
					case	INTEGER_KIND:		
					case	PASSWORD_KIND:				
					case	FLOAT_KIND:				gencode_string(gad,xfi);	break;
					case	BOX_KIND:				gencode_box(gad,xfi);	break;
					case	TEXT_KIND:				gencode_text(gad,xfi);	break;
					case	NUMBER_KIND:			gencode_number(gad,xfi);	break;
					case	STATUSBAR_KIND:			gencode_statusbar(gad,xfi);	break;
					case	LISTVIEW_KIND:
					case	LISTVIEW_HORIZ_KIND:
					case	LISTVIEW_VERT_KIND:
					case	LISTVIEW_ALL_KIND:		gencode_listview(gad,xfi);	break;
					case	OUTLISTVIEW_KIND:
					case	OUTLISTVIEW_HORIZ_KIND:
					case	OUTLISTVIEW_VERT_KIND:
					case	OUTLISTVIEW_ALL_KIND:	gencode_outlistview(gad,xfi);	break;
					case	TEDIT_KIND:
					case	TEDIT_HORIZ_KIND:
					case	TEDIT_VERT_KIND:
					case	TEDIT_ALL_KIND:			gencode_tedit(gad,xfi);	break;
next:;			}
			}
		}

		for (t = 0; t < wi->list.CountItems(); t++)
		{
			if (gad = (struct MyGadget *)wi->list.ItemAt(t))
			{
				for (k = 0; k < OnGadEnd; k++)
				{
					if (gad->idcmp & (1L << k))
					{
						sprintf(buf,"SetHandlerGadget g%s %s g%s_%s",&gad->Name[0],message_gadget[k],&gad->Name[0],message_gadget[k]);
						xwrite_string(buf);
					}
				}
			}
		}			

		fclose(xfi);

		set_sourcecode(fichier);
	}
}

void
generate_code(void)
{
	if (ProjetType == PROJET_BCC)
	{
		generate_basic();	
	}
		else
	{
		generate_ccplus();	
	}
}

void
generate_basic(void)
{
	int k;
	WrkWindow	*wk;
	char *str;
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];
	char xxx[B_PATH_NAME_LENGTH],*yak = &xxx[0];

	BDirectory dir(&ProjetPath[0]);
	BEntry et;
	
	if (dir.InitCheck() == B_OK)
	{
		RemoveDir(&ProjetPath[0]);

ok:		strcpy(yak,&ProjetPath[0]);

		for (k = 0; k < projet.CountItems(); k++)
		{
			if (wk = (WrkWindow *)projet.ItemAt(k))
			{
				sprintf(fichier,"%s/%s.bas",yak,&wk->Name[0]);

				gencode_basic(fichier,wk);
			}	
		}			
	}
		else
	{
		if (create_directory(&ProjetPath[0],0x0777) == B_OK)
		{
			goto ok;
		}
	}	
}

void
set_protection(char *file)
{
	BFile *fi;
	mode_t	md;

	if (fi = new BFile(file,B_READ_WRITE))
	{
		if (fi->InitCheck() == B_OK)
		{
			if	(fi->GetPermissions(&md) == B_NO_ERROR)
			{
				md |= S_IXUSR;
				md |= S_IXGRP;
				md |= S_IXOTH;

				fi->SetPermissions(md);
			}
		}

		delete fi;
	}		
}

void
create_script(char *chemin)
{
	BPath	path(chemin);
	FILE *fi;
	char *st,tmp[B_PATH_NAME_LENGTH],*buf = &tmp[0];

	path.Append("script");

	if ((st = path.Path()) != NULL)
	{
		if (fi = fopen(st,"w+"))
		{
			fwrite("#!/bin/sh\n",1,10,fi);

			sprintf(buf,"cd %s\n",chemin);

			fwrite(buf,1,strlen(buf),fi);

			fwrite("make\n",1,5,fi);

			fclose(fi);
		}

		set_sourcecode(st);

		set_protection(st);
	}
}

void
generate_ccplus(void)
{
	int k;
	WrkWindow	*wk;
	char *str;
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];
	char xxx[B_PATH_NAME_LENGTH],*yak = &xxx[0];

	BDirectory dir(&ProjetPath[0]);
	BEntry et;
	
	if (dir.InitCheck() == B_OK)
	{
		RemoveDir(&ProjetPath[0]);

ok:		strcpy(yak,&ProjetPath[0]);

		create_makefile(yak);

		create_application(yak);

		for (k = 0; k < projet.CountItems(); k++)
		{
			if (wk = (WrkWindow *)projet.ItemAt(k))
			{
				sprintf(fichier,"%s/%s.cpp",yak,wk->Title());

				gencode_ccplus(yak,fichier,wk);
			}	
		}			

		create_script(&ProjetPath[0]);

		if (!SysAlert("Compilation ?","Yes|No"))
		{
			sprintf(yak,"%s/script",&ProjetPath[0]);
			
			system(yak);
		}
	}
		else
	{
		if (create_directory(&ProjetPath[0],0x0777) == B_OK)
		{
			goto ok;
		}
	}	
}
