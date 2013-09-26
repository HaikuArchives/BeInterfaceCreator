#include "proto.h"

void
SetEnableGadget(struct MyGadget *gd,bool state)
{
	BControl 	*bt;
	WrkWindow	*wi;
	
	if (wi = (WrkWindow *)gd->pt->Window())
	{
		BAutolock tst(wi);

		if (bt = (BControl *)((GadView *)gd->pt)->ChildAt(0))
		{
			if (is_kind_of(bt,BControl))
			{
				bt->SetEnabled(state);
			}
		}
	}
}

void
SetTagsButton(struct MyGadget *gd)
{
	set_button_defaut(gd,gd->data.button.defaut);
}
	
void
SetTagsCheckBox(struct MyGadget *gd)
{
	set_checkbox_checked(gd,gd->data.bcheckbox.checked);
}

void
SetTagsBbox(struct MyGadget *gd)
{
	set_bbox_border(gd,gd->data.bbox.style);
	
	set_bbox_label(gd,&gd->data.bbox.Label[0]);
}

void
SetTagsColor(struct MyGadget *gd)
{
	set_color_layout(gd,gd->data.col.layout);
	set_color_cellsize(gd,gd->data.col.cellsize);
//	set_color_value(gd,&gd->data.col.value);
}

void
SetTagsSlider(struct MyGadget *gd)
{
	set_slider_value(gd,gd->data.bslider.pos);
	set_slider_style(gd,gd->data.bslider.style);
	set_slider_hashtype(gd,gd->data.bslider.hashtype);
	set_slider_hashcount(gd,gd->data.bslider.hashcount);
	set_slider_thickness(gd,gd->data.bslider.thickness);

	set_slider_fillcolor(gd,ReturnIntFromRgb(gd->data.bslider.fillcolor.red,gd->data.bslider.fillcolor.green,gd->data.bslider.fillcolor.blue));
	set_slider_barcolor(gd,ReturnIntFromRgb(gd->data.bslider.barcolor.red,gd->data.bslider.barcolor.green,gd->data.bslider.barcolor.blue));

	set_slider_label(gd,&gd->data.bslider.Label[0]);
	set_slider_minlabel(gd,&gd->data.bslider.MinLabel[0]);
	set_slider_maxlabel(gd,&gd->data.bslider.MaxLabel[0]);
}

void
SetTagsString(struct MyGadget *gd)
{
	set_string_divider(gd,gd->data.string.pixdiv);

	set_string_alignment_text(gd,gd->data.string.aligntxt);
	set_string_alignment_label(gd,gd->data.string.alignlab);

	set_string_label(gd,&gd->data.string.Text[0]);
}

void
SetTagsMx(struct MyGadget *gd)
{
	set_mx_divider(gd,gd->data.mx.pixdiv);
//	set_mx_select(gd,gd->data.mx.sel);
	set_mx_align(gd,gd->data.mx.align);

	set_mx_label(gd,&gd->data.mx.Label[0]);
}

void
SetTagsRadio(struct MyGadget *gd)
{
	set_radio_checked(gd,gd->data.rad.val);
}

void
SetTagsScroller(struct MyGadget *gd)
{
}

void
SetTagsStatus(struct MyGadget *gd)
{
	set_status_barheight(gd,gd->data.sta.barheight);
	set_status_maxvalue(gd,gd->data.sta.maxvalue);
	set_status_value(gd,gd->data.sta.value);

	set_status_barcolor(gd,&gd->data.sta.barcolor);

	set_status_label(gd,&gd->data.sta.Label[0]);
	set_status_trail(gd,&gd->data.sta.Trail[0]);
}

void
SetTagsText(struct MyGadget *gd)
{
	set_text_align(gd,gd->data.txt.align);
	
	set_text_text(gd,&gd->data.txt.Label[0]);
}

void
SetTagsNumber(struct MyGadget *gd)
{
	set_text_align(gd,gd->data.num.align);
	
	set_text_text(gd,&gd->data.txt.Label[0]);
}

void
SetTagsTab(struct MyGadget *gd)
{
	set_tab_select(gd,gd->data.tab.sel);
	set_tab_width(gd,gd->data.tab.tabwidth);
	set_tab_height(gd,gd->data.tab.tabheight);
}
