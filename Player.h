#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Animation.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	bool CheckCollision(sf::Sprite object);

	sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}

	sf::Sprite body;
	sf::Vector2f velocity;
	unsigned int row;
	float speed;
	bool faceRight;
	bool canJump;
	bool fighting;
	float jumpHeight;
	int direction = 0;
	int takeItem = 0;
	int hp = 6;
	bool alive = true;
	bool AK47 = false;
	bool immortal = false;
	int maxhp = 99;

private:
	Animation animation;

};

