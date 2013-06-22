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
				}
			}
		}
		~SpriteLoader() {
			for (auto it: textures) {
				delete it;
			}
		}
		Sprite getRandomSprite() {
			return Sprite(*textures[rand()%textures.size()]);
		}
		std::vector<sf::Sprite> getRandomSprites(unsigned int n) {
			assert(n<=textures.size());
			std::vector<sf::Sprite> output;
			output.resize(n);
			std::random_shuffle(textures.begin(),textures.end());
			for (unsigned int i = 0; i<n; ++i)
				output[i].setTexture(*(textures[i]));
			return output;
		}
		std::vector<sf::Sprite> getRandomSpriteNTimes(unsigned int n) {
			Texture& text = *(textures[rand()%textures.size()]);
			std::vector<sf::Sprite> output;
			output.resize(n);
			for (auto& s: output) s.setTexture(text);
			return output;
		}

	protected:
		std::vector<sf::Texture*> textures;
};

void RandomlyPlaceSprites(sf::Window& window,std::vector<sf::Sprite>& sprites) {
	const int width = window.getSize().x;
	const int height = window.getSize().y;
	unsigned int tries = 0;
	restart:
	for (auto it = sprites.begin(); it != sprites.end();++it) {
		it->setPosition(rand()%(int)(width - it->getLocalBounds().width),
				rand()%(int)(height - it->getLocalBounds().height));
		for (auto other = sprites.begin(); other != it; ++other) {
			if (tries < 1e5 && it->getGlobalBounds().intersects(other->getGlobalBounds())) {
				tries++;
				goto restart;
			}
		}
	}
}

int main()
{
	const int MAX_N = 3;
	SpriteLoader sprites;
	Music music;
	music.openFromFile("resources/mario.ogg");
	music.setLoop(true);
	music.play();
	boost::filesystem::directory_iterator it;

    // create the window
    //RenderWindow window(VideoMode(800, 600), "My window");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
	window.setMouseCursorVisible(false);

	std::vector<sf::Sprite> images = sprites.getRandomSpriteNTimes(rand()%(MAX_N)+1);
	RandomlyPlaceSprites(window,images);

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
						images = sprites.getRandomSpriteNTimes(rand()%(MAX_N)+1);
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
         window.draw(image);
		}

        // end the current frame
        window.display();
    }

    return 0;
}
