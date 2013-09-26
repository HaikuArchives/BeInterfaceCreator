//main.cpp
void	open_priwin(void);
void	placement_win(void);

//window.cpp
void	create_window(void);

//projet_win.cpp
void	create_projet_window(void);
void	search_window(void);

//win_gadget.cpp
void	create_gadget_window(void);
void	error_loading(int err);

//prefs.cpp
void	load_prefs(void);
void	default_prefs(void);
void	save_prefs(void);
int		SysAlert(char *str,char *ok);
void	grid_window(void);
char	*OpenFileReq(char *title,char *pathname,char *type = "a",char *mime = NULL,int xtype = B_OPEN_PANEL);
char	*SaveFileReq(char *title,char *name,char *pathname,char *mime = NULL);

//mime.cpp
void	check_isinstalled_mime(void);
void	install_mime(void);
void	set_mimefile(char *file,char *mime);
void	window_menu(void);

//sauvegarde.cpp
void	save_file(char *txt);
bool	write_data(void *pt,int nb);
bool	read_data(void *pt,int nb);
bool	write_double(double val);
bool	write_integer(int nb);
int		read_integer(void);
double	read_double(void);
bool	write_short(short nb);
short	read_short(void);
bool	read_string(char *str);
bool	seek_file(int type,int nb);
int		get_file_len(void);
bool	write_string(char *str,bool addcr = false);
void	sauve_gadget(struct MyGadget *gd);
void	sauve_window(WrkWindow *wi);
void	set_projet_update(void);
void 	window_menu(BList *ls);
void	save_as_files(void);
void	prefs_window(void);
void 	Editor_Win(void);
int		GetDataTableau(void);
void	spacement_window(void);

//filerequester.cpp
void	load_files(void);
void	save_files(void);
void	load_file(char *str);
char 	*MyStringStr(char *str);

char 	*GetTitle_Form(void);
void	DrawGadget(BView *view);
BView 	*Create_Tab(BRect rct,char *title);
BView 	*Create_Mx(BRect rct,char *title);
BView 	*Create_Lv(BRect rct,int type);
BView 	*Create_TEdit(BRect rct,int type);
void	*MyAlloc(int size);
void	MyFree(void *dat);
BPictureButton *CreateButton(BRect rct,char *a0,char *a1,int msg);
extern	void	GetBufferData_Window(int k,char *str);
extern	void	GetBufferData_Button(int k,char *str);
extern	void	GetBufferData_Mx(int k,char *str);
extern	void	GetBufferData_Radio(int k,char *str);
extern	void	GetBufferData_BBox(int k,char *str);
extern	void	GetBufferData_CheckBox(int k,char *str);
extern	void	GetBufferData_Scroller(int k,char *str);
extern	void	GetBufferData_Slider(int k,char *str);
extern	void	GetBufferData_Integer(int k,char *str);
extern	void	GetBufferData_String(int k,char *str);
extern	void	GetBufferData_Float(int k,char *str);
extern	void	GetBufferData_PP(int k,char *str);
extern	void	GetBufferData_Status(int k,char *str);
extern	void	GetBufferData_Color(int k,char *str);
extern	void	GetBufferData_Texte(int k,char *str);
extern	void	GetBufferData_Number(int k,char *str);
extern	void	GetBufferData_Tab(int k,char *str);
extern	void	GetBufferData_Menu(int k,char *str);
extern	void	GetBufferData_EText(int k,char *str);
extern	void	GetBufferData_ListView(int k,char *str);
extern	void	GetBufferData_OutListView(int k,char *str);
extern  char 	*GetBoolean(bool ret);
extern  char 	*GetAlignmentStyleStr(int nb);
extern  char 	*GetStyleBBox(int style);
extern  char 	*GetLayoutColor(int lay);
extern  char	*GetStringColor(rgb_color *cl);
extern  char	*GetStyleSliderHash(int nb);
extern  char	*GetStyleSlider(int nb);
void	About(void);
void	generate_basic(void);
void	generate_c(void);
void	generate_ccplus(void);
void	new_projet(void);
void	add_form(void);
void	show_help(void);
void	arrange_win0(void);
void	arrange_win1(void);
void	arrange_win2(void);
void	change_infowin_number(int type,int val);
void	busy_cursor(bool busy);
void	startup_tips(void);
BMenu 	*CreateMenu(BWindow *wi,char **tab,int msg,int sel);
BMenu 	*CreateMenu(BWindow *wi);
BMenuField *CreateMx(BRect rct,char *title,BMenu *mn,int div);
SpinControl *CreateSpin(BRect rct,char *title,int msg,int min,int max,int val,int div);
BCheckBox *CreateCheck(BRect rct,char *title,int msg,bool check);
void	AddItemInMenu(BMenu *mn,char *str,int what);
void	SetChoiceInMenu(BMenu *mn,int chx,bool check);
void	xwrite_string(char *str,bool cr = true);
void	xwrite_cr(void);
bool	IsSameColor(rgb_color *a,rgb_color *b);
void	addmenu_recent(BMenu *mn);
bool	is_not_in_list(char *str);
void	Store_Path_Files(char *chemin);
void	Save_Path_Files(void);
void	edit_win_tags(WrkWindow *edit);

void	SetSpinDivider(SpinControl *ct,int nb);
void	SetDivider(BTextControl *ct,int nb);
void	SetDivider(BMenuField *ct,int nb);
BView 	*CreateView(BRect rct);

void	edit_button_tags(struct MyGadget *gd);
BRadioButton *CreateRadio(BRect rct,char *title,int msg);
BTextControl *CreateString(BRect rct,char *title,int msg,int div);

void	SaveButton(struct MyGadget *gd);
void	SaveCheckBox(struct MyGadget *gd);
void	SaveBbox(struct MyGadget *gd);
void	SaveColor(struct MyGadget *gd);
void	SaveSlider(struct MyGadget *gd);
void	SaveString(struct MyGadget *gd);
void	SaveMx(struct MyGadget *gd);
void	SaveRadio(struct MyGadget *gd);
void	SaveScroller(struct MyGadget *gd);
void	SaveStatus(struct MyGadget *gd);
void	SaveText(struct MyGadget *gd);
void	SaveTab(struct MyGadget *gd);
void	SaveNumber(struct MyGadget *gd);
void	SaveEdit(struct MyGadget *gd);
void	SaveLv(struct MyGadget *gd);
void	SaveOLv(struct MyGadget *gd);

void	SetTagsButton(struct MyGadget *gd);
void	SetTagsCheckBox(struct MyGadget *gd);
void	SetTagsBbox(struct MyGadget *gd);
void	SetTagsColor(struct MyGadget *gd);
void	SetTagsSlider(struct MyGadget *gd);
void	SetTagsString(struct MyGadget *gd);
void	SetTagsMx(struct MyGadget *gd);
void	SetTagsRadio(struct MyGadget *gd);
void	SetTagsScroller(struct MyGadget *gd);
void	SetTagsStatus(struct MyGadget *gd);
void	SetTagsText(struct MyGadget *gd);
void	SetTagsTab(struct MyGadget *gd);
void	SetTagsNumber(struct MyGadget *gd);
void	SetTagsEdit(struct MyGadget *gd);
void	SetTagsLv(struct MyGadget *gd);
void	SetTagsOLv(struct MyGadget *gd);

void	LoadButton(struct MyGadget *gd);
void	LoadCheckBox(struct MyGadget *gd);
void	LoadBbox(struct MyGadget *gd);
void	LoadColor(struct MyGadget *gd);
void	LoadSlider(struct MyGadget *gd);
void	LoadString(struct MyGadget *gd);
void	LoadMx(struct MyGadget *gd);
void	LoadRadio(struct MyGadget *gd);
void	LoadScroller(struct MyGadget *gd);
void	LoadStatus(struct MyGadget *gd);
void	LoadText(struct MyGadget *gd);
void	LoadTab(struct MyGadget *gd);
void	LoadNumber(struct MyGadget *gd);
void	LoadEdit(struct MyGadget *gd);
void	LoadLv(struct MyGadget *gd);
void	LoadOLv(struct MyGadget *gd);
rgb_color	GetRgbFromInteger(int d);
int			ReturnIntFromRgb(int a,int b,int c);
void		write_color(rgb_color *cl);
void		read_color(rgb_color *cl);

void	set_bbox_border(struct MyGadget *gd,int border);
void	set_bbox_label(struct MyGadget *gd,char *txt);

void	set_button_defaut(struct MyGadget *gd,bool def);
void	set_button_enable(struct MyGadget *gd,bool def);
void	set_button_label(struct MyGadget *gd,char *def);

void	set_checkbox_checked(struct MyGadget *gd,bool def);

void	set_color_layout(struct MyGadget *gd,int val);
void	set_color_cellsize(struct MyGadget *gd,int val);
void	set_color_value(struct MyGadget *gd,int val);
void	set_mx_align(struct MyGadget *gd,int val);
void	set_mx_label(struct MyGadget *gd,char *txt);
void	set_mx_divider(struct MyGadget *gd,int val);
void	set_mx_select(struct MyGadget *gd,int val);

void	set_radio_checked(struct MyGadget *gd,int tb);
void	set_radio_enabled(struct MyGadget *gd,int tb);

void	set_scroller_value(struct MyGadget *gd,int val);
void	set_scroller_minstep(struct MyGadget *gd,int val);
void	set_scroller_maxstep(struct MyGadget *gd,int val);
void	set_scroller_minrange(struct MyGadget *gd,int val);
void	set_scroller_maxrange(struct MyGadget *gd,int val);

void	set_slider_value(struct MyGadget *gd,int val);
void	set_slider_style(struct MyGadget *gd,int val);
void	set_slider_keyinc(struct MyGadget *gd,int val);
void	set_slider_thickness(struct MyGadget *gd,int val);
void	set_slider_hashcount(struct MyGadget *gd,int val);
void	set_slider_barcolor(struct MyGadget *gd,int val);
void	set_slider_fillcolor(struct MyGadget *gd,int val);
void	set_slider_hashtype(struct MyGadget *gd,int val);
void	set_slider_minlabel(struct MyGadget *gd,char *txt);
void	set_slider_label(struct MyGadget *gd,char *txt);
void	set_slider_maxlabel(struct MyGadget *gd,char *txt);

void	set_status_barheight(struct MyGadget *gd,int val);
void	set_status_value(struct MyGadget *gd,int val);
void	set_status_barcolor(struct MyGadget *gd,int val);
void	set_status_maxvalue(struct MyGadget *gd,int val);
void	set_status_label(struct MyGadget *gd,char *txt);
void	set_status_trail(struct MyGadget *gd,char *txt);

void	set_string_alignment_text(struct MyGadget *gd,int val);
void	set_string_alignment_label(struct MyGadget *gd,int val);
void	set_string_divider(struct MyGadget *gd,int val);
void	set_string_label(struct MyGadget *gd,char *txt);

void	set_tab_width(struct MyGadget *gd,int val);
void	set_tab_height(struct MyGadget *gd,int tb);
void	set_tab_select(struct MyGadget *gd,int tb);

void	set_text_align(struct MyGadget *gd,int val);
void	set_text_text(struct MyGadget *gd,char *txt);
void	set_number_value(struct MyGadget *gd,int val);
void	SetEnableGadget(struct MyGadget *gd,bool state);

void	SetStringLen(BTextControl *xt,int nb);
BTextControl *CreateInteger(BRect rct,char *title,int msg,int div);
BButton *CreateButton(BRect rct,char *title,int msg);
void	ChangeWindowType(WrkWindow *wi,int type);
void	AddListWindow(struct MyGadget *gd);
void	create_mmxmenu(void);
void	ChangeView(int item,bool set);
extern void change_gadget_list(struct MyGadget *gd);
void	load_string(int nb,struct MyGadget *gd);
void	gencode_ccplus(char *str,char *fichier,WrkWindow *wi);
void	gencode_basic(char *fichier,WrkWindow *wi);
void	gencode_c(char *fichier,WrkWindow *wi);
bool	write_long(int64 nb);
int64	read_long(void);
void	xwrite_string(FILE *fi,char *str,bool cr = true);
void	xwrite_cr(FILE *fi);
void	generate_copyright_include(FILE *fi);
void	generate_header_ccplus_window(char *path,WrkWindow *wi);
void	generate_code_ccplus_window(char *path,WrkWindow *wi);

void	generate_header_gad_button(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_button(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_button(char *str,struct MyGadget *gad);

void	generate_header_gad_box(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_box(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_box(char *str,struct MyGadget *gad);

void	generate_header_gad_slider(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_slider(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_slider(char *str,struct MyGadget *gad);

void	generate_header_gad_tab(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_tab(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_tab(char *str,struct MyGadget *gad);

void	generate_header_gad_scroller(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_scroller(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_scroller(char *str,struct MyGadget *gad);

void	generate_header_gad_listview(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_listview(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_listview(char *str,struct MyGadget *gad);

void	generate_header_gad_view(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_view(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_view(char *str,struct MyGadget *gad);

void	generate_header_gad_tedit(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_tedit(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_tedit(char *str,struct MyGadget *gad);

void	generate_header_gad_outlistview(char *str,struct MyGadget *gad);
void	generate_code_ccplus_outlistview(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_outlistview(char *str,struct MyGadget *gad);

void	generate_header_gad_text(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_text(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_text(char *str,struct MyGadget *gad);

void	generate_header_gad_statusbar(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_statusbar(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_statusbar(char *str,struct MyGadget *gad);

void	generate_header_gad_string(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_string(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_string(char *str,struct MyGadget *gad);

void	generate_header_gad_color(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_color(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_color(char *str,struct MyGadget *gad);

void	generate_header_gad_checkbox(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_checkbox(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_checkbox(char *str,struct MyGadget *gad);

void	generate_header_gad_number(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_number(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_number(char *str,struct MyGadget *gad);

void	generate_header_gad_number(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_number(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_number(char *str,struct MyGadget *gad);

void	generate_header_gad_radio(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_radio(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_radio(char *str,struct MyGadget *gad);

void	generate_header_gad_mx(char *str,struct MyGadget *gad);
void	generate_code_ccplus_gad_mx(char *str,struct MyGadget *gad);
void	gen_ccplus_gad_mx(char *str,struct MyGadget *gad);

void	generate_header_end_creator(FILE *fi,char *name,int nb);
void	generate_header_begin_creator(FILE *fi,char *name,int nb);
void	generate_crochet_code(FILE *fi,struct MyGadget *gad = NULL,char *txt = "");
void	generate_code(void);

char 	*GetMessage(int nb);
char 	*GetAlign(struct MyGadget *gd);
char 	*GetTitle(struct MyGadget *gd);
char 	*GetFlagView(int nb);
char 	*GetNameFile(char *path,char *win,char *type,bool ccplus);
void	set_sourcecode(char *file);
void	create_makefile(char *str);
void	create_header_application(char *appname);
void	create_application(char *appname);
void	generate_code_menu(FILE *fi,struct MyGadget *gad);
char 	*ToLower(char *p);
void	docommand(WrkWindow *wi,int cmd);
void	keypress(WrkWindow *wi,int key);
void	load_keypress(void);
void	arrange_showall(bool show);
void	font_window(int a,int b,int c,char *name,char *style);
void	clear_recent(void);
void	gencode_gadget_all(FILE *fi,struct MyGadget *gad,char *str,int count,char **tab0,char **tab1);
void	generate_header_gad_all(char *name,int count,char *path,struct MyGadget *gad,char **tab);



