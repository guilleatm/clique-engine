#include "editor.h"

#include "../game/game_script.h"

using namespace CliqueEngine;

int main(int argc, char* argv[])
{
	Editor& editor = Editor::Instance();
	editor.Prepare();


	editor.RENAME_ENGINE.world.component<GameScript>().is_a<Behaviour>();

	Entity e = editor.RENAME_ENGINE.CreateEntity("Entity with Script");
	e.AddComponent<GameScript>();
	e.GetComponent<GameScript>()->Register();

	e = editor.RENAME_ENGINE.CreateEntity("Entity2 with Script");
	e.AddComponent<GameScript>();

	e = editor.RENAME_ENGINE.CreateEntity("Entity with Behaviour");
	e.AddComponent<Behaviour>();

	editor.Start();

	return 0;
}