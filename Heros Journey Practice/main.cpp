#include <SFML/Graphics.hpp>
using namespace sf;

#include <SFML/Window.hpp>
using namespace sf;

#include <string>
using namespace std;

#include <iostream>
using namespace std;

#include "AnimatedSprite.hpp"











const int windowX = 512;
const int windowY = 512;
const int mapX = 8;
const int mapY = 8;
const int reso = (windowX / 8);
const int scaling = (reso / 16);
const double moveSpeed = 0.05;
int frame = 1;


int loadTextures() {

	return 0;
}

int main()
{
	//Create the map (WE HAVE TO MOVE THIS OUTSIDE THE CODE
	//Cant do [x*y], causes errors with displaying maps.  Will have to use [x][y]
	int map[mapX * mapY] =
	{ 2,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,};


	//Call the texture function (SHOULD BE IN ANOTHER FILE)
	//loadTextures();

	// load the floor texture
	Texture wood;
	if (!wood.loadFromFile("basictiles_2.png", IntRect(0, 32, 16, 16)))
	{
	}

	//Sets the floor texture to the sprite and scales it up
	Sprite floor;
	floor.setTexture(wood);
	floor.setScale(scaling,scaling);

	Texture stone;
	if (!stone.loadFromFile("basictiles_2.png", IntRect(0, 0, 16, 16))) {}

	Sprite floorStone;
	floorStone.setTexture(stone);
	floorStone.setScale(scaling, scaling);

	Texture player;
	if (!player.loadFromFile("characters.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	Animation walkDown;
	walkDown.setSpriteSheet(player);
	walkDown.addFrame(IntRect(16, 0, 16, 16));
	walkDown.addFrame(IntRect(0, 0, 16, 16));
	walkDown.addFrame(IntRect(32, 0, 16, 16));

	Animation walkUp;
	walkUp.setSpriteSheet(player);
	walkUp.addFrame(IntRect(16, 48, 16, 16));
	walkUp.addFrame(IntRect(0, 48, 16, 16));
	walkUp.addFrame(IntRect(32, 48, 16, 16));

	Animation walkLeft;
	walkLeft.setSpriteSheet(player);
	walkLeft.addFrame(IntRect(16, 16, 16, 16));
	walkLeft.addFrame(IntRect(0, 16, 16, 16));
	walkLeft.addFrame(IntRect(32, 16, 16, 16));

	Animation walkRight;
	walkRight.setSpriteSheet(player);
	walkRight.addFrame(IntRect(16, 32, 16, 16));
	walkRight.addFrame(IntRect(0, 32, 16, 16));
	walkRight.addFrame(IntRect(32, 32, 16, 16));





	Animation* currentAnimation = &walkDown;

	// set up AnimatedSprite
	AnimatedSprite animatedSprite(seconds(0.15), true, false);
	animatedSprite.scale(scaling,scaling);

	//Make the Clock for animation frames
	Clock frameClock;
	float speed = 80.f;
	bool noKeyWasPressed = true;





	// create the window
	RenderWindow window(VideoMode(windowX, windowY), "The Hero's Journey v.0.0.1");
	window.setFramerateLimit(60);

	// run the program as long as the window is open
	while (window.isOpen())
	{

		window.clear();

		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(Color::Black);

		//DRAWING LOOP
		for (int n = 0; n < mapX; n++) {
			for (int m = 0; m < mapY; m++) {
				if (map[n * m] == 1)
				{
					floor.setPosition((reso * n), (reso * m));
					window.draw(floor);

				}
				if (map[n*m] == 2)
				{
					floorStone.setPosition((reso * n), (reso * m));
					window.draw(floorStone);

				}

			}
		}





		Time frameTime = frameClock.restart();
		//Move on keyboard input
		//START DOIN SHIET

		// if a key was pressed set the correct animation and move correctly
		Vector2f movement(0.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			currentAnimation = &walkUp;
			movement.y -= speed;
			noKeyWasPressed = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			currentAnimation = &walkDown;
			movement.y += speed;
			noKeyWasPressed = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			currentAnimation = &walkLeft;
			movement.x -= speed;
			noKeyWasPressed = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentAnimation = &walkRight;
			movement.x += speed;
			noKeyWasPressed = false;
		}

			animatedSprite.play(*currentAnimation);
			animatedSprite.move(movement * frameTime.asSeconds());

			// if no key was pressed stop the animation
			if (noKeyWasPressed)
			{
				animatedSprite.stop();
			}
			noKeyWasPressed = true;

			// update AnimatedSprite
			animatedSprite.update(frameTime);

			// draw
			window.draw(animatedSprite);
			window.display();

		}




		return 0;
	}


