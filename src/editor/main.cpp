#include "editor.h"

#include "../game/game_script.h"

#include "../engine/position.h" // DELETE

using namespace CliqueEngine;

int main(int argc, char* argv[])
{
	Engine& engine = Engine::Instance();
	Editor& editor = Editor::Instance();
	
	// engine.world.component<GameScript>().is_a<Behaviour>();

	Entity e = Engine::Instance().CreateEntity("Frog");
	// e.AddComponent<GameScript>();
	// e.GetComponent<GameScript>()->Register();

	// e.AddComponent<Behaviour>();
	// Sprite& s = e.AddComponent<Sprite>();
	Position* pos = e.AddComponent<Position>();

	std::cout << pos->x << std::endl;
	std::cout << pos->y << std::endl;


	editor.Start();

	return 0;
}