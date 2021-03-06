#include <SFML/Graphics.hpp>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <cmath>
#include <iostream>
#include <music.h>
#include <random_sprites.h>
#include <string>
#include <vector>

using namespace sf;
namespace fs = ::boost::filesystem;

int main() {
  const int MAX_N = 5;
  RandomSpriteLoader sprites;
  MarioPlayer mario;
  boost::filesystem::directory_iterator it;

  // create the window
  // RenderWindow window(VideoMode(800, 600), "My window");
  RenderWindow window(VideoMode::getFullscreenModes()[0], "My window",
                      Style::Fullscreen);
  window.setMouseCursorVisible(false);

  std::vector<sf::Sprite> images =
      sprites.getRandomSpriteNTimes(rand() % (MAX_N) + 1);
  RandomlyPlaceSprites(window, images);

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
          images = sprites.getRandomSpriteNTimes(rand() % (MAX_N) + 1);
          RandomlyPlaceSprites(window, images);
          break;
        }
      default:
        break;
      }
    }

    // clear the window with black color
    window.clear(Color(200, 255, 150));

    // draw everything here...
    for (auto image : images) {
      window.draw(image);
    }

    // end the current frame
    window.display();
  }

  return 0;
}
