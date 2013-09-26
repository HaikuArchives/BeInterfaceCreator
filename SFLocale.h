/*****************************************************************************

	SFLocale.h
	
	Copyright 2001, Siegfried Soft.   All Rights Reserved.

*****************************************************************************/
#include <Directory.h>
#include <Entry.h>
#include <Message.h>
#include <Path.h>
#include <String.h>

#ifndef _SFLOCALE
#define _SFLOCALE

//----------
//#define _BUILDING_sflocale 1				// for internal use only
//----------

#if _BUILDING_sflocale
#define	_IMPEXP_SFLOCALE		__declspec(dllexport)
#else
#define	_IMPEXP_SFLOCALE		__declspec(dllimport)
#endif


class _IMPEXP_SFLOCALE SFLocale
{
public:
	static SFLocale*	GetInstance();
				~SFLocale();

	int32		SetLanguage(BDirectory *folder, const char *language);
	int32		SetLanguage(BEntry *folder, const char *language);
	int32		SetLanguage(BPath *folder, const char *language);
	int32		SetLanguage(const char *folder, const char *language);
	int32		SetLanguage(entry_ref *folder, const char *language);

	void		SetDefaultText(const char *deftext[], int32 count, const char *language);

	void		SetAppID(const char *app_id);
	const char	*AppID();
	const char	*Language();
	
	const char	*Text(int32 id);
	bool		GetText(int32 id, char *text, int32 size);

protected:
				SFLocale();

private:

	static SFLocale	*cInstance;
	BMessage	cText;							// Buffer for "locale" text
	BMessage	cDefText;						// Buffer for built-in text
	BString		cLanguage;						// Name of current used language
	BString		cAppID;							// Application ID
};


#endif
