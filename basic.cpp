#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    //sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "My window", sf::Style::Fullscreen);
	double car_x = window.getSize().x/2;
	double car_y = window.getSize().y/2;

	sf::RectangleShape car(sf::Vector2f(10,20));
	car.setPosition(sf::Vector2f(window.getSize().x/2,window.getSize().y/2));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type) {
				// "close requested" event: we close the window

				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
						break;
					}
					if (event.key.code == sf::Keyboard::Space) {
						car.setPosition(sf::Vector2f(window.getSize().x/2,window.getSize().y/2));
						break;
					}
			}
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			car.move(sf::Vector2f(-10,0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			car.move(sf::Vector2f(10,0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			car.move(sf::Vector2f(0,-10));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			car.move(sf::Vector2f(0,10));

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
         window.draw(car);

        // end the current frame
        window.display();
    }

    return 0;
}
