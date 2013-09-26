#include "proto.h"
#include "edit_tags.h"

void
EditButtonWindow::SetMenu(void)
{
	BButton	*e;

	e = CreateButton(MyRect(10,10,120,25),GetMessage(msg_list),tab_menu_editlist);

	vie2->AddChild(e);
}
