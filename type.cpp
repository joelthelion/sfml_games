#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
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
		Background(Font& font, const RenderWindow& win) {
				txt.setCharacterSize(52);
				txt.setColor(Color::Black);
				txt.setFont(font);
				win_width = win.getSize().x;
				win_height = win.getSize().y;
		}
		void SetBackground(Texture& texture) {
				texture.loadFromFile(background_image);
		}
		void setOriginalTextPosition(int x,int y) {
				txt.setPosition(x*win_width/original_width,y*win_height/original_height);
		}
		void setOriginalWidth(int w) {
				width = w*win_width/original_width;
		}
		protected:
			int original_width=1920;
			int original_height=1080;
			int win_width;
			int win_height;
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

		Clock clock;
		bool first_run = true;
		
		std::vector<Background*> vec_backgrounds;
		Background flash(font,window);
		flash.setOriginalTextPosition(655,170);
    flash.background_image = "resources/cars.jpg";
		flash.setOriginalWidth(1132);
		vec_backgrounds.push_back(&flash);
		Background king(font,window);
		king.setOriginalTextPosition(655,170);
    king.background_image = "resources/king2.jpg";
		king.setOriginalWidth(1132);
		vec_backgrounds.push_back(&king);
		Background hicks(font,window);
		hicks.setOriginalTextPosition(696,118);
    hicks.background_image = "resources/hicks2.jpg";
		hicks.setOriginalWidth(1088);
		vec_backgrounds.push_back(&hicks);

		std::random_shuffle(vec_backgrounds.begin(),vec_backgrounds.end());
		std::list<Background*> backgrounds;
		std::copy(vec_backgrounds.begin(),vec_backgrounds.end(),std::back_inserter(backgrounds));

		char letter;

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
						letter = tolower((char)str[0]);
						if ((first_run || clock.getElapsedTime().asMilliseconds() >= 700) && (
												(letter >= 'a' && letter <= 'z') ||
												(letter >= '0' && letter <= '9'))) {
								clock.restart();
								first_run = false;

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
