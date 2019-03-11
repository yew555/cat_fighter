#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	fighting = false;

	body.setTexture(*texture);
	body.setScale(3.f, 3.f);
	body.setOrigin(body.getScale() / 2.0f);
	body.setPosition(600, 0.0f);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//Movement
	velocity.x = 0.0f;
	velocity.y += 981.0f * deltaTime;

	//InScreen
	int limLeft = -66;
	int limRight = 1167;
	int limBottom = 450;
	if (body.getPosition().x < limLeft || body.getPosition().x > limRight)
	{
		velocity.x = 0.0f;
	}
	if (body.getPosition().y > limBottom)
	{
		canJump = true;
		velocity.y = 0.0f;
	}

	//KeyPressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && body.getPosition().x > limLeft)
	{
		velocity.x -= speed * deltaTime;
		direction = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && body.getPosition().x < limRight)
	{
		velocity.x += speed * deltaTime;
		direction = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0 * 981.0f * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		fighting = true;
		velocity.x = 0;
	}

	//Animation
	if (AK47 == true)//AK47
	{
		if (velocity.x == 0.0f)
		{
			row = 5;
		}
		else
		{
			row = 6;
			if (velocity.x > 0.0f)
				faceRight = true;
			else
				faceRight = false;
		}
	}
	else if (fighting && !canJump)
	{
		row = 3;
	}
	else if (fighting && canJump)
	{
		row = 4;
	}
	else if (!fighting && velocity.y > 0.f)
	{
		row = 2;
	}
	else if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	fighting = false;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

