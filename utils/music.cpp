#include "music.h"
#include <SFML/Audio.hpp>

MarioPlayer::MarioPlayer(float volume) {
  music.openFromFile("resources/mario.ogg");
  music.setLoop(true);
  music.setVolume(volume);
  music.play();
}
