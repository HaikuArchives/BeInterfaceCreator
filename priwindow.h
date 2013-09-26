class PriWindow : public BWindow
{
public:
		PriWindow(BRect rct);
		~PriWindow(void);
		
		void	AddMenu(void);
		void	InitGUI(void);
	
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		void	MenusBeginning(void);
		BMenuItem *SetItemMenu(int a,int b,bool c);
		virtual void	Minimize(bool k);

	BMenuBar	*br;

};
