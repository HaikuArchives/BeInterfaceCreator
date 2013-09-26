#include "SpinButton.h"
#include "SpinControl.h"
#include "edit_proto.h"

using namespace BeUnited;

enum msg_align
{
	window_start = 7000,
	window_look,
	window_feel,
	window_workspace,
	window_type,
	window_minw,
	window_minh,
	window_maxw,
	window_maxh,

	gad_derived = 9150,

	align_type = 9200,
	align_x,
	align_y,

	tab_focus = 9300,
	tab_alignment,
	tab_label,
	tab_font,

	tab_color = 9500,
	tab_color_layout,
	tab_color_cellsize,
	tab_color_drawbuffered,
	tab_color_setvalue,
	tab_color_message,

	tab_selected,

	tab_button = 17000,
	tab_button_default,
	tab_button_enabled,

	tab_checkbox,
	tab_checkbox_checked,
	tab_checkbox_enabled,

	tab_bbox,
	tab_bbox_border,
	tab_bbox_label,
	
	tab_scroller,
	tab_scroller_min,
	tab_scroller_max,
	tab_scroller_value,
	tab_scroller_minstep,
	tab_scroller_maxstep,
	tab_scroller_minrange,
	tab_scroller_maxrange,

	tab_tab,
	tab_tab_height,
	tab_tab_width,
	tab_tab_selected,
	tab_tab_list,

	tab_slider,
	tab_slider_min,
	tab_slider_max,
	tab_slider_value,
	tab_slider_keyinc,
	tab_slider_style,
	tab_slider_hashtype,
	tab_slider_hashcount,
	tab_slider_thickness,
	tab_slider_minlabel,
	tab_slider_maxlabel,
	tab_slider_label,
	tab_slider_message,

	tab_lv,
	tab_lv_multi,
	tab_olv_multi,

	tab_text,
	tab_text_align,
	tab_text_label,
	tab_number_align,
	tab_number_number,

	tab_mx,
	tab_mx_align,
	tab_mx_label,
	tab_mx_diviser,
	tab_mx_list,
	
	tab_string,
	tab_string_label,
	tab_string_message,
	tab_string_aligntxt,
	tab_string_alignlab,
	tab_string_selectable,
	tab_string_editable,
	tab_string_wordwrap,
	tab_string_setstylable,
	tab_string_tabwidth,
	tab_string_maxbytes,
	tab_string_diviser,

	tab_tedit,
	tab_tedit_align,
	tab_tedit_selectable,
	tab_tedit_editable,
	tab_tedit_wordwrap,
	tab_tedit_setstylable,
	tab_tedit_autoident,
	tab_tedit_tabwidth,
	tab_tedit_maxbytes,

	tab_radio,
	tab_radio_value,
	tab_radio_enable,
	tab_radio_list,

	tab_status,
	tab_status_label,
	tab_status_trail,
	tab_status_value,
	tab_status_max,
	tab_status_barheight,
	tab_status_barcolor,

	tab_menu,
	tab_menu_list,
	tab_menu_editlist,
	
};	

class EditButtonWindow : public BWindow
{
public:
		EditButtonWindow(BRect rct,struct MyGadget *gd);
		~EditButtonWindow(void);
		
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);
		virtual void	WindowActivated(bool he);
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	InitGui(void);
		void	SetButton(void);
		void	SetCheckBox(void);
		void	SetSlider(void);
		void	SetScroller(void);
		void	SetBbox(void);
		void	SetColor(void);
		void	SetRadio(void);
		void	SetString(void);
		void	SetInteger(void);
		void	SetMenu(void);
		void	SetFloat(void);
		void	SetPassword(void);
		void	SetText(void);
		void	SetNumber(void);
		void	SetLv(void);
		void	SetOLv(void);
		void	SetTab(void);
		void	SetMx(void);
		void	SetEdit(void);
		void	SetStatus(void);
		void	SetWindow(void);
		void	SetGlobalInformation(void);
		void	ChangeGui(struct MyGadget *gd);
		void	EnableRadio(bool k);	
		void 	OpenColorPicker( BMessage* msg );
		void 	SetNewColor( BMessage* msg );
		void	SetColorGadget(int pos);
	
		struct MyGadget *gad;

		BTab 	*tab1,*tab2,*tab3;
		BView	*vie1,*vie2,*vie3;

		BMenu 		*menu;
		SpinControl *left,*top,*width,*height;
		BTextControl *title,*name,*msg;
		BMenuField  *alig;

		MyListView2	*idcmp;
		MyListView2 	*lv;

		BBox	*bbox;
		BMenuField	*alignx,*aligny;
		BCheckBox	*derived;
};

class EnStringView : public BStringView
{
	public:
		EnStringView( BRect frame, const char* name, const char* text );
		void Draw(BRect updateRect);
		void SetEnabled( bool );
		
	private:
		bool enabled;
};

extern char *align_select[];
extern char *true_false[];
extern char *border_bbox[];
extern char *orientation[];
extern char *hashmarks[];
extern char *align[];
extern char *selection_lv[];
extern char *mtab_width[];
extern char *layout_color[];

