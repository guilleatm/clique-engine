#include "editor.h"

#include "../game/game_script.h"

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



	Entity e = editor.engine.CreateEntity();
	e.AddComponent<GameScript>();

	e = editor.engine.CreateEntity();
	e.AddComponent<GameScript>();

	e = editor.engine.CreateEntity();
	e.AddComponent<GameScript>();

	e = editor.engine.CreateEntity();
	e.AddComponent<GameScript>();

	e = editor.engine.CreateEntity();
	e.AddComponent<GameScript>();

	editor.Start();

	return 0;
}