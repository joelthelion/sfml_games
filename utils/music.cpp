#include <SFML/Audio.hpp>
#include "music.h"

MarioPlayer::MarioPlayer(float volume) {
		music.openFromFile("resources/mario.ogg");
		music.setLoop(true);
		music.setVolume(volume);
		music.play();
}
