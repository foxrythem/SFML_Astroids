#define _USE_MATH_DEFINES
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include "astroid.h"
#include "Player.h"
#include "Bullet.h"
#include <typeinfo>

int randomNumX;
int randomNumY;
int randomNum;
bool isFiring = false;

using namespace std;
void setPosistionCircle(sf::CircleShape &shape, int x, int y);
void ScreenWrap(sf::CircleShape &shape, int x, int y, int offscreen);
float RandomFloat(float a, float b);


void setPosistionCircle(sf::CircleShape &shape, int x, int y) {



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
	cout << "LOADING..." << endl;

	sf::Texture background;
	sf::Texture shipTexture;
	sf::Texture rockTexture;
	sf::Texture bulletTexture;
	if (!background.loadFromFile("background.jpg") || 
		!shipTexture.loadFromFile("ShipTexture.png") ||
		!rockTexture.loadFromFile("RockTexture.jpg") ||
		!bulletTexture.loadFromFile("BulletTexture.png")) {
		cout << "Can't Load Texture" << endl;
		return -1;
	}

	sf::RectangleShape backdrop(sf::Vector2f(1280, 720));
	backdrop.setTexture(&background);


	int numAstroids = 50;
	double speed = 0;
	int offscreen = 25;
	int bulletSpeed = 10;
	srand(time(NULL));

	
	sf::Clock deltaClock;
	sf::Clock LifeSpan;
	
	Astroid listOfRocks[23];


	//window render setting 
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Astroids", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// Sets up and spawns astroids
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

		setPosistionCircle(listOfRocks[i].shape, window.getSize().x, window.getSize().y);
	
	}


	Player player(window.getSize().x / 2, window.getSize().y / 2);
	player.setScale(1.2);
	std::vector<Bullet> bulletVec;


	

	#pragma region Update

		while (window.isOpen())
		{
			
			
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

			//clears the draw window every frame
			window.clear();
			

			sf::Vector2u windowSize = window.getSize();


			//Set up keyboard input from player
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  ) {
				//roates the ship counter clockwise
				player.roatePlayer(-5);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  ) {
				//rotates ship clockwise
				player.roatePlayer(5);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  ) {
				//increases speed to a max speed of 5 
				if (player.speed < 5) {
					player.speed += .05;
				}
			}
			//This allows the ship to slowly reduce speed instead of stoping dead in its tracks
			else {
				if (player.speed > 0) {
					player.speed -= .02;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
				//Slows down ship 
				if (player.speed > 0) {
					player.speed -= .05;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.allowFire() ) {

					isFiring = true;

			}

			
			
			if (isFiring) {
				Bullet newBullet(10, bulletTexture);
				newBullet.setPos(sf::Vector2f(player.getX(), player.getY()));
				newBullet.setDirection(player.getDirection());
				bulletVec.push_back(newBullet);
				isFiring = false;
			}


			window.draw(backdrop);

			//Moves the ship based on current speed. This allows the ship to move as if in space 
			player.movePlayer(player.speed);
			player.ScreenWrap(windowSize.x, windowSize.y);
			//player.printPlayerPost();
			
			//Draws the ship every frame 
			
			player.drawPlayer(window);
			
			

			for (int i = 0; i < bulletVec.size(); i++) {
				bulletVec[i].draw(window);
				bulletVec[i].fire(player.getDirection(), bulletSpeed);
				if (bulletVec[i].isTimeEnd()) {
					bulletVec.erase(bulletVec.begin()+i);
				}
				
			}


			//Moves Astroids in class direction 
			for (int i = 0; i <23; i++) {
				srand(time(NULL));
				listOfRocks[i].shape.rotate(listOfRocks[i].roationSpeed);
				ScreenWrap(listOfRocks[i].shape, windowSize.x, windowSize.y, listOfRocks[i].size/2);
				listOfRocks[i].shape.move(listOfRocks[i].randX * listOfRocks[i].speed, listOfRocks[i].randY*listOfRocks[i].speed);
				window.draw(listOfRocks[i].shape);
			}

			//allows us to keep track of how much time goes on between each frame refresh
			sf::Time deltaTime = deltaClock.restart();
			

			
			
			window.display();
		}
		#pragma endregion Main Game play and logic goes here
}

