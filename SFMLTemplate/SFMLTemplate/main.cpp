#define _USE_MATH_DEFINES
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include "astroid.h"

int randomNumX;
int randomNumY;
int randomNum;

using namespace std;
void setPosistion(sf::CircleShape &shape, int x, int y);
void ScreenWrap(sf::CircleShape &shape, int x, int y, int offscreen);
float RandomFloat(float a, float b);

void setPosistion(sf::CircleShape &shape, int x, int y) {



	randomNumX = rand() % x + shape.getScale().x;
	randomNumY = rand() % y + shape.getScale().y;

	shape.setPosition(randomNumX, randomNumY);



}

void ScreenWrap(sf::CircleShape &shape, int x, int y, int offscreen) {

	
	//Set up screenWrap so if the player goes off screen they appear on the other side
	if (shape.getPosition().x > x + offscreen)
		shape.setPosition(0, shape.getPosition().y - offscreen);

	if (shape.getPosition().x < 0 - offscreen)
		shape.setPosition(x, shape.getPosition().y - offscreen);

	if (shape.getPosition().y > y + offscreen)
		shape.setPosition(shape.getPosition().x - offscreen, 0);

	if (shape.getPosition().y < 0 - offscreen)
		shape.setPosition(shape.getPosition().x - offscreen, y);
	


}


float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}








int main() {

	sf::Texture background;
	sf::Texture shipTexture;
	sf::Texture rockTexture;
	if (!background.loadFromFile("background.jpg") || 
		!shipTexture.loadFromFile("ShipTexture.png") ||
		!rockTexture.loadFromFile("RockTexture.jpg")) {
		//error
	}

	sf::RectangleShape backdrop(sf::Vector2f(1280, 720));
	backdrop.setTexture(&background);


	int numAstroids = 50;
	double speed = 0;
	int offscreen = 25;
	srand(time(NULL));

	
	sf::Clock clock;
	
	Astroid listOfRocks[23];

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Astroids", sf::Style::Default, settings);


	// Sets up astroids
	for (int i = 0; i < 23; i++) {

		int randSize = rand() % 50 + 25;
		float randSpeed = RandomFloat(0.1, .7);
		int randsides = rand() % 5 + 6;
		int randRoation = rand() % 3 + 1;
		randomNumX = rand() % 10 + (-5);
		randomNumY = rand() % 10 + (-5);

		listOfRocks[i] = Astroid(randSize, randsides, randSpeed, randRoation, randomNumX, randomNumY);
		listOfRocks[i].shape.setTexture(&rockTexture);
		listOfRocks[i].shape.setOutlineThickness(2);
		listOfRocks[i].shape.setOutlineColor(sf::Color(0, 0, 0));

		setPosistion(listOfRocks[i].shape, window.getSize().x, window.getSize().y);
	
	}


	
	



	
	sf::CircleShape shape(50, 3);
	shape.setTexture(&shipTexture);



	//shape.setFillColor(sf::Color(100, 250, 50));
	shape.setOrigin(50, 50);
	shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	

	#pragma region Update

		while (window.isOpen())
		{
			sf::Time elapsed1 = clock.getElapsedTime();
			
			//Close Window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

				window.close();

			}

			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}


			window.clear();
			


			sf::Vector2f shapePosition = shape.getPosition();
			sf::Vector2u windowSize = window.getSize();
			float SpriteAngle = shape.getRotation();





			//Convert current angle to radians
			float angleRADS = (3.1415926536 / 180)*(shape.getRotation() - 90);

			//Set x and y with roations
			float forx = speed * cos(angleRADS);
			float fory = speed * sin(angleRADS);



		



			//Set up keyboard input from player
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shapePosition.x > 50 ) {
				//roates the ship counter clockwise
				shape.rotate(-5);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shapePosition.x < windowSize.x - 50 ) {
				//rotates ship clockwise
				shape.rotate(5);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && shapePosition.y > 50 ) {
				//increases speed to a max speed of 5 
				if (speed < 5) {
					speed += .05;
				}

				
			}
			//This allows the ship to slowly reduce speed instead of stoping dead in its tracks
			else {
				if (speed > 0)
					speed -= .02;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && shapePosition.y < windowSize.y - 50) {
				//Slows down ship 
				if(speed > 0)
					speed -= .05;

			}
			
			
		
			
			

			//Moves the ship based on current speed. This allows the ship to move as if in space 
			shape.move(forx, fory);
			ScreenWrap(shape, windowSize.x, windowSize.y, offscreen);
			
			
			
			
			
			//Draws the ship every frame 
			window.draw(backdrop);
			window.draw(shape);
			for (int i = 0; i <23; i++) {
				srand(time(NULL));
				listOfRocks[i].shape.rotate(listOfRocks[i].roationSpeed);
				ScreenWrap(listOfRocks[i].shape, windowSize.x, windowSize.y, listOfRocks[i].size/2);
				listOfRocks[i].shape.move(listOfRocks[i].randX * listOfRocks[i].speed, listOfRocks[i].randY*listOfRocks[i].speed);
				window.draw(listOfRocks[i].shape);
			}
			
			
			//allows us to keep track of how much time goes on between each frame refresh
			sf::Time elapsed = clock.restart();
			window.display();
		}
		#pragma endregion Main Game play and logic goes here
}

