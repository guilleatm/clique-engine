#include "editor.h"

#include "../game/game_script.h"

using namespace CliqueEngine;

int main(int argc, char* argv[])
{

	Editor& editor = Editor::Instance();
	editor.Prepare();


	Engine::Instance().world.component<GameScript>().is_a<Behaviour>();

	Entity e = Engine::Instance().CreateEntity("Entity with Script");
	e.AddComponent<GameScript>();
	e.GetComponent<GameScript>()->Register();

	e = Engine::Instance().CreateEntity("Entity2 with Script");
	e.AddComponent<GameScript>();

	e = Engine::Instance().CreateEntity("Entity with Behaviour");
	e.AddComponent<Behaviour>();

	editor.Start();

	return 0;
}