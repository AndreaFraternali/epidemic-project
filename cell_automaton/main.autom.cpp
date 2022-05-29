#include "automaton.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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

  float display_width = 0.8 * sf::VideoMode::getDesktopMode().width;
  float display_height = 0.6 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Cellular automaton evolution");

  std::vector<sf::RectangleShape> grid;

  for (int i = 0; i != heigth; i++) {
    for (int j = 0; j != width; j++) {
      sf::RectangleShape r(sf::Vector2f{8, 8});
      r.setOutlineColor(sf::Color::Black);
      r.setOutlineThickness(2);
      r.setPosition(sf::Vector2f(0.2 * display_width + j * 1000/width,
                                 0.2 * display_height + i* 1000/heigth));
      grid.push_back(r);
    }
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

    for (int i = 0; i != width * heigth; i++) {
      window.draw(grid[i]);
    }

    window.display();
  }
}
