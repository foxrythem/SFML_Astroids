#pragma once

#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>


using namespace std;


class Astroid
{
public:
	Astroid();
	Astroid(int inputSize, int inputSides, float inputSpeed, int inputRoationSpeed, int iRandX, int iRandY);
	//~Astroid();


	int size;
	int roationSpeed;
	int sides;
	float speed;
	int randX;
	int randY;

	sf::CircleShape shape;

private:

};




