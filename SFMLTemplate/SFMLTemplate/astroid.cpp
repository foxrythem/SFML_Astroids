#include "astroid.h"
#include <time.h>



Astroid::Astroid() {


	
	size = 50;
	speed = 5;
	roationSpeed = 1;
	sides = 8;
	
	shape = sf::CircleShape(size, sides);
	shape.setOrigin(size, size);

	srand(time(NULL));
	randX = rand() % 5 + 1;
	
	randY = rand() % 5 + 1;
	

}


Astroid::Astroid( int inputSize, int inputSides, float inputSpeed, int inputRoationSpeed, int iRandX, int iRandY) {


	
	size = inputSize;
	speed = inputSpeed;
	roationSpeed = inputRoationSpeed;
	sides = inputSides;
	
	shape = sf::CircleShape(size, sides);
	shape.setOrigin(size, size);

	
	randX = iRandX;

	randY = iRandY;
}