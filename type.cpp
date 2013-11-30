#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <map>
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
				static SoundMap init_map() {
						SoundMap map;
						for (char i='a';i<='z';++i) {
								std::cout << "init " << i << std::endl;
								SoundBuffer b;
								std::string filename = "x.ogg";
								filename[0] = i;
								b.loadFromFile("lettres/"+filename);
								map[i] = b;  
						}
						return map;
				}
				static SoundMap sounds;
				static Sound snd;
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
		Text txt;
		txt.setFont(font);

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
						char letter = (char)str[0];
						if (letter >= 'a' && letter <= 'z') {
								std::cout << letter << std::endl;
								LetterSounds::play(letter);
								text += toupper(letter);
						}
						break;
					}
				default:
					break;
			}
        }

        // clear the window with black color
        window.clear(Color::Green);

        // draw everything here...
				txt.setString(text);
				window.draw(txt);
				

        // end the current frame
        window.display();
    }

    return 0;
}
