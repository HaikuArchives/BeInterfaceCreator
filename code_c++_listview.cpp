#include "proto.h"

extern FILE *xfi;

char *msg_gadevents_lv[] =
{
	"AddItem",
	"AddItem",
	"AddList",
	"AddList",
	"RemoveItem",
	"RemoveItem",
	"RemoveItems",
	"SelectionChanged",
	"SetSelectionMessage",
	"SetInvocationMessage",
	"SetListType",
	"MakeEmpty",
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

char *msg_gadevents_code_ccplus_listview[] =
{
	"bool AddItem(BListItem *item)",
	"bool AddItem(BListItem *item,int32 atIndex)",
	"bool AddList(BList *newItems)",
	"bool AddList(BList *newItems,int32 atIndex)",
	"bool RemoveItem(BListItem *item)",
	"BListItem* RemoveItem(int32 index)",
	"bool RemoveItems(int32 index,int32 count)",
	"void SelectionChanged(void)",
	"void SetSelectionMessage(BMessage *message)",
	"void SetInvocationMessage(BMessage *message)",
	"void SetListType(list_view_type type)",
	"void MakeEmpty(void)",
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

char *msg_gadevents_code_ccplus_listview_defroutine[] =
{
	"bool AddItem(item)",
	"bool AddItem(item,atIndex)",
	"bool AddList(newItems)",
	"bool AddList(newItems,atIndex)",
	"bool RemoveItem(item)",
	"BListItem* RemoveItem(index)",
	"bool RemoveItems(index,count)",
	"void SelectionChanged()",
	"void SetSelectionMessage(message)",
	"void SetInvocationMessage(message)",
	"void SetListType(type)",
	"void MakeEmpty()",
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
generate_code_ccplus_gad_listview(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_listview);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(&buf[0],"BListView%d::BListView%d(BRect rct):BListView(rct,\"%s\",%s,%s,%s)",count_listview,count_listview,&gad->Name[0],selection_lv[gad->data.lv.multi],GetAlign(gad),GetFlagView(gad->view));

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BListView%d::~BListView%d(void)\n{\n}\n",count_listview,count_listview);

		xwrite_string(fi,&buf[0]);

		gencode_gadget_all(fi,gad,"BListView",count_listview,&msg_gadevents_code_ccplus_listview[0],&msg_gadevents_code_ccplus_listview_defroutine[0]);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_listview(char *path,struct MyGadget *gad)
{
	++count_listview;

	generate_header_gad_all("ListView",count_listview,path,gad,&msg_gadevents_code_ccplus_listview[0]);

	generate_code_ccplus_gad_listview(path,gad);
}
