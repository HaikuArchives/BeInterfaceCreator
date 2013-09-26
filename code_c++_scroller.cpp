#include "proto.h"

extern FILE *xfi;

char *msg_gadevents_scroller[] =
{
	"AttachedToWindow",
	"ValueChanged",
	"MessageReceived",
	"MouseDown",
	"MouseUp",
	"MouseMoved",
	"DetachedFromWindow",
	"Draw",
	"FrameMoved",
	"FrameResized",
	"ResolveSpecifier",
	"ResizeToPreferred",
	"GetPreferredSize",
	"MakeFocus",
	"AllAttached",
	"AllDetached",
	"GetSupportedSuites",
	"Perform",
	NULL
};	

char *msg_gadevents_code_ccplus_scroller[] =
{
	"void AttachedToWindow(void)",
	"void ValueChanged(float value)",
	"void MessageReceived(BMessage *message)",
	"void MouseDown(BPoint point)",
	"void MouseUp(BPoint point)",
	"void MouseMoved(BPoint point,uint32 transit,const BMessage *message)",
	"void DetachedFromWindow(void)",
	"void Draw(BRect updateRect)",
	"void FrameMoved(BPoint parentPoint)",
	"void FrameResized(float width,float height)",
	"BHandler* ResolveSpecifier(BMessage *msg,int32 index,BMessage *specifier,int32 form,const char *property)",
	"void ResizeToPreferred(void)",
	"void GetPreferredSize(float *width,float *height)",
	"void MakeFocus(bool focus = true)",
	"void AllAttached(void)",
	"void AllDetached(void)",
	"status_t GetSupportedSuites(BMessage *data)",
	"status_t Perform(perform_code d,void *arg)",
	NULL
};	

char *msg_gadevents_code_ccplus_scroller_defroutine[] =
{
	"void AttachedToWindow()",
	"void ValueChanged(value)",
	"void MessageReceived(message)",
	"void MouseDown(point)",
	"void MouseUp(point)",
	"void MouseMoved(point,transit,message)",
	"void DetachedFromWindow()",
	"void Draw(updateRect)",
	"void FrameMoved(parentPoint)",
	"void FrameResized(width,height)",
	"BHandler* ResolveSpecifier(msg,index,specifier,form,property)",
	"void ResizeToPreferred()",
	"void GetPreferredSize(width,height)",
	"void MakeFocus(focus)",
	"void AllAttached()",
	"void AllDetached()",
	"status_t GetSupportedSuites(data)",
	"status_t Perform(d,arg)",
	NULL
};	

void
generate_code_ccplus_gad_scroller(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_scroller);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(&buf[0],"BScrollBar%d::BScrollBar%d(BRect rct):BScrollBar(rct,\"%s\",NULL,%d,%d,%s)",count_scroller,count_scroller,&gad->Name[0],gad->data.bscroller.min,gad->data.bscroller.max,orientation_str[(gad->type == SCROLLER_HORIZ_KIND) ? 0 : 1]);

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BScrollBar%d::~BScrollBar%d(void)\n{\n}\n",count_scroller,count_scroller);

		xwrite_string(fi,&buf[0]);

		gencode_gadget_all(fi,gad,"BScrollBar",count_scroller,&msg_gadevents_code_ccplus_scroller[0],&msg_gadevents_code_ccplus_scroller_defroutine[0]);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_scroller(char *path,struct MyGadget *gad)
{
	++count_scroller;

	generate_header_gad_all("ScrollBar",count_scroller,path,gad,&msg_gadevents_code_ccplus_scroller[0]);

	generate_code_ccplus_gad_scroller(path,gad);
}
