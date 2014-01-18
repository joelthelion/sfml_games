#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <cmath>
#include <list>
#include <algorithm>
#include <iostream>
#include <letter_sounds.h>

using namespace sf;

struct Background {
		std::string background_image;
		int width;
		Background(Font& f, const RenderWindow& win) :
				font(f),
				text_width(0)
		{
				font = f;
				win_width = win.getSize().x;
				win_height = win.getSize().y;
		}
		void SetBackground(Texture& texture) {
				texture.loadFromFile(background_image);
		}
		void setOriginalTextPosition(int x,int y) {
				position.x = x*win_width/original_width;
				position.y = y*win_height/original_height;
		}
		void setOriginalWidth(int w) {
				width = w*win_width/original_width;
		}
		void setString(std::string s) {
				letters.clear();
				float x = position.x;
				for (auto i:s) {
						letters.emplace_back();
						Text& txt = letters.back();
						txt.setCharacterSize(52);
						txt.setColor(Color::Black);
						txt.setFont(font);
						char a[] = {(char)tolower(i),'\n',(char)toupper(i),0};
						txt.setString(a);
						txt.setPosition(x,position.y);
						x += txt.getLocalBounds().width;
				}
				text_width = x - position.x;
		}
		void render(RenderWindow& window) {
				for (auto i:letters) {
						window.draw(i);
				}
		}
		protected:
			int original_width=1920;
			int original_height=1080;
			int win_width;
			int win_height;
			std::vector<Text> letters;
			Vector2f position;
			Font& font;
		public:
			int text_width;
};


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
		flash.setOriginalTextPosition(655,125);
    flash.background_image = "resources/cars.jpg";
		flash.setOriginalWidth(1132);
		vec_backgrounds.push_back(&flash);
		Background king(font,window);
		king.setOriginalTextPosition(655,125);
    king.background_image = "resources/king2.jpg";
		king.setOriginalWidth(1132);
		vec_backgrounds.push_back(&king);
		Background hicks(font,window);
		hicks.setOriginalTextPosition(696,73);
    hicks.background_image = "resources/hicks2.jpg";
		hicks.setOriginalWidth(1088);
		vec_backgrounds.push_back(&hicks);

		//std::random_shuffle(vec_backgrounds.begin(),vec_backgrounds.end());
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
								current.setString(text);
								if (current.text_width > current.width ) {
										text = toupper(letter);
										current.setString(text);
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
				backgrounds.front()->setString(text);
				backgrounds.front()->render(window);

        // end the current frame
        window.display();
    }

    return 0;
}
