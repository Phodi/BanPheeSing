
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"
#include "text_box.h"
#include "tilemap.h"

//Settings
const int WindowWidth = 1920/1;
const int WindowHeight = 1080/1;


//Global Variables
std::vector<Obj*> allObjPtr;


int main()
	{
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha");

	//Create Objects here
	Player Player(".\\textures\\a_sprite.png",32,32,4,3);
	Player.setScale(4.0f, 4.0f);

	Npc Npc1(sf::Vector2f(0.0f,0.0f), ".\\textures\\koy_sprite.png",32 ,32 ,4 ,3 , "B");
	Npc1.setScale(4.0f, 4.0f);
	sf::Vector2f NPCTarget = sf::Vector2f(500.0f,500.0f);


	//Font loading
	sf::Font mainFont;
	if (!mainFont.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf"))
	{
		std::cerr << "ERROR: Cannot load font\n";
	}

	TextBox testText;
	testText.setFont(mainFont);
	testText.setStrings("Claudette Morel", "Oh shit!!\nHe saw me.");
	testText.setImg(".\\textures\\test_portrait.png");
	testText.setColor(sf::Color::Magenta);
	testText.isDisplay = true;

	// define the level with an array of tile indices
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	TileMap map;
	map.load(".\\textures\\test_tileset.png", sf::Vector2u(32, 32), level, 16, 8);

	sf::Clock clock;

	while (window.isOpen())
	{
		testText.checkContinue();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape) window.close();
				break;
			case sf::Event::MouseButtonPressed:
				NPCTarget = sf::Vector2f(sf::Mouse::getPosition(window));
				Npc1.vec_moveToQueue.push_back(NPCTarget);
				break;
			}
		}

		//Player controls
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool Sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

		Player.control(Right, Left, Down, Up, Sprint);
		Player.walkingAnimate(Right-Left,Down-Up,Player.isSprinting ? 12 : 6);
		//NPC test
		Npc1.moveToQueue();
		Npc1.walkingAnimate();



		//Rendering
		window.clear();

		window.draw(map);
		Player.draw(window);
		Npc1.draw(window);
		testText.draw(window);

		window.display();
	}

	return 0;
}