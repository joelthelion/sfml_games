#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <map>

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
		txt.setCharacterSize(52);
		txt.setColor(Color::Black);
		txt.setFont(font);
		txt.setPosition(668,170);

		RectangleShape background;
		Texture background_t;
		background_t.loadFromFile("resources/cars.jpg");
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
						char letter = tolower((char)str[0]);
						if (letter >= 'a' && letter <= 'z') {
								LetterSounds::play(letter);
								if (text.size() >= 30) text = "";
								text += toupper(letter);
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
				txt.setString(text);
				window.draw(txt);
				

        // end the current frame
        window.display();
    }

    return 0;
}
