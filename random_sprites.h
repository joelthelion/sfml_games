#ifndef random_sprites_h
#define randm_sprites_h

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class RandomSpriteLoader {
	public:
		RandomSpriteLoader();
		~RandomSpriteLoader();
		sf::Sprite getRandomSprite();
		std::vector<sf::Sprite> getRandomSprites(unsigned int n);
		std::vector<sf::Sprite> getRandomSpriteNTimes(unsigned int n);

	protected:
		std::vector<sf::Texture*> textures;
};

void RandomlyPlaceSprites(sf::Window& window,std::vector<sf::Sprite>& sprites);

#endif
