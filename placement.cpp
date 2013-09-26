#include "proto.h"
#include "placement.h"

PlaceWindow::PlaceWindow(BRect rct):BWindow(rct,GetMessage(msg_placement),B_TITLED_WINDOW,B_NOT_ZOOMABLE|B_ASYNCHRONOUS_CONTROLS)
{
	BRect 	rect(Bounds());
	BView	*xt;

	xt = new BView(rect,"",B_FOLLOW_ALL,B_WILL_DRAW);

	xt->SetViewColor(255,255,255);

	b0 = CreateInteger(MyRect(5,5,70,25),"X:",9000,4);

	SetStringLen(b0,4);

	b1 = CreateInteger(MyRect(5,30,70,25),"Y:",9001,4);

	SetStringLen(b1,4);

	b2 = CreateInteger(MyRect(5,55,70,25),"W:",9002,4);

	SetStringLen(b2,4);

	b3 = CreateInteger(MyRect(5,80,70,25),"H:",9003,4);

	SetStringLen(b3,4);

	b4 = CreateButton(MyRect(80,5,16,16),"","",9004);
	b5 = CreateButton(MyRect(80,30,16,16),"","",9005);
	b6 = CreateButton(MyRect(80,55,16,16),"","",9006);
	b7 = CreateButton(MyRect(80,80,16,16),"","",9007);

	b8 = new BStringView(MyRect(5,100,100,20),"","");
	b9 = new BStringView(MyRect(5,120,100,20),"","");
	b10 = new BStringView(MyRect(5,140,100,20),"","");
	b11 = new BStringView(MyRect(5,160,100,20),"","");

	if (!DefWin)
	{
		b0->SetEnabled(false);
		b1->SetEnabled(false);
		b2->SetEnabled(false);
		b3->SetEnabled(false);
	}
	
	xt->AddChild(b0);
	xt->AddChild(b1);
	xt->AddChild(b2);
	xt->AddChild(b3);
	xt->AddChild(b4);
	xt->AddChild(b5);
	xt->AddChild(b6);
	xt->AddChild(b7);

	xt->AddChild(b8);
	xt->AddChild(b9);
	xt->AddChild(b10);
	xt->AddChild(b11);

	AddChild(xt);

	if (DefWin)
	{
		DefWin->Activate();
	}

	Show();
}

PlaceWindow::~PlaceWindow(void)
{
}

void
PlaceWindow::MessageReceived(BMessage *msg)
{
	char tmp[100],*buf = &tmp[0];
	WrkWindow *wi = (WrkWindow *)DefWin;
	BMessage mymsg(51000);
	int32 vl;

	msg->FindInt32("be:value",&vl);

	switch(msg->what)
	{
		case	9004:
		case	9005:
		case	9006:
		case	9007:
		{
			if (wi)
			{
				wi->MySetFlags(vl,msg->what);
			}
		}
		break;

		case	9000:
		{
			if	(wi)
			{
				if (wi->AcceptMsg(0))
				{
					mymsg.AddInt32("x",atoi(b0->Text()));	

					wi->PostMessage(&mymsg);
				}
					else
				{
					beep();
				}	
			}		
		}
		break;

		case	9001:
		{
			if	(wi)
			{
				if (wi->AcceptMsg(1))
				{
					mymsg.AddInt32("y",atoi(b1->Text()));	

					wi->PostMessage(&mymsg);
				}
					else
				{
					beep();
				}	
			}		
		}
		break;

		case	9002:
		{
			if	(wi)
			{
				int x = atoi(b2->Text());

				if (x < 10)
				{
					if (wi->sellist.CountItems())
					{
						beep();

						return;
					}
				}

				if (wi->AcceptMsg(2))
				{
					mymsg.AddInt32("w",x);	

					wi->PostMessage(&mymsg);
				}
			}		
		}
		break;

		case	9003:
		{
			if	(wi)
			{
				int x = atoi(b3->Text());

				if (x < 10)
				{
					if (wi->sellist.CountItems())
					{
						beep();

						return;
					}
				}

				if (wi->AcceptMsg(3))
				{
					mymsg.AddInt32("h",x);	

					wi->PostMessage(&mymsg);
				}
			}		
		}
		break;

		case	10001:
		{
			int32 a,b;

			if (msg->FindInt32("x",&a) == B_OK)
			{
				if (msg->FindInt32("y",&b) == B_OK)
				{
					if (a >= 0 && b >= 0)
					{
						sprintf(buf,"X:%04d - Y:%04d",a >= 0 ? a : 0,b >= 0 ? b : 0);

						b8->SetText(buf);	

						strcpy(buf,&DefWin->Name[0]);

						if (strcmp(buf,b11->Text()) != 0)
						{
							b11->SetText(buf);	
						}
					}
						else
					{
						b8->SetText("X:- - Y:-");	
						b11->SetText("");	
					}	
				}
			}	
		}
		break;

		case	10002:
		{
			int32 a,b;

			if (msg->FindInt32("nb",&a) == B_OK)
			{
				if (a > 0)
				{
					sprintf(buf,GetMessage(msg_selection2),a,(a > 1) ? "s" : "");

					if (strcmp(buf,b9->Text()) != 0)
					{
						b9->SetText(buf);	
					}
				}
					else
				{
					if (strcmp(GetMessage(msg_selection_none),b9->Text()) != 0)
					{
						b9->SetText(GetMessage(msg_selection_none));	
					}
				}
			}	
		}
		break;

		case	10003:
		{
			int32 a,b;
			char **tab;

			tab = (ProjetType == PROJET_BCC) ? &gad_name_basic[0] : &gad_name_ccplus[0];

			if (msg->FindInt32("type",&a) == B_OK)
			{
				if (strcmp(tab[a],b10->Text()) != 0)
				{
					b10->SetText(tab[a]);	
				}
			}	
		}
		break;
		
		case	51000:
		{
			int32 a,e;
			
			if (msg->FindInt32("x",&a) == B_OK)
			{
				if (a == -55555)
				{
					goto err0;
				}

				sprintf(buf,"%d",a);
				
				b0->SetEnabled(true);

				if (strcmp(buf,b0->Text()) != 0)
				{
					b0->SetText(buf);	
				}
			}
				else
			{
err0:			b0->SetEnabled(false);
			}	

			if (msg->FindInt32("y",&a) == B_OK)
			{
				if (a == -55555)
				{
					goto err1;
				}

				sprintf(buf,"%d",a);
				
				b1->SetEnabled(true);

				if (strcmp(buf,b1->Text()) != 0)
				{
					b1->SetText(buf);	
				}
			}
				else
			{
err1:			b1->SetEnabled(false);
			}	

			if (msg->FindInt32("w",&a) == B_OK)
			{
				if (a == -55555)
				{
					goto err2;
				}

				sprintf(buf,"%d",a);
				
				b2->SetEnabled(true);

				if (strcmp(buf,b2->Text()) != 0)
				{
					b2->SetText(buf);	
				}
			}
				else
			{
err2:			b2->SetEnabled(false);
			}	

			if (msg->FindInt32("h",&a) == B_OK)
			{
				if (a == -55555)
				{
					goto err3;
				}

				sprintf(buf,"%d",a);
				
				b3->SetEnabled(true);

				if (strcmp(buf,b3->Text()) != 0)
				{
					b3->SetText(buf);	
				}
			}
				else
			{
err3:			b3->SetEnabled(false);
			}	
			
			msg->FindInt32("f",&e);

			if (e == -55555)
			{
				b4->SetValue(B_CONTROL_OFF);	
				b5->SetValue(B_CONTROL_OFF);	
				b6->SetValue(B_CONTROL_OFF);	
				b7->SetValue(B_CONTROL_OFF);	
			}
				else
			{
				if (e & FLAG_LOCKX)	b4->SetValue(B_CONTROL_ON);	else b4->SetValue(B_CONTROL_OFF);	
				if (e & FLAG_LOCKY)	b5->SetValue(B_CONTROL_ON);	else b5->SetValue(B_CONTROL_OFF);	
				if (e & FLAG_LOCKW)	b6->SetValue(B_CONTROL_ON);	else b6->SetValue(B_CONTROL_OFF);	
				if (e & FLAG_LOCKH)	b7->SetValue(B_CONTROL_ON);	else b7->SetValue(B_CONTROL_OFF);	
			}
		}
		break;

		default:	BWindow::MessageReceived(msg);	break;
	}	
}

bool
PlaceWindow::QuitRequested(void)
{
	PlaceWin = NULL;

	return true;
}

void
PlaceWindow::FrameResized(float wi,float he)
{
	BWindow::FrameResized(wi,he);

	prefs.placerect = Frame();
}

void
PlaceWindow::FrameMoved(BPoint pt)
{
	BWindow::FrameMoved(pt);

	prefs.placerect = Frame();
}

void
placement_win(void)
{
	if (!PlaceWin)
	{
		PlaceWin = new PlaceWindow(prefs.placerect);
	}
		else
	{
		PlaceWin->Show();
		
		PlaceWin->Activate();
	}	
}
