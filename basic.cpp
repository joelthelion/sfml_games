#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

float limit(float x,float y) {
  double margin = 30;
  if (x < -margin)
    return -margin;
  else if (x > y + margin)
    return y+margin;
  else
    return x;
}

int main()
{
  // create the window
  RenderWindow window(VideoMode(800, 600), "My window");
  //RenderWindow window(VideoMode::getFullscreenModes()[0], "My window", Style::Fullscreen);

  RectangleShape car(Vector2f(10,20));
  car.setPosition(Vector2f(window.getSize().x/2,window.getSize().y/2));

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
            car.setPosition(Vector2f(window.getSize().x/2,window.getSize().y/2));
            break;
          }
        default:
          break;
      }
    }
    Vector2f delta;
    float speed = 6.f;
    if (Keyboard::isKeyPressed(Keyboard::Left))
      delta = Vector2f(-speed,0);
    if (Keyboard::isKeyPressed(Keyboard::Right))
      delta = Vector2f(speed,0);
    if (Keyboard::isKeyPressed(Keyboard::Up))
      delta = Vector2f(0,-speed);
    if (Keyboard::isKeyPressed(Keyboard::Down))
      delta = Vector2f(0,speed);
    Vector2f pos(limit(car.getPosition().x + delta.x,window.getSize().x), limit(car.getPosition().y+delta.y,window.getSize().y));
    car.setPosition(pos);

    // clear the window with black color
    window.clear(Color::Green);

    // draw everything here...
    window.draw(car);

    // end the current frame
    window.display();
  }

  return 0;
}
