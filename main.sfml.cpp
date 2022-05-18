#include "epidemic.cpp"

#include <SFML/Graphics.hpp>
#include <vector>

int main() {
  //acquiring data

  int days = 40;
  int N = 100000;
  Epidemic epidemic{0.0117399, 0.19317, Day{N, 500, 0}};
  std::vector<Day> evolution{};
  for (int i = 0; i != days; i++) {
    epidemic.evolve(1);
    evolution.push_back(epidemic.state());
  }

  //graphics
  auto display_width = 0.7 * sf::VideoMode::getDesktopMode().width;
  auto display_height = 0.8 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SIR model graphics");
  
  sf::VertexArray y_axis(sf::Lines, 2);
  sf::VertexArray x_axis(sf::Lines, 2);
  sf::Vertex origin{sf::Vector2f( 0.1 * display_width, 0.9 * display_height)};
  
  double xmax = 0.9 * display_width;
  double ymax = 0.1 * display_height;
  double xscale = xmax/days;  //da rivedere
  double yscale = ymax/N;     //da rivedere

  y_axis[0].position = origin.position;
  y_axis[1].position = sf::Vector2f(origin.position.x, ymax);
  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;
  
  x_axis[0].position = origin.position;
  x_axis[1].position = sf::Vector2f(xmax, origin.position.y);
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
      //come disegnarli?
      Spoint.setPosition((i * xscale + origin.position.x) , - evolution[i].S * yscale + origin.position.y);
      Ipoint.setPosition((i * xscale + origin.position.x), -evolution[i].I * yscale + origin.position.y );
      Rpoint.setPosition((i * xscale + origin.position.x), -evolution[i].R * yscale + origin.position.y);
      window.draw(Spoint);
      window.draw(Ipoint);
      window.draw(Rpoint);
    }

    window.display();


  }

}
