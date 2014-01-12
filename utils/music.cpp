#include <SFML/Audio.hpp>
#include "music.h"

MarioPlayer::MarioPlayer() {
		music.openFromFile("resources/mario.ogg");
		music.setLoop(true);
		music.play();
}
