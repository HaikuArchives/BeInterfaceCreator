#include "proto.h"

extern BFile *fi;

rgb_color
GetRgbFromInteger(int d)
{
	rgb_color k = {0};

	k.red 	= (d >> 24);
	k.green = (d >> 16);
	k.blue  = (d >> 8);
	k.alpha = d & 0x000000FF;

	return(k);
}

int
ReturnIntFromRgb(int a,int b,int c)
{
	int ret = 0;
	
	ret = (a << 24) + (b << 16) + (c << 8);
	
	return(ret);
}

void
write_color(rgb_color *cl)
{
	write_integer(ReturnIntFromRgb(cl->red,cl->green,cl->blue));
}

void
read_color(rgb_color *cl)
{
	*cl = GetRgbFromInteger(read_integer());
}

void
SaveButton(struct MyGadget *gd)
{
	write_integer(gd->data.button.defaut);
}

void
SaveCheckBox(struct MyGadget *gd)
{
	write_integer(gd->data.bcheckbox.checked);
}

void
SaveBbox(struct MyGadget *gd)
{
	write_integer(gd->data.bbox.style);
	
	write_string(&gd->data.bbox.Label[0]);
}

void
SaveColor(struct MyGadget *gd)
{
	write_integer(gd->data.col.cellsize);
	write_integer(gd->data.col.layout);
	write_integer(gd->data.col.redrawbuffer);

	write_color(&gd->data.col.value);
}

void
SaveSlider(struct MyGadget *gd)
{
	write_integer(gd->data.bslider.min);
	write_integer(gd->data.bslider.max);
	write_integer(gd->data.bslider.pos);
	write_integer(gd->data.bslider.style);
	write_integer(gd->data.bslider.hashtype);
	write_integer(gd->data.bslider.hashcount);
	write_integer(gd->data.bslider.thickness);
	write_integer(gd->data.bslider.keyinc);
	write_integer(gd->data.bslider.fillall);

	write_color(&gd->data.bslider.fillcolor);
	write_color(&gd->data.bslider.barcolor);

	write_string(&gd->data.bslider.Label[0]);
	write_string(&gd->data.bslider.MinLabel[0]);
	write_string(&gd->data.bslider.MaxLabel[0]);
}

void
SaveString(struct MyGadget *gd)
{
	write_integer(gd->data.string.editable);
	write_integer(gd->data.string.selectable);
	write_integer(gd->data.string.maxchars);
	write_integer(gd->data.string.pixdeb);
	write_integer(gd->data.string.pixdiv);
	write_integer(gd->data.string.value);
	write_integer(gd->data.string.aligntxt);
	write_integer(gd->data.string.alignlab);
	write_integer(gd->data.string.acceptvir);
	write_integer(gd->data.string.negvalue);
	write_integer(gd->data.string.car);

	write_string(&gd->data.string.Text[0]);
}

void
SaveMx(struct MyGadget *gd)
{
	write_integer(gd->data.mx.pixdiv);
	write_integer(gd->data.mx.sel);
	write_integer(gd->data.mx.align);

	write_string(&gd->data.mx.Label[0]);
}

void
SaveRadio(struct MyGadget *gd)
{
	write_integer(gd->data.rad.val);
	write_integer(gd->data.rad.sel);
}

void
SaveScroller(struct MyGadget *gd)
{
	write_integer(gd->data.bscroller.min);
	write_integer(gd->data.bscroller.max);
	write_integer(gd->data.bscroller.minrange);
	write_integer(gd->data.bscroller.maxrange);
	write_integer(gd->data.bscroller.setprop);
	write_integer(gd->data.bscroller.pos);
	write_integer(gd->data.bscroller.minstep);
	write_integer(gd->data.bscroller.maxstep);
}

void
SaveStatus(struct MyGadget *gd)
{
	write_integer(gd->data.sta.barheight);
	write_integer(gd->data.sta.maxvalue);
	write_integer(gd->data.sta.value);

	write_color(&gd->data.sta.barcolor);

	write_string(&gd->data.sta.Label[0]);
	write_string(&gd->data.sta.Trail[0]);
}

void
SaveText(struct MyGadget *gd)
{
	write_integer(gd->data.txt.align);
	
	write_string(&gd->data.txt.Label[0]);
}

void
SaveNumber(struct MyGadget *gd)
{
	write_integer(gd->data.num.align);
	
	write_string(&gd->data.num.Label[0]);
}

void
SaveTab(struct MyGadget *gd)
{
	write_integer(gd->data.tab.sel);
	write_integer(gd->data.tab.tabwidth);
	write_integer(gd->data.tab.tabheight);
}

void
SaveEdit(struct MyGadget *gd)
{
	write_integer(gd->data.edi.tabwidth);
	write_integer(gd->data.edi.align);
	write_integer(gd->data.edi.maxchars);
	write_integer(gd->data.edi.editable);
	write_integer(gd->data.edi.stylable);
	write_integer(gd->data.edi.selectable);
	write_integer(gd->data.edi.autoident);
	write_integer(gd->data.edi.wordwrap);
}

void
SaveLv(struct MyGadget *gd)
{
	write_integer(gd->data.lv.multi);
	write_integer(gd->data.lv.sel);
}

void
SaveOLv(struct MyGadget *gd)
{
	write_integer(gd->data.olv.multi);
	write_integer(gd->data.olv.sel);
}

