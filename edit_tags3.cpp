#include "proto.h"
#include "edit_tags.h"

extern void	ChangeColor(int id,rgb_color cl);
extern void	ChangeFlags(int item,bool set);

const uint32 BEAIM_NEW_COLOR_PICKED = 'nCLR';

bool
is_title_available(char *txt)
{
	WrkWindow *wi;
	struct MyGadget *gd;
	int i,k;

	for (k = 0; k < projet.CountItems(); k++)
	{
		if (wi = (WrkWindow *)projet.ItemAt(k))
		{
			if (strcmp(txt,&wi->Name[0]) == 0)
			{
				return(false);
			}

			for (i = 0; i < wi->list.CountItems(); i++)
			{
				if	(gd = wi->list.ItemAt(i))
				{
					if (strcmp(txt,&wi->Name[0]) == 0)
					{
						return(false);
					}
				}
			}
		}
	}

	return(true);
}

void
EditButtonWindow::FrameResized(float wi,float he)
{
	BScrollBar *xi;

	BWindow::FrameResized(wi,he);

	if (idcmp)
	{
		if (xi = idcmp->ScrollBar(B_HORIZONTAL))
		{
			xi->Invalidate();
		}

		if (xi = idcmp->ScrollBar(B_VERTICAL))
		{
			xi->Invalidate();
		}	
	}
	
	if (lv)
	{
		if (xi = lv->ScrollBar(B_VERTICAL))
		{
			xi->Invalidate();
		}	
	}

	prefs.editorwinrect = Frame();
}

void
EditButtonWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	prefs.editorwinrect = Frame();
}

void 
EditButtonWindow::WindowActivated(bool act)
{
	BWindow::WindowActivated(act);
}

void 
EditButtonWindow::OpenColorPicker( BMessage* msg )
{

	int cid;
	BRect frame(0,0,312,110);
	BPoint lt = this->Frame().LeftTop();
	rgb_color* startColor;
	void *pt;
	BString title;
	ssize_t size;

	cid = msg->FindInt32("cid");
	msg->FindPointer("pt",(void **)&pt);

	msg->FindData( "color",B_RGB_COLOR_TYPE,(const void**)&startColor,&size );
	
	frame.OffsetTo( lt.x + 20,lt.y + 40 );
	ColorPickerWindow* stuff = new ColorPickerWindow( frame,GetMessage(msg_color),cid,this,pt);

	stuff->SetTheColor( *startColor );
	stuff->Show();
}

void
EditButtonWindow::SetNewColor( BMessage *msg)
{
	int cid;
	rgb_color cl,*startColor;
	ssize_t size;
	
	cid = msg->FindInt32("cid");
	msg->FindData( "color",B_RGB_COLOR_TYPE,(const void**)&startColor,&size );

	cl.red 		= startColor->red;
	cl.green 	= startColor->green;
	cl.blue 	= startColor->blue;

	ChangeColor(cid,cl);
}

void
ChangeGadgetLabel(struct MyGadget *gad,char *txt)
{
	BControl *xt;
	BAutolock win(gad->pt->Window());
	
	if (xt = (BControl *)gad->pt->ChildAt(0))
	{
		if (is_kind_of(xt,BControl))
		{
			xt->SetLabel(txt);		
		}	
	}
}

void
EditButtonWindow::MessageReceived(BMessage *msg)
{
	BMessage mymsg(51000);
	int32 id,vl;
	BTextControl *xt = NULL;
	char *txt = "";
	WrkWindow *win = DefWin,*wi = OldWindow;

	msg->FindInt32("be:value",&vl);
	msg->FindInt32("index",&id);

	if (msg->FindPointer("source",(void **)&xt) == B_OK)
	{
		if (is_instance_of(xt,BTextControl))
		{
			txt = xt->Text();		
		}	
	}

	switch(msg->what)
	{
		case	73500:
		case	73501:
		case	73502:
		{
			CheckItemBox *it;
			int k;

			for (k = 0; k < idcmp->CountItems(); k++)
			{
				if (it = (CheckItemBox *)idcmp->ItemAt(k))
				{
					switch(msg->what)
					{
						case	73500:	it->checked = true;		break;
						case	73501:	it->checked = false;	break;
						case	73502:	it->checked = !it->checked;	break;
					}

					ChangeFlags(k,it->checked);

					idcmp->InvalidateItem(idcmp->IndexOf(it));
				}			
			}
		}
		break;

		case	73600:
		case	73601:
		case	73602:
		{
			CheckItemBox *it;
			int k;

			for (k = 0; k < lv->CountItems(); k++)
			{
				if (it = (CheckItemBox *)lv->ItemAt(k))
				{
					switch(msg->what)
					{
						case	73600:	it->checked = true;		break;
						case	73601:	it->checked = false;	break;
						case	73602:	it->checked = !it->checked;	break;
					}

					ChangeView(k,it->checked);

					lv->InvalidateItem(lv->IndexOf(it));
				}			
			}
		}
		break;

		case	2200:
		{
			OpenColorPicker(msg);
		}
		break;

		case BEAIM_NEW_COLOR_PICKED:
		{
			ColorView *bt;

			if (msg->FindPointer("pt",(void **)&bt) == B_OK)
			{
				rgb_color cl,*startColor;
				ssize_t size;
	
				msg->FindData( "color",B_RGB_COLOR_TYPE,(const void**)&startColor,&size );

				cl.red 		= startColor->red;
				cl.green 	= startColor->green;
				cl.blue 	= startColor->blue;

				bt->SetColor(cl);
			}

			SetNewColor(msg);
		}
		break;	

		case	tab_tab_list:
		{
			AddListWindow(win->sellist.ItemAt(0));
		}
		break;

		case	tab_menu_list:
		{
			create_mmxmenu();
		}
		break;

		case	tab_menu_editlist:
		{
			struct MyGadget *gad;

			if (gad = win->sellist.ItemAt(0))
			{
				window_menu(&gad->name);
			}
		}
		break;

		case	window_minh:
		{
			if (wi)
			{
				wi->minh = vl;			
			}
		}
		break;

		case	window_maxh:
		{
			if (wi)
			{
				wi->maxh = vl;			
			}
		}
		break;

		case	window_minw:
		{
			if (wi)
			{
				wi->minw = vl;			
			}
		}
		break;

		case	window_maxw:
		{
			if (wi)
			{
				wi->maxw = vl;			
			}
		}
		break;

		case	tab_font:
		{
			struct MyGadget *gad;

			if (wi = win)
			{
				if (gad = win->sellist.ItemAt(0))
				{
					font_window(gad->FontType,gad->FontSize,gad->FontAntiliasing,&gad->FontName[0],&gad->FontStyle[0]);
				}
					else
				{
					font_window(wi->FontType,wi->FontSize,wi->FontAntiliasing,&wi->FontName[0],&wi->FontStyle[0]);
				}
			}		
		}
		break;

		case	window_type:
		{
			if (wi)
			{
				wi->typewin = id;			

				ChangeWindowType(wi,id);
			}
		}
		break;

		case	window_look:
		{
			if (wi)
			{
				wi->look = id;			
			}
		}
		break;

		case	window_feel:
		{
			if (wi)
			{
				wi->feel = id;			
			}
		}
		break;

		case	window_workspace:
		{
			if (wi)
			{
				wi->wrk = id;			
			}
		}
		break;
			
		case	9000:
		{
			mymsg.AddInt32("x",vl);	
	
			win->PostMessage(&mymsg);
		}
		break;

		case	9001:
		{
			mymsg.AddInt32("y",vl);	
	
			win->PostMessage(&mymsg);
		}
		break;

		case	9002:
		{
			mymsg.AddInt32("w",vl);	
	
			win->PostMessage(&mymsg);
		}
		break;

		case	9003:
		{
			mymsg.AddInt32("h",vl);	
	
			win->PostMessage(&mymsg);
		}
		break;

		case	9004:
		{
			if (strcmp(txt,"") != 0)
			{
				if (is_title_available(txt))
				{
					if (win)
					{
						if (gad = win->sellist.ItemAt(0))
						{
							strcpy(&gad->Name[0],txt);		
						}
							else
						{
							strcpy(&win->Name[0],txt);		
						}
					}
				}
					else
				{
err:				if (EditorWin)
					{
						BAutolock lock(EditorWin);

						if (win)
						{
							if (gad = win->sellist.ItemAt(0))
							{
								EditorWin->name->SetText(&gad->Name[0]);
							}
								else
							{
								EditorWin->name->SetText(&win->Name[0]);
							}
						}	
					}	
				}	
			}
				else
			{
				::beep();
				
				goto err;
			}	
		}
		break;

		case	9005:
		{
			if (win)
			{
				if (gad = win->sellist.ItemAt(0))
				{
					strcpy(&gad->Title[0],txt);		

					ChangeGadgetLabel(gad,txt);
				}
					else
				{
					strcpy(&win->WTitle[0],txt);		

					win->Lock();

					win->ChangeTitleWindow();

					win->Unlock();
				}
			}	
		}
		break;

		case	9006:
		{
			if (gad)
			{
				gad->msg = atoi(txt);
			}
		}
		break;

		case	tab_focus:
		{
			gad->focus = id;		
		}
		break;

		case	align_type:
		{
			if (id == 2)
			{
				EnableRadio(true);

				SetChoiceInMenu(alignx->Menu(),gad->alignx,true);
				SetChoiceInMenu(aligny->Menu(),gad->aligny,true);

			}
				else
			{
				EnableRadio(false);
			}	

			gad->align = id;
		}
		break;
		
		case	align_x:
		{
			gad->alignx = id;
		}
		break;	

		case	align_y:
		{
			gad->aligny = id;
		}
		break;	

		case	gad_derived:
		{
			gad->derived = vl;
		}
		break;

//**************************** BUTTON *****************

		case	tab_button_default:
		{
			gad->data.button.defaut = id;

			set_button_defaut(gad,id);
		}
		break;

		case	tab_button_enabled:
		case	tab_checkbox_enabled:
		{
			gad->enable = id;

			SetEnableGadget(gad,id);
		}
		break;

//**************************** BBOX *****************

		case	tab_bbox_border:
		{
			gad->data.bbox.style = id;

			set_bbox_border(gad,id);
		}
		break;

		case	tab_bbox_label:
		{
			strcpy(&gad->data.bbox.Label[0],txt);

			set_bbox_label(gad,txt);		
		}
		break;

//**************************** CHECKBOX *****************

		case	tab_checkbox_checked:
		{
			gad->data.bcheckbox.checked = id;

			set_checkbox_checked(gad,id);
		}
		break;

//**************************** RADIO *****************

		case	tab_radio_value:
		{
			gad->data.rad.val = id;

			set_radio_checked(gad,id);
		}
		break;

		case	tab_radio_enable:
		{
			gad->enable = id;

			set_radio_enabled(gad,id);
		}
		break;

//**************************** STRING *****************

		case	tab_string_alignlab:
		{
			gad->data.string.alignlab = id;

			set_string_alignment_label(gad,id);		
		}
		break;

		case	tab_string_aligntxt:
		{
			gad->data.string.aligntxt = id;

			set_string_alignment_text(gad,id);		
		}
		break;

		case	tab_string_diviser:
		{
			gad->data.string.pixdiv = vl;

			set_string_divider(gad,vl);		
		}
		break;

		case	tab_string_label:
		{
			strcpy(&gad->data.string.Text[0],txt);

			set_string_label(gad,txt);		
		}
		break;

//**************************** STATUS *****************

		case	tab_status_trail:
		{
			strcpy(&gad->data.sta.Trail[0],txt);

			set_status_label(gad,txt);		
		}
		break;

		case	tab_status_label:
		{
			strcpy(&gad->data.sta.Label[0],txt);

			set_status_trail(gad,txt);		
		}
		break;

		case	tab_status_value:
		{
			gad->data.sta.value = vl;

			set_status_value(gad,vl);
		}
		break;

		case	tab_status_barheight:
		{
			gad->data.sta.barheight = vl;

			set_status_barheight(gad,vl);
		}
		break;

		case	tab_status_max:
		{
			gad->data.sta.maxvalue = vl;

			set_status_maxvalue(gad,vl);
		}
		break;

//**************************** SCROLLER *****************

		case	tab_scroller_value:
		{
			gad->data.bscroller.pos = vl;

			set_scroller_value(gad,vl);
		}
		break;

		case	tab_scroller_min:
		{
			gad->data.bscroller.min = vl;
		}
		break;

		case	tab_scroller_max:
		{
			gad->data.bscroller.max = vl;
		}
		break;

		case	tab_scroller_minstep:
		{
			gad->data.bscroller.minstep = vl;

			set_scroller_minstep(gad,vl);
		}
		break;

		case	tab_scroller_maxstep:
		{
			gad->data.bscroller.maxstep = vl;

			set_scroller_maxstep(gad,vl);
		}
		break;

		case	tab_scroller_minrange:
		{
			gad->data.bscroller.minrange = vl;

			set_scroller_minrange(gad,vl);
		}
		break;

		case	tab_scroller_maxrange:
		{
			gad->data.bscroller.maxrange = vl;

			set_scroller_maxrange(gad,vl);
		}
		break;

//**************************** TAB *****************

		case	tab_tab_width:
		{
			gad->data.tab.tabwidth = id;

			set_tab_width(gad,id);
		}
		break;

		case	tab_tab_height:
		{
			gad->data.tab.tabheight = vl;

			set_tab_height(gad,vl);
		}
		break;

		case	tab_tab_selected:
		{
			gad->data.tab.sel = vl;

			set_tab_select(gad,vl);
		}
		break;

//**************************** MX *****************

		case	tab_mx_align:
		{
			gad->data.mx.align = id;

			set_mx_align(gad,id);
		}
		break;

		case	tab_mx_diviser:
		{
			gad->data.mx.pixdiv = vl;

			set_mx_divider(gad,vl);
		}
		break;

		case	tab_mx_label:
		{
			strcpy(&gad->data.mx.Label[0],txt);

			set_mx_label(gad,txt);		
		}
		break;

//**************************** SLIDER *****************

		case	tab_slider_style:
		{
			gad->data.bslider.style = id;

			set_slider_style(gad,id);
		}
		break;

		case	tab_slider_hashtype:
		{
			gad->data.bslider.hashtype = id;

			set_slider_hashtype(gad,id);
		}
		break;

		case	tab_slider_hashcount:
		{
			gad->data.bslider.hashcount = vl;

			set_slider_hashcount(gad,vl);
		}
		break;

		case	tab_slider_value:
		{
			gad->data.bslider.pos = vl;

			set_slider_value(gad,vl);
		}
		break;

		case	tab_slider_min:
		{
			gad->data.bslider.min = vl;
		}
		break;

		case	tab_slider_max:
		{
			gad->data.bslider.max = vl;
		}
		break;

		case	tab_slider_thickness:
		{
			gad->data.bslider.thickness = vl;

			set_slider_thickness(gad,vl);
		}
		break;

		case	tab_slider_keyinc:
		{
			gad->data.bslider.keyinc = vl;

			set_slider_keyinc(gad,vl);
		}
		break;

		case	tab_slider_label:
		{
			strcpy(&gad->data.bslider.Label[0],txt);

			set_slider_label(gad,txt);		
		}
		break;

		case	tab_slider_minlabel:
		{
			strcpy(&gad->data.bslider.MinLabel[0],txt);

			set_slider_minlabel(gad,txt);		
		}
		break;

		case	tab_slider_maxlabel:
		{
			strcpy(&gad->data.bslider.MaxLabel[0],txt);

			set_slider_maxlabel(gad,txt);		
		}
		break;

//**************************** COLOR *****************

		case	tab_color_layout:
		{
			gad->data.col.layout = id;

			set_color_layout(gad,id);
		}
		break;

		case	tab_color_cellsize:
		{
			gad->data.col.cellsize = id;

			set_color_cellsize(gad,id);
		}
		break;

		case	tab_color_drawbuffered:
		{
			gad->data.col.redrawbuffer = id;
		}
		break;

//**************************** LV *****************

		case	tab_lv_multi:
		{
			gad->data.lv.multi = id;
		}
		break;

//**************************** OLV *****************

		case	tab_olv_multi:
		{
			gad->data.olv.multi = id;
		}
		break;

//**************************** TEXT *****************

		case	tab_text_align:
		{
			gad->data.txt.align = id;

			set_text_align(gad,id);
		}
		break;

		case	tab_number_align:
		{
			gad->data.num.align = id;

			set_text_align(gad,id);
		}
		break;

		case	tab_text_label:
		{
			strcpy(&gad->data.txt.Label[0],txt);

			set_text_text(gad,txt);		
		}
		break;

		case	tab_number_number:
		{
			strcpy(&gad->data.num.Label[0],txt);

			set_number_value(gad,atoi(txt));		
		}
		break;

//**************************** TEDIT *****************

		case	tab_tedit_align:
		{
			gad->data.edi.align = id;
		}
		break;

		case	tab_tedit_selectable:
		{
			gad->data.edi.selectable = id;
		}
		break;

		case	tab_tedit_editable:
		{
			gad->data.edi.editable = id;
		}
		break;

		case	tab_tedit_wordwrap:
		{
			gad->data.edi.wordwrap = id;
		}
		break;

		case	tab_tedit_setstylable:
		{
			gad->data.edi.stylable = id;
		}
		break;

		case	tab_tedit_autoident:
		{
			gad->data.edi.autoident = id;
		}
		break;

		case	tab_tedit_tabwidth:
		{
			gad->data.edi.tabwidth = vl;
		}
		break;

		case	tab_tedit_maxbytes:
		{
			gad->data.edi.maxchars = vl;
		}
		break;

//**************************** END *****************
	
		default:
		{
			BWindow::MessageReceived(msg);
		}
	}
}
	
void 
Editor_Win(void)
{
	WrkWindow	*xt;

	if (!EditorWin)
	{
		if (xt = DefWin)
		{
			OldWindow = xt;

			EditorWin = new EditButtonWindow(prefs.editorwinrect,(struct MyGadget *)xt->sellist.ItemAt(0));

			EditorWin->Show();
		}
	}
		else
	{
		EditorWin->Show();
	
		EditorWin->Activate();
	}	
}
	