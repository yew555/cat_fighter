#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "PickUp.h"

using namespace std;

int generateRandom(int max)
{
	int randomNumber = rand();
	float random = (randomNumber % max) + 1;
	int myRandom = random;
	return myRandom;
}

int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Cat Fighter", sf::Style::Close);
	window.setFramerateLimit(60);

	//Mode
	int mode = 0;

	//Sound
	sf::SoundBuffer bufferShot;
	bufferShot.loadFromFile("sound/Gun.ogg");
	sf::Sound soundShot;
	soundShot.setBuffer(bufferShot);

	sf::SoundBuffer bufferClick;
	bufferClick.loadFromFile("sound/Click.ogg");
	sf::Sound soundClick;
	soundClick.setBuffer(bufferClick);

	sf::SoundBuffer bufferItem;
	bufferItem.loadFromFile("sound/Item.ogg");
	sf::Sound soundItem;
	soundItem.setBuffer(bufferItem);

	sf::SoundBuffer bufferPunch;
	bufferPunch.loadFromFile("sound/Punch.ogg");
	sf::Sound soundPunch;
	soundPunch.setBuffer(bufferPunch);

	sf::SoundBuffer bufferPlayerDie;
	bufferPlayerDie.loadFromFile("sound/PlayerDie.ogg");
	sf::Sound soundPlayerDie;
	soundPlayerDie.setBuffer(bufferPlayerDie);

	sf::SoundBuffer bufferDamaged;
	bufferDamaged.loadFromFile("sound/Damaged.ogg");
	sf::Sound soundDamaged;
	soundDamaged.setBuffer(bufferDamaged);

	sf::Music music;
	music.openFromFile("sound/music.ogg");
	music.setVolume(40);
	music.setLoop(true);

	//Variable
	sf::Clock clock;
	sf::Clock clock1;
	sf::Clock clock2;
	sf::Clock clock3;
	sf::Clock clock4;
	sf::Clock clock5;
	sf::Clock clock6;
	sf::Clock clock7;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int counter5 = 0;
	float deltaTime = 0.0f;
	sf::Vector2i mouse;

	//Font
	sf::Font font;
	font.loadFromFile("font/2005_iannnnnCPU.ttf");

	//Bullet
	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("pic/obj/bullet.png");
	Projectile bullet(&bulletTexture);
	//Projectile
	vector<Projectile>::const_iterator iter;
	vector<Projectile> projectileArray;

	//Fire
	sf::Texture fireTexture;
	fireTexture.loadFromFile("pic/obj/fire.png");
	Projectile fire(&fireTexture);
	//Projectile
	vector<Projectile>::const_iterator iter5;
	vector<Projectile> fireArray;
	fire.lifeTime = 5;

	//End Game
	sf::Text enterText("Enter Your Name :", font, 100);
	enterText.setPosition(410, 250);
	enterText.setFillColor(sf::Color::White);

	sf::String playerInput;
	sf::Text playerText("", font, 150);
	playerText.setPosition(500, 320);
	playerText.setFillColor(sf::Color::Black);

	//Main Menu
	sf::Texture mainbg, menu0, menu1, menu2, menu3, howto0, howto1;
	mainbg.loadFromFile("pic/ui/bg.png");
	menu0.loadFromFile("pic/ui/menu0.png");
	menu1.loadFromFile("pic/ui/menu1.png");
	menu2.loadFromFile("pic/ui/menu2.png");
	menu3.loadFromFile("pic/ui/menu3.png");
	howto0.loadFromFile("pic/ui/howto.png");
	howto1.loadFromFile("pic/ui/howto1.png");
	sf::Sprite smainbg, smenu0, smenu1, smenu2, smenu3, showto0, showto1;
	smainbg.setTexture(mainbg);
	smenu0.setTexture(menu0);
	smenu1.setTexture(menu1);
	smenu2.setTexture(menu2);
	smenu3.setTexture(menu3);
	showto0.setTexture(howto0);
	showto1.setTexture(howto1);
	//Name
	sf::Text nameText("Watcharakorn Thankaew 61010958", font, 50);
	nameText.setPosition(780, 0);
	nameText.setFillColor(sf::Color::White);

	//High Score
	sf::Texture highs, ok;
	highs.loadFromFile("pic/ui/hs.png");
	ok.loadFromFile("pic/ui/ok.png");
	sf::Sprite shighs, sok;
	shighs.setTexture(highs);
	sok.setTexture(ok);

	//How to Control
	sf::Texture control;
	control.loadFromFile("pic/ui/control.png");
	sf::Sprite scontrol;
	scontrol.setTexture(control);

	//Game Overbody
	sf::Texture gameOver;
	gameOver.loadFromFile("pic/ui/gameOver.png");
	sf::Sprite sgameOver;
	sgameOver.setTexture(gameOver);


	while (window.isOpen())
	{

		//Player
		unsigned int score = 0;
		sf::Texture playerTexture;
		Collision::CreateTextureAndBitmask(playerTexture, "pic/ch/player.png");
		Player player(&playerTexture, sf::Vector2u(6, 7), 0.1f, 50000, 250.0f);
		//Player HP
		sf::Texture heartTexture;
		heartTexture.loadFromFile("pic/obj/heart.png");
		sf::Sprite heart;
		heart.setTexture(heartTexture);
		heart.setScale(0.1f, 0.1f);
		heart.setPosition(1000, 25);
		sf::Text textHP("", font, 100);
		textHP.setFillColor(sf::Color::Red);
		textHP.setPosition(1100, -20);
		//Player Score
		sf::Text  textScore("", font, 100);
		textScore.setFillColor(sf::Color::Black);
		textScore.setPosition(25, -20);

		//Enemy
		float spawnTime = 1;
		float enemySpeed = 10000.0f;
		int countEnemy = 0;
		sf::Texture enemyTexture;
		Collision::CreateTextureAndBitmask(enemyTexture, "pic/ch/monster.png");
		Enemy enemy(&enemyTexture, sf::Vector2u(5, 4), 0.1f, enemySpeed);
		vector<Enemy>::const_iterator iter2;
		vector<Enemy> enemyArray;
		enemyArray.push_back(enemy);

		//Item
		sf::Texture AKTexture;
		Collision::CreateTextureAndBitmask(AKTexture, "pic/obj/ak.png");
		sf::Texture immortalTexture;
		Collision::CreateTextureAndBitmask(immortalTexture, "pic/obj/immortal.png");
		sf::Texture healTexture;
		Collision::CreateTextureAndBitmask(healTexture, "pic/obj/heal.png"); sf::
			Texture Meteorit;
		Collision::CreateTextureAndBitmask(Meteorit, "pic/obj/Meteorit.png");
		sf::Texture onFireTexture;
		Collision::CreateTextureAndBitmask(onFireTexture, "pic/obj/onFire.png");
		sf::Sprite onFire;
		onFire.setTexture(onFireTexture);
		class PickUp pickup;
		vector<PickUp>::const_iterator iter3;
		vector<PickUp> pickupArray;
		pickupArray.push_back(pickup);
		float dropItemTime = 1;

		//Background
		sf::Texture bgTexture;
		bgTexture.loadFromFile("pic/bg/bg1.png");
		sf::Sprite background;
		background.setTexture(bgTexture);

		//File High Score
		vector<pair<int, string>> scoreboard;
		ifstream loadFile;
		loadFile.open("score.txt");
		while (!loadFile.eof())
		{
			string tempName;
			int tempScore;
			loadFile >> tempName >> tempScore;
			scoreboard.push_back({ tempScore,tempName });
		}
		sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());

		music.play();
		//Main Menu
		while (mode == 0)
		{
			mouse = sf::Mouse::getPosition(window);
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();
			window.draw(smainbg);
			window.draw(smenu0);
			window.draw(showto0);

			if (mouse.x < 770 && mouse.x > 510 && mouse.y < 480 && mouse.y > 400)
			{
				window.draw(smenu1);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					soundClick.play();
					mode = 1;
				}
			}
			if (mouse.x < 800 && mouse.x > 480 && mouse.y < 580 && mouse.y > 510)
			{
				window.draw(smenu2);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					soundClick.play();
					mode = 2;  //High Score
				}
			}
			if (mouse.x < 710 && mouse.x > 580 && mouse.y < 670 && mouse.y > 600)
			{
				window.draw(smenu3);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					soundClick.play();
					window.close();
				}
			}
			if (mouse.x < 75 && mouse.x > 30 && mouse.y < 100 && mouse.y > 25)
			{
				window.draw(showto1);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					soundClick.play();
					mode = 4; //How to control
				}
			}

			window.draw(nameText);
			window.display();
		}

		//HighScore
		while (mode == 2)
		{
			mouse = sf::Mouse::getPosition(window);

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();
			window.draw(shighs);

			if (mouse.x < 692 && mouse.x > 592 && mouse.y < 697 && mouse.y > 636)
			{
				window.draw(sok);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					soundClick.play();
					mode = 0; //go to Main Menu
				}
			}

			int cnt = 0;
			for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i)
			{
				++cnt;
				if (cnt > 5)
				{
					break;
				}
				sf::Text a, b;
				a.setString(to_string(i->first));
				a.setFont(font);
				a.setCharacterSize(80);
				a.setPosition(780, 80 + (80 * cnt));
				a.setFillColor(sf::Color::White);
				window.draw(a);
				b.setString(i->second);
				b.setFont(font);
				b.setCharacterSize(80);
				b.setPosition(380, 80 + (80 * cnt));
				b.setFillColor(sf::Color::Green);
				window.draw(b);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				mode = 0; //go to Main Menu
			}
			window.display();
		}

		//How to Control
		while (mode == 4)
		{
			mouse = sf::Mouse::getPosition(window);
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.clear();
			window.draw(scontrol);

			if (mouse.x < 692 && mouse.x > 592 && mouse.y < 697 && mouse.y > 636)
			{
				window.draw(sok);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					soundClick.play();
					mode = 0; //go to Main Menu
				}
			}
			window.display();
		}


		//Game Mode
		while (mode == 1)
		{
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				mode = 0; //go to Main Menu
			}

			//Clock
			sf::Time elasped1 = clock1.getElapsedTime();
			sf::Time elasped2 = clock2.getElapsedTime();
			sf::Time elasped3 = clock3.getElapsedTime();
			sf::Time elasped4 = clock4.getElapsedTime();
			sf::Time elasped5 = clock5.getElapsedTime();
			sf::Time elasped6 = clock6.getElapsedTime();
			sf::Time elasped7 = clock7.getElapsedTime();

			//Difficult
			if (score > 30)
			{
				enemy.speed = 20000;
			}
			if (score > 50)
			{
				enemy.hp = 2;
				dropItemTime = 4;
			}
			if (score > 60)
			{
				spawnTime = 0.75;
				dropItemTime = 3;
			}
			if (score > 70)
			{
				enemy.atk = 2;
				dropItemTime = 1.5;
			}
			if (score > 80)
			{
				spawnTime = 0.5;
				dropItemTime = 1;
			}
			window.clear();
			//Draw BG
			window.draw(background);

			//Item
						//Player collision pick up Item
			counter3 = 0;
			for (iter3 = pickupArray.begin(); iter3 != pickupArray.end(); iter3++)
			{
				if (Collision::PixelPerfectTest(player.body, pickupArray[counter3].body)
					|| Collision::PixelPerfectTest(pickupArray[counter3].body, player.body) && elasped3.asSeconds() >= 0.5)
				{
					clock3.restart();
					if (pickupArray[counter3].isHeal == true)
					{
						soundItem.play();
						player.hp++;
						if (player.hp > player.maxhp)
						{
							player.hp = player.maxhp;
						}
						pickupArray[counter3].destroy = true;
					}
					else if (pickupArray[counter3].isAK == true)
					{
						soundItem.play();
						clock7.restart();
						player.AK47 = true;
						player.immortal = false;
						pickupArray[counter3].destroy = true;
					}
					else if (pickupArray[counter3].isImmortal == true)
					{
						soundItem.play();
						clock7.restart();
						player.AK47 = false;
						player.immortal = true;
						pickupArray[counter3].destroy = true;
					}
					else if (pickupArray[counter3].isMeteorit == true)
					{
						soundDamaged.play();
						player.hp--;
						if (player.hp <= 0)
						{
							player.hp = 0;
							player.alive = false;
						}
						pickupArray[counter3].destroy = true;
					}
				}
				counter3++;
			}
			if (elasped7.asSeconds() >= 15)
			{
				clock7.restart();
				player.AK47 = false;
				player.immortal = false;
			}
			//Draw Item
			if (elasped6.asSeconds() >= dropItemTime)
			{
				clock6.restart();
				int tempRandom = generateRandom(14);
				if (tempRandom >= 1 && tempRandom <= 4)
				{
					pickup.isAK = true;
					pickup.isImmortal = false;
					pickup.isHeal = false;
					pickup.isMeteorit = false;
					pickup.body.setTexture(AKTexture);
					pickup.body.setScale(3.f, 3.f);
					pickup.body.setPosition(-100, 0);
					pickupArray.push_back(pickup);
				}
				if (tempRandom >= 5 && tempRandom <= 6)
				{
					pickup.isAK = false;
					pickup.isImmortal = true;
					pickup.isHeal = false;
					pickup.isMeteorit = false;
					pickup.body.setTexture(immortalTexture);
					pickup.body.setScale(3.f, 3.f);
					pickup.body.setPosition(-100, 0);
					pickupArray.push_back(pickup);
				}
				if (tempRandom >= 7 && tempRandom <= 10)
				{
					pickup.isHeal = true;
					pickup.isMeteorit = false;
					pickup.body.setTexture(healTexture);
					pickup.body.setScale(3.f, 3.f);
					pickup.body.setPosition(-100, 0);
					pickupArray.push_back(pickup);
				}
				if (tempRandom >= 11 && tempRandom <= 14)
				{
					pickup.isAK = false;
					pickup.isImmortal = false;
					pickup.isMeteorit = true;
					pickup.isHeal = false;
					pickup.body.setTexture(Meteorit);
					pickup.body.setScale(3.f, 3.f);
					pickup.body.setPosition(-100, 0);
					pickupArray.push_back(pickup);
				}
				pickup.body.setPosition(generateRandom(1200), 0);
				pickupArray.push_back(pickup);
			}
			counter3 = 0;
			for (iter3 = pickupArray.begin(); iter3 != pickupArray.end(); iter3++)
			{
				pickupArray[counter3].Update(deltaTime);
				window.draw(pickupArray[counter3].body);
				counter3++;
			}
			//Detect Item
			counter3 = 0;
			for (iter3 = pickupArray.begin(); iter3 != pickupArray.end(); iter3++)
			{
				if (pickupArray[counter3].destroy == true)
				{
					pickupArray.erase(iter3);
					break;
				}
				counter3++;
			}
			//Immortal Form
			if (player.immortal)
			{
				onFire.setScale(.5f, .5f);
				onFire.setPosition(player.GetPosition().x + 20, player.GetPosition().y - 10);
				window.draw(onFire);
			}

			//Player
						//Collision with enemy
			counter2 = 0;
			for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++)
			{
				if ((Collision::PixelPerfectTest(player.body, enemyArray[counter2].body)
					|| Collision::PixelPerfectTest(enemyArray[counter2].body, player.body)) && elasped4.asSeconds() >= 1)
				{
					clock4.restart();
					soundDamaged.play();
					if (!player.immortal)
					{
						player.hp -= enemy.atk;
					}

					if (player.hp <= 0)
					{
						player.hp = 0;
						player.alive = false;
					}
				}
				counter2++;
			}
			//Player Die
			if (player.alive == false)
			{
				soundPlayerDie.play();
				mode = 3; //goto End Game
			}
			player.Update(deltaTime);
			window.draw(player.body);

			//Fire Punch
						//Collision with enemy
			counter5 = 0;
			for (iter5 = fireArray.begin(); iter5 != fireArray.end(); iter5++)
			{
				counter2 = 0;
				for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++)
				{
					if (Collision::PixelPerfectTest(fireArray[counter5].body, enemyArray[counter2].body)
						|| Collision::PixelPerfectTest(enemyArray[counter2].body, fireArray[counter5].body))
					{
						fireArray[counter5].destroy = true;
						enemyArray[counter2].hp--;
						if (enemyArray[counter2].hp <= 0)
						{
							enemyArray[counter2].alive = false;
						}
					}
					counter2++;
				}
				counter5++;
			}
			//Detect Fire
			counter5 = 0;
			for (iter5 = fireArray.begin(); iter5 != fireArray.end(); iter5++)
			{
				if (fireArray[counter5].destroy == true)
				{
					fireArray.erase(iter5);
					break;
				}
				counter5++;
			}
			//Spawn Fire
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
				player.AK47 == false && elasped5.asSeconds() >= 0.3)
			{
				clock5.restart();
				soundPunch.play();
				int x;
				if (player.faceRight == true)
					x = 110;
				else
					x = 50;
				fire.body.setPosition(player.GetPosition().x + x, player.GetPosition().y + 80);
				fire.direction = player.direction;
				fireArray.push_back(fire);
			}
			//Draw Fire
			counter5 = 0;
			for (iter5 = fireArray.begin(); iter5 != fireArray.end(); iter5++)
			{
				fireArray[counter5].Update(deltaTime);
				window.draw(fireArray[counter5].body);
				counter5++;
			}

			//Bullet Projectile
						//Collision with enemy
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				counter2 = 0;
				for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++)
				{
					if (Collision::PixelPerfectTest(projectileArray[counter].body, enemyArray[counter2].body)
						|| Collision::PixelPerfectTest(enemyArray[counter2].body, projectileArray[counter].body))
					{
						projectileArray[counter].destroy = true;
						enemyArray[counter2].hp--;
						if (enemyArray[counter2].hp <= 0)
						{
							enemyArray[counter2].alive = false;
						}
					}
					counter2++;
				}
				counter++;
			}
			//Detect Projectile
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				if (projectileArray[counter].destroy == true)
				{
					projectileArray.erase(iter);
					break;
				}
				counter++;
			}
			//Spawn Projectile
			if (player.AK47 == true && elasped1.asSeconds() >= 0.2)
			{
				soundShot.play();
				clock1.restart();
				int x;
				if (player.faceRight == true)
					x = 125;
				else
					x = 30;
				bullet.body.setPosition(player.GetPosition().x + x, player.GetPosition().y + 100);
				bullet.direction = player.direction;
				projectileArray.push_back(bullet);
			}
			//Draw Projectile
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				projectileArray[counter].Update(deltaTime);
				window.draw(projectileArray[counter].body);
				counter++;
			}

			//Enemy
						//Draw Enemy
			if (elasped2.asSeconds() >= spawnTime && countEnemy <= 1)
			{
				clock2.restart();
				int randomLR = generateRandom(2);
				if (randomLR == 1)
				{
					enemy.body.setPosition(-60, 460);
				}
				else
				{
					enemy.body.setPosition(1220, 460);
				}
				enemyArray.push_back(enemy);
				countEnemy++;
			}
			//Enemy Die
			counter = 0;
			for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++)
			{
				if (enemyArray[counter].alive == false)
				{
					countEnemy--;
					score++;
					enemyArray.erase(iter2);
					break;
				}
				counter++;
			}
			//Draw Enemy
			counter2 = 0;
			for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++)
			{
				enemyArray[counter2].Update(deltaTime, player.GetPosition(), player.body);
				window.draw(enemyArray[counter2].body);
				counter2++;
			}

			//Interface
			//Draw HP
			window.draw(heart);
			textHP.setString(": " + to_string(player.hp));
			window.draw(textHP);

			//Draw Score
			textScore.setString("SCORE : " + to_string(score));
			window.draw(textScore);

			window.display();
		}

		//Game Over
		while (mode == 3)
		{
			music.pause();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode >= 32 && event.text.unicode <= 126)
					{
						playerInput += (char)event.text.unicode;
					}
					else if (event.text.unicode == 8 && playerInput.getSize() > 0)
					{
						playerInput.erase(playerInput.getSize() - 1, playerInput.getSize());
					}
					playerText.setString(playerInput);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				music.play();
				ofstream myFile;
				myFile.open("score.txt", ios::out | ios::app);
				myFile << "\n" << (string)playerInput << " " << score;
				myFile.close();
				mode = 2; //goto HighScore
			}
			window.clear();
			window.draw(sgameOver);
			window.draw(enterText);
			window.draw(playerText);
			window.display();
		}
	}
	return 0;
}

