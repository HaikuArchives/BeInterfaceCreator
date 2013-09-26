#include "proto.h"
#include <ctype.h>

extern FILE *xfi;

char *msg_winevents_ccplus_gencode[] = 
{
	"void Quit(void);",
	"void DispatchMessage(BMessage *message,BHandler *target);",
	"void MessageReceived(BMessage *message);",
	"void FrameMoved(BPoint origin);",
	"void WorkspacesChanged(uint32 oldWorkspaces,uint32 newWorkspaces);",
	"void WorkspaceActivated(int32 workspace,bool active);",
	"void FrameResized(float width,float height);",
	"void Minimize(bool minimize);",
	"void Zoom(BPoint origin,float width,float height);",
	"void ScreenChanged(BRect frame,color_space mode);",
	"void MenusBeginning(void);",
	"void MenusEnded(void);",
	"void WindowActivated(bool active);",
	"void Show(void);",
	"void Hide(void);",
	"BHandler*ResolveSpecifier(BMessage *msg,int32 index,BMessage *specifier,int32 form,const char *property);",
	"status_t GetSupportedSuites(BMessage *data);",
	"status_t Perform(perform_code d,void *arg);",
	"bool QuitRequested(void);",
	"thread_id Run(void);",
	NULL
};

void
generate_header_derived_h(FILE *fi,WrkWindow *wi)
{
	char *str = "";
	struct MyGadget *gad;
	int nb,t;

	int nb_button = 0;
	int nb_tab = 0;
	int nb_checkbox = 0;
	int nb_radio = 0;
	int nb_color = 0;
	int nb_mx = 0;
	int nb_slider = 0;
	int nb_scroller = 0;
	int nb_string = 0;
	int nb_box = 0;
	int nb_text = 0;
	int nb_status = 0;
	int nb_listview = 0;
	int nb_outlistview = 0;
	int nb_tedit = 0;

	xwrite_cr(fi);

	for (t = 0; t < wi->list.CountItems(); t++)
	{
		if (gad = (struct MyGadget *)wi->list.ItemAt(t))
		{
			if (gad->derived)
			{
				sprintf(&buf[0],"#include \"%s_%s.h\"",&wi->Name[0],&gad->Name[0]);

				xwrite_string(fi,&buf[0]);	
			}
		}
	}

	xwrite_cr(fi);
}			

char *
ToLower(char *p)
{
	char tmp[128] = "",*s = &tmp[0];

	strcpy(s,p);

	while(*s) { *s = tolower(*s); s++; }

	return &tmp[0];
}

bool
add_scrollview_adress(WrkWindow *wi)
{
	struct MyGadget *gad;
	int t;

	for (t = 0; t < wi->list.CountItems(); t++)
	{
		if (gad = (struct MyGadget *)wi->list.ItemAt(t))
		{
			switch(gad->type)
			{
				case	LISTVIEW_HORIZ_KIND:
				case	LISTVIEW_VERT_KIND:
				case	LISTVIEW_ALL_KIND:
				case	OUTLISTVIEW_HORIZ_KIND:
				case	OUTLISTVIEW_VERT_KIND:
				case	OUTLISTVIEW_ALL_KIND:
				case	TEDIT_HORIZ_KIND:
				case	TEDIT_VERT_KIND:
				case	TEDIT_ALL_KIND:		return(true);	break;
			}
		}
	}
	
	return(false);		
}

void
generate_header_ccplus_window(char *path,WrkWindow *wi)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0],*str = "";
	struct MyGadget *gad;
	FILE *fi;

	int t,k,nb,idx = projet.IndexOf(wi) + 1;

	sprintf(fichier,"%s/form%d.h",path,idx);
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		generate_header_derived_h(fi,wi);

		sprintf(&buf[0],"#ifndef __Window%d",idx);

		xwrite_string(fi,&buf[0]);	

		xwrite_cr(fi);

		sprintf(&buf[0],"class Window%d : public BWindow",idx);

		xwrite_string(fi,&buf[0]);	

		xwrite_string(fi,"{\npublic:\n");	

		sprintf(&buf[0],"\tWindow%d(void);",idx);

		xwrite_string(fi,&buf[0]);	

		sprintf(&buf[0],"\t~Window%d(void);",idx);

		xwrite_string(fi,&buf[0]);	

		xwrite_cr(fi);

		nb = count_array(&msg_winevents_ccplus_gencode[0]);

		for (k = 0; k < nb; k++)
		{
			if (wi->idcmp & (1L << k))
			{
				sprintf(&buf[0],"\tvirtual %s",msg_winevents_ccplus_gencode[k]);

				xwrite_string(fi,&buf[0]);	
			}
		}
		
		xwrite_cr(fi);

		xwrite_string(fi,"\tBView *back;");	

		if (add_scrollview_adress(wi))
		{
			for (t = 0; t < wi->list.CountItems(); t++)
			{
				if (gad = (struct MyGadget *)wi->list.ItemAt(t))
				{
					switch(gad->type)
					{
						case	LISTVIEW_HORIZ_KIND:
						case	LISTVIEW_VERT_KIND:
						case	LISTVIEW_ALL_KIND:
						case	OUTLISTVIEW_HORIZ_KIND:
						case	OUTLISTVIEW_VERT_KIND:
						case	OUTLISTVIEW_ALL_KIND:
						case	TEDIT_HORIZ_KIND:
						case	TEDIT_VERT_KIND:
						case	TEDIT_ALL_KIND:
						{
							sprintf(&buf[0],"\tBScrollView *__%s;",&gad->Name[0]);
	
							xwrite_string(fi,&buf[0]);	
						}
						break;
					}
				}
			}
		}
	
		xwrite_cr(fi);

		{
			int nb_button = 0;
			int nb_tab = 0;
			int nb_checkbox = 0;
			int nb_radio = 0;
			int nb_color = 0;
			int nb_mx = 0;
			int nb_slider = 0;
			int nb_scroller = 0;
			int nb_string = 0;
			int nb_box = 0;
			int nb_text = 0;
			int nb_status = 0;
			int nb_listview = 0;
			int nb_outlistview = 0;
			int nb_tedit = 0;
			int nb_menu = 0;
			int nb_view = 0;

			for (t = 0; t < wi->list.CountItems(); t++)
			{
				if (gad = (struct MyGadget *)wi->list.ItemAt(t))
				{
					if (gad->derived)
					{
						switch(gad->type)
						{
							case	VIEW_KIND:					++nb_view;		nb = nb_view;		str = "View";			break;
							case	BUTTON_KIND:				++nb_button;	nb = nb_button;		str = "Button";			break;
							case	MX_KIND:					++nb_mx;		nb = nb_mx;			str = "MenuField";		break;
							case	TAB_KIND:					++nb_tab;		nb = nb_tab;		str = "Tab";			break;
							case	CHECKBOX_KIND:				++nb_checkbox;	nb = nb_checkbox;	str = "CheckBox";		break;
							case	RADIO_KIND:					++nb_radio;		nb = nb_radio;		str = "RadioButton";	break;
							case	COLOR_KIND:					++nb_color;		nb = nb_color;		str = "Color";			break;
							case	SLIDER_HORIZ_KIND:
							case	SLIDER_VERT_KIND:			++nb_slider;	nb = nb_slider;		str = "Slider";			break;
							case	SCROLLER_HORIZ_KIND:	
							case	SCROLLER_VERT_KIND:			++nb_scroller;	nb = nb_scroller;	str = "ScrollBar";	break;
							case	STRING_KIND:			
							case	INTEGER_KIND:		
							case	PASSWORD_KIND:				
							case	FLOAT_KIND:					++nb_string;	nb = nb_string;		str = "TextControl";		break;
							case	BOX_KIND:					++nb_box;		nb = nb_box;		str = "Box";		break;
							case	NUMBER_KIND:
							case	TEXT_KIND:					++nb_text;		nb = nb_text;		str = "StringView";		break;
							case	STATUSBAR_KIND:				++nb_status;	nb = nb_status;		str = "StatusBar";		break;
							case	LISTVIEW_KIND:
							case	LISTVIEW_HORIZ_KIND:
							case	LISTVIEW_VERT_KIND:
							case	LISTVIEW_ALL_KIND:			++nb_listview;	nb = nb_listview;	str = "ListView";	break;
							case	OUTLISTVIEW_KIND:
							case	OUTLISTVIEW_HORIZ_KIND:
							case	OUTLISTVIEW_VERT_KIND:
							case	OUTLISTVIEW_ALL_KIND:		++nb_outlistview; nb = nb_outlistview;	str = "OutlineListView";	break;
							case	TEDIT_KIND:
							case	TEDIT_HORIZ_KIND:
							case	TEDIT_VERT_KIND:
							case	TEDIT_ALL_KIND:				++nb_tedit;	nb = nb_tedit;			str = "TextView";	break;
						}
					
						if (gad->type != MENU_KIND)
						{
							sprintf(&buf[0],"\tB%s%d *%s;",str,nb,&gad->Name[0]);

							xwrite_string(fi,&buf[0]);	
						}
					}
						else
					{	
						switch(gad->type)
						{
							case	VIEW_KIND:				++nb_view;		nb = nb_view;		str = "BView";			break;
							case	BUTTON_KIND:			++nb_button;	nb = nb_button;		str = "BButton";		break;
							case	MENU_KIND:				++nb_menu;		nb = nb_menu;		str = "BMenuBar";		break;
							case	MX_KIND:				++nb_mx;		nb = nb_mx;			str = "BMenuField";		break;
							case	TAB_KIND:				++nb_tab;		nb = nb_tab;		str = "BTabView";		break;
							case	CHECKBOX_KIND:			++nb_checkbox;	nb = nb_checkbox;	str = "BCheckBox";		break;
							case	RADIO_KIND:				++nb_radio;		nb = nb_radio;		str = "BRadioButton";	break;
							case	COLOR_KIND:				++nb_color;		nb = nb_color;		str = "BColorControl";	break;
							case	SLIDER_HORIZ_KIND:
							case	SLIDER_VERT_KIND:		++nb_slider;	nb = nb_slider;		str = "BSlider";		break;
							case	SCROLLER_HORIZ_KIND:	
							case	SCROLLER_VERT_KIND:		++nb_scroller;	nb = nb_scroller;	str = "BScrollBar";		break;
							case	STRING_KIND:			
							case	INTEGER_KIND:		
							case	PASSWORD_KIND:				
							case	FLOAT_KIND:				++nb_string;	nb = nb_string;		str = "BTextControl";	break;
							case	BOX_KIND:				++nb_box;		nb = nb_box;		str = "BBox";			break;
							case	NUMBER_KIND:
							case	TEXT_KIND:				++nb_text;		nb = nb_text;		str = "BStringView";		break;
							case	STATUSBAR_KIND:			++nb_status;	nb = nb_status;		str = "BStatusBar";			break;
							case	LISTVIEW_KIND:
							case	LISTVIEW_HORIZ_KIND:
							case	LISTVIEW_VERT_KIND:
							case	LISTVIEW_ALL_KIND:		++nb_listview;	nb = nb_listview;	str = "BListView";		break;
							case	OUTLISTVIEW_KIND:
							case	OUTLISTVIEW_HORIZ_KIND:
							case	OUTLISTVIEW_VERT_KIND:
							case	OUTLISTVIEW_ALL_KIND:	++nb_outlistview; nb = nb_outlistview;	str = "BOutlineListView";	break;
							case	TEDIT_KIND:
							case	TEDIT_HORIZ_KIND:
							case	TEDIT_VERT_KIND:
							case	TEDIT_ALL_KIND:			++nb_tedit;	nb = nb_tedit;		str = "BTextView";	break;
						}

						sprintf(&buf[0],"\t%s *%s;",str,&gad->Name[0]);

						xwrite_string(fi,&buf[0]);	

						if (gad->type == MENU_KIND)
						{
							xwrite_string(fi,"\tBMenu *mn,*sb;");	
							xwrite_string(fi,"\tBMenuItem *it;");	
						}
					}
				}
			}
		}
			
		xwrite_string(fi,"};");	

		xwrite_cr(fi);

		xwrite_cr(fi);

		sprintf(&buf[0],"#define __Window%d",idx);

		xwrite_string(fi,&buf[0]);	

		xwrite_string(fi,"#endif");	

		fclose(fi);	

		set_sourcecode(fichier);
	}
}

struct MyGadget *
find_by_gadget(WrkWindow *wi,void *tr)
{
	int t;
	struct MyGadget *gad;

	for (t = 0; t < wi->list.CountItems(); t++)
	{
		if (gad = (struct MyGadget *)wi->list.ItemAt(t))
		{
			if (gad->pt == tr)
			{
				return gad;
			}
		}
	}
	
	return NULL;	
}

void
generate_code_ccplus_window(char *path,WrkWindow *wi)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	BRect rct = wi->Frame();

	int k,nb,idx = projet.IndexOf(wi) + 1;

	sprintf(fichier,"%s/form%d.cpp",path,idx);
	
	if (fi = fopen(fichier,"w+"))
	{
		BAutolock win(wi);

		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"form%d.h\"",idx);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);

		generate_header_derived_h(fi,wi);

		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(&buf[0],"Window%d::Window%d(void):BWindow(BRect(%d,%d,%d,%d),\"%s\",%s,0,%s)",idx,idx,(int)rct.left,(int)rct.top,(int)rct.right,(int)rct.bottom,&wi->WTitle[0],type_win[wi->typewin],wrk_win[wi->wrk]);

		xwrite_string(fi,&buf[0]);

		xwrite_string(fi,"{");
	
		if (wi->minw != 0 || wi->minh != 0 || wi->maxh != 32768 || wi->maxw != 32768)
		{
			sprintf(&buf[0],"\tSetSizeLimits(%d,%d,%d,%d);",wi->minw,wi->maxw,wi->minh,wi->maxh);

			xwrite_string(fi,&buf[0]);
		}

		xwrite_string(fi,"\tback = new BView(Bounds(),\"\",B_FOLLOW_ALL,B_WILL_DRAW);");

		rgb_color cl = wi->bck->ViewColor(),white = { 255,255,255 };

		if (!IsSameColor(&cl,&white))
		{
			sprintf(&buf[0],"\tback->SetViewColor(%d,%d,%d);",cl.red,cl.green,cl.blue);

			xwrite_string(fi,&buf[0]);
		}	

		{
			char *str = "";
			struct MyGadget *gad;
			int t;

			int nb_button = 0;
			int nb_tab = 0;
			int nb_checkbox = 0;
			int nb_radio = 0;
			int nb_color = 0;
			int nb_mx = 0;
			int nb_slider = 0;
			int nb_scroller = 0;
			int nb_string = 0;
			int nb_box = 0;
			int nb_text = 0;
			int nb_status = 0;
			int nb_listview = 0;
			int nb_outlistview = 0;
			int nb_tedit = 0;
			int nb_menu = 0;
			int nb_view = 0;

			for (t = 0; t < wi->list.CountItems(); t++)
			{
				if (gad = (struct MyGadget *)wi->list.ItemAt(t))
				{
					int x = gad->x,y = gad->y,wi = gad->x + gad->wi,he = gad->y + gad->he;

					if (gad->parent)
					{
						BRect rct = gad->pt->Frame();						
						
						x = (int)rct.left;
						y = (int)rct.top;
						wi = (int)rct.Width();
						he = (int)rct.Height();
					}

					if (gad->derived)
					{
						switch(gad->type)
						{
							case	VIEW_KIND:					++nb_view;		nb = nb_view;	str = "View";			break;
							case	BUTTON_KIND:				++nb_button;	nb = nb_button;	str = "Button";			break;
							case	MX_KIND:					++nb_mx;		nb = nb_mx;	str = "MenuField";					break;
							case	TAB_KIND:					++nb_tab;		nb = nb_tab;	str = "Tab";			break;
							case	CHECKBOX_KIND:				++nb_checkbox;	nb = nb_checkbox;	str = "CheckBox";	break;
							case	RADIO_KIND:					++nb_radio;		nb = nb_radio;	str = "RadioButton";			break;
							case	COLOR_KIND:					++nb_color;		nb = nb_color;	str = "Color";			break;
							case	SLIDER_HORIZ_KIND:
							case	SLIDER_VERT_KIND:			++nb_slider;	nb = nb_slider;	str = "Slider";			break;
							case	SCROLLER_HORIZ_KIND:	
							case	SCROLLER_VERT_KIND:			++nb_scroller;	nb = nb_scroller;	str = "ScrollBar";	break;
							case	STRING_KIND:			
							case	INTEGER_KIND:		
							case	PASSWORD_KIND:				
							case	FLOAT_KIND:					++nb_string;	nb = nb_string;	str = "TextControl";		break;
							case	BOX_KIND:					++nb_box;		nb = nb_box;	str = "Box";		break;
							case	NUMBER_KIND:
							case	TEXT_KIND:					++nb_text;		nb = nb_text;	str = "StringView";		break;
							case	STATUSBAR_KIND:				++nb_status;	nb = nb_status;	str = "StatusBar";		break;
							case	LISTVIEW_KIND:
							case	LISTVIEW_HORIZ_KIND:
							case	LISTVIEW_VERT_KIND:
							case	LISTVIEW_ALL_KIND:			++nb_listview;	nb = nb_listview;	str = "ListView";	break;
							case	OUTLISTVIEW_KIND:
							case	OUTLISTVIEW_HORIZ_KIND:
							case	OUTLISTVIEW_VERT_KIND:
							case	OUTLISTVIEW_ALL_KIND:		++nb_outlistview; nb = nb_outlistview;	str = "OutlineListView";	break;
							case	TEDIT_KIND:
							case	TEDIT_HORIZ_KIND:
							case	TEDIT_VERT_KIND:
							case	TEDIT_ALL_KIND:				++nb_tedit;	nb = nb_tedit;		str = "TextView";	break;
						}
					
						sprintf(&buf[0],"\t%s = new B%s%d(BRect(%d,%d,%d,%d));",&gad->Name[0],str,nb,x,y,x + wi,y + he);

						xwrite_string(fi,&buf[0]);	
					
						switch(gad->type)
						{
							case	LISTVIEW_HORIZ_KIND:
							case	LISTVIEW_VERT_KIND:
							case	LISTVIEW_ALL_KIND:
							case	OUTLISTVIEW_HORIZ_KIND:
							case	OUTLISTVIEW_VERT_KIND:
							case	OUTLISTVIEW_ALL_KIND:
							case	TEDIT_HORIZ_KIND:
							case	TEDIT_VERT_KIND:
							case	TEDIT_ALL_KIND:
							{
								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,false,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));

								xwrite_string(fi,&buf[0]);	
							}
							break;
						}
					}
						else
					{
						switch(gad->type)
						{
							case	VIEW_KIND:
							{
								sprintf(&buf[0],"\t%s = new BView(BRect(%d,%d,%d,%d),\"%s\",%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	BUTTON_KIND:
							{
								sprintf(&buf[0],"\t%s = new BButton(BRect(%d,%d,%d,%d),\"%s\",\"%s\",new BMessage((uint32)%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],gad->msg,GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	CHECKBOX_KIND:
							{
								sprintf(&buf[0],"\t%s = new BCheckBox(BRect(%d,%d,%d,%d),\"%s\",\"%s\",new BMessage((uint32)%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],gad->msg,GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	BOX_KIND:
							{
								sprintf(&buf[0],"\t%s = new BBox(BRect(%d,%d,%d,%d),\"%s\",%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	RADIO_KIND:
							{
								sprintf(&buf[0],"\t%s = new BRadioButton(BRect(%d,%d,%d,%d),\"%s\",\"%s\",new BMessage((uint32)%d));",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],gad->msg);
							}
							break;	

							case	COLOR_KIND:
							{
								sprintf(&buf[0],"\t%s = new BColorControl(BPoint(%d,%d),B_CELLS_32x8,8,\"%s\",new BMessage((uint32)%d));",&gad->Name[0],x,y,GetTitle(gad),gad->msg);
							}
							break;	

							case	SLIDER_HORIZ_KIND:
							case	SLIDER_VERT_KIND:
							{
								sprintf(&buf[0],"\t%s = new BSlider(BRect(%d,%d,%d,%d),\"%s\",\"%s\",new BMessage((uint32)%d),0,100,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],gad->msg,orientation_str[(gad->type == SLIDER_HORIZ_KIND) ? 0 : 1]);
							}
							break;	

							case	SCROLLER_VERT_KIND:
							case	SCROLLER_HORIZ_KIND:
							{
								sprintf(&buf[0],"\t%s = new BScrollBar(BRect(%d,%d,%d,%d),\"%s\",NULL,0,100,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),orientation_str[(gad->type == SCROLLER_HORIZ_KIND) ? 0 : 1]);
							}
							break;	

							case	STATUSBAR_KIND:
							{
								sprintf(&buf[0],"\t%s = new BStatusBar(BRect(%d,%d,%d,%d),\"%s\",\"%s\");",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0]);
							}
							break;	

							case	TAB_KIND:
							{
								int tb = 0;

								switch(gad->data.tab.tabwidth)
								{
									case	B_WIDTH_FROM_WIDEST:	tb = 0;		break;
									case	B_WIDTH_AS_USUAL:		tb = 1;		break;
									case	B_WIDTH_FROM_LABEL:		tb = 2;		break;
								}

								sprintf(&buf[0],"\t%s = new BTabView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),mtab_width[tb],GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	FLOAT_KIND:			
							case	INTEGER_KIND:		
							case	PASSWORD_KIND:				
							case	STRING_KIND:
							{
								sprintf(&buf[0],"\t%s = new BTextControl(BRect(%d,%d,%d,%d),\"%s\",\"%s\",NULL,new BMessage((uint32)%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],gad->msg,GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	MENU_KIND:
							{
								sprintf(&buf[0],"\t%s = new BMenuBar(BRect(%d,%d,%d,%d),\"%s\");",&gad->Name[0],x,y,wi,he,GetTitle(gad));

								xwrite_string(fi,&buf[0]);	

								generate_code_menu(fi,gad);
							}
							break;	

							case	MX_KIND:
							{
								sprintf(&buf[0],"\t%s = new BMenuField(BRect(%d,%d,%d,%d),\"%s\",\"%s\",new BMenu(\"\"),new BMessage((uint32)%d));",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],gad->msg,orientation_str[(gad->type == SCROLLER_HORIZ_KIND) ? 0 : 1]);
							}
							break;	

							case	TEXT_KIND:
							case	NUMBER_KIND:
							{
								sprintf(&buf[0],"\t%s = new BStringView(BRect(%d,%d,%d,%d),\"%s\",\"%s\",%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),&gad->Title[0],GetAlign(gad),GetFlagView(gad->view));
							}
							break;	

							case	TEDIT_KIND:
							{
								sprintf(&buf[0],"\t%s = new BTextView(BRect(%d,%d,%d,%d),\"%s\",BRect(%d,%d,%d,%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),x,y,wi,he,GetAlign(gad),GetFlagView(gad->view));
							}
							break;

							case	TEDIT_HORIZ_KIND:
							{
								sprintf(&buf[0],"\t%s = new BTextView(BRect(%d,%d,%d,%d),\"%s\",BRect(%d,%d,%d,%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),x,y,wi,he,GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,false,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	TEDIT_VERT_KIND:
							{
								sprintf(&buf[0],"\t%s = new BTextView(BRect(%d,%d,%d,%d),\"%s\",BRect(%d,%d,%d,%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),x,y,wi,he,GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,false,true,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	TEDIT_ALL_KIND:
							{
								sprintf(&buf[0],"\t%s = new BTextView(BRect(%d,%d,%d,%d),\"%s\",BRect(%d,%d,%d,%d),%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),x,y,wi,he,GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,true,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	LISTVIEW_KIND:
							{
								sprintf(&buf[0],"\t%s = new BListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.lv.multi],GetAlign(gad),GetFlagView(gad->view));
							}
							break;

							case	LISTVIEW_HORIZ_KIND:
							{
								sprintf(&buf[0],"\t%s = new BListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.lv.multi],GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,false,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	LISTVIEW_VERT_KIND:
							{
								sprintf(&buf[0],"\t%s = new BListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.lv.multi],GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,false,true,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	LISTVIEW_ALL_KIND:
							{
								sprintf(&buf[0],"\t%s = new BListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.lv.multi],GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,true,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	OUTLISTVIEW_KIND:
							{
								sprintf(&buf[0],"\t%s = new BOutlineListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.olv.multi],GetAlign(gad),GetFlagView(gad->view));
							}
							break;

							case	OUTLISTVIEW_HORIZ_KIND:
							{
								sprintf(&buf[0],"\t%s = new BOutlineListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.olv.multi],GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,false,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	OUTLISTVIEW_VERT_KIND:
							{
								sprintf(&buf[0],"\t%s = new BOutlineListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.olv.multi],GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,false,true,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;

							case	OUTLISTVIEW_ALL_KIND:
							{
								sprintf(&buf[0],"\t%s = new BOutlineListView(BRect(%d,%d,%d,%d),\"%s\",%s,%s,%s);",&gad->Name[0],x,y,wi,he,GetTitle(gad),selection_lv[gad->data.olv.multi],GetAlign(gad),GetFlagView(gad->view));

								xwrite_string(fi,&buf[0]);	

								sprintf(&buf[0],"\t__%s = new BScrollView(\"\",%s,B_FOLLOW_LEFT|B_FOLLOW_TOP,B_WILL_DRAW|B_NAVIGABLE,true,true,B_FANCY_BORDER);",&gad->Name[0],GetTitle(gad));
							}
							break;
						}
				
						if (gad->type != MENU_KIND)
						{
							xwrite_string(fi,&buf[0]);	
						}
					}	
				}
			}
		}	

		xwrite_cr(fi);

		{
			char tmp[512];

			struct MyGadget *gad;
			int t;

			for (t = 0; t < wi->list.CountItems(); t++)
			{
				if (gad = (struct MyGadget *)wi->list.ItemAt(t))
				{
					switch(gad->type)
					{
						case	FLOAT_KIND:			
						case	INTEGER_KIND:		
						case	PASSWORD_KIND:				
						case	STRING_KIND:
						case	BUTTON_KIND:
						case	CHECKBOX_KIND:
						case	BOX_KIND:
						case	VIEW_KIND:
						case	RADIO_KIND:
						case	COLOR_KIND:
						case	OUTLISTVIEW_KIND:
						case	SLIDER_HORIZ_KIND:
						case	SLIDER_VERT_KIND:
						case	SCROLLER_VERT_KIND:
						case	SCROLLER_HORIZ_KIND:
						case	STATUSBAR_KIND:
						case	TAB_KIND:
						case	MENU_KIND:
						case	MX_KIND:
						case	TEXT_KIND:
						case	NUMBER_KIND:
						case	TEDIT_KIND:
						case	LISTVIEW_KIND:
						{
							sprintf(&buf[0],&gad->Name[0]);
						}
						break;	

						case	TEDIT_HORIZ_KIND:
						case	TEDIT_VERT_KIND:
						case	TEDIT_ALL_KIND:
						case	LISTVIEW_HORIZ_KIND:
						case	LISTVIEW_VERT_KIND:
						case	LISTVIEW_ALL_KIND:
						case	OUTLISTVIEW_HORIZ_KIND:
						case	OUTLISTVIEW_VERT_KIND:
						case	OUTLISTVIEW_ALL_KIND:
						{
							sprintf(&buf[0],"__%s",&gad->Name[0]);
						}
						break;
					}	

					{
						char xt[256],jp[256];
						
						strcpy(&jp[0],ToLower(&buf[0]));					

						if (!gad->parent)
						{
							sprintf(&tmp[0],"\tback->AddChild(%s);",&jp[0]);

							xwrite_string(fi,&tmp[0]);	
						}
							else
						{
							strcpy(&xt[0],ToLower(&gad->parent->Name[0]));					

							sprintf(&tmp[0],"\t%s->AddChild(%s);",&xt[0],&jp[0]);

							xwrite_string(fi,&tmp[0]);	
						}
					}
				}
			}
		}	

		xwrite_string(fi,"\tAddChild(back);");

		xwrite_string(fi,"\tShow();");

		xwrite_string(fi,"}");

		xwrite_cr(fi);

		sprintf(&buf[0],"Window%d::~Window%d(void)\n{",idx,idx);

		xwrite_string(fi,&buf[0]);

		if (!(wi->idcmp & (1L << 18)))
		{
			xwrite_string(fi,"\tbe_app->PostMessage(B_QUIT_REQUESTED);");
		}
		
		xwrite_string(fi,"}\n");

		nb = count_array(&msg_winevents_ccplus_gencode[0]);

		for (k = 0; k < nb; k++)
		{
			if (wi->idcmp & (1L << k))
			{
				char *fd,tmp[512];
				
				strcpy(&tmp[0],msg_winevents_ccplus_gencode[k]);

				if (fd = strchr(&tmp[0],' '))
				{
					*fd++ = '\0';

					xwrite_string(fi,&tmp[0]);

					sprintf(&buf[0],"Window%d::%s",idx,fd);

					buf[strlen(&buf[0]) - 1] = 0;

					xwrite_string(fi,&buf[0]);	

					xwrite_string(fi,"{");

					if (k == 18)
					{
						xwrite_string(fi,"\tbe_app->PostMessage(B_QUIT_REQUESTED);");
						xwrite_string(fi,"\treturn true;");
					}

					xwrite_string(fi,"}");

					xwrite_cr(fi);
				}
			}
		}

		fclose(fi);	

		set_sourcecode(fichier);
	}
}
