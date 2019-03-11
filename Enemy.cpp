#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	fighting = false;

	body.setScale(2.5f, 2.5f);
	body.setOrigin(body.getScale() / 2.0f);
	body.setTexture(*texture);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, sf::Vector2f playerPosition, sf::Sprite playerSprite)
{
	//Movement
	velocity.x = 0.0f;
	velocity.y += 981.0f * deltaTime;

	//InScreen
	int limLeft = -66;
	int limRight = 1167;
	int limBottom = 480;
	if (body.getPosition().x < limLeft || body.getPosition().x > limRight)
	{
		velocity.x = 0.0f;
	}
	if (body.getPosition().y > limBottom)
	{
		canJump = true;
		velocity.y = 0.0f;
	}

	//Movement
	if (!Collision::PixelPerfectTest(body, playerSprite) && !Collision::PixelPerfectTest(playerSprite, body))
	{
		if (playerPosition.x + 10 < body.getPosition().x) //EnemyRight
		{
			velocity.x -= speed * deltaTime;
			faceRight = false;
		}
		else if (playerPosition.x - 10 > body.getPosition().x) //EnemyLeft
		{
			velocity.x += speed * deltaTime;
			faceRight = true;
		}
		row = 1;
	}
	else
	{
		row = 2;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	fighting = false;
}


