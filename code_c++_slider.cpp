#include "proto.h"

extern FILE *xfi;

char *msg_gadevents_slider[] =
{
	"SetLimitLabels",
	"ValueForPoint",
	"SetPosition",
	"SetLabel",
	"SetValue",
	"SetEnabled",
	"Draw",
	"DrawSlider",
	"DrawBar",
	"DrawHashMarks",
	"DrawThumb",
	"DrawFocusMark",
	"DrawText",
	"UpdateText",
	"BarFrame",
	"HashMarksFrame",
	"SetModificationMessage",
	"SetSnoozeAmount",
	"SetKeyIncrementValue",
	"SetHashMarkCount",
	"SetHashMarks",
	"SetStyle",
	"SetBarColor",
	"UseFillColor",
	"SetOrientation",
	"SetBarThickness",
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
	"SetFont)",
	"SetFlags",
	"SetResizingMode",
	"Show",
	"Hide",
	"TargetedByScrollView",
	NULL
};	

char *msg_gadevents_code_ccplus_slider[] =
{
	"void SetLimitLabels(const char *minLabel,const char *maxLabel)",
	"int32 ValueForPoint(BPoint point)",
	"void SetPosition(float position)",
	"void SetLabel(const char *text)",
	"void SetValue(int32 value)",
	"void SetEnabled(bool enabled)",
	"void Draw(BRect updateRect)",
	"void DrawSlider(void)",
	"void DrawBar(void)",
	"void DrawHashMarks(void)",
	"void DrawThumb(void)",
	"void DrawFocusMark(void)",
	"void DrawText(void)",
	"char* UpdateText(void)",
	"BRect BarFrame(void)",
	"BRect HashMarksFrame(void)",
	"void SetModificationMessage(BMessage *message)",
	"void SetSnoozeAmount(int32 amount)",
	"void SetKeyIncrementValue(int32 value)",
	"void SetHashMarkCount(int32 count)",
	"void SetHashMarks(hash_mark_location where)",
	"void SetStyle(thumb_style style)",
	"void SetBarColor(rgb_color color)",
	"void UseFillColor(bool status,const rgb_color* color=NULL)",
	"void SetOrientation(orientation value)",
	"void SetBarThickness(float thickness)",
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

char *msg_gadevents_code_ccplus_slider_defroutine[] =
{
	"void SetLimitLabels(minLabel,maxLabel)",
	"int32 ValueForPoint(point)",
	"void SetPosition(position)",
	"void SetLabel(text)",
	"void SetValue(value)",
	"void SetEnabled(enabled)",
	"void Draw(updateRect)",
	"void DrawSlider()",
	"void DrawBar()",
	"void DrawHashMarks()",
	"void DrawThumb()",
	"void DrawFocusMark()",
	"void DrawText()",
	"char* UpdateText()",
	"BRect BarFrame()",
	"BRect HashMarksFrame()",
	"void SetModificationMessage(message)",
	"void SetSnoozeAmount(amount)",
	"void SetKeyIncrementValue(value)",
	"void SetHashMarkCount(count)",
	"void SetHashMarks(where)",
	"void SetStyle(style)",
	"void SetBarColor(color)",
	"void UseFillColor(status,color)",
	"void SetOrientation(value)",
	"void SetBarThickness(thickness)",
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

extern char *slider_style[];

void
generate_code_ccplus_gad_slider(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;
	int tb = 0;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_slider);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		switch(gad->data.bslider.style)
		{
			case	B_BLOCK_THUMB:		tb = 0;	break;
			case	B_TRIANGLE_THUMB:	tb = 1;	break;
		}

		sprintf(&buf[0],"BSlider%d::BSlider%d(BRect rct):BSlider(rct,\"%s\",\"%s\",new BMessage((uint32)%d),%d,%d,%s,%s,%s)",count_slider,count_slider,&gad->Name[0],&gad->Title[0],gad->msg,gad->data.bslider.min,gad->data.bslider.max,slider_style[tb],GetAlign(gad),GetFlagView(gad->view));

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BSlider%d::~BSlider%d(void)\n{\n}\n",count_slider,count_slider);

		xwrite_string(fi,&buf[0]);

		gencode_gadget_all(fi,gad,"BSlider",count_slider,&msg_gadevents_code_ccplus_slider[0],&msg_gadevents_code_ccplus_slider_defroutine[0]);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_slider(char *path,struct MyGadget *gad)
{
	++count_slider;

	generate_header_gad_all("Slider",count_slider,path,gad,&msg_gadevents_code_ccplus_slider[0]);

	generate_code_ccplus_gad_slider(path,gad);
}
