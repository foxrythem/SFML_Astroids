#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>


class Bullet {
public:
	
	sf::Clock lifeClock;


	Bullet(int size, sf::Texture &bulletTexture) {
		bullet = sf::CircleShape(size);
		//bullet.setFillColor(sf::Color::Blue);
		if (!pTexture.loadFromFile("BulletTexture.png")) {
			cout << "Error\n";
		}
		bullet.setTexture(&bulletTexture);
		lifeClock.restart();
		bullet.setOrigin(size, size);
	}

	void setDirection(float direction) {
		
		dirX = cos(direction);
		dirY = sin(direction);

	}

	void fire(float direction, int speed) {
		
		bullet.move(dirX * speed, dirY * speed);
	}

	int getRight() {
		return bullet.getPosition().x;
	}

	int getLeft() {
		return bullet.getPosition().x;
	}

	int getTop() {
		return bullet.getPosition().y;
	}

	int getBottom() {
		return bullet.getPosition().y;
	}

	void draw(sf::RenderWindow &window) {
		window.draw(bullet);
	}

	void setPos(sf::Vector2f newPos) {
		bullet.setPosition(newPos);
	}

	bool isTimeEnd() {

		if (lifeClock.getElapsedTime().asSeconds() > 2)
			return true;
		else
			return false;
	}

	void ScreenWrap(int screenBoarderX, int screenBoarderY) {

		
		////Set up screenWrap so if the player goes off screen they appear on the other side
		//if (bullet.getPosition().x > screenBoarderX)
		//	pSprite.setPosition(0, bullet.getPosition().);
		//else if (playerY > screenBoarderY)
		//	pSprite.setPosition(playerX, 0);
		//else if (playerX < 0)
		//	pSprite.setPosition(screenBoarderX, playerY);
		//else if (playerY < 0)
		//	pSprite.setPosition(playerX, screenBoarderY);

	}

private:
	sf::CircleShape bullet;
	sf::Time lifeSpan;
	sf::Texture pTexture;
	float dirX;
	float dirY;
};