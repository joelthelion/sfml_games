#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;


int main()
{
    // create the window
    RenderWindow window(VideoMode(800, 600), "My window");

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
						std::cout << str.toAnsiString() << std::endl;
						break;
					}
				default:
					break;
			}
        }

        // clear the window with black color
        window.clear(Color::Green);

        // draw everything here...

        // end the current frame
        window.display();
    }

    return 0;
}
