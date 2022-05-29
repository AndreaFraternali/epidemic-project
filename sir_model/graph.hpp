#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <vector>

sf::Vector2f ConvertCoordinates(sf::Vector2f p, sf::Vector2f origin);

class Graph : public sf::Drawable {
  sf::VertexArray y_axis_{};
  sf::VertexArray x_axis_{};
  sf::Vector2f origin_{};
  sf::Text x_label_{};
  sf::Text y_label_{};
  sf::Font font_{};
  std::vector<sf::CircleShape> points_{};

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(y_axis_, states);
    target.draw(x_axis_, states);
    target.draw(x_label_, states);
    target.draw(y_label_, states);
    for (auto const& p : points_) {
      target.draw(p, states);
    }
  }

 public:
  Graph(sf::Vector2f origin, double xmax, double ymax)
      : y_axis_{sf::Lines, 2}, x_axis_{sf::Lines, 2}, origin_{origin} {
    y_axis_[0].position = origin;
    y_axis_[1].position = sf::Vector2f(origin.x, ymax);
    y_axis_[0].color = sf::Color::Black;
    y_axis_[1].color = sf::Color::Black;

    x_axis_[0].position = origin;
    x_axis_[1].position = sf::Vector2f(xmax, origin.y);
    x_axis_[0].color = sf::Color::Black;
    x_axis_[1].color = sf::Color::Black;

    if (!font_.loadFromFile("times.ttf")) {
      throw std::runtime_error("Opening font file failed");
    }
  };

  void add_sp(sf::CircleShape sp);
  void add_ip(sf::CircleShape ip);
  void add_rp(sf::CircleShape rp);
  void add_xlabel(std::string s);
  void add_ylabel(std::string s);
};

#endif