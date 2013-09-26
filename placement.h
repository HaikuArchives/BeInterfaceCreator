class PlaceWindow : public BWindow
{
public:
		PlaceWindow(BRect rct);
		~PlaceWindow(void);
		
		void	MessageReceived(BMessage* msg);
		bool	QuitRequested(void);
		virtual void	FrameMoved(BPoint pt);
		virtual void	FrameResized(float wi,float he);

	BTextControl 	*b0,*b1,*b2,*b3;
	BPictureButton 	*b4,*b5,*b6,*b7;
	BStringView		*b8,*b9,*b10,*b11;
};
