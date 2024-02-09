#include "editor.h"

#include "../game/game_script.h"

using namespace CliqueEngine;

int main(int argc, char* argv[])
{
	Editor& editor = Editor::Instance();
	editor.Prepare();


	Entity e = editor.engine.CreateEntity();
	e.AddComponent<Behaviour>();

	editor.Start();

	return 0;
}