#pragma once

#include <cmath>
#include <time.h>

using namespace std;

class Player {
public:
	float speed = 0;
	int score = 0;
	


	Player(float posX, float posY) {
		if (!pTexture.loadFromFile("ShipTexture.png")) {
			cerr << "Error\n";
		}
		pSprite.setTexture(pTexture);
		pSprite.setOrigin(pSprite.getTextureRect().width / 2,
			pSprite.getTextureRect().height / 2);
		pSprite.setPosition(posX, posY);
		abilityClock.restart();
	}

	void drawPlayer(sf::RenderWindow &window) {
		window.draw(pSprite);
	}
	
	void roatePlayer(int direction) {
		pSprite.rotate(direction);

	}

	float getDirection() {
		float angleRADS = (3.1415926536 / 180)*(pSprite.getRotation() - 90);

		return angleRADS;
	}

	void movePlayer(float speed) {
		
		float angleRADS = (3.1415926536 / 180)*(pSprite.getRotation() - 90);
		float dirX =  cos(angleRADS);
		float dirY =  sin(angleRADS);


		pSprite.move(dirX * speed, dirY * speed);
		
	}

	
	void ScreenWrap(int screenBoarderX, int screenBoarderY) {
		
		playerX = pSprite.getPosition().x;
		playerY = pSprite.getPosition().y;

		//Set up screenWrap so if the player goes off screen they appear on the other side
		if (playerX > screenBoarderX)
			pSprite.setPosition(0, playerY);
		if (playerY > screenBoarderY)
			pSprite.setPosition(playerX, 0);
		if (playerX < 0)
			pSprite.setPosition(screenBoarderX, playerY);
		if (playerY < 0)
			pSprite.setPosition(playerX, screenBoarderY);

	}

	bool allowFire() {

		if (abilityClock.getElapsedTime().asSeconds() > .5) {
			abilityClock.restart();
			return true;
		}
		else
			return false;


	}

	void printPlayerPost() {
		if (playerX != pSprite.getPosition().x || playerY != pSprite.getPosition().y) {
			playerX = pSprite.getPosition().x;
			playerY = pSprite.getPosition().y;
			system("cls");
			cout << "Player X: " << playerX << " Player Y: " << playerY << endl;
		}
	}

	void setScale(float scaleSize) {
		pSprite.setScale(scaleSize, scaleSize);


	}

	float getX() {
		playerX = pSprite.getPosition().x;
		return playerX;
	}

	float getY() {
		playerY = pSprite.getPosition().y;
		return playerY;
	}


private:
	sf::Texture pTexture;
	sf::Sprite pSprite;
	sf::Clock abilityClock;
	float playerHeight = pSprite.getTextureRect().height;
	float playerWidth = pSprite.getTextureRect().width;
	int playerX = pSprite.getPosition().x;
	int playerY = pSprite.getPosition().y;
};