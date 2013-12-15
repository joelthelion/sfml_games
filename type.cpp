#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <map>
#include <list>
#include <algorithm>
#include <iostream>

using namespace sf;

class LetterSounds {
		public:
				static void play(char letter) {
						snd.setBuffer(sounds[letter]);
						snd.play();
				}
		protected:
				typedef std::map<char,SoundBuffer> SoundMap;
				static void make_buffer(char i,SoundBuffer& b) {
						std::string filename = "x.ogg";
						filename[0] = i;
						b.loadFromFile("lettres2/"+filename);
				}
				static SoundMap init_map() {
						SoundMap map;
						for (char i='a';i<='z';++i) {
								SoundBuffer b;
								make_buffer(i,b);
								map[i] = b;  
						}
						for (char i='0';i<='9';++i) {
								SoundBuffer b;
								make_buffer(i,b);
								map[i] = b;  
						}
						return map;
				}
				static SoundMap sounds;
				static Sound snd;
};

struct Background {
		Text txt;
		std::string background_image;
		int width;
		Background(Font& font) {
				txt.setCharacterSize(52);
				txt.setColor(Color::Black);
				txt.setFont(font);
		}
		void SetBackground(Texture& texture) {
				texture.loadFromFile(background_image);
		}
};

LetterSounds::SoundMap LetterSounds::sounds = LetterSounds::init_map();
Sound LetterSounds::snd;


int main()
{
    // create the window
    RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);
    //RenderWindow window(VideoMode(800, 600), "My window");
		std::string text;
		Font font;
		font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
		
		std::vector<Background*> vec_backgrounds;
		Background flash(font);
		flash.txt.setPosition(655,170);
    flash.background_image = "resources/cars.jpg";
		flash.width = 1132;
		vec_backgrounds.push_back(&flash);
		Background king(font);
		king.txt.setPosition(655,170);
    king.background_image = "resources/king2.jpg";
		king.width = 1132;
		vec_backgrounds.push_back(&king);
		std::random_shuffle(vec_backgrounds.begin(),vec_backgrounds.end());
		std::list<Background*> backgrounds;
		std::copy(vec_backgrounds.begin(),vec_backgrounds.end(),std::back_inserter(backgrounds));

		char letter=0;

		RectangleShape background;
		Texture background_t;
		backgrounds.front()->SetBackground(background_t);
		background.setSize(Vector2f(window.getSize().x,window.getSize().y));
		background.setTexture(&background_t);

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
				case Event::TextEntered:
					{
						String str(event.text.unicode);
						if (str == "[") { return 0; }
						char new_letter = tolower((char)str[0]);
						if (new_letter != letter) {// Disallow long presses
								letter = new_letter;
								if ((letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9')) {
										LetterSounds::play(letter);
										text += toupper(letter);
										Background& current = *(backgrounds.front());
										current.txt.setString(text);
										if (current.txt.getLocalBounds().width > current.width ) {
												text = toupper(letter);
												current.txt.setString(text);
												backgrounds.splice(backgrounds.end(),backgrounds,backgrounds.begin());
												backgrounds.front()->SetBackground(background_t);
										}
								}
						}
						break;
					}
				default:
					break;
			}
        }

        // clear the window with black color
        window.clear();
				window.draw(background);

        // draw everything here...
				backgrounds.front()->txt.setString(text);
				window.draw(backgrounds.front()->txt);
				

        // end the current frame
        window.display();
    }

    return 0;
}
