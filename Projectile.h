#pragma once
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile(sf::Texture* texture);
	virtual ~Projectile();
	int movementSpeed = 1000;
	int attackDamage = 5;
	int direction = 0;
	bool destroy = false;
	int counterLifeTime = 0;
	int lifeTime = 100;
	sf::Sprite body;

	void Update(float deltaTime);

protected:

private:
};

