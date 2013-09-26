#include "proto.h"

char *gen_app_header[] =
{
	"",
	"#ifndef _Application1_",
	"class Application1 : public BApplication",
	"{",
	"public:",
	"	Application1 ();",
	"	~Application1 (void);",
	"",
	"	virtual void ReadyToRun(void);",
	"	virtual bool QuitRequested(void);",
	"};",
	"",
	"#define _Application1_",
	"#endif",
	NULL
};

char *gen_app_code[] =
{
	"",
	"Application1::Application1()",
	":BApplication(\"application/x-bxml.application\")",
	"{",
	"}",
	"",
	"Application1::~Application1(void)",
	"{",
	"}",
	"",
	"void",
	"Application1::ReadyToRun(void)",
	"{",
	"	form1 = new Window1();",
	"}",
	"",
	"bool",
	"Application1::QuitRequested(void)",
	"{",
	"	return true;",
	"}",
	"",
	"int",
	"main(void)",
	"{",
	"	Application1 *app = new Application1();",
	"	app->Run();",
	"	delete app;",
	"	return B_OK;",
	"};",
	NULL
};	

void
create_header_application(char *appname)
{
	FILE *fi;
	WrkWindow	*wk;

	char *st,my[1025],tmp[1025],*buf = &tmp[0];
	int z,k = 0;

	sprintf(&tmp[0],"%s/application.h",appname);

	strcpy(&my[0],&tmp[0]);

	if (fi = fopen(&tmp[0],"w+"))
	{
		xwrite_string(fi,"#include <Application.h>");

		xwrite_cr(fi);

		for (z = 0; z < projet.CountItems(); z++)
		{
			sprintf(&tmp[0],"#include \"form%d.h\"",z + 1);

			xwrite_string(fi,&tmp[0]);	
		}

		for (k = 0; k < 10; k++)
		{
			xwrite_string(fi,gen_app_header[k]);	
		}

		xwrite_cr(fi);

		for (z = 0; z < projet.CountItems(); z++)
		{
			sprintf(&tmp[0],"\tWindow%d *form%d;",z + 1,z + 1);

			xwrite_string(fi,&tmp[0]);	
		}

		for (k = 10; k < 14; k++)
		{
			xwrite_string(fi,gen_app_header[k]);	
		}

		fclose(fi);

		set_sourcecode(&my[0]);
	}
}

void
create_application(char *appname)
{
	FILE *fi;
	WrkWindow	*wk;

	char *st,my[1025],tmp[1025],*buf = &tmp[0];
	int z,k = 0;

	create_header_application(appname);

	sprintf(&tmp[0],"%s/application.cpp",appname);

	strcpy(&my[0],&tmp[0]);

	if (fi = fopen(&tmp[0],"w+"))
	{
		xwrite_string(fi,"#include <Application.h>");
		xwrite_string(fi,"#include \"application.h\"");

		for (z = 0; z < projet.CountItems(); z++)
		{
			sprintf(&tmp[0],"#include \"form%d.h\"",z + 1);

			xwrite_string(fi,&tmp[0]);	
		}

		while (st = gen_app_code[k++])
		{
			xwrite_string(fi,st);	
		}

		fclose(fi);

		set_sourcecode(&my[0]);
	}
}
