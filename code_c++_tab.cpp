#include "proto.h"

extern FILE *xfi;

char *msg_gadevents_tab[] =
{
	"Select",
	"SetFocusTab",
	"DrawTabs",
	"DrawBox",
	"TabFrame",
	"AddTab",
	"RemoveTab",
	"SetTabWidth",
	"SetTabHeight",
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

char *msg_gadevents_code_ccplus_tab[] =
{
	"void Select(int32 tabIndex)",
	"void SetFocusTab(int32 tabIndex,bool focusState)",
	"BRect DrawTabs(void)",
	"void DrawBox(BRect selectedTabFrame)",
	"BRect TabFrame(int32 tabIndex)",
	"void AddTab(BView* tabContents,BTab* tab=NULL)",
	"BTab* RemoveTab(int32 tabIndex)",
	"void SetTabWidth(button_width width)",
	"void SetTabHeight(float height)",
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

char *msg_gadevents_code_ccplus_tab_defroutine[] =
{
	"void Select(tabIndex)",
	"void SetFocusTab(tabIndex,focusState)",
	"BRect DrawTabs()",
	"void DrawBox(selectedTabFrame)",
	"BRect TabFrame(tabIndex)",
	"void AddTab(tabContents,tab)",
	"BTab* RemoveTab(tabIndex)",
	"void SetTabWidth(width)",
	"void SetTabHeight(height)",
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
generate_header_gad_tab(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],false));
	
	if (fi = fopen(fichier,"w+"))
	{
		sprintf(&buf[0],"#ifndef __Tab%d",count_tab);

		xwrite_string(fi,&buf[0]);	

		xwrite_cr(fi);

		sprintf(&buf[0],"class Tab%d : public BTabView",count_tab);

		xwrite_string(fi,&buf[0]);	

		xwrite_string(fi,"{\npublic:\n");	

		sprintf(&buf[0],"\tTab%d(void);",count_tab);

		xwrite_string(fi,&buf[0]);	

		sprintf(&buf[0],"\t~Tab%d(void);",count_tab);

		xwrite_string(fi,&buf[0]);	

		xwrite_cr(fi);

		gencode_gadget_all(fi,gad,"BTabView",count_tab,&msg_gadevents_code_ccplus_tab[0],&msg_gadevents_code_ccplus_tab_defroutine[0]);

		generate_header_end_creator(fi,"Tab",count_tab);

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
generate_code_ccplus_gad_tab(char *path,struct MyGadget *gad)
{
	char tmp[B_PATH_NAME_LENGTH],*fichier = &tmp[0];

	FILE *fi;

	int nb,k;

	sprintf(fichier,GetNameFile(path,&defwin->Name[0],&gad->Name[0],true));
	
	if (fi = fopen(fichier,"w+"))
	{
		int tb = 0;

		switch(gad->data.tab.tabwidth)
		{
			case	B_WIDTH_FROM_WIDEST:	tb = 0;		break;
			case	B_WIDTH_AS_USUAL:		tb = 1;		break;
			case	B_WIDTH_FROM_LABEL:		tb = 2;		break;
		}

		generate_copyright_include(fi);

		sprintf(&buf[0],"#include \"%s_%s.h\"",&defwin->Name[0],&gad->Name[0],count_tab);

		xwrite_string(fi,&buf[0]);
	
		xwrite_cr(fi);
		xwrite_cr(fi);

		sprintf(&buf[0],"BTab%d::BTab%d(BRect rct):BTabView(rct,\"%s\",%s,%s,%s)",count_tab,count_tab,&gad->Name[0],mtab_width[tb],GetAlign(gad),GetFlagView(gad->view));

		xwrite_string(fi,&buf[0]);

		generate_crochet_code(fi,gad);

		sprintf(&buf[0],"BTab%d::~BTab%d(void)\n{\n}\n",count_tab,count_tab);

		xwrite_string(fi,&buf[0]);

		nb = count_array(&msg_gadevents_code_ccplus_tab[0]);

		for (k = 0; k < nb; k++)
		{
			if (gad->idcmp & (1L << k))
			{
				char *fd,tmp[512];
				
				strcpy(&tmp[0],msg_gadevents_code_ccplus_tab[k]);

				if (fd = strchr(&tmp[0],' '))
				{
					*fd++ = '\0';

					xwrite_string(fi,&tmp[0]);

					sprintf(&buf[0],"BTab%d::%s)",count_tab,fd);

					buf[strlen(&buf[0]) - 1] = 0;

					xwrite_string(fi,&buf[0]);	

					generate_crochet_code(fi);
				}
			}
		}

		fclose(fi);

		set_sourcecode(fichier);
	}
}

void
gen_ccplus_gad_tab(char *path,struct MyGadget *gad)
{
	++count_tab;

	generate_header_gad_tab(path,gad);

	generate_code_ccplus_gad_tab(path,gad);
}
