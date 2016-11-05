#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <cmath>
#include <cstdio>
#include <letter_sounds.h>
#include <music.h>
#include <random_sprites.h>
#include <vector>

using namespace sf;
namespace fs = ::boost::filesystem;

struct Dice {
  Dice() {
    fs::directory_iterator end_it;
    std::vector<std::string> files;
    for (fs::directory_iterator it("resources/dice/"); it != end_it; ++it) {
      if (fs::is_regular_file(*it)) {
        files.push_back(it->path().generic_string());
      }
    }
    std::sort(files.begin(), files.end());
    for (auto it : files) {
      Texture *text = new Texture();
      text->loadFromFile(it);
      textures.push_back(text);
    }
  }
  ~Dice() {
    for (auto it : textures)
      delete it;
  }
  std::vector<Texture *> textures;
};

Vector2f AdaptToWindowSize(int x, int y, const RenderWindow &window,
                           int original_width = 1920,
                           int original_height = 1080) {
  Vector2f pos;
  pos.x = static_cast<double>(x) * window.getSize().x / original_width;
  pos.y = static_cast<double>(y) * window.getSize().y / original_height;
  return pos;
}

int main() {
  const int MAX_N = 3;
  MarioPlayer mario(20.);
  // create the window
  // RenderWindow window(VideoMode(800, 600), "My window");
  RenderWindow window(VideoMode::getFullscreenModes()[0], "My window",
                      Style::Fullscreen);
  Text text;
  Font font;
  font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
  text.setFont(font);
  text.setCharacterSize(247 * window.getSize().y / 1080);
  text.setFillColor(Color::Black);
  Vector2f pos = AdaptToWindowSize(1660, 193, window);
  text.setPosition(pos.x, pos.y);

  Texture background_t;
  background_t.loadFromFile("resources/dice_bck.png");
  Sprite background;
  background.setTexture(background_t);
  background.setScale(window.getSize().x / 1920., window.getSize().y / 1080.);

  Sprite sprite;
  RandomSpriteLoader random_sprites;
  // random_sprites.Get
  Dice dice;
  // Texture texture;
  // texture.loadFromFile("resources/dice/1.png");
  pos = AdaptToWindowSize(1600, 540, window);
  sprite.setPosition(pos.x, pos.y);
  sprite.setScale(window.getSize().y / 1080., window.getSize().y / 1080.);
  int current = rand() % MAX_N + 1;
  sprite.setTexture(*(dice.textures[current - 1]));
  text.setString(static_cast<char>(48 + current));
  std::vector<Sprite> sprites = random_sprites.getRandomSpriteNTimes(current);
  Vector2f sprite_region = AdaptToWindowSize(1500, 1080, window);
  RandomlyPlaceSprites(window, sprites, sprite_region);
  LetterSounds::play(48 + current);

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
          current = rand() % MAX_N + 1;
          sprite.setTexture(*(dice.textures[current - 1]));
          text.setString(static_cast<char>(48 + current));
          sprites = random_sprites.getRandomSpriteNTimes(current);
          RandomlyPlaceSprites(window, sprites, sprite_region);
          if (current > 9)
            LetterSounds::play(48 + current);
          break;
        }
      default:
        break;
      }
    }

    // clear the window with black color
    window.clear(Color::Green);

    // draw everything here...
    window.draw(background);
    window.draw(text);
    window.draw(sprite);
    for (auto s : sprites)
      window.draw(s);

    // end the current frame
    window.display();
  }

  return 0;
}
