#include "application.h"
#include "proto.h"
#include "SFTexts.h"

BMessageRunner *msg = 0;

MyApp::MyApp():BApplication("application/x-vnd.rgb.Bic")
{
}

MyApp::~MyApp(void)
{
	Save_Path_Files();
}

void
MyApp::ReadyToRun(void)
{
	cLang = SFLocale::GetInstance();							// set instance to locale library
	cLang->SetAppID(SF_TEXT_APP_ID);							// set ID for "locale" files
	cLang->SetDefaultText(mText, SF_LAST_ID, SF_DEFAULT_LANGUAGE);	// set default text and native language name

	check_isinstalled_mime();

	load_prefs();
	load_keypress();

	msg = new BMessageRunner(be_app,new BMessage(77145),(prefs.automin * 60) * 1000000);

	open_priwin();
}

static property_info mPropList[] = {
	{ "DefaultText", {B_GET_PROPERTY, 0}, {B_DIRECT_SPECIFIER, 0}, "get the default texts for localization", 0},
	{ "DefaultLanguage", {B_GET_PROPERTY, 0}, {B_DIRECT_SPECIFIER, 0}, "get the default language name for localization", 0},
	{ "TextAppID", {B_GET_PROPERTY, 0}, {B_DIRECT_SPECIFIER, 0}, "get the id for locale files", 0},
	0 // terminate list
};

status_t MyApp::GetSupportedSuites(BMessage *msg)
{
BPropertyInfo PropInfo(mPropList);

msg->AddString("suites", "suite/vnd.SiegfriedSoft-locale");
msg->AddFlat("messages", &PropInfo);

return BApplication::GetSupportedSuites(msg);
}

BHandler *MyApp::ResolveSpecifier(BMessage *msg, int32 index, BMessage *spec, int32 form, const char *prop)
{
BPropertyInfo PropInfo(mPropList);

if (PropInfo.FindMatch(msg, index, spec, form, prop) >= 0)
	return this;

return BApplication::ResolveSpecifier(msg, index, spec, form, prop);
}   

bool
MyApp::QuitRequested(void)
{
	return true;
}

void
About(void)
{
	SysAlert(GetMessage(msg_copyright),GetMessage(msg_ok));
}

bool saved_ok = true;

void
MyApp::MessageReceived(BMessage* lmsg)
{
BMessage	spec, reply;
bool		found;
int32		index, what;
const char	*prop;

	switch(lmsg->what)
	{
		case B_GET_PROPERTY:
			found = false;
		if (lmsg->GetCurrentSpecifier(&index, &spec, &what, &prop) == B_OK)
			{
			reply.what = B_REPLY;
			if (strcmp(prop, "DefaultLanguage") == 0 && what == B_DIRECT_SPECIFIER)
				{
				found = true;
				reply.AddString("result", SF_DEFAULT_LANGUAGE);
				}
			if (strcmp(prop, "DefaultText") == 0 && what == B_DIRECT_SPECIFIER)
				{
				found = true;
				for (index = 0; index < SF_LAST_ID; index++)
					reply.AddString("result", mText[index]);
				}
			if (strcmp(prop, "TextAppID") == 0 && what == B_DIRECT_SPECIFIER)
				{
				found = true;
				reply.AddString("result", SF_TEXT_APP_ID);
				}
			}  							
		if (found)
			lmsg->SendReply(&reply);
		else
			BApplication::MessageReceived(lmsg);
		break;

		case	77145:
		{
			if (prefs.autosave && saved_ok)
			{
				if (projet.CountItems())
				{
					saved_ok = false;
		
					msg->SetCount(0);

					save_files();

					msg->SetCount(-1);

					saved_ok = true;
				}
			}
		}
		break;

		default:
		{
			BApplication::MessageReceived(lmsg);
		}
		break;
	}
}		

void
MyApp::RefsReceived(BMessage* msg)
{
	entry_ref	ref;
	type_code	type;
	int32		count;
	msg->GetInfo("refs", &type, &count);
	if(type != B_REF_TYPE)
		return;

	msg->FindRef("refs", 0, &ref);
		BEntry*		entry = new BEntry(&ref);
		
	if (entry)
	{
		BPath path;

		if (entry->GetPath(&path) == B_OK)
		{
			char *str;

			if (str = path.Path())
			{
				load_file(str);
			}
		}
	}
}
	
void
MyApp::AboutRequested(void)
{
	About();
}

int
main(int argc,char **argv)
{
	MyApp app;

	app.Run();
	
	return 0;
}

SFLocale	*cLang = NULL;					// Pointer to text data

char *
GetMessage(int nb)
{
	if (!cLang)
	{
		cLang = SFLocale::GetInstance();			// Get text data access
	}
	
	if (!prefs.locale)
	{
		return(cLang->Text(nb));
	}
		else
	{
		return(cLang->Text(nb + msg_locale_french));
	}	
}


