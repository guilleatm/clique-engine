#include "editor.h"

#include "../game/game_script.h"

using namespace CliqueEngine;

int main(int argc, char* argv[])
{
	Engine& engine = Engine::Instance();
	Editor& editor = Editor::Instance();
	
	engine.world.component<GameScript>().is_a<Behaviour>();

	Entity e = Engine::Instance().CreateEntity("Entity with Script");
	// e.AddComponent<GameScript>();
	// e.GetComponent<GameScript>()->Register();

	e.AddComponent<Behaviour>();
	e.AddComponent<Sprite>();


	editor.Start();

	return 0;
}