#include "automaton.hpp"
#include "graph.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

int main() {
  std::cout << "Larghezza = ";
  int width;
  std::cin >> width;
  std::cout << "Altezza = ";
  int height;
  std::cin >> height;
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
  std::cout << "Giorni = ";
  int days;
  std::cin >> days;

  Automaton autom{width, height, beta, gamma};
  std::random_device gen{};
  std::uniform_int_distribution<int> dis{0, width * height - 1};
  for (int i = 0; i != init_inf;) {
    int n = dis(gen);
    if (autom.set(n, Cell::I)) {
      i++;
    }
  }
  for (int i = 0; i != init_rem;) {
    int n = dis(gen);
    if (autom.set(n, Cell::R)) {
      i++;
    }
  }

  // graphics
  float display_width = 0.8 * sf::VideoMode::getDesktopMode().width;
  float display_height = 0.7 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Cellular automaton evolution");
  sf::Vector2f topleft_vertex{.02f * display_width, .1f * display_height};
  sf::Vector2f topright_vertex{.5f * display_width, .1f * display_height};

  // fattori di riscalo per la griglia
  float xscale = (topright_vertex.x - topleft_vertex.x) / width;
  float yscale = (display_height - 2 * topleft_vertex.y) / height;

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

  // Building graph
  sf::Vector2f origin{topright_vertex.x + 40,
                      topright_vertex.y + height * yscale};
  Graph graph{origin, .95 * display_width, topleft_vertex.y};
  graph.add_xlabel("Day");
  graph.add_ylabel("People");
  sf::CircleShape circ{};

  // fattori di riscalo per il grafico
  float gscale_x = (.95 * display_width - origin.x) / days;
  float gscale_y = (origin.y - topleft_vertex.y) / (width * height);

  // labels e legenda
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

  sf::Text legS{"Suscettibili", font, 22};
  legS.setFillColor(sf::Color::Black);
  legS.setPosition(0.85 * display_width, 0.05 * display_height);
  sf::Text legI{"Infetti", font, 22};
  legI.setFillColor(sf::Color::Black);
  legI.setPosition(0.85 * display_width, 0.09 * display_height);
  sf::Text legR{"Rimossi", font, 22};
  legR.setFillColor(sf::Color::Black);
  legR.setPosition(0.85 * display_width, 0.13 * display_height);

  sf::CircleShape Scirc{6};
  Scirc.setFillColor(sf::Color::Green);
  Scirc.setPosition(0.95 * display_width, 0.065 * display_height);
  sf::CircleShape Icirc{6};
  Icirc.setFillColor(sf::Color::Red);
  Icirc.setPosition(0.95 * display_width, 0.105 * display_height);
  sf::CircleShape Rcirc{6};
  Rcirc.setFillColor(sf::Color::Blue);
  Rcirc.setPosition(0.95 * display_width, 0.145 * display_height);

  window.setFramerateLimit(5);

  while (window.isOpen()) {
    // managing events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);
    // drawing graph
    window.draw(graph);
    // drawing grid
    for (auto const& r : grid) {
      window.draw(r);
    }
    // drawing day counter
    window.draw(label);
    day.setString(std::to_string(d));
    window.draw(day);

    // drawing legend
    window.draw(legS);
    window.draw(legI);
    window.draw(legR);
    window.draw(Scirc);
    window.draw(Icirc);
    window.draw(Rcirc);

    // evolving autom, setting cells colors and adding points
    if (d < days) {
      int count_s = 0;
      int count_i = 0;
      int count_r = 0;
      autom.evolve();
      for (int i = 0, n = autom.state().size(); i != n; i++) {
        if (autom.state()[i] == Cell::S) {
          grid[i].setFillColor(sf::Color::Green);
          count_s++;
        } else {
          if (autom.state()[i] == Cell::I) {
            grid[i].setFillColor(sf::Color::Red);
            count_i++;
          } else {
            grid[i].setFillColor(sf::Color::Blue);
            count_r++;
          }
        }
      }
      circ.setPosition(ConvertCoordinates(
          sf::Vector2f(d * gscale_x, count_s * gscale_y), origin));
      graph.add_sp(circ);
      circ.setPosition(ConvertCoordinates(
          sf::Vector2f(d * gscale_x, count_i * gscale_y), origin));
      graph.add_ip(circ);
      circ.setPosition(ConvertCoordinates(
          sf::Vector2f(d * gscale_x, count_r * gscale_y), origin));
      graph.add_rp(circ);
      d++;
    }

    window.display();
  }
}
