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
  float display_height = 0.65 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Cellular automaton evolution");

  long unsigned n = 4 * width * heigth;
  sf::VertexArray grid{
      sf::LineStrip,
      n};  // sf::LineStrip o sf::Quad ? non ho capito la differenza. con quad non si vede niente, con LineStrip roba brutta
  sf::Vector2f topleft_vertex{.1f * display_width, .2f * display_height};

  for (int i = 0; i != 2 * width; i++) {
    for (int j = 0; j != 2 * heigth; j++) {
      grid[i + j * width].position =
          sf::Vector2f(topleft_vertex.x + i * 10, topleft_vertex.y + j * 10);
      grid[i + j * width].color = sf::Color::Black;
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
    window.draw(grid);
    window.display();
  }
}
