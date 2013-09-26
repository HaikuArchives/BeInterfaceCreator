#include "proto.h"

char *msg_gadevents_box[] =
{
	"AttachedToWindow",
	"AllAttached",
	"SetBorder",
	"DetachedFromWindow",
	"AllDetached",
	"FrameMoved",
	"FrameResized",
	"KeyDown",
	"KeyUp",
	"MessageReceived",
	"MouseDown",
	"MouseMoved",
	"MouseUp",
	"WindowActivated",
	"Archive",
	"ConstrainClippingRegion",
	"GetClippingRegion",
	"Draw",
	"DrawAfterChildren",
	"GetPreferredSize",
	"ResizeToPreferred",
	"GetSupportedSuites",
	"MakeFocus",
	"Perform",
	"Pulse",
	"ResolveSpecifier",
	"ScrollTo",
	"SetDrawingMode",
	"SetPenSize",
	"SetViewColor",
	"SetHighColor",
	"SetLowColor",
	"SetFont",
	"SetFlags",
	"SetResizingMode",
	"Show",
	"Hide",
	"TargetedByScrollView",
	NULL
};	

char *msg_gadevents_code_ccplus_box[] =
{
	"void AttachedToWindow(void)",
	"void AllAttached(void)",
	"void SetBorder(border_style style)",
	"void DetachedFromWindow(void)",
	"void AllDetached(void)",
	"void FrameMoved(BPoint parentPoint)",
	"void FrameResized(float width,float height)",
	"void KeyDown(const char *bytes,int32 numByte)",
	"void KeyUp(const char *bytes,int32 numByte)",
	"void MessageReceived(BMessage *message)",
	"void MouseDown(BPoint point)",
	"void MouseMoved(BPoint point,uint32 transit,const BMessage *message)",
	"void MouseUp(BPoint point)",
	"void WindowActivated(bool active)",
	"status_t Archive(BMessage *data,bool deep = true)",
	"void ConstrainClippingRegion(BRegion *region)",
	"void GetClippingRegion(BRegion *region)",
	"void Draw(BRect updateRect)",
	"void DrawAfterChildren(BRect updateRect)",
	"void GetPreferredSize(float *width,float *height)",
	"void ResizeToPreferred(void)",
	"status_t GetSupportedSuites(BMessage *data)",
	"void MakeFocus(bool focus = true)",
	"status_t Perform(perform_code d,void *arg)",
	"void Pulse(void)",
	"BHandler* ResolveSpecifier(BMessage *msg,int32 index,BMessage *specifier,int32 form,const char *property)",
	"void ScrollTo(BPoint where)",
	"void SetDrawingMode(drawing_mode mode)",
	"void SetPenSize(float size)",
	"void SetViewColor(rgb_color color)",
	"void SetHighColor(rgb_color color)",
	"void SetLowColor(rgb_color color)",
	"void SetFont(const BFont *font,uint32 mask = B_FONT_ALL)",
	"void SetFlags(uint32 flags)",
	"void SetResizingMode(uint32 mode)",
	"void Show(void)",
	"void Hide(void)",
	"void TargetedByScrollView(BScrollView *scroller)",
	NULL
};	

char *msg_gadevents_code_ccplus_box_defroutine[] =
{
	"void AttachedToWindow()",
	"void AllAttached()",
	"void SetBorder(style)",
	"void DetachedFromWindow()",
	"void AllDetached()",
	"void FrameMoved(parentPoint)",
	"void FrameResized(width,height)",
	"void KeyDown(bytes,numByte)",
	"void KeyUp(bytes,numByte)",
	"void MessageReceived(message)",
	"void MouseDown(point)",
	"void MouseMoved(point,transit,message)",
	"void MouseUp(point)",
	"void WindowActivated(active)",
	"status_t Archive(data,deep)",
	"void ConstrainClippingRegion(region)",
	"void GetClippingRegion(region)",
	"void Draw(updateRect)",
	"void DrawAfterChildren(updateRect)",
	"void GetPreferredSize(width,height)",
	"void ResizeToPreferred()",
	"status_t GetSupportedSuites(data)",
	"void MakeFocus(focus)",
	"status_t Perform(d,arg)",
	"void Pulse()",
	"BHandler* ResolveSpecifier(msg,index,specifier,form,property)",
	"void ScrollTo(where)",
	"void SetDrawingMode(mode)",
	"void SetPenSize(size)",
	"void SetViewColor(color)",
	"void SetHighColor(color)",
	"void SetLowColor(color)",
	"void SetFont(font,mask)",
	"void SetFlags(flags)",
	"void SetResizingMode(mode)",
	"void Show()",
	"void Hide()",
	"void TargetedByScrollView(scroller)",
	NULL
};	

void
generate_crochet_code(FILE *fi,struct MyGadget *gad = NULL,char *defrtn = "")
{
	xwrite_string(fi,"{");

	if	(gad)
	{
		BAutolock win(gad->pt->Window());

		BView	*xt = (BView *)gad->pt->ChildAt(0);
		rgb_color c0,c1,c2;

		c0 = xt->ViewColor();
		c1 = xt->HighColor();
		c2 = xt->LowColor();

		if (gad->type == BOX_KIND && strlen(&gad->data.bbox.Label[0]))
		{
			sprintf(&buf[0],"\tSetLabel(\"%s\");",&gad->data.bbox.Label[0]);

			xwrite_string(fi,&buf[0]);
		}	

		if (!IsSameColor(&gad->ColView,&c0))
		{
			sprintf(&buf[0],"\tSetViewColor(%d,%d,%d);",c0.red,c0.green,c0.blue);

			xwrite_string(fi,&buf[0]);
		}	

		if (!IsSameColor(&gad->ColHigh,&c1))
		{
			sprintf(&buf[0],"\tSetHighColor(%d,%d,%d);",c1.red,c1.green,c1.blue);

			xwrite_string(fi,&buf[0]);
		}	

		if (!IsSameColor(&gad->ColLow,&c2))
		{
			sprintf(&buf[0],"\tSetLowColor(%d,%d,%d);",c2.red,c2.green,c2.blue);

			xwrite_string(fi,&buf[0]);
		}	

		switch(gad->FontType)
		{
			case	1:
			{
				sprintf(&buf[0],"\tSetFont(be_plain_font);");

				xwrite_string(fi,&buf[0]);
			}
			break;

			case	2:
			{
				sprintf(&buf[0],"\tSetFont(be_bold_font);");

				xwrite_string(fi,&buf[0]);
			}
			break;

			case	3:
			{
				sprintf(&buf[0],"\tSetFont(be_fixed_font);");

				xwrite_string(fi,&buf[0]);
			}
			break;

			case	4:
			{
				sprintf(&buf[0],"\tBFont font;");

				xwrite_string(fi,&buf[0]);
			
				sprintf(&buf[0],"\tfont.SetFamilyAndStyle(\"%s\",\"%s\");",&gad->FontName[0],&gad->FontStyle[0]);

				xwrite_string(fi,&buf[0]);

				sprintf(&buf[0],"\tfont.SetSize(%d);",gad->FontSize);

				xwrite_string(fi,&buf[0]);

				sprintf(&buf[0],"\tSetFont(&font);");

				xwrite_string(fi,&buf[0]);
			}
			break;
		}	
	}

	if (prefs.code_default_routine)
	{
		if (strcmp(defrtn,"") != 0)
		{
			xwrite_string(fi,defrtn);
		}
	}

	xwrite_string(fi,"}");

	xwrite_cr(fi);
}

void
generate_code_ccplus_box(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	int nb,k;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_box);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(&buf[0],"BBox%d::BBox%d(BRect rct):BBox(rct,\"%s\",%s,%s)",count_box,count_box,&gad->Name[0],GetAlign(gad),GetFlagView(gad->view));

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BBox%d::~BBox%d(void)\n{\n}\n",count_box,count_box);

		xwrite_string(fi,&buf[0]);

		gencode_gadget_all(fi,gad,"BBox",count_box,&msg_gadevents_code_ccplus_box[0],&msg_gadevents_code_ccplus_box_defroutine[0]);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_box(char *path,struct MyGadget *gad)
{
	++count_box;

	generate_header_gad_all("Box",count_box,path,gad,&msg_gadevents_code_ccplus_box[0]);

	generate_code_ccplus_box(path,gad);
}
