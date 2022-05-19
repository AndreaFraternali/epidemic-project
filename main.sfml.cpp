#include "epidemic.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

//Function which converts positions from SFML coordinates to user-defined ones, centred in origin
sf::Vector2f ConvertCoordinates(sf::Vector2f p, sf::Vector2f origin){
  return sf::Vector2f{p.x + origin.x, origin.y - p.y};
}

int main() {
  //acquiring data

  int days = 40;
  int N = 100000;
  Epidemic epidemic{0.0117399, 0.19317, 0.01, Day{N, 500, 0}};
  std::vector<Day> evolution{};
  for (int i = 0; i != days; i++) {
    epidemic.evolve(1);
    evolution.push_back(epidemic.state());
  }

  //graphics
  float display_width = 0.7 * sf::VideoMode::getDesktopMode().width;
  float display_height = 0.8 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SIR model graphics");
  
  sf::VertexArray y_axis(sf::Lines, 2);
  sf::VertexArray x_axis(sf::Lines, 2);
  sf::Vector2f origin{ 0.1f * display_width, 0.9f * display_height};
  
  double xmax = 0.9 * display_width;
  double ymax = 0.1 * display_height;
  double xscale = xmax/days;  //da rivedere
  double yscale = ymax/N;     //da rivedere

  y_axis[0].position = origin;
  y_axis[1].position = sf::Vector2f(origin.x, ymax);
  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;
  
  x_axis[0].position = origin;
  x_axis[1].position = sf::Vector2f(xmax, origin.y);
  x_axis[0].color = sf::Color::Black;
  x_axis[1].color = sf::Color::Black;
  
  sf::CircleShape Spoint{};
  Spoint.setRadius(5);
  Spoint.setFillColor(sf::Color::Green);

  sf::CircleShape Ipoint{};
  Ipoint.setRadius(5);
  Ipoint.setFillColor(sf::Color::Red);

  sf::CircleShape Rpoint{};
  Rpoint.setRadius(5);
  Rpoint.setFillColor(sf::Color::Blue);

  //game loop
  while (window.isOpen()) {
    
    //managing events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
  
    window.draw(y_axis);
    window.draw(x_axis);

    for(int i = 0; i < days; i++){
      // //come disegnarli?
      
      // window.draw(Spoint);
      // window.draw(Ipoint);
      // window.draw(Rpoint);
    }

    window.display();


  }

}
