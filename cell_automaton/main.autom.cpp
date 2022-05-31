#include "automaton.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>


int main() {
  // std::cout << "Larghezza = ";
  // int width;
  // std::cin >> width;
  // std::cout << "Altezza = ";
  // int heigth;
  // std::cin >> heigth;
  // std::cout << "Infetti iniziali = ";
  // int init_inf;
  // std::cin >> init_inf;
  // std::cout << "Rimossi iniziali = ";
  // int init_rem;
  // std::cin >> init_rem;
  // std::cout << "Beta = ";
  // double beta;
  // std::cin >> beta;
  // std::cout << "Gamma = ";
  // double gamma;
  // std::cin >> gamma;
  int width = 30;
  int height = 20;
  double beta = .3;
  double gamma = .1;
  int days = 100;
  int init_inf = 5;

  Automaton autom{width, height, beta, gamma};
  std::random_device gen{};
  std::uniform_int_distribution<int> dis{0, width * height - 1};
  int i = 0;
  do {
    int n = dis(gen);
    if (autom.set(n, Cell::I)) {
      i++;
    }
  } while (i != init_inf);

  // graphics
  float display_width = 0.8 * sf::VideoMode::getDesktopMode().width;
  float display_height = 0.7 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Cellular automaton evolution");
  sf::Vector2f topleft_vertex{.05f * display_width, .15f * display_height};

  // fattori di riscalo, sono da rivedere
  double xscale = (display_width - 2 * topleft_vertex.x) / width;
  double yscale = (display_height - 2 * topleft_vertex.y) / height;

  // Building grid
  std::vector<sf::RectangleShape> grid(width * height);
  for (int j = 0; j != height; j++) {
    for (int i = 0; i != width; i++) {
      grid[i + j * width].setPosition(sf::Vector2f(
          topleft_vertex.x + i * xscale, topleft_vertex.y + j * yscale));
      grid[i + j * width].setOutlineColor(sf::Color::Black);
      grid[i + j * width].setOutlineThickness(2);
      grid[i + j * width].setSize(sf::Vector2f(xscale, yscale));
    }
  }

  // labels
  sf::Font font;
  if (!font.loadFromFile("times.ttf")) {
  }
  sf::Text label{"Day : ", font, 24};
  label.setFillColor(sf::Color::Black);
  label.setPosition(sf::Vector2f(topleft_vertex.x, topleft_vertex.y - 35));
  int d = 0;
  sf::Text day{};
  day.setPosition(sf::Vector2f(topleft_vertex.x + 60, topleft_vertex.y - 35));
  day.setFillColor(sf::Color::Black);
  day.setFont(font);
  day.setCharacterSize(24);

  while (window.isOpen()) {
    // managing events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);

    for (auto const& r : grid) {
      window.draw(r);
    }

    window.draw(label);
    day.setString(std::to_string(d));
    window.draw(day);

    autom.evolve();
    for (int i = 0, n = autom.state().size(); i != n; i++) {
      if (autom.state()[i] == Cell::S) {
        grid[i].setFillColor(sf::Color::Green);
      } else {
        if (autom.state()[i] == Cell::I) {
          grid[i].setFillColor(sf::Color::Red);

        } else {
          grid[i].setFillColor(sf::Color::Blue);
        }
      }
    }

    d++;
    window.display();
  }
}
