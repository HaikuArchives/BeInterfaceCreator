#include "proto.h"

char *msg_gadevents_button[] =
{
	"MakeDefault",
	"SetValue",
	"SetLabel",
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
	"MouseMoved",
	"MouseUp",
	"WindowActivated",
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

char *msg_gadevents_code_ccplus_button[] =
{
	"void MakeDefault(bool state)",
	"void SetValue(int32 value)",
	"void SetLabel(const char *text)",
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
	"void MouseMoved(BPoint point,uint32 transit,const BMessage *message)",
	"void MouseUp(BPoint point)",
	"void WindowActivated(bool active)",
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

char *msg_gadevents_code_ccplus_button_defroutine[] =
{
	"void MakeDefault(state)",
	"void SetValue(value)",
	"void SetLabel(text)",
	"void SetEnabled(enabled)",
	"status_t SetMessage(message)",
	"status_t SetTarget(handler)",
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
	"void MouseMoved(point,transit,message)",
	"void MouseUp(point)",
	"void WindowActivated(active)",
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

char *
GetNameFile(char *path,char *win,char *name,bool ccplus)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	sprintf(fichier,"%s/%s_%s.%s",path,win,name,(!ccplus) ? "h" : "cpp");

	return fichier;
}

void
generate_code_ccplus_gad_button(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_button);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(&buf[0],"BButton%d::BButton%d(BRect rct):BButton(rct,\"%s\",\"%s\",new BMessage((uint32)%d),%s,%s)",count_button,count_button,&gad->Name[0],&gad->Title[0],gad->msg,GetAlign(gad),GetFlagView(gad->view));

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BButton%d::~BButton%d(void)\n{\n}\n",count_button,count_button);

		xwrite_string(fi,&buf[0]);

		gencode_gadget_all(fi,gad,"BButton",count_button,&msg_gadevents_code_ccplus_button[0],&msg_gadevents_code_ccplus_button_defroutine[0]);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_button(char *path,struct MyGadget *gad)
{
	++count_button;

	generate_header_gad_all("Button",count_button,path,gad,&msg_gadevents_code_ccplus_button[0]);

	generate_code_ccplus_gad_button(path,gad);
}
