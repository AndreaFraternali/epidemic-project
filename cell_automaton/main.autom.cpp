#include "automaton.hpp"
#include "graph.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
  // reading and checking input values
  int width;
  int height;
  int init_inf;
  int init_rem;
  double beta;
  double gamma;
  int days;
  try {
    std::cout << "Larghezza = ";
    std::cin >> width;
    if (!std::cin) {
      throw std::runtime_error("Lettura della larghezza della griglia fallita");
    }
    std::cout << "Altezza = ";
    std::cin >> height;
    if (!std::cin) {
      throw std::runtime_error("Lettura dell'altezza della griglia fallita");
    }
    std::cout << "Infetti iniziali = ";
    std::cin >> init_inf;
    if (!std::cin) {
      throw std::runtime_error(
          "Lettura del numero di infetti iniziali fallita");
    }
    std::cout << "Rimossi iniziali = ";
    std::cin >> init_rem;
    if (!std::cin) {
      throw std::runtime_error(
          "Lettura del numero di rimossi iniziali fallita");
    }
    std::cout << "Beta = ";
    std::cin >> beta;
    if (!std::cin) {
      throw std::runtime_error("Lettura del parametro beta fallita");
    }
    std::cout << "Gamma = ";
    std::cin >> gamma;
    if (!std::cin) {
      throw std::runtime_error("Lettura del parametro gamma fallita");
    }
    std::cout << "Giorni = ";
    std::cin >> days;
    if (!std::cin) {
      throw std::runtime_error("Lettura del numero di giorni fallita");
    }
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
    std::exit(0);
  }

  // creating automaton
  Automaton autom{};
  try {
    autom = Automaton{width, height, beta, gamma, init_inf, init_rem};
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
    std::exit(0);
  }
  int const N = width * height;

  // graphics
  float const display_width = 0.85 * sf::VideoMode::getDesktopMode().width;
  float const display_height = 0.7 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Cellular automaton evolution");
  
  sf::Vector2f const topleft_vertex{.02f * display_width, .1f * display_height};
  sf::Vector2f const topright_vertex{.5f * display_width, .1f * display_height};
  
  float const delta_x = .01 * display_width;
  float const delta_y = .02 * display_height;

  // grid scale factors
  float const xscale = (topright_vertex.x - topleft_vertex.x) / width;
  float const yscale = (display_height - 2 * topleft_vertex.y) / height;

  // building grid
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

  // building graph
  sf::Vector2f origin{topright_vertex.x + 5 * delta_x,
                      topright_vertex.y + height * yscale};
  double const xmax = .95 * display_width;
  double const ymax = topleft_vertex.y;
  Graph graph{origin, xmax, ymax};
  graph.add_xlabel("giorni");
  graph.add_ylabel("persone");
  sf::CircleShape circ{};

  // graph scale factors
  float const gscale_x = (xmax - origin.x - delta_x) / days;
  float const gscale_y = (origin.y - topleft_vertex.y - delta_y) / N;

  // labels and legend
  sf::Font font;
  try {
    if (!font.loadFromFile("times.ttf")) {
      throw std::runtime_error("Lettura del file di font fallita");
    }
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  }
  sf::Text legS{"Suscettibili", font, 22};
  legS.setFillColor(sf::Color::Black);
  legS.setPosition(.85 * display_width, .03 * display_height);
  sf::Text legI{"Infetti", font, 22};
  legI.setFillColor(sf::Color::Black);
  legI.setPosition(.85 * display_width, .07 * display_height);
  sf::Text legR{"Rimossi", font, 22};
  legR.setFillColor(sf::Color::Black);
  legR.setPosition(.85 * display_width, .11 * display_height);

  sf::CircleShape Scirc{6};
  Scirc.setFillColor(sf::Color::Green);
  Scirc.setPosition(.95 * display_width, .045 * display_height);
  sf::CircleShape Icirc{6};
  Icirc.setFillColor(sf::Color::Red);
  Icirc.setPosition(.95 * display_width, .085 * display_height);
  sf::CircleShape Rcirc{6};
  Rcirc.setFillColor(sf::Color::Blue);
  Rcirc.setPosition(.95 * display_width, .125 * display_height);

  sf::Text label{"Giorno : ", font, 24};
  label.setFillColor(sf::Color::Black);
  label.setPosition(
      sf::Vector2f(topleft_vertex.x, topleft_vertex.y - 3 * delta_y));
  int d = 0;
  sf::Text day{};
  day.setPosition(sf::Vector2f(topleft_vertex.x + .07 * display_width,
                               topleft_vertex.y - 3 * delta_y));
  day.setFillColor(sf::Color::Black);
  day.setFont(font);
  day.setCharacterSize(24);

  window.setFramerateLimit(5);

  // game loop
  while (window.isOpen()) {
    // managing closing event
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
    day.setString(std::to_string(d - 1));
    window.draw(day);

    // drawing legend
    window.draw(legS);
    window.draw(legI);
    window.draw(legR);
    window.draw(Scirc);
    window.draw(Icirc);
    window.draw(Rcirc);

    // evolving autom, setting cells colors and adding points
    if (d <= days) {
      int count_s = 0;
      int count_i = 0;
      int count_r = 0;
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
      autom.evolve();
      d++;
    }

    // writing numbers along axes
    for (double i = origin.x; i <= xmax; i += days / 10 * gscale_x) {
      int n = (i - origin.x) / gscale_x;
      sf::Text num{std::to_string(n), font, 18};
      num.setFillColor(sf::Color::Black);
      num.setPosition(i, origin.y + delta_y);
      window.draw(num);
    }

    for (double i = origin.y; i >= ymax; i -= N / 10 * gscale_y) {
      int n = (origin.y - i) / gscale_y;
      sf::Text num{std::to_string(n), font, 18};
      num.setFillColor(sf::Color::Black);
      num.setPosition(origin.x - 3 * delta_x, i - delta_y);
      window.draw(num);
    }

    window.display();
  }
}
