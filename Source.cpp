#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include"SFML/Window.hpp"
#include<iostream>
#include<vector>
#include<cstdlib>
using namespace sf;
int main()
{
	srand(time(NULL));
	//Window setup
	RenderWindow window(VideoMode(1920, 1080), "Starfighter", Style::Default);
	int keytime=0;
	window.setFramerateLimit(60);
	
	//Player
	RectangleShape player(Vector2f(99.f,75.f));
	player.setOrigin(player.getSize().x/2,player.getSize().y/2);
	player.setPosition(window.getSize().x/2.f,window.getSize().y-100.f);
	Texture p1;
	p1.loadFromFile("tex/playerShip3_red.png");
	player.setTexture(&p1);

	//bullet
	RectangleShape projectile(Vector2f(13,37));
	projectile.setFillColor(Color::Green);
	std::vector<RectangleShape>projectiles;
	projectiles.push_back(RectangleShape(projectile));
	int shootTimer = 0;
	int bulletcooldown = 15;

	//Enemy beta
	RectangleShape enemy(Vector2f(104,84));
	Texture e1;
	e1.loadFromFile("tex/enemyBlack2.png");
	enemy.setTexture(&e1);
	enemy.setPosition(((rand() % window.getSize().x) - enemy.getSize().x) < 0 ? 0 : (rand() % window.getSize().x) - enemy.getSize().x, rand() % 360);
	std::vector<RectangleShape>enemies;
	enemies.push_back(RectangleShape(enemy));
	int spawnTimer = 0;
	int n = 60;
	int count=0;
	int aliveEnemies = 7;
	

	//Game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		
		//Enemy update
		if (spawnTimer < n)
			spawnTimer++;
		if (spawnTimer >= n && count < aliveEnemies)
		{
			enemy.setPosition(((rand()%window.getSize().x)-enemy.getSize().x)<0 ? 0: (rand() % window.getSize().x) - enemy.getSize().x,rand()%360);
			enemies.push_back(RectangleShape(enemy));
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].getPosition().x < 0)
				{
					enemies.erase(enemies.begin() + i);
					count--;
				}
			}
			spawnTimer = 0;
			count++;
		}
	


		//Ship update

		if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 80)
		{
			player.move(0.f, -10.f);
			keytime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y < (1080 - 80))
		{
			player.move(0.f, 10.f);
			keytime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x > 49.5)
		{
			player.move(-10.f, 0.f);
			keytime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x < (1920 - 49.5))
		{
			player.move(10.f, 0.f);
			keytime = 0;
		}
		Vector2f playercenter(player.getPosition().x - 7, player.getPosition().y - player.getSize().y);
		
		
		//Projectiles update
		if (shootTimer<bulletcooldown)
			shootTimer++;
		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer>=bulletcooldown)
		{
			projectile.setPosition(playercenter);
			projectiles.push_back(RectangleShape(projectile));
			shootTimer = 0;
		}
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].move(0, -20);
			if (projectiles[i].getPosition().y < 0)
				projectiles.erase(projectiles.begin() + i);
		}

		//Collision
		for (int i = 0; i < enemies.size(); i++)
		{
			for (int k = 0; k < projectiles.size(); k++)
			{
				if (enemies[i].getGlobalBounds().intersects(projectiles[k].getGlobalBounds()))
				{
					projectiles.erase(projectiles.begin() + k);
					enemies.erase(enemies.begin() + i);
					count --;
					break;
				}
			}
		}
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				player.setPosition(window.getSize().x / 2.f, window.getSize().y - 100.f);
				count--;
				break;
			}
		}

		
		//Draw
		window.clear();
			//player
		window.draw(player);

			//enemies
		for (size_t i = 0; i < enemies.size(); i++)
		{
				window.draw(enemies[i]);
		}
			//projectile(bullets)
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i]);
		}
		window.display();
	}
	return 0;
}