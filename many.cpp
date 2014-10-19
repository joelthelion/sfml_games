#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <cmath>
#include <vector>
#include <cstdio>
#include <random_sprites.h>
#include <music.h>
#include <sstream>

using namespace sf;
namespace fs = ::boost::filesystem;

Vector2f AdaptToWindowSize(int x, int y, const RenderWindow& window, int original_width=1920,int original_height=1080) {
		Vector2f pos;
		pos.x = static_cast<double>(x) * window.getSize().x / original_width;
		pos.y = static_cast<double>(y) * window.getSize().y / original_height;
		return pos;
}


int main()
{
    MarioPlayer mario(20.);
    // create the window
    // RenderWindow window(VideoMode(800, 600), "My window");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
    Text text;
    Font font;
    font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(180*window.getSize().y/1080);
    text.setColor(Color::Black);
    Vector2f pos = AdaptToWindowSize(1600,193,window);
    text.setPosition(pos.x,pos.y);

    Texture background_t;
    background_t.loadFromFile("resources/dice_bck.png");
    Sprite background;
    background.setTexture(background_t);
    background.setScale(window.getSize().x/1920.,window.getSize().y/1080.);

    RandomSpriteLoader random_sprites("resources/smarties/");
    //random_sprites.Get
    //Texture texture;
    //texture.loadFromFile("resources/dice/1.png");
    pos = AdaptToWindowSize(1600,540,window);
    const int max_smarties = 200;
    int current = rand() % max_smarties +1;
    std::stringstream ss;
    ss << current;
    text.setString(ss.str());
    std::vector<Sprite> sprites = random_sprites.getRandomSpritesWithRepeat(current);
    Vector2f sprite_region = AdaptToWindowSize(1500,1080,window);
    RandomlyPlaceSprites(window,sprites,sprite_region);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
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
                        current = rand() % max_smarties +1;
                        std::stringstream ss;
                        ss << current;
                        text.setString(ss.str());
                        sprites = random_sprites.getRandomSpritesWithRepeat(current);
                        RandomlyPlaceSprites(window,sprites,sprite_region);
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
        for (auto s: sprites)
            window.draw(s);

        // end the current frame
        window.display();
    }

    return 0;
}
