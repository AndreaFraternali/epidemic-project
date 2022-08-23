#include "epidemic.hpp"
#include "graph.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
  // reading and checking input values
  int days = 0;
  int s = 0;
  int i = 0;
  int r = 0;
  double beta = 0;
  double gamma = 0;
  try {
    std::cout << "Numero di giorni =  ";
    std::cin >> days;
    if (!std::cin) {
      throw std::runtime_error("Lettura del numero di giorni fallita");
    }
    std::cout << "Suscettibili iniziali = ";
    std::cin >> s;
    if (!std::cin) {
      throw std::runtime_error(
          "Lettura del numero di suscettibili iniziali fallita");
    }
    std::cout << "Infetti iniziali = ";
    std::cin >> i;
    if (!std::cin) {
      throw std::runtime_error(
          "Lettura del numero di infetti iniziali fallita");
    }
    std::cout << "Rimossi iniziali = ";
    std::cin >> r;
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
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
    std::exit(0);
  }
  int const N = s + i + r;

  // getting states
  Epidemic epidemic{};
  std::vector<Day> evolution{};
  try {
    epidemic = Epidemic{beta, gamma, Day{s, i, r}};
    for (int i = 0; i != days; i++) {
      epidemic.evolve();
      evolution.push_back(epidemic.state());
    }
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
    std::exit(0);
  }

  // graphics
  float display_width = .6f * sf::VideoMode::getDesktopMode().width;
  float display_height = .7f * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Grafico del modello SIR");

  sf::Vector2f origin{.1f * display_width, .9f * display_height};

  // graph instance
  double xmax = .9 * display_width;
  double ymax = .1 * display_height;
  double delta_x = .01 * display_width;
  double delta_y = .02 * display_height;

  Graph graph{origin, xmax, ymax};
  graph.add_xlabel("giorni");
  graph.add_ylabel("persone");

  // legend objects setting
  sf::Font font{};
  try {
    if (!font.loadFromFile("times.ttf")) {
      throw std::runtime_error("Lettura del file di font fallita");
    }
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  }

  sf::Text legS{"Suscettibili", font, 24};
  legS.setFillColor(sf::Color::Black);
  legS.setPosition(.8 * display_width, .02 * display_height);
  sf::Text legI{"Infetti", font, 24};
  legI.setFillColor(sf::Color::Black);
  legI.setPosition(.8 * display_width, .06 * display_height);
  sf::Text legR{"Rimossi", font, 24};
  legR.setFillColor(sf::Color::Black);
  legR.setPosition(.8 * display_width, .1 * display_height);

  sf::CircleShape Scirc{8};
  Scirc.setFillColor(sf::Color::Green);
  Scirc.setPosition(.95 * display_width, .035 * display_height);
  sf::CircleShape Icirc{8};
  Icirc.setFillColor(sf::Color::Red);
  Icirc.setPosition(.95 * display_width, .075 * display_height);
  sf::CircleShape Rcirc{8};
  Rcirc.setFillColor(sf::Color::Blue);
  Rcirc.setPosition(.95 * display_width, .115 * display_height);

  // position scale factors
  double const xscale = (xmax - origin.x - delta_x) / days;
  double const yscale = (origin.y - delta_y - ymax) / N;

  // point instance
  sf::CircleShape point;

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

    // drawing legend and labels
    window.draw(legS);
    window.draw(legI);
    window.draw(legR);
    window.draw(Scirc);
    window.draw(Icirc);
    window.draw(Rcirc);

    // adding points to graph
    for (int i = 0; i != days; i++) {
      point.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].S * yscale), origin));
      graph.add_sp(point);
      point.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].I * yscale), origin));
      graph.add_ip(point);
      point.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].R * yscale), origin));
      graph.add_rp(point);
    }

    // writing numbers along axes
    for (double i = origin.x; i <= xmax; i += days / 10 * xscale) {
      int n = (i - origin.x) / xscale;
      sf::Text num{std::to_string(n), font, 18};
      num.setFillColor(sf::Color::Black);
      num.setPosition(i, origin.y + delta_y);
      window.draw(num);
    }

    for (double i = origin.y; i >= ymax; i -= N / 10 * yscale) {
      int n = (origin.y - i) / yscale;
      sf::Text num{std::to_string(n), font, 18};
      num.setFillColor(sf::Color::Black);
      num.setPosition(origin.x - 6 * delta_x, i - delta_y);
      window.draw(num);
    }

    // drawing graph
    window.draw(graph);

    window.display();
  }
}
