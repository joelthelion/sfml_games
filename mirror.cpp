#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace sf;
std::default_random_engine generator;
const String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
const String letters = "69537JSZNCDL";

void random_update(Text& text) {
  std::uniform_int_distribution<int> idx_dist(0,letters.getSize()-1);
  std::bernoulli_distribution flip_dist(0.5);
  int idx = idx_dist(generator);
  text.setString(letters[idx]);
  if (flip_dist(generator)) {
    text.setScale(-1,1);
  } else {
    text.setScale(1,1);
  }
  text.setOrigin((text.getLocalBounds().width)/2.,
      (text.getLocalBounds().height)/2.);
}

int main() {
  Music music;
  music.openFromFile("resources/mario.ogg");
  music.setLoop(true);
  music.play();

  // create the window
  RenderWindow window(VideoMode::getFullscreenModes()[0], "Mirror letters",
                      Style::Fullscreen);
  window.setMouseCursorVisible(false);

  Font font;
  font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
  sf::Text alpha = sf::Text();
  alpha.setCharacterSize(72);
  alpha.setFont(font);
  alpha.setFillColor(Color::Black);
  alpha.setString(alphabet);
  alpha.setPosition((window.getSize().x-alpha.getLocalBounds().width)/2., 0.);
  sf::Text text = sf::Text();
  text.setCharacterSize(196);
  text.setFont(font);
  text.setFillColor(Color::Black);
  /* text.setOrigin(0,0); */
  text.setPosition((window.getSize().x)/2.,
      (window.getSize().y)/2.);
  /* text.setPosition((window.getSize().x-text.getLocalBounds().width)/2., */
  /*     (window.getSize().y - text.getLocalBounds().height)/2.); */
  random_update(text);

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    Event event;
    while (window.pollEvent(event)) {
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
          random_update(text);
          break;
        }
      default:
        break;
      }
    }

    // clear the window with black color
    window.clear(Color::Green);

    // draw everything here...
    window.draw(text);
    window.draw(alpha);

    // end the current frame
    window.display();
  }

  return 0;
}
