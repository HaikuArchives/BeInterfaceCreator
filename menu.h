class CMenuItem : public BStringItem
{
public:
			CMenuItem(bool menu,char *name,char car,int msg,bool enable,bool checked,bool radio,uint32 level = 0);
			~CMenuItem();

	char *name;
	bool menu,enable,checked,radio;
	int  msg;
	char car;
};

class MyLv2 : public BOutlineListView
{
public:
	MyLv2(BRect rct);
	~MyLv2(void);

	virtual void SelectionChanged(void);
};

class MenuWindow : public BWindow
{
public:
		MenuWindow(BRect rct);
		~MenuWindow(void);
		
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);

		void	InfoShow(void);
		void	StoreInfo(void);
		void	StoreInList(bool men,char *str,int nb,int car,int msg,bool enable,bool checked,bool radio);
		void	BuildMenuItems(BMenu* pMenu, BListItem* pSuperitem,BOutlineListView* pView);
		void	LoadInfo(void);
		void	Delete(void);
		void	AddMenu(void);
		void	AddItem(void);

	BOutlineListView	*b0;
	BButton				*b1,*b2,*b3;

	BTextControl		*b4,*b5;
	BCheckBox			*b6,*b7;
	BTextControl		*b8;
	BCheckBox			*b9;
	BButton				*b10;

	BView	*xt;

};
