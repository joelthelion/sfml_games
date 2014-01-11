#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <cmath>
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
				std::sort(files.begin(),files.end());
				for (auto it: files) {
						Texture* text = new Texture();
						text->loadFromFile(it);
						textures.push_back(text);
				}
		}
		~Dice() {
				for (auto it: textures)
						delete it;
		}
		std::vector<Texture*> textures;

};


int main()
{
		// create the window
		//RenderWindow window(VideoMode(800, 600), "My window");
		RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
		Text text;
		Font font;
		font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
		text.setFont(font);
		text.setCharacterSize(247);
		text.setColor(Color::Black);
		text.setPosition(1660,193);

		Sprite sprite;
		Dice dice;
		//Texture texture;
		//texture.loadFromFile("resources/dice/1.png");
		sprite.setPosition(1600,540);
		int current = rand() % 6 +1;
		sprite.setTexture(*(dice.textures[current-1]));
		text.setString(static_cast<char>(48+current));

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
												int current = rand() % 6 +1;
												sprite.setTexture(*(dice.textures[current-1]));
												text.setString(static_cast<char>(48+current));
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
				window.draw(sprite);

				// end the current frame
				window.display();
		}

		return 0;
}
