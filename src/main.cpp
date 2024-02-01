// #include "engine_settings.h"
#include "editor.h"


int main(int argc, char* argv[])
{
	Editor& editor = Editor::Instance();
	try
	{
		editor.Prepare();
	}
	catch ( ... )
	{
		return -1;
	}

	editor.Start();

	return 0;
}