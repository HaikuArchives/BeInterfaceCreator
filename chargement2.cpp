#include "proto.h"

extern BFile *fi;

void
LoadButton(struct MyGadget *gd)
{
	gd->data.button.defaut = read_integer();

	SetTagsButton(gd);
}

void
LoadCheckBox(struct MyGadget *gd)
{
	gd->data.bcheckbox.checked  = read_integer();

	SetTagsCheckBox(gd);
}

void
LoadBbox(struct MyGadget *gd)
{
	char tmp[512],*buf = &tmp[0];

	gd->data.bbox.style  = read_integer();
	
	read_string(buf);
	
	strcpy(&gd->data.bbox.Label[0],buf);

	SetTagsBbox(gd);
}

void
LoadColor(struct MyGadget *gd)
{
	rgb_color cl;

	gd->data.col.cellsize 		= read_integer();
	gd->data.col.layout 		= read_integer();
	gd->data.col.redrawbuffer 	= read_integer();

	read_color(&cl);
	
	gd->data.col.value = cl;
}

void
LoadSlider(struct MyGadget *gd)
{
	char tmp[512],*buf = &tmp[0];

	rgb_color cl;

	gd->data.bslider.min		= read_integer();
	gd->data.bslider.max		= read_integer();
	gd->data.bslider.pos		= read_integer();
	gd->data.bslider.style		= read_integer();
	gd->data.bslider.hashtype	= read_integer();
	gd->data.bslider.hashcount	= read_integer();
	gd->data.bslider.thickness	= read_integer();
	gd->data.bslider.keyinc		= read_integer();
	gd->data.bslider.fillall	= read_integer();

	read_color(&cl);

	gd->data.bslider.fillcolor = cl;

	read_color(&cl);

	gd->data.bslider.barcolor = cl;

	read_string(buf);

	strcpy(&gd->data.bslider.Label[0],buf);

	read_string(buf);

	strcpy(&gd->data.bslider.MinLabel[0],buf);

	read_string(buf);

	strcpy(&gd->data.bslider.MaxLabel[0],buf);
}

void
LoadString(struct MyGadget *gd)
{
	char tmp[512],*buf = &tmp[0];

	gd->data.string.editable	= read_integer();
	gd->data.string.selectable	= read_integer();
	gd->data.string.maxchars	= read_integer();
	gd->data.string.pixdeb		= read_integer();
	gd->data.string.pixdiv		= read_integer();
	gd->data.string.value		= read_integer();
	gd->data.string.aligntxt	= read_integer();
	gd->data.string.alignlab	= read_integer();
	gd->data.string.acceptvir	= read_integer();
	gd->data.string.negvalue	= read_integer();
	gd->data.string.car			= read_integer();

	read_string(buf);

	strcpy(&gd->data.string.Text[0],buf);

	SetTagsString(gd);
}

void
LoadScroller(struct MyGadget *gd)
{
	gd->data.bscroller.min		= read_integer();
	gd->data.bscroller.max		= read_integer();
	gd->data.bscroller.minrange	= read_integer();
	gd->data.bscroller.maxrange	= read_integer();
	gd->data.bscroller.setprop	= read_integer();
	gd->data.bscroller.pos		= read_integer();
	gd->data.bscroller.minstep	= read_integer();
	gd->data.bscroller.maxstep	= read_integer();

	SetTagsScroller(gd);
}

void
LoadStatus(struct MyGadget *gd)
{
	char tmp[512],*buf = &tmp[0];
	rgb_color cl;

	gd->data.sta.barheight	= read_integer();
	gd->data.sta.maxvalue	= read_integer();
	gd->data.sta.value		= read_integer();

	read_color(&cl);

	gd->data.sta.barcolor = cl;

	read_string(buf);

	strcpy(&gd->data.sta.Label[0],buf);

	read_string(buf);

	strcpy(&gd->data.sta.Trail[0],buf);

	SetTagsStatus(gd);
}

void
LoadText(struct MyGadget *gd)
{
	char tmp[512],*buf = &tmp[0];

	gd->data.txt.align 	= read_integer();
	
	read_string(buf);

	strcpy(&gd->data.txt.Label[0],buf);

	SetTagsText(gd);
}

void
LoadNumber(struct MyGadget *gd)
{
	char tmp[512],*buf = &tmp[0];

	gd->data.num.align 	= read_integer();
	
	read_string(buf);

	strcpy(&gd->data.num.Label[0],buf);

	SetTagsNumber(gd);
}

void
LoadTab(struct MyGadget *gd)
{
	int a;

	gd->data.tab.sel		= read_integer();
	gd->data.tab.tabwidth	= read_integer();
	gd->data.tab.tabheight	= read_integer();

	if (a = read_integer())
	{
		gd->name.MakeEmpty();

		load_string(a,gd);

		change_gadget_list(gd);
	}

	SetTagsTab(gd);
}

void
LoadMx(struct MyGadget *gd)
{
	int a;
	char tmp[512],*buf = &tmp[0];

	gd->data.mx.pixdiv	= read_integer();
	gd->data.mx.sel		= read_integer();
	gd->data.mx.align	= read_integer();

	read_string(buf);

	strcpy(&gd->data.mx.Label[0],buf);

	if (a = read_integer())
	{
		gd->name.MakeEmpty();

		load_string(a,gd);

		change_gadget_list(gd);
	}

	SetTagsMx(gd);
}

void
LoadRadio(struct MyGadget *gd)
{
	int a;

	gd->data.rad.val	= read_integer();
	gd->data.rad.sel	= read_integer();

	if (a = read_integer())
	{
		gd->name.MakeEmpty();

		load_string(a,gd);

		change_gadget_list(gd);
	}

	SetTagsRadio(gd);
}

void
LoadEdit(struct MyGadget *gd)
{
	gd->data.edi.tabwidth	= read_integer();
	gd->data.edi.align		= read_integer();
	gd->data.edi.maxchars	= read_integer();
	gd->data.edi.editable	= read_integer();
	gd->data.edi.stylable	= read_integer();
	gd->data.edi.selectable	= read_integer();
	gd->data.edi.autoident	= read_integer();
	gd->data.edi.wordwrap	= read_integer();
}

void
LoadLv(struct MyGadget *gd)
{
	gd->data.lv.multi	= read_integer();
	gd->data.lv.sel		= read_integer();
}

void
LoadOLv(struct MyGadget *gd)
{
	gd->data.olv.multi	= read_integer();
	gd->data.olv.sel	= read_integer();
}


