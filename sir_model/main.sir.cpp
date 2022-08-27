#include "epidemic.hpp"
#include "graph.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{
  // reading and checking input values
  int days = 0;
  int s = 0;
  int i = 0;
  int r = 0;
  double beta = 0;
  double gamma = 0;
  try
  {
    std::cout << "Numero di giorni =  ";
    std::cin >> days;
    if (!std::cin)
    {
      throw std::runtime_error("Lettura del numero di giorni fallita");
    }
    std::cout << "Suscettibili iniziali = ";
    std::cin >> s;
    if (!std::cin)
    {
      throw std::runtime_error(
          "Lettura del numero di suscettibili iniziali fallita");
    }
    std::cout << "Infetti iniziali = ";
    std::cin >> i;
    if (!std::cin)
    {
      throw std::runtime_error(
          "Lettura del numero di infetti iniziali fallita");
    }
    std::cout << "Rimossi iniziali = ";
    std::cin >> r;
    if (!std::cin)
    {
      throw std::runtime_error(
          "Lettura del numero di rimossi iniziali fallita");
    }
    std::cout << "Beta = ";
    std::cin >> beta;
    if (!std::cin)
    {
      throw std::runtime_error("Lettura del parametro beta fallita");
    }
    std::cout << "Gamma = ";
    std::cin >> gamma;
    if (!std::cin)
    {
      throw std::runtime_error("Lettura del parametro gamma fallita");
    }

    // getting states
    Epidemic epidemic{};
    std::vector<Day> evolution{};

    epidemic = Epidemic{beta, gamma, Day{s, i, r}};
    for (int i = 0; i != days; i++)
    {
      epidemic.evolve();
      evolution.push_back(epidemic.state());
    }

    // Printing day
    for (int i = 0; i != days; i++)
    {
      std::cout << "Day " << i + 1 << '\n';
      std::cout << "S: " << evolution[i].S << '\t';
      std::cout << "I: " << evolution[i].I << '\t';
      std::cout << "R: " << evolution[i].R << '\n';
    }

    int const N = s + i + r;

    float const display_width = .6f * sf::VideoMode::getDesktopMode().width;
    float const display_height = .7f * sf::VideoMode::getDesktopMode().height;

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

    // Legend objects setting
    Par par{};
    sf::Font font{};

    if (!font.loadFromFile("times.ttf"))
    {
      throw std::runtime_error("Lettura del file di font fallita");
    }

    graph.set_Legend(display_width, display_height, par);

    // Position scale factors
    double const xscale = (xmax - origin.x - delta_x) / days;
    double const yscale = (origin.y - delta_y - ymax) / N;

    // Point instance
    sf::CircleShape point;

    // Game loop
    while (window.isOpen())
    {
      // Managing closing event
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
      }
      window.clear(sf::Color::White);

      // Drawing legend and labels
      graph.draw_Leg_Lab(window, par);

      // Adding points to graph
      for (int i = 0; i != days; i++)
      {
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

      // Writing numbers along axes
      for (double i = origin.x; i <= xmax; i += days / 10 * xscale)
      {
        int n = (i - origin.x) / xscale;
        sf::Text num{std::to_string(n), font, 18};
        num.setFillColor(sf::Color::Black);
        num.setPosition(i, origin.y + delta_y);
        window.draw(num);
      }

      for (double i = origin.y; i >= ymax; i -= N / 10 * yscale)
      {
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
  catch (std::runtime_error const &e)
  {
    std::cerr << e.what() << '\n';
  }
  catch (...) // Catching unknown errors
  {
  }
}
