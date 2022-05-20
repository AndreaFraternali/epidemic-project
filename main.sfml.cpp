//aggiungere numeri, legenda e aggiustare distanze 

#include "epidemic.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

// Function which converts positions from SFML coordinates to user-defined ones,
// centred in origin
sf::Vector2f ConvertCoordinates(sf::Vector2f p, sf::Vector2f origin) {
  return sf::Vector2f{p.x + origin.x + 3, origin.y - p.y - 6};
}

int main() {
  // acquiring data

  int days = 120;
  int N = 100000;
  Epidemic epidemic{0.0117399, 0.19317, 0, Day{N, 300, 0}};
  std::vector<Day> evolution{};
  for (int i = 0; i != days; i++) {
    epidemic.evolve(1);
    evolution.push_back(epidemic.state());
  }

  // graphics
  float display_width = 0.6 * sf::VideoMode::getDesktopMode().width;
  float display_height = 0.7 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SIR model graphics");

  sf::VertexArray y_axis(sf::Lines, 2);
  sf::VertexArray x_axis(sf::Lines, 2);
  sf::Vector2f origin{0.1f * display_width, 0.9f * display_height};

  double xmax = 0.9 * display_width;
  double ymax = 0.1 * display_height;
  double xscale = (xmax - origin.x) / days;  
  double yscale = (origin.y - ymax) / N;  
  double delta_x = 0.01 * display_width;
  double delta_y = 0.02 * display_height;   


  y_axis[0].position = origin;
  y_axis[1].position = sf::Vector2f(origin.x, ymax - delta_y);
  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;

  x_axis[0].position = origin;
  x_axis[1].position = sf::Vector2f(xmax + delta_x, origin.y);
  x_axis[0].color = sf::Color::Black;
  x_axis[1].color = sf::Color::Black;

  sf::CircleShape Spoint{3};
  Spoint.setFillColor(sf::Color::Green);

  sf::CircleShape Ipoint{3};
  Ipoint.setFillColor(sf::Color::Red);

  sf::CircleShape Rpoint{3};
  Rpoint.setFillColor(sf::Color::Blue);

  // game loop
  while (window.isOpen()) {
    // managing events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);

    window.draw(y_axis);
    window.draw(x_axis);

    for (int i = 0; i != days ; i++) {
      Spoint.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].S * yscale),
          origin)); 
      Ipoint.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].I * yscale),
          origin));
      Rpoint.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].R * yscale),
          origin));
      window.draw(Spoint);
      window.draw(Ipoint);
      window.draw(Rpoint);
    }

    window.display();
  }
}
