#ifndef music_h
#define music_h
#include <SFML/Audio.hpp>

//Repetitively play mario
class MarioPlayer {
		public:
				MarioPlayer(float volume=100.);
		protected:
				sf::Music music;
};

#endif
