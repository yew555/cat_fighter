#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Animation.h"
#include "Player.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Enemy();

	void Update(float deltaTime, sf::Vector2f playerPosition, sf::Sprite playerSprite);

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
	int atk = 1;
	int hp = 1;
	int limit = 1;
	bool alive = true;


private:
	Animation animation;
};

