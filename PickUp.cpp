#include "PickUp.h"

PickUp::PickUp()
{
}

PickUp::~PickUp()
{
}

void PickUp::Update(float deltaTime)
{
	velocity.y += 8.0f * deltaTime;
	body.move(0, velocity.y);
	counterLifeTime++;
	if (counterLifeTime >= lifeTime)
	{
		destroy = true;
	}
}
