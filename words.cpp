#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using std::cout;
using std::endl;
namespace fs = ::boost::filesystem;

class TextLoader {
	public:
		const unsigned int N_OTHER_WORDS = 3;
		TextLoader() :
			colors({Color::Black,Color::White,Color::Blue,Color::Red,Color::Yellow,
					Color::Magenta,Color::Cyan,Color(255,128,0),Color(50,128,70),
					Color(130,60,30)})
		{
			font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
		}
		~TextLoader() {
		}
		void AddString(const std::string input) {
			strings.push_back(input);
		}
		void SetOtherWords(const std::vector<std::string>& input) {
			other_words = input;
		}
		void AddText(std::string word,std::vector<Text>& texts) {
			//cout << word << endl;
			Text text(word,font);
			text.setCharacterSize(72);
			text.setColor(colors[8]);
			texts.push_back(text);
			//cout << (texts[texts.size()-1].getString().toAnsiString()) << endl;
		}
		std::vector<sf::Text> getRandomTexts() {
			assert(strings.size());
			assert(other_words.size());
			std::vector<sf::Text> output;
			random_shuffle(strings.begin(),strings.end());
			random_shuffle(other_words.begin(),other_words.end());
			AddText(strings[0],output);
			for (unsigned int i=0; i<N_OTHER_WORDS;i++)
				AddText(other_words[i],output);
			return output;
		}
	protected:
		std::vector<std::string> strings;
		std::vector<std::string> other_words;
		std::vector<Color> colors;
		Font font;
};


void RandomlyPlaceTexts(sf::Window& window,std::vector<sf::Text>& sprites) {
	const int width = window.getSize().x;
	const int height = window.getSize().y-00;
	unsigned int tries = 0;
	//cout << "SIZE:" << sprites.size() << endl;
	restart:
	for (auto it = sprites.begin(); it != sprites.end();++it) {
		it->setOrigin(0,0);
		it->setPosition(rand()%(int)(width - it->getGlobalBounds().width - it->getLocalBounds().left),
				rand()%(int)(height - it->getLocalBounds().height -it->getLocalBounds().top));
		//cout << it->getPosition().x << "/" << it->getPosition().y << endl;
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
	//sprites.AddString("LISA");
	//sprites.AddString("MAMAN");
	//sprites.AddString("PAPA");
	//sprites.AddString("JOEL");
	std::vector<std::string> other_words = {"VOITURE","VELO","SCENIC","PAPA","MAMAN","LISA","MAISON","CLIO","CRECHE","MALHEUREUSEMENT","BIBA"};
	sprites.SetOtherWords(other_words);
	Music music;
	music.openFromFile("resources/mario.ogg");
	music.setLoop(true);
	music.play();

    // create the window
    //RenderWindow window(VideoMode(800, 600), "My window");
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
	window.setMouseCursorVisible(false);

	std::vector<sf::Text> images = sprites.getRandomTexts();
	//cout << images.size() << endl;
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
