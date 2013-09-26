#include "proto.h"

SpaceWindow *SpaceWin = 0;
GadWindow *GadWin = 0;
PrjWindow *PrjWin = 0;
PriWindow *PriWin = 0;
WrkWindow *DefWin = 0;
PlaceWindow *PlaceWin = 0;
SearchWindow *SearchWin = 0;
EditButtonWindow *EditorWin = 0;
GridWindow *GridWin = 0;

struct myprefs prefs;
BList projet;

char buf[B_PATH_NAME_LENGTH];
bool saved = false;
char buttons[] = "buttons";

char ProjetName[100] = "";
char ProjetPath[B_PATH_NAME_LENGTH] = "";
char ProjetFile[B_PATH_NAME_LENGTH] = "";
int  ProjetType;

char *alignx_select[] =
{
	"B_FOLLOW_LEFT",
	"B_FOLLOW_RIGHT",
	"B_FOLLOW_LEFT_RIGHT",
	"B_FOLLOW_H_CENTER",
	NULL
};

char *aligny_select[] =
{
	"B_FOLLOW_TOP",
	"B_FOLLOW_BOTTOM",
	"B_FOLLOW_TOP_BOTTOM",
	"B_FOLLOW_V_CENTER",
	NULL
};

char *align_select[] =
{
	"B_FOLLOW_NONE",
	"B_FOLLOW_ALL",
	"Choose",
	NULL
};	

char *true_false[] =
{
	"False",
	"True",
	NULL
};	

char *border_bbox[] =
{
	"B_PLAIN_BORDER",
	"B_FANCY_BORDER",
	"B_NO_BORDER",
	NULL
};	

char *orientation_str[] =
{
	"B_HORIZONTAL",
	"B_VERTICAL",
	NULL
};	

char *hashmarks[] =
{
	"B_HASH_MARKS_NONE",
	"B_HASH_MARKS_TOP",
	"B_HASH_MARKS_LEFT",
	"B_HASH_MARKS_BOTTOM",
	"B_HASH_MARKS_RIGHT",
	"B_HASH_MARKS_BOTH",
	NULL
};	

char *align[] =
{
	"B_ALIGN_LEFT",
	"B_ALIGN_RIGHT",
	"B_ALIGN_CENTER",
	NULL
};	

char *selection_lv[] = 
{
	"B_SINGLE_SELECTION_LIST",
	"B_MULTIPLE_SELECTION_LIST",
	NULL
};	

char *mtab_width[] =
{
	"B_WIDTH_AS_USUAL",
	"B_WIDTH_FROM_WIDEST",
	"B_WIDTH_FROM_LABEL",
	NULL
};	

char *layout_color[] =
{
	"4x64",
	"8x32",
	"16x16",
	"64x4",
	"32x8",
	NULL
};	

char *gad_name_basic[] =
{
	"Button",
	"Checkbox",
	"String",
	"Integer",
	"Float",
	"Password",
	"Tab",
	"Box",
	"Radio",
	"Mx",
	"Text",
	"Number",
	"Statusbar",
	"Color",
	"Listview",
	"Listview horiz",
	"Listview vert",
	"Listview all",
	"Outlistview",
	"Outlistview horiz",
	"Outlistview vert",
	"Outlistview all",
	"Slider horiz",
	"Slider vert",
	"Scroller horiz",
	"Scroller vert",
	"TextEditor",
	"TextEditor horiz",
	"TextEditor vert",
	"TextEditor all",
	"Menu",
	NULL
};	

char *gad_name_ccplus[] =
{
	"BButton",
	"BCheckbox",
	"BTextControl",
	"BTextControl (Integer)",
	"BTextControl (Float)",
	"BTextControl (Password)",
	"BTab",
	"BBox",
	"BRadio",
	"BMenuField",
	"BStringView ",
	"BStringView (Number)",
	"BStatusbar",
	"BColorControl",
	"BListview",
	"BListview horiz",
	"BListview vert",
	"BListview all",
	"BOutlinelistview",
	"BOutlinelistview horiz",
	"BOutlinelistview vert",
	"BOutlinelistview all",
	"BSlider horiz",
	"Blider vert",
	"BScroller horiz",
	"BSroller vert",
	"BTextView",
	"BTextView horiz",
	"BTextView vert",
	"BTextView all",
	"BMenuBar",
	"BView",
	NULL
};	

char *tableau[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"Visible",
	"Style",
	"Resizable",
	"Minimizable",
	"Movable",
	"Zoomable",
	"ResizeMode",
	"ViewColor",
	"HighColor",
	"Closable",
	"MinWidthSize",
	"MinHeightSize",
	"MaxWidthSize",
	"MaxHeightSize",
	NULL
};

char *tableau_button[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"Antiliasing",
	"Disabled",
	NULL
};

char *tableau_mx[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Liste",
	"Align",
	"Selected",
	"Divider",
	NULL
};

char *tableau_radio[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Liste",
	"Selected",
	NULL
};

char *tableau_bbox[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"Antiliasing",
	"Disabled",
	"Style",
	NULL
};

char *tableau_slider[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Min",
	"Max",
	"Pos",
	"Style",
	"Hashstyle",
	"Hashcount",
	"Keyinc",
	"Minlabel",
	"Maxlabel",
	"Fillall",
	"Fillcolor",
	"Barcolor",
	NULL
};

char *tableau_scroller[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Min",
	"Max",
	"Pos",
	"Setprop",
	"Minstep",
	"Maxstep",
	NULL
};

char *tableau_tab[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"TabWidth",
	"TabHeight",
	"Liste",
	"Select",
	NULL
};

char *tableau_number[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Number",
	"Alignment",
	NULL
};

char *tableau_text[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Text",
	"Alignment",
	NULL
};

char *tableau_integer[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Align",
	"Value",
	"MaxChars",
	"Selectable",
	"Editable",
	"NegValue",
	"Divider",
	NULL
};

char *tableau_pp[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Align",
	"Text",
	"MaxChars",
	"Selectable",
	"Editable",
	"Char",
	"Divider",
	NULL
};

char *tableau_color[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"CellSize",
	"Layout",
	"Value",
	NULL
};

char *tableau_olv[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"MultiSel",
	"Sel",
	NULL
};

char *tableau_lv[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"MultiSel",
	"Sel",
	NULL
};

char *tableau_status[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Trail",
	"BarColor",
	"BarHeight",
	"MaxValue",
	"Value",
	NULL
};

char *tableau_string[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Align",
	"Text",
	"MaxChars",
	"Selectable",
	"Editable",
	"Divider",
	NULL
};

char *tableau_float[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Align",
	"Value",
	"MaxChars",
	"Selectable",
	"Editable",
	"NegValue",
	"AcceptVir",
	"Divider",
	NULL
};

char *tableau_etext[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Selectable",
	"Editable",
	"TabWidth",
	"WordWrap",
	"AutoIdent",
	"Align",
	"MaxChars",
	NULL
};

char *tableau_menu[] =
{
	"Liste",
	NULL
};

char *tableau_checkbox[] =
{
	"Caption",
	"Title",
	"Left",
	"Top",
	"Width",
	"Height",
	"Font",
	"AntiLiasing",
	"Disabled",
	"Checked",
	NULL
};

char *type_win[] =
{
	"B_TITLED_WINDOW",
	"B_MODAL_WINDOW",
	"B_DOCUMENT_WINDOW",
	"B_BORDERED_WINDOW",
	"B_FLOATING_WINDOW",
	NULL
};	

char *wrk_win[] =
{
	"B_CURRENT_WORKSPACE",
	"B_ALL_WORKSPACE",
	NULL
};	

char *look_win[] =
{
	"B_BORDERED_WINDOW_LOOK",
	"B_NO_BORDERED_WINDOW_LOOK",
	"B_TITLED_WINDOW_LOOK",
	"B_DOCUMENT_WINDOW_LOOK",
	"B_MODAL_WINDOW_LOOK",
	"B_FLOATING_WINDOW_LOOK",
	NULL
};

char *feel_win[] =
{
	"B_NORMAL_WINDOW_FEEL",
	"B_MODAL_SUBSET_WINDOW_FEEL",
	"B_MODAL_APP_WINDOW_FEEL",
	"B_MODAL_ALL_WINDOW_FEEL",
	"B_FLOATING_SUBSET_WINDOW_FEEL",
	"B_FLOATING_APP_WINDOW_FEEL",
	"B_FLOATING_ALL_WINDOW_FEEL",
	NULL
};	

char *msg_winevents_basic[] = 
{
	"Active",
	"Inactive",
	"Minimize",
	"Moved",
	"Zoom",
	"Hide",
	"Show",
	"Paint",
	"Resized",
	"Screen",
	"WKactived",
	"Wkchanged",
	"Closed",
	"Key",
	"Mousedown",
	"Mousemouve",
	"Timer",
	"Menu",
	"Begin",
	"Watchdevices",
	"Watchdir",
	"Dropped",
	"WatchApp",
	"Message",
	NULL
};

char *msg_winevents_ccplus[] = 
{
	"Quit",
	"DispatchMessage",
	"MessageReceived",
	"FrameMoved",
	"WorkspacesChanged",
	"WorkspaceActived",
	"FrameResized",
	"Minimize",
	"Zoom",
	"ScreenChanged",
	"MenusBeginning",
	"MenusEnded",
	"WindowActivated",
	"Show",
	"Hide",
	"ResolveSpecifier",
	"GetSupportedSuites",
	"Perform",
	"QuitRequested",
	"Run",
	NULL
};

char *msg_gadevents_basic[] =
{
	"clicked",
	"selected",
	"keydown",
	"doubleclick",
	"dropped",
	"dragicon",	
	"keyfilter",
	"keyenter",
	NULL
};	

char *msg_gadviewflags[] =
{
	"B_WILL_DRAW",
	"B_FULL_UPDATE_ON_RESIZE",
	"B_FRAME_EVENTS",
	"B_PULSE_NEEDED",
	"B_NAVIGABLE",
	"B_NAVIGABLE_JUMP",
	"B_SUBPIXEL_PRECISE",
	NULL
};	

char *msg_windowflags[] =
{
	"B_NOT_MOVABLE",
	"B_NOT_CLOSABLE",
	"B_NOT_ZOOMABLE",
	"B_NOT_MINIMIZABLE",
	"B_NOT_H_RESIZABLE",
	"B_NOT_V_RESIZABLE",
	"B_NOT_RESIZABLE",
	"B_OUTLINE_RESIZE",
	"B_WILL_ACCEPT_FIRST_CLICK",
	"B_AVOID_FRONT",
	"B_AVOID_FOCUS",
	"B_NO_WORKSPACE_ACTIVATION",
	"B_NOT_ANCHORED_ON_ACTIVATE",
	"B_ASYNCHRONOUS_CONTROLS",
	NULL
};	

char *search_type[] =
{
	"Name Gadget",
	"Button",
	"Checkbox",
	"String",
	"Integer",
	"Float",
	"Password",
	"Tab",
	"Box",
	"Radio",
	"Mx",
	"Text",
	"Number",
	"Statusbar",
	"Color",
	"Listview",
	"Listview horiz",
	"Listview vert",
	"Listview all",
	"Outlistview",
	"Outlistview horiz",
	"Outlistview vert",
	"Outlistview all",
	"Slider horiz",
	"Slider vert",
	"Scroller horiz",
	"Scroller vert",
	"TextEditor",
	"TextEditor horiz",
	"TextEditor vert",
	"TextEditor all",
	"Menu",
	NULL
};	

char *msg_gadevents_menu[] =
{
	NULL
};	

BList cliplist;

int prefs_genc = 0;
int count_button;
int count_tab;
int count_box;
int count_slider;
int count_scroller;
int count_text;
int count_number;
int count_listview;
int count_outlistview;
int count_checkbox;
int count_string;
int count_tedit;
int count_color;
int count_statusbar;
int count_mx;
int count_radio;
int count_view;

