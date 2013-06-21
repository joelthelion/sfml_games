#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
					textures.push_back(text);
					Sprite* sprite = new Sprite(*text);
					sprites.push_back(sprite);
				}
			}
		}
		~SpriteLoader() {
			for (auto it: textures) {
				delete it;
			}
			for (auto it: sprites) {
				delete it;
			}
		}
		Sprite& getRandomSprite() {
			return *sprites[rand()%sprites.size()];
		}
		std::vector<sf::Sprite*> getRandomSprites(unsigned int n) {
			assert(n<=sprites.size());
			std::random_shuffle(sprites.begin(),sprites.end());
			return std::vector<sf::Sprite*>(sprites.begin(),sprites.begin()+n);
		}

	protected:
		std::vector<sf::Sprite*> sprites;
		std::vector<sf::Texture*> textures;
};

void RandomlyPlaceSprites(sf::Window& window,std::vector<sf::Sprite*>& sprites) {
	const int width = window.getSize().x;
	const int height = window.getSize().y;
	restart:
	for (auto it = sprites.begin(); it != sprites.end();++it) {
		(*it)->setPosition(rand()%(int)(width - (*it)->getLocalBounds().width),
				rand()%(int)(height - (*it)->getLocalBounds().height));
		for (auto other = sprites.begin(); other != it; ++other) {
			if ((*it)->getGlobalBounds().intersects((*other)->getGlobalBounds())) {
				goto restart;
			}
		}
	}
}

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

	//RectangleShape car(Vector2f(10,20));
	std::vector<sf::Sprite*> images = sprites.getRandomSprites(8);
	RandomlyPlaceSprites(window,images);
	//Sprite &car = sprites.getRandomSprite();


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
						images = sprites.getRandomSprites(8);
						RandomlyPlaceSprites(window,images);
						break;
					}
				default:
					break;
			}
        }

        // clear the window with black color
        window.clear(Color::Green);

        // draw everything here...
		for (auto image:images) {
         window.draw(*image);
		}

        // end the current frame
        window.display();
    }

    return 0;
}
