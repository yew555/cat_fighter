#include "Projectile.h"

Projectile::Projectile(sf::Texture* texture)
{
	body.setScale(0.04f, 0.04f);
	body.setOrigin(body.getScale() / 2.0f);
	body.setTexture(*texture);
}

Projectile::~Projectile()
{
}

void Projectile::Update(float deltaTime)
{
	if (direction == 1)
	{
		body.move(-movementSpeed * deltaTime, 0);
	}
	if (direction == 2)
	{
		body.move(movementSpeed * deltaTime, 0);
	}
	counterLifeTime++;
	if (counterLifeTime >= lifeTime)
	{
		destroy = true;
	}
}
