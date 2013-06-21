#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
namespace fs = ::boost::filesystem;

class SpriteLoader {
	public:
		SpriteLoader(){
			fs::directory_iterator end_it;
			for (fs::directory_iterator it("sprites/"); it != end_it; ++it) {
				if (fs::is_regular_file(*it)) {
					Texture* text = new Texture();
					//std::cout << it->path().generic_string() << std::endl;
					text->loadFromFile(it->path().generic_string());
					Sprite sprite(*text);
					textures.push_back(text);
					sprites.push_back(sprite);
				}
			}
		}
		~SpriteLoader() {
			for (auto it: textures) {
				delete it;
			}
		}
		Sprite& getRandomSprite() {
			return sprites[rand()%sprites.size()];
		}

	protected:
		std::vector<sf::Sprite> sprites;
		std::vector<sf::Texture*> textures;


};

int main()
{
	SpriteLoader sprites;
	Music music;
	music.openFromFile("resources/mario.ogg");
	music.play();
	boost::filesystem::directory_iterator it;

    // create the window
    //RenderWindow window(VideoMode(800, 600), "My window");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
	const int width = window.getSize().x;
	const int height = window.getSize().y;

	//RectangleShape car(Vector2f(10,20));
	Sprite &car = sprites.getRandomSprite();

	car.setPosition(Vector2f(window.getSize().x/2,window.getSize().y/2));
	car.setOrigin(16,23.5);

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
				default:
					break;
			}
        }

        // clear the window with black color
        window.clear(Color::Green);

        // draw everything here...
         window.draw(car);

        // end the current frame
        window.display();
    }

    return 0;
}
