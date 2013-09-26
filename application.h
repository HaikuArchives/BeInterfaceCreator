#include <AppKit.h>

#include "SFLocale.h"

#ifndef _MyApp

class MyApp : public BApplication
{
public:
	MyApp(void);
	~MyApp(void);

	virtual void ReadyToRun(void);
	virtual void AboutRequested(void);
	virtual bool QuitRequested(void);
	virtual void MessageReceived(BMessage *msg);
	virtual void RefsReceived(BMessage *msg);
	virtual BHandler 	*ResolveSpecifier(BMessage *msg, int32 index, BMessage *spec, int32 form, const char *prop);
	virtual status_t	GetSupportedSuites(BMessage *msg);

	SFLocale			*cLang;					// Pointer to text data
};

#define _MyApp
#endif
