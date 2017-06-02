/*
* @file: GameManager.cpp
* @author: Stig M. Halvorsen <halsti@nith.no>
* @version: 1.0.0 <11.02.2013>
*
* @description: A singleton class to control all gameplay.
*/

#include "SDL/SDLBmp.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "IoStream"
#include "math.h"

using namespace std;

/* Initializes SDL, creates the game window and fires off the timer. */
GameManager::GameManager()
{
	SDLManager::Instance().init();
	m_window = SDLManager::Instance().createWindow("Snake");
	Timer::Instance().init();

}


/* Kicks off/is the the gameloop */
void GameManager::play()
{
	bool notGameOver = true;

	// Load bitmaps
	SDLBmp background = ("Assets/gfx/sdl2.bmp");
	SDLBmp player = ("Assets/gfx/sdl_bro.bmp");
	SDLBmp food = ("Assets/gfx/food.bmp");

	bool left = false;
	bool right = true;
	bool up = false;
	bool down = false;

	bool keyPressed = false;

	int randX = rand() % 500 + 1;
	int randY = rand() % 350 + 1;
	

	int counter = 0;

	player.x = 250;
	player.y = 150;
	player.h = 50;
	player.w = 50;

	food.w = 50;
	food.h = 50;
	food.x = 300;
	food.y = 250;

	background.w = 550;
	background.h = 400;

	// Calculate render frames per second (second / frames) (60)
	float render_fps = 1.f / 60.f;
	m_lastRender = render_fps; // set it to render immediately

							   // Gameloop
	while (notGameOver)
	{
		// Update input and deltatime
		InputManager::Instance().Update();
		Timer::Instance().update();

		// Calculate displacement based on deltatime
		int displacement = 50;
		counter++;

		/* Input Management */

		// Left key
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_LEFT) && right == false)
		{

			left = true;
			right = false;
			up = false;
			down = false;
			keyPressed = true;
		}

		// Right key
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_RIGHT) && left == false)
		{
			left = false;
			right = true;
			up = false;
			down = false;
			keyPressed = true;
		}


		if (InputManager::Instance().KeyDown(SDL_SCANCODE_UP) && down == false)
		{
			left = false;
			right = false;
			up = true;
			down = false;
			keyPressed = true;
		}


		if (InputManager::Instance().KeyDown(SDL_SCANCODE_DOWN) && up == false)
		{
			left = false;
			right = false;
			up = false;
			down = true;
			keyPressed = true;
		}

		if (counter > 300) {

			if (left == true) {
				player.x -= displacement;
				keyPressed = false;
			}
			else if (right == true) {
				player.x += displacement;
				keyPressed = false;
			}
			else if (up == true) {
				player.y -= displacement;
				keyPressed = false;
			}
			else if (down == true) {
				player.y += displacement;
				keyPressed = false;
			}
			counter = 0;
		}

		//Colliders - Jan Erik
		if (player.x < food.x + food.w && player.x + player.w > food.x &&
			player.y < food.y + food.h &&
			player.y + player.h > food.y)
		{

			food.x = rand() % 500 + 1;
			food.y = rand() % 350 + 1;
		
			if (food.x < 50)
			{
				food.x = rand() % 500 + 1;
				food.x = round(50);
			}
			else if (food.x > 50 && food.x < 150)
			{
				food.x = rand() % 500 + 1;
				food.x = round(100);
			}
			else if (food.x > 100 && food.x < 200 )
			{
				food.x = rand() % 500 + 1;
				food.x = round(150);
			}
			else if (food.x > 150 && food.x < 250)
			{
				food.x = rand() % 500 + 1;
				food.x = round(200);
			}
			else if (food.x > 200 && food.x < 300)
			{
				food.x = rand() % 500 + 1;
				food.x = round(250);
			}
			else if (food.x > 250 && food.x < 350)
			{
				food.x = rand() % 500 + 1;
				food.x = round(300);
			}
			else if (food.x > 300 && food.x < 400)
			{
				food.x = rand() % 500 + 1;
				food.x = round(350);
			}
			else if (food.x > 350 && food.x < 450)
			{
				food.x = rand() % 500 + 1;
				food.x = round(400);
			}
			else if (food.x > 400 && food.x < 500)
			{
				food.x = rand() % 500 + 1;
				food.x = round(450);
			}
			else if (food.x > 450)
			{
				food.x = rand() % 500 + 1;
				food.x = round(500);
			}


			if (food.y < 50)
			{
				food.y = rand() % 500 + 1;
				food.y = round(50);
			}
			else if (food.y	> 50 && food.y < 150)
			{
				food.y = rand() % 500 + 1;
				food.y = round(100);
			}
			else if (food.y > 100 && food.y < 200)
			{
				food.y = rand() % 500 + 1;
				food.y = round(150);
			}
			else if (food.y > 150 && food.y < 250)
			{
				food.y = rand() % 500 + 1;
				food.y = round(200);
			}
			else if (food.y > 200 && food.y < 300)
			{
				food.y = rand() % 500 + 1;
				food.y = round(250);
			}
			else if (food.y > 250 && food.y < 350)
			{
				food.y = rand() % 500 + 1;
				food.y = round(300);
			}
			else if (food.y > 300 && food.y < 400)
			{
				food.y = rand() % 500 + 1;
				food.y = round(350);
			}
		}


		if (player.x < 0 || player.x >= 550 || player.y < 0 || player.y >= 500)
		{
			notGameOver = false;
		}

		// Exit on [Esc], or window close (user X-ed out the window)
		if (InputManager::Instance().hasExit() || InputManager::Instance().KeyDown(SDL_SCANCODE_ESCAPE))
		{
			notGameOver = false;
		}

		// Update time since last render
		m_lastRender += Timer::Instance().deltaTime();

		// Check if it's time to render
		if (m_lastRender >= render_fps)
		{

			background.draw();
			player.draw();
			food.draw();

			// Render window
			SDLManager::Instance().renderWindow(m_window);
			m_lastRender = 0;


		}
		cout << "Food X: " << food.x << "Food Y: " << food.y << endl;
		// Sleep to prevent CPU exthaustion (1ms == 1000 frames per second)
		SDL_Delay(1);

	}

}