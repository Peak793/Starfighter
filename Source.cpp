#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include"SFML/Window.hpp"
#include<iostream>
using namespace sf;
int main()
{
	//Window setup
	RenderWindow window(VideoMode(1920, 1080), "Starfighter", Style::Default);
	int keytime=0;
	window.setFramerateLimit(60);
	
	//Player
	RectangleShape player(Vector2f(99.f,75.f));
	player.setOrigin(player.getSize().x/2,player.getSize().y/2);
	player.setPosition(window.getSize().x/2,window.getSize().y-100);
	Texture p1;
	p1.loadFromFile("tex/playerShip3_red.png");
	player.setTexture(&p1);

	//bullet
	bool isFire = false;
	RectangleShape bullet(Vector2f(13.f,37.f));
	Texture b1;
	b1.loadFromFile("tex/laserGreen04.png");
	bullet.setTexture(&b1);

	//Enemy beta
	CircleShape test(50.f);
	test.setPosition(0,20);
	int dir = 0;
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
		if (dir == 0)
			if (test.getPosition().x < (1920 - 100))
				test.move(5.f, 0);
			else
				dir = 1;
		if (dir == 1)
			if (test.getPosition().x > 0)
				test.move(-5.f, 0);
			else
				dir = 0;

		//Ship update

		if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 80)
		{
			player.move(0.f, -8.f);
			keytime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y < (1080 - 80))
		{
			player.move(0.f, 8.f);
			keytime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x > 49.5)
		{
			player.move(-8.f, 0.f);
			keytime = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x < (1920 - 49.5))
		{
			player.move(8.f, 0.f);
			keytime = 0;
		}

		//Bullet update
		
		if (Keyboard::isKeyPressed(Keyboard::Space) && isFire==0)
		{
			isFire = true;
			bullet.setPosition(player.getPosition().x-8, player.getPosition().y -75);
		}
		if (isFire==1)
		{
			bullet.move(0.f, -10.f);
		}
		if (bullet.getPosition().y < -37 || bullet.getGlobalBounds().intersects(test.getGlobalBounds()))
		{
			isFire = 0;
		}

		window.clear();
		window.draw(test);
		window.draw(player);
		if(isFire)
		window.draw(bullet);
		window.display();
	}
	return 0;
}
