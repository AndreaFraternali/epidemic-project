#include "automaton.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  std::cout << "Larghezza = ";
  int width;
  std::cin >> width;
  std::cout << "Altezza = ";
  int heigth;
  std::cin >> heigth;
  std::cout << "Infetti iniziali = ";
  int init_inf;
  std::cin >> init_inf;
  std::cout << "Rimossi iniziali = ";
  int init_rem;
  std::cin >> init_rem;
  std::cout << "Beta = ";
  double beta;
  std::cin >> beta;
  std::cout << "Gamma = ";
  double gamma;
  std::cin >> gamma;

  float display_width = 0.6 * sf::VideoMode::getDesktopMode().width;
  float display_height = 0.7 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Cellular automaton evolution");

  sf::VertexArray grid(sf::LineStrip, width * heigth);
  for(int i = 0; i < width*heigth; i++){
      grid[i].position = sf::Vector2f((i +100) * display_width, 0.5 * display_height);
  }

  while (window.isOpen()) {
    // managing events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);


    window.draw(grid);

    window.display();
  }
}
  