#include <vector>
#include <string>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "random_sprites.h"

using namespace sf;
namespace fs = ::boost::filesystem;

RandomSpriteLoader::RandomSpriteLoader(){
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
RandomSpriteLoader::~RandomSpriteLoader() {
		for (auto it: textures) {
				delete it;
		}
}
Sprite RandomSpriteLoader::getRandomSprite() {
		return Sprite(*textures[rand()%textures.size()]);
}
std::vector<sf::Sprite> RandomSpriteLoader::getRandomSprites(unsigned int n) {
		assert(n<=textures.size());
		std::vector<sf::Sprite> output;
		output.resize(n);
		std::random_shuffle(textures.begin(),textures.end());
		for (unsigned int i = 0; i<n; ++i)
				output[i].setTexture(*(textures[i]));
		return output;
}
std::vector<sf::Sprite> RandomSpriteLoader::getRandomSpriteNTimes(unsigned int n) {
		Texture& text = *(textures[rand()%textures.size()]);
		std::vector<sf::Sprite> output;
		output.resize(n);
		for (auto& s: output) s.setTexture(text);
		return output;
}

void RandomlyPlaceSprites(sf::Window& window,std::vector<sf::Sprite>& sprites, Vector2f size) {
		if (size.x == 0) {
				size.x = window.getSize().x;
				size.y = window.getSize().y;
		}
		unsigned int tries = 0;
restart:
		for (auto it = sprites.begin(); it != sprites.end();++it) {
				it->setPosition(rand()%(int)(size.x - it->getLocalBounds().width),
								rand()%(int)(size.y - it->getLocalBounds().height));
				for (auto other = sprites.begin(); other != it; ++other) {
						if (tries < 1e5 && it->getGlobalBounds().intersects(other->getGlobalBounds())) {
								tries++;
								goto restart;
						}
				}
		}
}
