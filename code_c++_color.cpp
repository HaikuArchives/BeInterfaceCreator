#include "proto.h"

extern FILE *xfi;

char *msg_gadevents_color[] =
{
	"SetCellSize",
	"SetLayout",
	"SetValue",
	"SetEnabled",
	"SetMessage",
	"SetTarget",
	"SetTarget",
	"SetHandlerForReply",
	"Invoke",
	"AttachedToWindow",
	"DetachedFromWindow",
	"AllAttached",
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

char *msg_gadevents_code_ccplus_color[] =
{
	"void SetCellSize(float size)",
	"void SetLayout(color_control_layout layout)",
	"void SetValue(int32 value)",
	"void SetEnabled(bool enabled)",
	"status_t SetMessage(BMessage *message)",
	"status_t SetTarget(const BHandler *handler,const BLooper *looper = NULL)",
	"status_t SetTarget(BMessenger messenger)",
	"status_t SetHandlerForReply(BHandler *handler)",
	"status_t Invoke(BMessage *msg = NULL)",
	"void AttachedToWindow(void)",
	"void DetachedFromWindow(void)",
	"void AllAttached(void)",
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

char *msg_gadevents_code_ccplus_color_defroutine[] =
{
	"void SetCellSize(size)",
	"void SetLayout(layout)",
	"void SetValue(value)",
	"void SetEnabled(enabled)",
	"status_t SetMessage(message)",
	"status_t SetTarget(handler,looper)",
	"status_t SetTarget(messenger)",
	"status_t SetHandlerForReply(handler)",
	"status_t Invoke(msg)",
	"void AttachedToWindow()",
	"void DetachedFromWindow()",
	"void AllAttached()",
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
generate_code_ccplus_gad_color(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*str,*fichier = &tmp[0];

	FILE *fi;

	int tb;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_color);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		switch(gad->data.col.layout)
		{
			case	B_CELLS_4x64:	tb = 0;		break;
			case	B_CELLS_8x32:	tb = 1;		break;
			case	B_CELLS_16x16:	tb = 2;		break;
			case	B_CELLS_32x8:	tb = 3;		break;
			case	B_CELLS_64x4:	tb = 4;		break;
		}

		sprintf(&buf[0],"BColor%d::BColor%d(BPoint pt):BColorControl(pt,B_CELLS_%s,%d,\"%s\",new BMessage((uint32)%d))",count_color,count_color,layout_color[tb],gad->data.col.cellsize,&gad->Name[0],gad->msg);

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BColor%d::~BColor%d(void)\n{\n}\n",count_color,count_color);

		gencode_gadget_all(fi,gad,"BColor",count_color,&msg_gadevents_code_ccplus_color[0],&msg_gadevents_code_ccplus_color_defroutine[0]);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_color(char *path,struct MyGadget *gad)
{
	++count_color;

	generate_header_gad_all("Color",count_color,path,gad,&msg_gadevents_code_ccplus_color[0]);

	generate_code_ccplus_gad_color(path,gad);
}
