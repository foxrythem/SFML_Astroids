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

int numberOfAstroids = 23;
int randomNumX;
int randomNumY;
int randomNum;
bool isFiring = false;
bool isGameOver = false;

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



void gameOver(sf::RenderWindow &window , Player player) {
	
	sf::Font font;
	sf::Text gameOverText;
	sf::Text playerScore;


	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setStyle(sf::Text::Bold);

	playerScore.setFont(font);
	playerScore.setCharacterSize(60);
	playerScore.setFillColor(sf::Color::White);
	playerScore.setStyle(sf::Text::Bold);

	
	if (!font.loadFromFile("PressStart2P.ttf") ) {
		cout << "Font unable to load" << endl;
	}
	
	gameOverText.setString("Game Over");
	playerScore.setString("Final Score: " + to_string(player.score));

	gameOverText.setPosition((window.getSize().x / 2) - gameOverText.getLocalBounds().width/2, window.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);

	playerScore.setPosition((window.getSize().x / 2) - playerScore.getLocalBounds().width / 2, (window.getSize().y / 2) - (playerScore.getLocalBounds().height / 2) + gameOverText.getLocalBounds().height);

	
	window.draw(gameOverText);
	window.draw(playerScore);

}










int main() {
	cout << "LOADING..." << endl;

	sf::Font font;
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(24);
	score.setFillColor(sf::Color::White);
	score.setStyle(sf::Text::Bold);
	score.setPosition(20, 20);

	if (!font.loadFromFile("PressStart2P.ttf")) {
		cout << "Font unable to load" << endl;
	}

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


	double speed = 0;
	int offscreen = 25;
	int bulletSpeed = 10;
	srand(time(NULL));

	
	sf::Clock deltaClock;
	sf::Clock LifeSpan;
	
	std::vector<Astroid> astroidVec;


	//window render setting 
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Astroids", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// Sets up and spawns astroids
	for (int i = 0; i < numberOfAstroids; i++) {

		int randSize = rand() % 50 + 25;
		float randSpeed = RandomFloat(0.1, .7);
		int randsides = rand() % 5 + 6;
		int randRoation = rand() % 3 + 1;
		randomNumX = rand() % 10 + (-5);
		randomNumY = rand() % 10 + (-5);

		Astroid newAstroid = Astroid(randSize, randsides, randSpeed, randRoation, randomNumX, randomNumY);
		newAstroid.shape.setTexture(&rockTexture);
		newAstroid.shape.setOutlineThickness(2);
		newAstroid.shape.setOutlineColor(sf::Color(0, 0, 0));

		setPosistionCircle(newAstroid.shape, window.getSize().x, window.getSize().y);
		astroidVec.push_back(newAstroid);
	
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
					bulletVec.erase(bulletVec.begin() + i);
				}

			}


			
			//Moves Astroids in class direction 
			for (int i = 0; i < astroidVec.size(); i++) {
				srand(time(NULL));
				astroidVec[i].shape.rotate(astroidVec[i].roationSpeed);
				ScreenWrap(astroidVec[i].shape, windowSize.x, windowSize.y, astroidVec[i].size / 2);
				astroidVec[i].shape.move(astroidVec[i].randX * astroidVec[i].speed, astroidVec[i].randY*astroidVec[i].speed);
				window.draw(astroidVec[i].shape);
				int distanceToPlayer = astroidVec[i].checkDistance(player, astroidVec[i]);
				
				
				//Collision check for player
				if (distanceToPlayer < astroidVec[i].size + 10 && astroidVec[i].isFarAway == true) {
					cout << "Astroid number " << i << " is close to player" << endl;
					astroidVec[i].changeDirection(player, astroidVec[i]);
					astroidVec[i].isFarAway = false;
					player.score -= 100;
				}
				else if(distanceToPlayer > astroidVec[i].size + 11)
				{
					astroidVec[i].isFarAway = true;
				}
				if (astroidVec[i].speed >= astroidVec[i].startSpeed)
					astroidVec[i].speed -= .1;
			

			}

			
			//Collision Check for bullets
			for (int i = 0; i < bulletVec.size(); i++) {
				for (int j = 0; j < astroidVec.size(); j++) {
					if (i < bulletVec.size()) {
						int checkBulletDistance = astroidVec[j].checkDistance(bulletVec[i], astroidVec[j]);
						if (checkBulletDistance < astroidVec[j].size + bulletVec[i].bulletSize) {
							player.score += 10 * astroidVec[j].size;
							astroidVec.erase(astroidVec.begin() + j);
							bulletVec.erase(bulletVec.begin() + i);
							
						}
					}
				}
			}



			//allows us to keep track of how much time goes on between each frame refresh
			sf::Time deltaTime = deltaClock.restart();
			
			score.setString("Score: " + to_string(player.score));
			
			
			if (astroidVec.size() < 1) {
				isGameOver = true;
			}
			else
			{
				window.draw(score);
			}

			
			if (isGameOver) {
				gameOver(window, player);
			}
			
			window.display();
		}
		#pragma endregion Main Game play and logic goes here
}

