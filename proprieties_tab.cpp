#include "proto.h"

char *tab_width[] = 
{
	"WITH_AS_USUAL",
	"FROM_WIDEST",
	NULL
};	

char
*GetStyleSlider(int nb)
{
	switch(nb)
	{
		case	B_BLOCK_THUMB:		return("BLOCK");	break;
		case	B_TRIANGLE_THUMB:	return("TRIANGLE");	break;
	}	
}

char
*GetStyleSliderHash(int nb)
{
	switch(nb)
	{
		case	B_HASH_MARKS_NONE:		return("HASH_NONE");	break;
		case	B_HASH_MARKS_TOP:		return("HASH_TOP");		break;
		case	B_HASH_MARKS_BOTTOM:	return("HASH_BOTTOM");	break;
		case	B_HASH_MARKS_BOTH:		return("HASH_BOTH");	break;
	}
}

char
*GetStringColor(rgb_color *cl)
{
	static char buf[256];
	
	sprintf(&buf[0],"%d,%d,%d",cl->red,cl->green,cl->blue);

	return(&buf[0]);
}

char *
GetBoolean(bool ret)
{
	return((ret) ? "True" : "False");
}

char *
GetAlignmentStyleStr(int nb)
{
	switch(nb)
	{
		case 	0: return("ALIGN_LEFT");	break;
		case 	1: return("ALIGN_RIGHT");	break;
		case 	2: return("ALIGN_CENTER");	break;
	}

	return "";
}

char *
GetStyleBBox(int style)
{
	switch(style)
	{
		case	B_PLAIN_BORDER:	return("PLAIN_BORDER");	break;	
		case	B_FANCY_BORDER:	return("FANCY_BORDER");	break;	
		case	B_NO_BORDER:	return("NO_BORDER");	break;	
	}

	return("");
}

char *
GetLayoutColor(int lay)
{
	switch(lay)
	{
		case	0:	return("4x64");		break;
		case	1:	return("8x32");		break;
		case	2:	return("16x16");	break;
		case	3:	return("64x4");		break;
		case	4:	return("32x8");		break;
	}
}

char *GetStyleWindow[] = 
{
	"TITLED_WINDOW",
	"BORDERED_WINDOW",
	"MODAL_WINDOW",
	"FLOATING_WINDOW",
	"NO_BORDER_WINDOW",
	"DOCUMENT_WINDOW",
	NULL
};

void
GetBufferData_Window(int k,char *str)
{
	BAutolock win(DefWin);
	float a,b,c,d;
	WrkWindow *wi = (WrkWindow *)DefWin;
	BRect ft = wi->Frame();
	uint32 vt = wi->Flags();

	wi->GetSizeLimits(&a,&b,&c,&d);

	strcpy(str,"");

	switch(k)
	{
		case	WCaption:	strcpy(str,wi->Title());			break;
		case	WHeight:	sprintf(str,"%d",ft.IntegerHeight());	break;
		case	WLeft:		sprintf(str,"%d",(int)ft.left);			break;
		case	WTop:		sprintf(str,"%d",(int)ft.top);			break;
		case	WWidth:		sprintf(str,"%d",ft.IntegerWidth());	break;

		case	WStyle:
		{
			strcpy(str,GetStyleWindow[wi->Style]);
		}
		break;

		case	WVisible:
		{
			strcpy(str,GetBoolean(wi->Visible));
		}
		break;

		case	WResizable:
		{
			strcpy(str,GetBoolean( wi->Resizable));
		}
		break;

		case	WClosable:
		{
			strcpy(str,GetBoolean( wi->Closable));
		}
		break;

		case	WMinimizable:
		{
			strcpy(str,GetBoolean( wi->Minimizable));
		}
		break;

		case	WMovable:
		{
			strcpy(str,GetBoolean( wi->Movable));
		}
		break;

		case	WZoomable:
		{
			strcpy(str,GetBoolean( wi->Zoomable));
		}
		break;

		case	WResizeMode:
		{
			strcpy(str,GetBoolean(wi->ResizeMode));
		}
		break;

		case	WViewColor:
		{
			rgb_color col0 = wi->bck->ViewColor();
			sprintf(str,"%d,%d,%d",col0.red,col0.green,col0.blue);
		}
		break;

		case	WHighColor:
		{
			rgb_color col1 = wi->bck->HighColor();
			sprintf(str,"%d,%d,%d",col1.red,col1.green,col1.blue);
		}
		break;

		case	WminWsize:	sprintf(str,"%d",(int)a);	break;
		case	WminHsize:	sprintf(str,"%d",(int)b);	break;
		case	WmaxWsize:	sprintf(str,"%d",(int)c);	break;
		case	WmaxHsize:	sprintf(str,"%d",(int)d);	break;
	}
}

void
GetBufferData_Button(int k,char *str)
{
}

void
GetBufferData_Mx(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	mx_Divider:		sprintf(str,"%d",gd->data.mx.pixdiv);						break;
//		case	mx_Selected:	sprintf(str,"%d",gd->data.mx.sel);							break;

		case	mx_Align:
		{
			strcpy(str,GetAlignmentStyleStr(gd->align));
		}
		break;
	}
}

void
GetBufferData_Radio(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	strcpy(str,"");
	
	switch(k)
	{
		case	rad_Selected:	sprintf(str,"%d",gd->data.rad.sel);		break;
		case	rad_Width:		sprintf(str,"%d",gd->wi);				break;
		case	rad_Height:		sprintf(str,"%d",gd->he);				break;
	}
}

void
GetBufferData_BBox(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	bbox_Style:
		{
			if (str) strcpy(str,GetStyleBBox(gd->data.bbox.style));
		}
		break;
	}
}

void
GetBufferData_CheckBox(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	che_Checked:
		{
			strcpy(str,GetBoolean(gd->data.bcheckbox.checked));	
		}
		break;
	}
}

void
GetBufferData_Scroller(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	scr_Min:		sprintf(str,"%d",gd->data.bscroller.minrange);	break;
		case	scr_Max:		sprintf(str,"%d",gd->data.bscroller.maxrange);	break;
		case	scr_Pos:		sprintf(str,"%d",gd->data.bscroller.pos);		break;
		case	scr_Setprop:	sprintf(str,"%d",gd->data.bscroller.setprop);	break;
		case	scr_Minstep:	sprintf(str,"%d",gd->data.bscroller.minstep);	break;
		case	scr_Maxstep:	sprintf(str,"%d",gd->data.bscroller.maxstep);	break;
	}
}

void
GetBufferData_Slider(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	sli_Min:		sprintf(str,"%d",gd->data.bslider.min);						break;
		case	sli_Max:		sprintf(str,"%d",gd->data.bslider.max);						break;
		case	sli_Pos:		sprintf(str,"%d",gd->data.bslider.pos);						break;
		case	sli_Keyinc:		sprintf(str,"%d",gd->data.bslider.keyinc);					break;
//		case	sli_Minlabel:	strcpy(str,(gd->data.bslider.minlabel) ? gd->data.bslider.minlabel : "");					break;
//		case	sli_Maxlabel:	strcpy(str,(gd->data.bslider.maxlabel) ? gd->data.bslider.maxlabel : "");					break;

		case	sli_Fillcolor:
		{
			strcpy(str,GetStringColor(&gd->data.bslider.fillcolor));
		}
		break;

		case	sli_Barcolor:
		{
			strcpy(str,GetStringColor(&gd->data.bslider.barcolor));
		}
		break;

		case	sli_Style:
		{
			strcpy(str,GetStyleSlider(gd->data.bslider.style));
		}
		break;

		case	sli_Hashstyle:
		{
			strcpy(str,GetStyleSliderHash(gd->data.bslider.hashtype));
		}
		break;

		case	sli_Fillall:
		{
			strcpy(str,GetBoolean(gd->data.bslider.fillall));
		}
		break;

		case	sli_Hashcount:
		{
			sprintf(str,"%d",gd->data.bslider.hashcount);
		}
		break;
	}
}

void
GetBufferData_Integer(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	int_Value:		sprintf(str,"%d",gd->data.string.value);				break;
		case	int_Divider:	sprintf(str,"%d",gd->data.string.pixdiv);				break;
		case	int_MaxChars:	sprintf(str,"%d",gd->data.string.maxchars);			break;

		case	int_NegValue:
		{
			strcpy(str,GetBoolean(gd->data.string.negvalue));
		}
		break;

		case	int_Align:
		{
			strcpy(str,GetAlignmentStyleStr(gd->align));
		}
		break;

		case	int_Selectable:
		{
			strcpy(str,GetBoolean(gd->data.string.selectable));
		}
		break;

		case	int_Editable:
		{
			strcpy(str,GetBoolean(gd->data.string.editable));
		}
		break;
	}
}

void
GetBufferData_String(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	str_MaxChars:	sprintf(str,"%d",gd->data.string.maxchars);					break;
		case	str_Divider:	sprintf(str,"%d",gd->data.string.pixdiv);					break;

//		case	str_Text:		strcpy(str,(gd->data.string.txt) ? gd->data.string.txt : "");	break;

		case	str_Align:
		{
			strcpy(str,GetAlignmentStyleStr(gd->align));	
		}
		break;

		case	str_Selectable:
		{
			strcpy(str,GetBoolean(gd->data.string.selectable));
		}
		break;

		case	str_Editable:
		{
			strcpy(str,GetBoolean(gd->data.string.editable));
		}
		break;

		case	but_AntiLiasing:
		{
			sprintf(str,"%s",(gd->flag & IS_FONTLEASING) ? GetBoolean(true) : GetBoolean(false));
		}
		break;

		case	but_Disabled:
		{
			sprintf(str,"%s",(gd->flag & IS_DISABLED) ? GetBoolean(true) : GetBoolean(false));
		}
		break;
	}
}

void
GetBufferData_Float(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	flo_Value:
		{
			bool debut = false;
			char *fd,c,*deb;

			sprintf(str,"%f",gd->data.string.value);

			if (fd = strchr(str,'.'))
			{
				deb = fd;

				fd = fd + 1;
			
				if (*fd != '0') debut = true;
	
				while (c = *fd)
				{
					if (c == '0')
					{
						*fd = 0;
						break;
					}

					fd++;
				}

				if (!debut) *deb = 0;
			}
		}
		break;

		case	flo_Divider:	sprintf(str,"%d",gd->data.string.pixdiv);				break;
		case	flo_MaxChars:	sprintf(str,"%d",gd->data.string.maxchars);			break;

		case	flo_Align:
		{
			strcpy(str,GetAlignmentStyleStr(gd->align));
		}
		break;

		case	flo_Selectable:
		{
			strcpy(str,GetBoolean(gd->data.string.selectable));
		}
		break;

		case	flo_AcceptVir:
		{
			strcpy(str,GetBoolean(gd->data.string.acceptvir));
		}
		break;

		case	flo_NegValue:
		{
			strcpy(str,GetBoolean(gd->data.string.negvalue));
		}
		break;


		case	flo_Editable:
		{
			strcpy(str,GetBoolean(gd->data.string.editable));
		}
		break;
	}
}

void
GetBufferData_PP(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	pp_Width:		sprintf(str,"%d",gd->wi);								break;
		case	pp_Height:		sprintf(str,"%d",gd->he);								break;
		case	pp_MaxChars:	sprintf(str,"%d",gd->data.string.maxchars);					break;
		case	pp_Divider:		sprintf(str,"%d",gd->data.string.pixdiv);					break;

//		case	pp_Text:		strcpy(str,(gd->data.string.txt) ? gd->data.string.txt : "");	break;
		case	pp_Char:		sprintf(str,"%c",gd->data.string.car);						break;

		case	pp_Align:
		{
			strcpy(str,GetAlignmentStyleStr(gd->align));	
		}
		break;

		case	pp_Selectable:
		{
			strcpy(str,GetBoolean(gd->data.string.selectable));
		}
		break;

		case	pp_Editable:
		{
			strcpy(str,GetBoolean(gd->data.string.editable));
		}
		break;
	}
}

void
GetBufferData_Status(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	sta_BarHeight:	sprintf(str,"%d",gd->data.sta.barheight);					break;
		case	sta_MaxValue:	sprintf(str,"%d",gd->data.sta.maxvalue);					break;
		case	sta_Value:		sprintf(str,"%d",gd->data.sta.value);					break;

//		case	sta_Trail:		strcpy(str,(gd->data.sta.trail) ? gd->data.sta.trail : "");	break;

		case	sta_BarColor:
		{
			strcpy(str,GetStringColor(&gd->data.sta.barcolor));	
		}
		break;
	}
}

void
GetBufferData_Color(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{	
		case	col_Value:
		{
			strcpy(str,GetStringColor(&gd->data.col.value));
		}
		break;
		
		case	col_CellSize:	sprintf(str,"%d",gd->data.col.cellsize);			break;

		case	col_Layout:
		{
			sprintf(str,GetLayoutColor(gd->data.col.layout));
		}
		break;
	}
}

void
GetBufferData_Texte(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
//		case	txt_Text:		strcpy(str,(gd->data.txt.txt) ? gd->data.txt.txt : "");	break;

		case	txt_Alignment:
		{
			sprintf(str,GetAlignmentStyleStr(gd->align));
		}
		break;
	}
}

void
GetBufferData_Number(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	num_Caption:	strcpy(str,&gd->Name[0]);						break;
		case	num_Width:		sprintf(str,"%d",gd->wi);						break;
		case	num_Height:		sprintf(str,"%d",gd->he);						break;
		case	num_Number:		sprintf(str,"%d",gd->data.num.val);						break;

		case	num_Alignment:
		{
			sprintf(str,GetAlignmentStyleStr(gd->align));
		}
		break;
	}
}

void
GetBufferData_Tab(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	tab_TabHeight:	sprintf(str,"%d",gd->data.tab.tabheight);	break;
		case	tab_Select:		sprintf(str,"%d",gd->data.tab.sel);			break;

		case	tab_TabWidth:
		{
			strcpy(str,tab_width[gd->data.tab.tabwidth]);
		}
		break;
	}
}

void
GetBufferData_Menu(int k,char *str)
{
}

void
GetBufferData_EText(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	edi_MaxChars:	sprintf(str,"%d",gd->data.edi.maxchars);			break;
		case	edi_TabWidth:	sprintf(str,"%d",gd->data.edi.tabwidth);			break;

		case	edi_WordWrap:
		{
			strcpy(str,GetBoolean(gd->data.edi.wordwrap));
		}
		break;

		case	edi_AutoIdent:
		{
			strcpy(str,GetBoolean(gd->data.edi.autoident));
		}
		break;

		case	edi_Align:
		{
			strcpy(str,GetAlignmentStyleStr(gd->align));
		}
		break;

		case	edi_Selectable:
		{
			strcpy(str,GetBoolean(gd->data.edi.selectable));
		}
		break;

		case	edi_Editable:
		{
			strcpy(str,GetBoolean(gd->data.edi.editable));
		}
		break;
	}
}

void
GetBufferData_ListView(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	lv_MultiSel:
		{
			sprintf(str,GetBoolean(gd->data.lv.multi));
		}
		break;

		case	lv_Sel:
		{
			sprintf(str,"%d",gd->data.lv.sel);
		}
		break;
	}
}

void
GetBufferData_OutListView(int k,char *str)
{
	struct MyGadget *gd = DefWin->sellist.ItemAt(0);

	switch(k)
	{
		case	lv_MultiSel:
		{
			sprintf(str,GetBoolean(gd->data.lv.multi));
		}
		break;

		case	lv_Sel:
		{
			sprintf(str,"%d",gd->data.lv.sel);
		}
		break;
	}
}
