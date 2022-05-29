// rifiniture: validare l'input e aggiustare distanze

#include "epidemic.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Function which converts positions from user-defined coordinates,
// centred in origin, to SFML ones
sf::Vector2f ConvertCoordinates(sf::Vector2f p, sf::Vector2f origin) {
  return sf::Vector2f{p.x + origin.x + 3, origin.y - p.y - 6};
}

int main() {
  std::cout << "Numero di giorni: ";
  int days;
  std::cin >> days;
  std::cout << "Suscettibili iniziali: ";
  int s;
  std::cin >> s;
  std::cout << "Infetti iniziali: ";
  int i;
  std::cin >> i;
  std::cout << "Rimossi iniziali: ";
  int r;
  std::cin >> r;
  std::cout << "Beta = ";
  double beta;
  std::cin >> beta;
  std::cout << "Gamma = ";
  double gamma;
  std::cin >> gamma;
  Epidemic epidemic{beta, gamma, Day{s, i, r}};
  int const N = s + i + r;

  std::vector<Day> evolution{};
  for (int i = 0; i != days; i++) {
    epidemic.evolve(1);
    evolution.push_back(epidemic.state());
  }

  // graphics
  float display_width = .6f * sf::VideoMode::getDesktopMode().width;
  float display_height = .7f * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SIR model graphics");

  sf::VertexArray y_axis{sf::Lines, 2};
  sf::VertexArray x_axis{sf::Lines, 2};
  sf::Vector2f origin{.1f * display_width, .9f * display_height};

  double xmax = .9 * display_width;
  double ymax = .1 * display_height;
  double delta_x = .01 * display_width;
  double delta_y = .02 * display_height;

  // setting degli assi cartesiani
  y_axis[0].position = origin;
  y_axis[1].position = sf::Vector2f(origin.x, ymax - delta_y);
  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;

  x_axis[0].position = origin;
  x_axis[1].position = sf::Vector2f(xmax + delta_x, origin.y);
  x_axis[0].color = sf::Color::Black;
  x_axis[1].color = sf::Color::Black;

  // setting dei punti
  sf::CircleShape Spoint{3};
  Spoint.setFillColor(sf::Color::Green);
  sf::CircleShape Ipoint{3};
  Ipoint.setFillColor(sf::Color::Red);
  sf::CircleShape Rpoint{3};
  Rpoint.setFillColor(sf::Color::Blue);

  // Setting degli oggetti per la legenda
  sf::Font font{};
  if (!font.loadFromFile("times.ttf")) {
    throw std::runtime_error("Opening font file failed");
  }

  sf::Text legS{"Suscettibili", font, 24};
  legS.setFillColor(sf::Color::Black);
  legS.setPosition(0.7 * display_width, 0.05 * display_height);
  sf::Text legI{"Infetti", font, 24};
  legI.setFillColor(sf::Color::Black);
  legI.setPosition(0.7 * display_width, 0.09 * display_height);
  sf::Text legR{"Rimossi", font, 24};
  legR.setFillColor(sf::Color::Black);
  legR.setPosition(0.7 * display_width, 0.13 * display_height);

  sf::CircleShape Scirc{8};
  Scirc.setFillColor(sf::Color::Green);
  Scirc.setPosition(0.85 * display_width, 0.065 * display_height);
  sf::CircleShape Icirc{8};
  Icirc.setFillColor(sf::Color::Red);
  Icirc.setPosition(0.85 * display_width, 0.105 * display_height);
  sf::CircleShape Rcirc{8};
  Rcirc.setFillColor(sf::Color::Blue);
  Rcirc.setPosition(0.85 * display_width, 0.145 * display_height);

  // fattori di riscalo per le posizioni
  double xscale = (xmax - origin.x) / days;
  double yscale = (origin.y - ymax) / N;

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

    // drawing legend
    window.draw(legS);
    window.draw(legI);
    window.draw(legR);
    window.draw(Scirc);
    window.draw(Icirc);
    window.draw(Rcirc);

    // drawing points
    for (int i = 0; i != days; i++) {
      Spoint.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].S * yscale), origin));
      Ipoint.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].I * yscale), origin));
      Rpoint.setPosition(ConvertCoordinates(
          sf::Vector2f(i * xscale, evolution[i].R * yscale), origin));
      window.draw(Spoint);
      window.draw(Ipoint);
      window.draw(Rpoint);
    }

    // scrive i numeri lungo gli assi
    for (double i = origin.x; i <= xmax; i += days / 10 * xscale) {
      int n = (i - origin.x) / xscale;
      sf::Text num{std::to_string(n), font, 18};
      num.setFillColor(sf::Color::Black);
      num.setPosition(i, origin.y + delta_y);
      window.draw(num);
    }
    sf::Text num{std::to_string(days), font, 18};
    num.setFillColor(sf::Color::Black);
    num.setPosition(xmax, origin.y + delta_y);
    window.draw(num);
    sf::Text label{"(giorni)", font, 18};
    label.setFillColor(sf::Color::Black);
    label.setPosition(xmax + 1.5 * delta_x, origin.y - delta_y);
    window.draw(label);

    for (double i = origin.y; i >= ymax; i -= N / 10 * yscale) {
      int n = (origin.y - i) / yscale;
      sf::Text num{std::to_string(n), font, 18};
      num.setFillColor(sf::Color::Black);
      num.setPosition(origin.x - 6 * delta_x, i - delta_y);
      window.draw(num);
    }
    num.setString(std::to_string(N));
    num.setPosition(origin.x - 6.5 * delta_x, ymax - delta_y);
    window.draw(num);
    label.setString("(persone)");
    label.setPosition(origin.x - 3 * delta_x, ymax - 3 * delta_y);
    window.draw(label);

    window.display();
  }
}
