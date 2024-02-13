#include "editor.h"

#include "../game/game_script.h"

using namespace CliqueEngine;

int main(int argc, char* argv[])
{

	int a = 0;

	Editor& editor = Editor::Instance();
	editor.Prepare();


	my_engine.world.component<GameScript>().is_a<Behaviour>();

	Entity e = my_engine.CreateEntity("Entity with Script");
	e.AddComponent<GameScript>();
	e.GetComponent<GameScript>()->Register();

	e = my_engine.CreateEntity("Entity2 with Script");
	e.AddComponent<GameScript>();

	e = my_engine.CreateEntity("Entity with Behaviour");
	e.AddComponent<Behaviour>();

	editor.Start();

	return 0;
}