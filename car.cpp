#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

float wrap(float x,float max,float margin) {
	if (x < -margin)
		return fmod(x,max+margin) + max+margin;
	else
		return fmod(x,max+margin);
}

int main()
{
	Music music;
	music.openFromFile("resources/mario.ogg");
	music.setLoop(true);
	music.play();

    // create the window
    //RenderWindow window(VideoMode(800, 600), "My window");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	RectangleShape background;
	Texture background_t;
	background_t.loadFromFile("resources/city1.jpg");
	background.setSize(Vector2f(window.getSize().x,window.getSize().y));
	background.setTexture(&background_t);

	//RectangleShape car(Vector2f(10,20));
	Sprite car;
	Texture car_t;
	car_t.loadFromFile("resources/car.png");
	car.setTexture(car_t);
	car.setPosition(Vector2f(window.getSize().x/2,window.getSize().y/2));
	car.setOrigin(16,23.5);
	sf::Clock clock;
	bool driving = false;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
			switch (event.type) {
				// "close requested" event: we close the window

				case Event::Closed:
					window.close();
					break;
				case Event::KeyPressed:
					if (event.key.code == Keyboard::Escape) {
						window.close();
						break;
					}
					if (event.key.code == Keyboard::Space) {
						car.setPosition(Vector2f(window.getSize().x/2,window.getSize().y/2));
						break;
					}
					if (event.key.code == Keyboard::Up) {
						driving = not driving;
						break;
					}
				default: break;
			}
        }

		sf::Time elapsed = clock.restart();
		//std::cout << elapsed.asMicroseconds()	<< std::endl;
		Vector2f delta;
		float rotation = 0.f;
		float rotation_speed = 2.f;
		float speed = 0.5e-4f * elapsed.asMicroseconds();
		float angle = car.getRotation()/180*M_PI + M_PI_2;
		Vector2f increment(speed*cos(angle), speed*sin(angle));
		if (Keyboard::isKeyPressed(Keyboard::Left))
			rotation = -rotation_speed;
		if (Keyboard::isKeyPressed(Keyboard::Right))
			rotation = rotation_speed;
		//if (Keyboard::isKeyPressed(Keyboard::Up))
			//driving = not driving;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			driving = false;
		if (driving)
		{
			delta = -increment;
			Vector2f pos(wrap(car.getPosition().x + delta.x,window.getSize().x,200), wrap(car.getPosition().y+delta.y,window.getSize().y,200));
			car.setPosition(pos);
		}
		car.rotate(rotation);

        // clear the window with black color
        window.clear(Color::Green);

        // draw everything here...
		window.draw(background);
		window.draw(car);

        // end the current frame
        window.display();
    }

    return 0;
}
