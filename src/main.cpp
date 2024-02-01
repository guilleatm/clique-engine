// #include <SDL.h>
// #include <SDL_image.h>

// #include "engine_settings.h"
#include "editor.h"


int main(int argc, char* argv[])
{
	try
	{
		Editor editor = Editor();
		editor.Start();
	}
	catch ( ... )
	{
		return -1;
	}

	return 0;
}