enum rtn_window
{
	OnActivate = 0,
	OnInactive,
	OnMinimize,
	OnMoved,
	OnZoom,
	OnHide,
	OnShow,
	OnPaint,
	OnResized,
	OnScreen,
	OnWkActived,
	OnWkChanged,
	OnClosed,
	OnKey,
	OnMousedown,
	OnMousemove,
	OnTimer,
	OnMenu,
	OnBegin,
	OnWatchdevices,
	OnWatchdir,
	OnDropped,
	OnWatch,
	OnMessage,
	OnEnd
};

enum tags_window
{
	WCaption = 0,
	WTitle,
	WLeft,
	WTop,
	WWidth,
	WHeight,
	WFont,
	WVisible,
	WStyle,
	WResizable,
	WMinimizable,
	WMovable,
	WZoomable,
	WResizeMode,
	WViewColor,
	WHighColor,
	WClosable,
	WminWsize,
	WminHsize,
	WmaxWsize,
	WmaxHsize,
	WEnd
};	

enum rtn_gadget
{
	OnGadClicked = 0,
	OnGadSelect,
	OnGadKeyDown,
	OnKeyFilter,
	OnKeyEnter,
	OnGadDoubleClick,
	OnGadDropped,	
	OnGadDragIcon,
	OnGadEnd
};

enum tags_button
{
	but_Caption = 0,
	but_Title,
	but_Left,
	but_Top,
	but_Width,
	but_Height,
	but_Font,
	but_AntiLiasing,
	but_Disabled,
	but_End
};

enum tags_menu
{
	men_Caption = 0,
	men_End
};

enum tags_bbox
{
	bbox_Caption = 0,
	bbox_Title,
	bbox_Left,
	bbox_Top,
	bbox_Width,
	bbox_Height,
	bbox_Font,
	bbox_AntiLiasing,
	bbox_Disabled,
	bbox_Style,
	bbox_End
};

enum tags_radio
{
	rad_Caption = 0,
	rad_Title,
	rad_Left,
	rad_Top,
	rad_Width,
	rad_Height,
	rad_Font,
	rad_AntiLiasing,
	rad_Disabled,
	rad_Liste,
	rad_Selected,
	rad_End
};

enum tags_mx
{
	mx_Caption = 0,
	mx_Title,
	mx_Left,
	mx_Top,
	mx_Width,
	mx_Height,
	mx_Font,
	mx_AntiLiasing,
	mx_Disabled,
	mx_Liste,
	mx_Align,
	mx_Selected,
	mx_Divider,
	mx_End
};	

enum tags_checkbox
{
	che_Caption = 0,
	che_Title,
	che_Left,
	che_Top,
	che_Width,
	che_Height,
	che_Font,
	che_AntiLiasing,
	che_Disabled,
	che_Checked,
	che_End	
};

enum tags_slider
{
	sli_Caption = 0,
	sli_Title,
	sli_Left,
	sli_Top,
	sli_Width,
	sli_Height,
	sli_Font,
	sli_AntiLiasing,
	sli_Disabled,
	sli_Min,
	sli_Max,
	sli_Pos,
	sli_Style,
	sli_Hashstyle,
	sli_Hashcount,
	sli_Keyinc,
	sli_Minlabel,
	sli_Maxlabel,
	sli_Fillall,
	sli_Fillcolor,
	sli_Barcolor,
	sli_End
};

enum tags_scroller
{
	scr_Caption = 0,
	scr_Title,
	scr_Left,
	scr_Top,
	scr_Width,
	scr_Height,
	scr_Font,
	scr_AntiLiasing,
	scr_Disabled,
	scr_Min,
	scr_Max,
	scr_Pos,
	scr_Setprop,
	scr_Minstep,
	scr_Maxstep,
	scr_End
};

enum tags_integer
{
	int_Caption = 0,
	int_Title,
	int_Left,
	int_Top,
	int_Width,
	int_Height,
	int_Font,
	int_AntiLiasing,
	int_Disabled,
	int_Align,
	int_Value,
	int_MaxChars,
	int_Selectable,
	int_Editable,
	int_NegValue,
	int_Divider,
	int_End
};

enum tags_string
{
	str_Caption = 0,
	str_Title,
	str_Left,
	str_Top,
	str_Width,
	str_Height,
	str_Font,
	str_AntiLiasing,
	str_Disabled,
	str_Align,
	str_Text,
	str_MaxChars,
	str_Selectable,
	str_Editable,
	str_Divider,
	str_End
};

enum tags_pp
{
	pp_Caption = 0,
	pp_Title,
	pp_Left,
	pp_Top,
	pp_Width,
	pp_Height,
	pp_Font,
	pp_AntiLiasing,
	pp_Disabled,
	pp_Align,
	pp_Text,
	pp_MaxChars,
	pp_Selectable,
	pp_Editable,
	pp_Char,
	pp_Divider,
	pp_End
};

enum tags_float
{
	flo_Caption = 0,
	flo_Title,
	flo_Left,
	flo_Top,
	flo_Width,
	flo_Height,
	flo_Font,
	flo_AntiLiasing,
	flo_Disabled,
	flo_Align,
	flo_Value,
	flo_MaxChars,
	flo_Selectable,
	flo_Editable,
	flo_NegValue,
	flo_AcceptVir,
	flo_Divider,
	flo_End
};

enum tags_number
{
	num_Caption = 0,
	num_Title,
	num_Left,
	num_Top,
	num_Width,
	num_Height,
	num_Font,
	num_AntiLiasing,
	num_Disabled,
	num_Number,
	num_Alignment,
	num_End
};

enum tags_text
{
	txt_Caption = 0,
	txt_Title,
	txt_Left,
	txt_Top,
	txt_Width,
	txt_Height,
	txt_Font,
	txt_AntiLiasing,
	txt_Disabled,
	txt_Text,
	txt_Alignment,
	txt_End
};

enum tags_color
{
	col_Caption = 0,
	col_Title,
	col_Left,
	col_Top,
	col_Width,
	col_Height,
	col_Font,
	col_AntiLiasing,
	col_Disabled,
	col_CellSize,
	col_Layout,
	col_Value,
	col_End
};

enum tags_status
{
	sta_Caption = 0,
	sta_Title,
	sta_Left,
	sta_Top,
	sta_Width,
	sta_Height,
	sta_Font,
	sta_AntiLiasing,
	sta_Disabled,
	sta_Trail,
	sta_BarColor,
	sta_BarHeight,
	sta_MaxValue,
	sta_Value,
	sta_End
};

enum tags_lv
{
	lv_Caption = 0,
	lv_Title,
	lv_Left,
	lv_Top,
	lv_Width,
	lv_Height,
	lv_Font,
	lv_AntiLiasing,
	lv_Disabled,
	lv_MultiSel,
	lv_Sel,
	lv_End	
};

enum tags_olv
{
	olv_Caption = 0,
	olv_Title,
	olv_Left,
	olv_Top,
	olv_Width,
	olv_Height,
	olv_Font,
	olv_AntiLiasing,
	olv_Disabled,
	olv_MultiSel,
	olv_Sel,
	olv_End	
};

enum tags_edit
{
	edi_Caption = 0,
	edi_Title,
	edi_Left,
	edi_Top,
	edi_Width,
	edi_Height,
	edi_Font,
	edi_AntiLiasing,
	edi_Disabled,
	edi_Selectable,
	edi_Editable,
	edi_TabWidth,
	edi_WordWrap,
	edi_AutoIdent,
	edi_Align,
	edi_MaxChars,
	edi_End
};

enum tags_tab
{
	tab_Caption = 0,
	tab_Title,
	tab_Left,
	tab_Top,
	tab_Width,
	tab_Height,
	tab_Font,
	tab_AntiLiasing,
	tab_Disabled,
	tab_TabWidth,
	tab_TabHeight,
	tab_Liste,
	tab_Select,
	tab_End
};	

class CheckItemBox : public BListItem
{
public:
					CheckItemBox(char *src,bool checked = false);
					~CheckItemBox();
	virtual void	DrawItem(BView*, BRect, bool);
	virtual void	Update(BView*,const BFont *);

	bool			checked;
	char			*name;
};

class MyListView2 : public BListView
{
public:
	MyListView2(BRect rct);
	~MyListView2();
	virtual	void	MouseDown(BPoint pt);

	void	MakeEmpty();

	char **tab;

private:
	int32 mLastButton;
	int32 mClickCount;
};

class MyListView3 : public BListView
{
public:
	MyListView3(BRect rct);
	~MyListView3();
	virtual	void	MouseDown(BPoint pt);

	void	MakeEmpty();

	char **tab;

private:
	int32 mLastButton;
	int32 mClickCount;
};

class TEZLauncherView : public BListView
{
public:
					TEZLauncherView(BRect);
					~TEZLauncherView();
	virtual void	AttachedToWindow();
	virtual void	MakeEmpty();
	virtual void	Draw(BRect);
	virtual	void 	KeyDown(const char *bytes,int32 nb);
	virtual void	MouseDown(BPoint);
	virtual void	MouseMoved(BPoint,uint32 code,const BMessage *msg);
	BPopUpMenu		*fMenu;
};

class MyBTabView : public BTabView
{
public:
	
	MyBTabView(BRect rct);

	MyListView2 *list0;
	MyListView2 *list1;
	
	virtual void Select(int32 nb);
};	

class InfoWin : public BWindow
{
public:
					InfoWin(BRect frame); 
	virtual void	MessageReceived(BMessage*);
	virtual	bool	QuitRequested();
	virtual	void	Quit(void);
	virtual void	FrameMoved(BPoint pt);
	virtual void	WindowActivated(bool foc);
	virtual void	FrameResized(float wi,float he);
	void			SetInformation(void);

	MyListView2 *fList0;
	MyListView2 *fList1;

	MyBTabView 	*tb;
	BTab		*s0,*s1;
	BView		*fd,*v0,*v1;
	bool ok;
};
