#ifndef random_sprites_h
#define random_sprites_h

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class RandomSpriteLoader {
	public:
		RandomSpriteLoader();
		RandomSpriteLoader(std::string directory);
		~RandomSpriteLoader();
		sf::Sprite getRandomSprite();
		std::vector<sf::Sprite> getRandomSpritesWithRepeat(unsigned int n);
		std::vector<sf::Sprite> getRandomSprites(unsigned int n);
		std::vector<sf::Sprite> getRandomSpriteNTimes(unsigned int n);

	protected:
		std::vector<sf::Texture*> textures;
};

void RandomlyPlaceSprites(sf::Window& window,std::vector<sf::Sprite>& sprites,
				sf::Vector2f size=sf::Vector2f(0,0));

#endif
