#pragma once
#include <SFML\Graphics.hpp>

class PickUp
{
public:
	PickUp();
	virtual ~PickUp();

	bool isAK = false;
	bool isImmortal = false;
	bool isHeal = false;
	bool isMeteorit = false;

	int counterLifeTime = 0;
	int lifeTime = 100;
	bool destroy = false;

	sf::Sprite body;
	sf::Vector2f velocity;

	void Update(float deltaTime);

private:
};

