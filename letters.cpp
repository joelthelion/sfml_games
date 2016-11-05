#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
namespace fs = ::boost::filesystem;

class TextLoader {
	public:
		TextLoader() :
			colors({Color::Black,Color::White,Color::Blue,Color::Red,Color::Yellow,
					Color::Magenta,Color::Cyan,Color(255,128,0),Color(50,128,70),
					Color(130,60,30)})
		{
			font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
		}
		~TextLoader() {
		}
		void AddString(const std::string input) {
			for (auto c: input) {
				if (std::find(letters.begin(),letters.end(),c) == letters.end()) {
					letters.push_back(c);
				}
			}
			strings.push_back(input);
		}
		std::vector<sf::Text> getRandomTexts() {
			assert(strings.size());
			std::string choice = strings[rand() % strings.size()];
			std::vector<sf::Text> output;
			output.resize(choice.size());
			//for (auto c: letters) std::cout << c;
			//std::cout << std::endl;
			for (unsigned int i = 0; i<choice.size(); ++i) {
				output[i].setFont(font);
				output[i].setString(choice[i]);
				output[i].setCharacterSize(128);
				output[i].setFillColor(colors[(std::find(letters.begin(),letters.end(),choice[i])-letters.begin())%colors.size()]);
			}
			return output;
		}
	protected:
		std::vector<std::string> strings;
		std::vector<Color> colors;
		std::vector<char> letters;
		Font font;

};

void RandomlyPlaceTexts(sf::Window& window,std::vector<sf::Text>& sprites) {
	const int width = window.getSize().x;
	const int height = window.getSize().y-00;
	unsigned int tries = 0;
	restart:
	for (auto it = sprites.begin(); it != sprites.end();++it) {
		it->setOrigin(0,0);
		it->setPosition(rand()%(int)(width - it->getGlobalBounds().width - it->getLocalBounds().left),
				rand()%(int)(height - it->getLocalBounds().height -it->getLocalBounds().top));
		for (auto other = sprites.begin(); other != it; ++other) {
			if (tries < 1e5 && it->getGlobalBounds().intersects(other->getGlobalBounds())) {
				tries++;
				goto restart;
			}
		}
	}
}

int main()
{
	TextLoader sprites;
	//sprites.AddString("ANTONINNNANTONIN");
	sprites.AddString("ANTONIN");
	sprites.AddString("LISA");
	sprites.AddString("MAMAN");
	sprites.AddString("PAPA");
	sprites.AddString("JOEL");
	Music music;
	music.openFromFile("resources/mario.ogg");
	music.setLoop(true);
	music.play();

    // create the window
    //RenderWindow window(VideoMode(800, 600), "My window");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
	window.setMouseCursorVisible(false);

	std::vector<sf::Text> images = sprites.getRandomTexts();
	RandomlyPlaceTexts(window,images);

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
						images = sprites.getRandomTexts();
						RandomlyPlaceTexts(window,images);
						break;
					}
				default:
					break;
			}
        }

        // clear the window with black color
        window.clear(Color::Green);

        // draw everything here...
		for (auto image:images) {
         window.draw(image);
		}

        // end the current frame
        window.display();
    }

    return 0;
}
