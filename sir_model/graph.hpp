#include <vector>
#include <SFML/Graphics.hpp>

class Graph : public sf::Drawable {

  sf::VertexArray y_axis_{sf::Lines, 2};
  sf::VertexArray x_axis_{sf::Lines, 2};
  std::vector<sf::CircleShape> points_{};

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
      target.draw(y_axis_, states);
      target.draw(x_axis_, states);
      for(auto const& p : points_){
          target.draw(p, states);
      }

  }

 public:
  Graph(sf::Vector2f origin, double xmax, double ymax) : y_axis_{}, x_axis_{} {
    y_axis_[0].position = origin;
    y_axis_[1].position = sf::Vector2f(origin.x, ymax);
    y_axis_[0].color = sf::Color::Black;
    y_axis_[1].color = sf::Color::Black;

    x_axis_[0].position = origin;
    x_axis_[1].position = sf::Vector2f(xmax, origin.y);
    x_axis_[0].color = sf::Color::Black;
    x_axis_[1].color = sf::Color::Black;
  };

    void insert_sp(sf::CircleShape sp);
    void insert_ip(sf::CircleShape ip);
    void insert_rp(sf::CircleShape rp);
};