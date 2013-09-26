//button
void	set_button_defaut(struct MyGadget *gd,bool def);
void	set_button_enable(struct MyGadget *gd,bool def);
void	set_button_label(struct MyGadget *gd,char *def);
//checkbox
void	set_checkbox_checked(struct MyGadget *gd,bool def);
//bbox
void	set_bbox_border(struct MyGadget *gd,int border);
void	set_bbox_label(struct MyGadget *gd,char *txt);
//scroller
void	set_scroller_value(struct MyGadget *gd,int val);
void	set_scroller_minstep(struct MyGadget *gd,int val);
void	set_scroller_maxstep(struct MyGadget *gd,int val);
void	set_scroller_minrange(struct MyGadget *gd,int val);
void	set_scroller_maxrange(struct MyGadget *gd,int val);
//tab
void	set_tab_width(struct MyGadget *gd,int val);
void	set_tab_height(struct MyGadget *gd,int val);
//slider
void	set_slider_value(struct MyGadget *gd,int val);
void	set_slider_style(struct MyGadget *gd,int val);
void	set_slider_keyinc(struct MyGadget *gd,int val);
void	set_slider_thickness(struct MyGadget *gd,int val);
void	set_slider_hashcount(struct MyGadget *gd,int val);
void	set_slider_hashtype(struct MyGadget *gd,int val);
void	set_slider_minlabel(struct MyGadget *gd,char *txt);
void	set_slider_maxlabel(struct MyGadget *gd,char *txt);
void	set_slider_label(struct MyGadget *gd,char *txt);
//color
void	set_color_layout(struct MyGadget *gd,int val);
void	set_color_cellsize(struct MyGadget *gd,int val);
void	set_color_value(struct MyGadget *gd,int val);
//text & number
void	set_text_align(struct MyGadget *gd,int val);
void	set_number_value(struct MyGadget *gd,int val);
void	set_text_text(struct MyGadget *gd,char *txt);
//string
void	set_string_alignment_text(struct MyGadget *gd,int val);
void	set_string_alignment_label(struct MyGadget *gd,int val);
void	set_string_divider(struct MyGadget *gd,int val);
void	set_string_label(struct MyGadget *gd,char *txt);
//mx
void	set_mx_align(struct MyGadget *gd,int val);
void	set_mx_label(struct MyGadget *gd,char *txt);
void	set_mx_divider(struct MyGadget *gd,int val);
void	set_mx_select(struct MyGadget *gd,int val);	
//radio
void	set_radio_checked(struct MyGadget *gd,int tb);
void	set_radio_enabled(struct MyGadget *gd,int tb);
//status
void	set_status_barheight(struct MyGadget *gd,int val);
void	set_status_barcolor(struct MyGadget *gd,int val);
void	set_status_value(struct MyGadget *gd,int val);
void	set_status_maxvalue(struct MyGadget *gd,int val);
void	set_status_label(struct MyGadget *gd,char *txt);
void	set_status_trail(struct MyGadget *gd,char *txt);
