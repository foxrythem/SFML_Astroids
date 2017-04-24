#pragma once

#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Player.h"
#include "Bullet.h"


using namespace std;


class Astroid
{
public:

	bool isFarAway = true;
	float astroidX = shape.getPosition().x;
	float astroidY = shape.getPosition().y; 


	Astroid();
	Astroid(int inputSize, int inputSides, float inputSpeed, int inputRoationSpeed, int iRandX, int iRandY);
	//~Astroid();


	int size;
	int roationSpeed;
	int sides;
	float speed;
	int randX;
	int randY;
	int startSpeed;

	sf::CircleShape shape;


	float getX() {
		return shape.getPosition().x;
	}

	float getY() {
		return shape.getPosition().y;
	}


	float checkDistance(Player player, Astroid astroid2) {

		

		sf::Vector2f ast1Pos = sf::Vector2f(player.getX(), player.getY());
		sf::Vector2f ast2Pos = sf::Vector2f(astroid2.shape.getPosition().x, astroid2.shape.getPosition().y);

		float distX = abs(ast1Pos.x - ast2Pos.x);
		float distY = abs(ast1Pos.y - ast2Pos.y);
		float distance = sqrt(distX * distX + distY * distY);


		return distance;
		


	}

	float checkDistance(Astroid astroid1, Astroid astroid2) {



		sf::Vector2f ast1Pos = sf::Vector2f(astroid1.shape.getPosition().x, astroid1.shape.getPosition().y);
		sf::Vector2f ast2Pos = sf::Vector2f(astroid2.shape.getPosition().x, astroid2.shape.getPosition().y);

		float distX = abs(ast1Pos.x - ast2Pos.x);
		float distY = abs(ast1Pos.y - ast2Pos.y);
		float distance = sqrt(distX * distX + distY * distY);


		return distance;



	}

	float checkDistance(Bullet astroid1, Astroid astroid2) {



		sf::Vector2f ast1Pos = sf::Vector2f(astroid1.getX(), astroid1.getY());
		sf::Vector2f ast2Pos = sf::Vector2f(astroid2.shape.getPosition().x, astroid2.shape.getPosition().y);

		float distX = abs(ast1Pos.x - ast2Pos.x);
		float distY = abs(ast1Pos.y - ast2Pos.y);
		float distance = sqrt(distX * distX + distY * distY);


		return distance;



	}

	


	void changeDirection(Player player, Astroid astroid) {

		float directionX = astroid.getX() - player.getX();
		float directionY = astroid.getY() - player.getY();

		 
		cout << randX << endl;
		cout << randY << endl;
	
		randX = (-randX);
		randY = (-randY);

		speed = 6;



	}

	



private:

};




