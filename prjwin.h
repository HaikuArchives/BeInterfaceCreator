class WrkWindow;

class TListItem : public BListItem
{
public:
			TListItem(WrkWindow *wi,struct MyGadget *gd,BBitmap *bit,char *name);
			~TListItem();
	virtual void	DrawItem(BView*, BRect, bool);
	virtual	void	Update(BView*, const BFont*);

	WrkWindow 	*win;
	struct MyGadget *gad;
	BBitmap		*icon;
	char		*name;
};

class MyLv : public BOutlineListView
{
public:
	MyLv(BRect rct);
	~MyLv(void);

	virtual void SelectionChanged(void);
	virtual void KeyDown(const char *bytes,int32 nb);
	virtual void MouseDown(BPoint pt);
	virtual void FrameResized(float wi,float he);
};

class PrjWindow : public BWindow
{
public:
		PrjWindow(BRect rct);
		~PrjWindow(void);
		
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);
		virtual	void	MessageReceived(BMessage* msg);
		virtual	bool	QuitRequested(void);
		virtual void	WindowActivated(bool act);

		void	AddWindow(WrkWindow *wi,const char *name);
		TListItem *FindGadget(struct MyGadget *gd);
		void	AddGadget(WrkWindow *wi,struct MyGadget *gd,char *name,int type,struct MyGadget *inside = NULL);
		void	RemoveWindow(WrkWindow *wi);
		void	RemoveGadget(WrkWindow *wi,struct MyGadget *gd);
		void	ChooseGadget(struct MyGadget *gd);

	MyLv *xt;
};
