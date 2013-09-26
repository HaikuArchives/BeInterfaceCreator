#include "proto.h"
#include <ctype.h>

char *makefile_tab[] =
{
	"## BeOS Generic Makefile v2.0 ##",
	"",
	"## Fill in this file to specify the project being created, and the referenced",
	"## makefile-engine will do all of the hard work for you.  This handles both",
	"## Intel and PowerPC builds of the BeOS.",
	"",
	"## Application Specific Settings ---------------------------------------------",
	"",
	"# specify the name of the binary",
	"# specify the type of binary",
	"#	APP:	Application",
	"#	SHARED:	Shared library or add-on",
	"#	STATIC:	Static library archive",
	"#	DRIVER: Kernel Driver",
	"#	specify the source files to use",
	"#	full paths or paths relative to the makefile can be included",
	"# 	all files, regardless of directory, will have their object",
	"#	files created in the common object directory.",
	"#	Note that this means this makefile will not work correctly",
	"#	if two source files with the same name (source.c or source.cpp)",
	"#	are included from different directories.  Also note that spaces",
	"#	in folder names do not work well with this makefile.",
	"#	specify the resource files to use",
	"#	full path or a relative path to the resource file can be used.",
	"#	specify additional libraries to link against",
	"#	there are two acceptable forms of library specifications",
	"#	-	if your library follows the naming pattern of:",
	"#		libXXX.so or libXXX.a you can simply specify XXX",
	"#		library: libbe.so entry: be",
	"#		",
	"#	- 	if your library does not follow the standard library",
	"#		naming scheme you need to specify the path to the library",
	"#		and it's name",
	"#		library: my_lib.a entry: my_lib.a or path/my_lib.a",
	"LIBS= be",
	"",
	"#	specify additional paths to directories following the standard",
	"#	libXXX.so or libXXX.a naming scheme.  You can specify full paths",
	"#	or paths relative to the makefile.  The paths included may not",
	"#	be recursive, so include all of the paths where libraries can",
	"#	be found.  Directories where source files are found are",
	"#	automatically included.",
	"LIBPATHS= ",
	"",
	"#	additional paths to look for system headers",
	"#	thes use the form: #include <header>",
	"#	source file directories are NOT auto-included here",
	"SYSTEM_INCLUDE_PATHS = ",
	"",
	"#	additional paths to look for local headers",
	"#	thes use the form: #include \"header\"",
	"#	source file directories are automatically included",
	"LOCAL_INCLUDE_PATHS = ",
	"",
	"#	specify the level of optimization that you desire",
	"#	NONE, SOME, FULL",
	"OPTIMIZE= ",
	"",
	"#	specify any preprocessor symbols to be defined.  The symbols",
	"#	will be set to a value of 1.  For example specify DEBUG if you want",
	"#	DEBUG=1 to be set when compiling.",
	"DEFINES= ",
	"",
	"#	specify special warning levels",
	"#	if unspecified default warnings will be used",
	"#	NONE = supress all warnings",
	"#	ALL = enable all warnings",
	"WARNINGS = ALL",
	"",
	"#	specify whether image symbols will be created",
	"#	so that stack crawls in the debugger are meaningful",
	"#	if TRUE symbols will be created",
	"SYMBOLS = ",
	"",
	"#	specify debug settings",
	"#	if TRUE will allow application to be run from",
	"#	a source-level debugger",
	"DEBUGGER = ",
	"",
	"#	specify additional compiler flags for all files",
	"COMPILER_FLAGS =",
	"",
	"#	specify additional linker flags",
	"LINKER_FLAGS =",
	"",
	"",
	"## include the makefile-engine",
	"include /boot/develop/etc/makefile-engine",
	NULL
};

char *ggtab[] =
{
	"APP",
	"SHARED",
	"STATIC",
	"DRIVER",
	NULL
};

char *xxtab[] =
{
	"NONE",
	"SOME",
	"MORE",
	"FULL",
	NULL
};
	
void
create_makefile(char *appname)
{
	FILE *fi;
	WrkWindow	*wk;
	struct MyGadget *gd;

	char *st,my[1025],tmp[1025],*buf = &tmp[0];
	int e,k;

	sprintf(buf,"%s/makefile",appname);

	strcpy(&my[0],buf);

	if (fi = fopen(buf,"w+"))
	{
		for (k = 0; k < 9; k++)
		{
			if (st = makefile_tab[k])
			{
				xwrite_string(fi,st);	
			}
		}	

		sprintf(buf,"NAME= %s",&prefs.appname[0]);

		xwrite_string(fi,buf);	

		xwrite_cr(fi);

		for (k = 9; k < 14; k++)
		{
			if (st = makefile_tab[k])
			{
				xwrite_string(fi,st);	
			}
		}	

		sprintf(buf,"TYPE= %s",ggtab[prefs.typeapp]);

		xwrite_string(fi,buf);	

		xwrite_cr(fi);

		for (k = 14; k < 22; k++)
		{
			if (st = makefile_tab[k])
			{
				xwrite_string(fi,st);	
			}
		}	

		sprintf(buf,"SRCS=\tapplication.cpp \\");

		xwrite_string(fi,buf);

		for (k = 0; k < projet.CountItems(); k++)
		{
			if (wk = (WrkWindow *)projet.ItemAt(k))
			{
				for (e = 0; e < wk->list.CountItems(); e++)
				{
					if (gd = (struct MyGadget *)wk->list.ItemAt(e))
					{
						if (!gd->derived)
						{
							goto next;
						}
							else
						{
							sprintf(buf,"\t%s_%s.cpp %c",&wk->Name[0],&gd->Name[0],'\\');
						}
							
						xwrite_string(fi,buf);
					}
next:;
				}

				char car = ' ';

				if (k < projet.CountItems() - 1)
				{
					car = '\\';					
				}

				sprintf(buf,"\t%s.cpp %c",&wk->Name[0],car);

				xwrite_string(fi,buf);
			}
		}	

		xwrite_cr(fi);

		for (k = 22; k < 24; k++)
		{
			if (st = makefile_tab[k])
			{
				xwrite_string(fi,st);	
			}
		}	

		xwrite_string(fi,"RSRCS=");	

		xwrite_cr(fi);

		for (k = 24; k < 88; k++)
		{
			if (st = makefile_tab[k])
			{
				switch(k)
				{
					case	56:
					{
						sprintf(buf,"OPTIMIZE = %s",xxtab[prefs.optiapp]);

						xwrite_string(fi,buf);	
					}
					break;

					case	67:
					{
						sprintf(buf,"WARNING = %s",(prefs.warningapp) ? "ALL" : "");

						xwrite_string(fi,buf);	
					}
					break;

					case	77:
					{
						sprintf(buf,"DEBUGGER = %s",(prefs.debugapp) ? "TRUE" : "");

						xwrite_string(fi,buf);	
					}
					break;

					case	80:
					{
						sprintf(buf,"COMPILER_FLAGS = %s",&prefs.compflag[0]);

						xwrite_string(fi,buf);	
					}
					break;

					case	83:
					{
						sprintf(buf,"LINKER_FLAGS = %s",&prefs.linkflag[0]);

						xwrite_string(fi,buf);	
					}
					break;

					default:
					{
						xwrite_string(fi,st);	
					}
					break;
				}
			}
		}	

		fclose(fi);

		set_sourcecode(&my[0]);
	}
}
