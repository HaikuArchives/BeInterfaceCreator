#include <InterfaceKit.h>
#include <SupportKit.h>
#include <StorageKit.h>
#include <AppKit.h>
#include <TranslationKit.h>
#include "ToolTip.h"
#include "proprieties.h"
#include "mylocale.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SpinButton.h"
#include "SpinControl.h"

using namespace BeUnited;

#define GENERATE_ALL_HOOK		(1L << 0)
#define GENERATE_ALL_EMPTY_CALL	(1L << 1)

#define GAD_MAX_TITLE	100
#define GAD_MAX_NAME	100

enum chgcolor
{
	CHANGE_VIEWCOLOR,
	CHANGE_HIGHCOLOR,
	CHANGE_LOWCOLOR,
	CHANGE_BARCOLOR,
};	

enum followh
{
	FOLLOW_NONE,
	FOLLOW_ALL,
	FOLLOW_CHOOSE,
};	

enum follow
{
	FOLLOW_LEFT = 0,
	FOLLOW_RIGHT,
	FOLLOW_LEFT_RIGHT,
	FOLLOW_H_CENTER,

	FOLLOW_TOP,
	FOLLOW_BOTTOM,
	FOLLOW_TOP_BOTTOM,
	FOLLOW_V_CENTER,
};

struct myprefs
{
	int 	magic,ver,size;
	BRect 	prirect,gadrect,projrect,workrect;
	BRect 	tipsrect,editorwinrect;
	bool	gad,prj,edit,place,showstartup;
	bool 	autocreate,autosave,lastprj,confquit,confdel;	
	bool	code_default_void,code_default_routine,code_default_name;
	int 	automin,locale,type,desacdelkey;
	BRect    searchrect,placerect;
	BRect	 editrect;
	BPoint	grillepoint,prefspoint;
	char   	lastprjname[B_PATH_NAME_LENGTH];
	char   	appname[B_PATH_NAME_LENGTH];
	char   	compflag[1025];
	char   	linkflag[1025];
	int		typeapp,optiapp,warningapp,debugapp;
};

#define PREFS_FILE "Bic_Prefs"

#define PROJET_BCC		0
#define PROJET_STANDARD	1

#define	FLAG_SELECTED	(1L << 0)
#define	FLAG_LOCKX		(1L << 1)
#define	FLAG_LOCKY		(1L << 2)
#define	FLAG_LOCKW		(1L << 3)
#define	FLAG_LOCKH		(1L << 4)
#define	IS_FONTLEASING	(1L << 5)

#define	CHANGE_WIDTH	(1L << 0)
#define	CHANGE_HEIGHT	(1L << 1)

enum mlk
{
	MN_FICHIER,
	MN_EDITION,
	MN_OUTILS,
	MN_FENETRE,
	MN_AIDE
};	

enum gadlist
{
	BUTTON_KIND = 0,
	CHECKBOX_KIND,
	STRING_KIND,
	INTEGER_KIND,
	FLOAT_KIND,
	PASSWORD_KIND,
	TAB_KIND,
	BOX_KIND,
	RADIO_KIND,
	MX_KIND,
	TEXT_KIND,
	NUMBER_KIND,
	STATUSBAR_KIND,
	COLOR_KIND,
	LISTVIEW_KIND,
	LISTVIEW_HORIZ_KIND,
	LISTVIEW_VERT_KIND,
	LISTVIEW_ALL_KIND,
	OUTLISTVIEW_KIND,
	OUTLISTVIEW_HORIZ_KIND,
	OUTLISTVIEW_VERT_KIND,
	OUTLISTVIEW_ALL_KIND,
	SLIDER_HORIZ_KIND,
	SLIDER_VERT_KIND,
	SCROLLER_HORIZ_KIND,
	SCROLLER_VERT_KIND,
	TEDIT_KIND,
	TEDIT_HORIZ_KIND,
	TEDIT_VERT_KIND,
	TEDIT_ALL_KIND,
	MENU_KIND,
	VIEW_KIND,

	WINDOW_KIND = 500,
};	

enum center
{
	CENTER_WIDTH,
	CENTER_HEIGHT,
	CENTER_ALL,
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_TOP,
	ALIGN_BOTTOM,
	SPACING_WIDTH,
	SPACING_HEIGHT,
	SPACING_ALL,
	UNIFORM_WIDTH,
	UNIFORM_HEIGHT,
	UNIFORM_ALL,
};

#define	 MAGIC_HEADER_FORM	0xFAACD7045	
#define	 MAGIC_HEADER_PROJ	0xFECAA094E	

#define	PROJET_BASIC		0x4512c
#define	PROJET_C			0x4512d
#define	PROJET_CCPLUS		0x4512e

#define	GAD_EVENTS0		(1L << 0)
#define	GAD_EVENTS1		(1L << 1)
#define	GAD_EVENTS2		(1L << 2)
#define	GAD_EVENTS3		(1L << 3)
#define	GAD_EVENTS4		(1L << 4)
#define	GAD_EVENTS5		(1L << 5)
#define	GAD_EVENTS6		(1L << 6)
#define	GAD_EVENTS7		(1L << 7)

#define	WIN_EVENTS0		(1L << 0)
#define	WIN_EVENTS1		(1L << 1)
#define	WIN_EVENTS2		(1L << 2)
#define	WIN_EVENTS3		(1L << 3)
#define	WIN_EVENTS4		(1L << 4)
#define	WIN_EVENTS5		(1L << 5)
#define	WIN_EVENTS6		(1L << 6)
#define	WIN_EVENTS7		(1L << 7)
#define	WIN_EVENTS8		(1L << 8)
#define	WIN_EVENTS9		(1L << 9)
#define	WIN_EVENTS10	(1L << 10)
#define	WIN_EVENTS11	(1L << 11)
#define	WIN_EVENTS12	(1L << 12)
#define	WIN_EVENTS13	(1L << 13)
#define	WIN_EVENTS14	(1L << 14)
#define	WIN_EVENTS15	(1L << 15)
#define	WIN_EVENTS16	(1L << 16)
#define	WIN_EVENTS17	(1L << 17)
#define	WIN_EVENTS18	(1L << 18)
#define	WIN_EVENTS19	(1L << 19)
#define	WIN_EVENTS22	(1L << 20)
#define	WIN_EVENTS21	(1L << 21)
#define	WIN_EVENTS22	(1L << 22)
#define	WIN_EVENTS23	(1L << 23)

struct	MyGadget
{
	int	x,y;
	int	wi,he;
	int type,align;
	int alignx,aligny;
	int enable,flag;
	int view,msg;
	int64 idcmp;
	BView	*pt;
	struct MyGadget *parent;
	char	Name[50];
	char	Title[50];
	bool	derived,focus;
	char	FontName[127];
	char	FontStyle[127];

	int		FontType,FontSize,FontAntiliasing;

	BList	children;
	BList	name;

	rgb_color	ColHigh,ColLow,ColView;

	union
	{
		struct 
		{
			int defaut;
		}	button;

		struct 
		{
			int	val,sel;
		}	rad;

		struct 
		{
			char Label[100];
			int	pixdiv;
			int sel,align;
		}	mx;

		struct
		{
			int style;
			char Label[100];
		}	bbox;
		
		struct
		{
			int checked;
		}	bcheckbox;

		struct
		{
			int	min,max,pos;
			int	style,hashtype,hashcount;
			int	thickness,keyinc;
			char Label[100],MinLabel[100],MaxLabel[100];
			bool	fillall;
			rgb_color	fillcolor,barcolor;
		}	bslider;
		
		struct
		{
			int	minrange,maxrange,setprop,pos;
			int	minstep,maxstep;
			int min,max;
		}	bscroller;

		struct
		{
			bool editable,selectable;
			int	maxchars,pixdeb,pixdiv;
			int	value;
			int	aligntxt,alignlab;
			bool acceptvir,negvalue;
			int car;
			char Text[100];
		}	string;

		struct
		{
			char Label[100];
			int align;
		}	txt;

		struct
		{
			char Label[100];
			int val;
			int align;
		}	num;

		struct
		{
			int cellsize,layout;
			rgb_color value;
			bool redrawbuffer;
		}	col;

		struct
		{
			char Label[100],Trail[100];
			rgb_color barcolor;
			int barheight,maxvalue,value;
		}	sta;

		struct
		{
			bool multi;
			int sel;
		
		}	lv;

		struct
		{
			bool multi;
			int sel;
		
		}	olv;

		struct 
		{
			int sel,tabwidth,tabheight;
		
		}	tab;	

		struct
		{
			int tabwidth,align,maxchars;
			bool editable,stylable,selectable;
			bool autoident,wordwrap;
		}	edi;
	} data;		
};

class GadView : public BView
{
public:
	GadView(struct MyGadget *gd,BRect rct,int type,char *title);
	~GadView(void);

	virtual void MouseDown(BPoint pt);
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void DrawAfterChildren(BRect rct);
	virtual void AttachedToWindow(void);

	BView 	*gad;
	struct MyGadget *gd;
};

class ColorView : public BView
{
	public:
		ColorView(BRect frame, int);
		~ColorView();
		void Draw(BRect updateRect);
		void MouseDown(BPoint point);
		void SetColor( rgb_color );
		void SetColor( int32, int32, int32 );
		rgb_color GetColor();
		void SetEnabled( bool );
		int cid;
		
	private:
		rgb_color color;
		rgb_color lowcolor;
		bool enabled;
};

class ColorPickerView : public BView
{
	friend class ColorPickerWindow;

	public:
		ColorPickerView(BWindow *wi,BRect rect );
		
	private:
 		BButton* btnSave;
		BButton* btnCancel;
		BColorControl* picker;
		ColorView* colPick;
};


class ColorPickerWindow : public BWindow
{
	public:
		ColorPickerWindow( BRect frame, const char* title, int id, BWindow* own,void *pt);
		~ColorPickerWindow();

		virtual void MessageReceived(BMessage* message);
		virtual void DispatchMessage( BMessage* msg, BHandler* handler );	
		virtual	bool QuitRequested();
		void SetTheColor( rgb_color );

	private:
	
		void *ptr;
		ColorPickerView *genView;
		BWindow* owner;
		int cid;
};

class MyFilterInteger : public BMessageFilter
{
	public:
		
	MyFilterInteger();
	
	virtual filter_result Filter(BMessage *message,BHandler **target);
};

class PrefilledBitmap : public BBitmap
{
	public:
		PrefilledBitmap(BRect bounds, color_space space, const void *data, int32 length = 0,
			bool acceptsViews = false, bool needsContiguousMemory = false);
		~PrefilledBitmap();
};

class TListItem0 : public BListItem
{
public:
		TListItem0(BBitmap *bit,char *name);
		~TListItem0();
	virtual void	DrawItem(BView*, BRect, bool);
	virtual	void	Update(BView*, const BFont*);

	BBitmap		*icon;
	char		*name;
};

class MyView : public BView
{
public:
	MyView(BRect rct);
	~MyView(void);

	virtual void KeyDown(const char *bytes,int32 nb);
	virtual void MouseDown(BPoint pt);
	virtual void MouseUp(BPoint pt);
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void MessageReceived(BMessage *msg);
	virtual void Draw(BRect rct);
};

class MyButton : public BButton
{
public:
	MyButton(BRect rct,char *title);
	~MyButton(void);
	
	virtual void KeyDown(const char *bytes,int32 nb);
	virtual void MouseDown(BPoint pt);
	virtual void MouseUp(BPoint pt);
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void Draw(BRect rct);
};

class MyCheckBox : public BCheckBox
{
public:
	MyCheckBox(BRect rct,char *title);
	~MyCheckBox(void);
	
	virtual void MouseDown(BPoint pt);
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void AttachedToWindow(void);
	virtual void Draw(BRect rct);
	virtual void FrameResized(float wi,float he);
};

class MyColor : public BColorControl
{
public:
	MyColor(BRect rct);
	~MyColor(void);
	
	virtual void MouseDown(BPoint pt);
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void AttachedToWindow(void);
	virtual void Draw(BRect rct);
	virtual void FrameResized(float wi,float he);
	virtual void DrawAfterChildren(BRect rct);
};

class MyBox : public BBox
{
public:
	MyBox(BRect rct,char *title);
	~MyBox(void);
	
	virtual void MouseDown(BPoint pt);
	virtual void AttachedToWindow(void);
	virtual void Draw(BRect rct);
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
};

class MyString : public BTextControl
{
public:
	MyString(BRect rct,char *title);
	~MyString(void);
	
	virtual void MouseDown(BPoint pt);
	virtual void Draw(BRect rct);
	virtual void AttachedToWindow(void);
	virtual void DrawAfterChildren(BRect rct);
};

class MySlider : public BSlider
{
public:
	MySlider(struct MyGadget *gd,BRect rct,orientation pos,char *title);
	~MySlider(void);
	
	virtual void Draw(BRect rct);
	virtual void DrawSlider();

	struct MyGadget *gad;
};

class MyScroller : public BScrollBar
{
public:
	MyScroller(BRect rct,orientation pos);
	~MyScroller(void);
	
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
	virtual void MouseDown(BPoint pt);
	virtual void Draw(BRect rct);
	virtual void DrawAfterChildren(BRect rct);
};

class MyMx : public BMenuField
{
public:
	MyMx(BRect rct,char *title);
	~MyMx(void);
	
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
	virtual void AttachedToWindow(void);
	virtual void MouseDown(BPoint pt);
	virtual void Draw(BRect rct);
	virtual void DrawAfterChildren(BRect rct);
};

class MyRadio : public BRadioButton
{
public:
	MyRadio(BRect rct,char *title);
	~MyRadio(void);
	
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
	virtual void AttachedToWindow(void);
	virtual void MouseDown(BPoint pt);
	virtual void Draw(BRect rct);
	virtual void DrawAfterChildren(BRect rct);
};

class MyListView : public BListView
{
public:
	MyListView(BRect rct,int type);
	~MyListView(void);
	
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
	virtual void MouseDown(BPoint pt);
	virtual void Draw(BRect rct);
	virtual void DrawAfterChildren(BRect rct);
};

class MyStatus : public BStatusBar
{
public:
	MyStatus(BRect rct,char *title);
	~MyStatus(void);
	
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
	virtual void MouseDown(BPoint pt);
	virtual void AttachedToWindow(void);
	virtual void Draw(BRect rct);
	virtual void DrawAfterChildren(BRect rct);
};

class MyText : public BStringView
{
public:
	MyText(BRect rct,char *title);
	~MyText(void);
	
	virtual void MouseMoved(BPoint pt,uint32 transit,const BMessage *msg);
	virtual void FrameResized(float wi,float he);
	virtual void MouseDown(BPoint pt);
	virtual void Draw(BRect rct);
	virtual void AttachedToWindow(void);
	virtual void DrawAfterChildren(BRect rct);
};

class MyContainLv : public BView
{
public:
	MyContainLv(BRect rct);
	
	virtual	void	Draw(BRect rct);
	virtual	void	DrawAfterChildren(BRect rct);
	virtual void    AttachedToWindow(void);
};

class WrkWindow : public BWindow
{
public:
		WrkWindow(BRect rct,char *title);
		~WrkWindow(void);
		
		void	WindowActivated(bool act);
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);

		struct MyGadget *CreateGadget(int type,int x,int y,int wi,int he,bool add = true,bool relative = false,bool check = true,bool attach = true,char *title = NULL);
		struct MyGadget *CheckPosition(int x,int y,bool add = true);
		bool	DeleteGadget(void);
		bool	AcceptMsg(int nb);
		void	SelectAll(void);
		void	UnDelete(void);
		void	InverseSelection(void);
		void	RemoveProjet(void);
		void	UnSelectAll(bool update = true);
		void	AddGadget(struct MyGadget *gd,bool draw = true,bool update = true);
		void	MoveAll(int x,int y);
		void	MoveAllPosition(int x,int y);
		void	MoveGadget(struct MyGadget *gd,int x,int y);
		void	ResizeGadget(struct MyGadget *gd,int x,int y);
		void	MySetFlags(bool set,int nb);
		void	ChangeSize(int flag,int x,int y);
		void	ResizeGadget(int x,int y);
		void	CenterInForm(int flag);
		void	AlignRtn(int flag);
		void	UniForm(int flag);
		void	SpaceInForm(int flag);
		int		CountSelected(int alig,int *val);
		void	ChangeTitleWindow();
		void	PostInfo(bool empty = false);
		void	_Init(void);
		void	SelectPrevGadget(void);
		void	SelectNextGadget(void);
		bool	ExistsMenu(void);
		char	*GetTitle_Gadget(int type);
		void	Cut(void);
		void	Copy(void);
		void	Paste(void);
		void	ChangeFont(int nb);
		void	AllDerived(bool deriv);
		void	SetGrid(bool grid);
		void	LockGadget(int nb,bool lock);

		BList	list,dellist,sellist;
		int		flag;
		int64	idcmp;
		bool	grid;
		int		spacex,spacey;
		int		gridx,gridy;

		char	Name[100];
		char	WTitle[100];
		char	FontName[127];
		char	FontStyle[127];

		int		FontType,FontSize,FontAntiliasing;
		int		Style;
		bool	Visible,Closable,Minimizable,Resizable,Movable,Zoomable,ResizeMode;
		bool 	undelete;
		int		feel,look,wrk,typewin;
		int		minw,minh,maxh,maxw;

	MyView	*bck;
};

#define MyRect(x,y,w,h) BRect(x,y,x + w,y + h)

struct mymenu
{
	char *name;
	bool menu,enable,checked,radio;
	int car,msg;
	int level;
};

class PlaceWindow;
class GadWindow;
class PrjWindow;
class GridWindow;
class PriWindow;
class SpaceWindow;
class WrkWindow;
class SearchWindow;
class EditButtonWindow;

extern GadWindow *GadWin;
extern PrjWindow *PrjWin;
extern WrkWindow *DefWin;
extern PlaceWindow *PlaceWin;
extern SearchWindow *SearchWin;
extern EditButtonWindow *EditorWin;
extern GridWindow *GridWin;
extern SpaceWindow *SpaceWin;

extern struct myprefs prefs;

extern BPoint start;

extern GadView *selected;
extern int offx,offy;
extern BList projet;

extern char ProjetFile[B_PATH_NAME_LENGTH];
extern bool saved;
extern char buf[],buttons[];
extern char *gad_name_basic[];
extern char *gad_name_ccplus[];

extern char *tableau[],*tableau2[],*tableau_button[],*tableau_mx[],*tableau_radio[];
extern char *tableau_bbox[],*tableau_slider[],*tableau_scroller[],*tableau_tab[];
extern char *tableau_pp[],*tableau_integer[],*tableau_color[],*tableau_text[],*tableau_number[];
extern char *tableau_status[],*tableau_lv[],*tableau_olv[],*tableau_menu[],*tableau_etext[];
extern char *tableau_float[],*tableau_string[],*tableau_checkbox[];

extern char ProjetName[];
extern char ProjetPath[];
extern int  ProjetType;
extern BList cliplist;
extern char *type_win[],*wrk_win[],*look_win[],*feel_win[];
extern char *msg_winevents_basic[],*msg_gadevents_basic[];
extern char *msg_winevents_ccplus[]; 
extern char *msg_gadevents_checkbox[];
extern char *msg_gadevents_box[];
extern char *msg_gadevents_color[];
extern char *msg_gadevents_menu[];
extern char *msg_gadevents_slider[];
extern char *msg_gadevents_string[];
extern char *msg_gadevents_mx[];
extern char *msg_gadevents_radio[];
extern char *msg_gadevents_scroller[];
extern char *msg_gadevents_status[];
extern char *msg_gadevents_text[];
extern char *msg_gadevents_tab[];
extern char *msg_gadevents_number[],*selection_lv[];
extern char *msg_gadevents_edit[];
extern char *msg_gadevents_lv[];
extern char *msg_gadevents_olv[],*msg_gadevents_view[];
extern char *msg_gadevents_button[],*alignx_select[],*aligny_select[],*align_select[],*search_type[];
extern char *msg_gadviewflags[],*msg_gadevents_code_ccplus_button[];
extern char *mtab_width[],*msg_windowflags[];

extern WrkWindow *OldWindow;
extern int prefs_genc;
extern int count_button;
extern int count_tab;
extern int count_box;
extern int count_slider;
extern int count_scroller;
extern int count_text;
extern int count_number;
extern int count_listview;
extern int count_outlistview;
extern int count_checkbox;
extern int count_string;
extern int count_tedit;
extern int count_color,count_view;
extern int count_statusbar,count_mx,count_radio;

extern char buf[],*orientation_str[],*layout_color[];
int	count_array(char **tab);
extern unsigned char button_icon[];
extern unsigned char color_icon[];
extern unsigned char checkbox_icon[];
extern unsigned char box_icon[];
extern unsigned char listview_icon[];
extern unsigned char mx_icon[];
extern unsigned char radio_icon[];
extern unsigned char text_icon[];
extern unsigned char string_icon[];
extern unsigned char slider_icon[];
extern unsigned char scroller_icon[];
extern unsigned char menu_icon[];
extern unsigned char tab_icon[];
extern unsigned char tedit_icon[];
extern unsigned char outlistview_icon[];
extern unsigned char status_icon[];

extern FILE *xfi;
extern WrkWindow *defwin;

#include "prototype.h"
#include "SFTexts.h"
