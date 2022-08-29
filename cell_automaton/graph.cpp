#include "graph.hpp"
#include <SFML/Graphics.hpp>

void Graph::set_Legend(float const display_width, float const display_height, Par &par)
{
  par.legS = {"Suscettibili", font_, 22};
  par.legS.setFillColor(sf::Color::Black);
  par.legS.setPosition(.85 * display_width, .03 * display_height);
  par.legI = {"Infetti", font_, 22};
  par.legI.setFillColor(sf::Color::Black);
  par.legI.setPosition(.85 * display_width, .07 * display_height);
  par.legR = {"Rimossi", font_, 22};
  par.legR.setFillColor(sf::Color::Black);
  par.legR.setPosition(.85 * display_width, .11 * display_height);

  par.Scirc = sf::CircleShape{6};
  par.Scirc.setFillColor(sf::Color::Green);
  par.Scirc.setPosition(.95 * display_width, .045 * display_height);
  par.Icirc = sf::CircleShape{6};
  par.Icirc.setFillColor(sf::Color::Red);
  par.Icirc.setPosition(.95 * display_width, .085 * display_height);
  par.Rcirc = sf::CircleShape{6};
  par.Rcirc.setFillColor(sf::Color::Blue);
  par.Rcirc.setPosition(.95 * display_width, .125 * display_height);
}

void Graph::draw_Legend (sf::RenderWindow& window, Par& par)
{
  window.draw(par.legS);
  window.draw(par.legI);
  window.draw(par.legR);
  window.draw(par.Scirc);
  window.draw(par.Icirc);
  window.draw(par.Rcirc);
}

void Graph::add_sp(sf::CircleShape sp)
{
  sp.setRadius(3);
  sp.setFillColor(sf::Color::Green);
  points_.push_back(sp);
}

void Graph::add_ip(sf::CircleShape ip)
{
  ip.setRadius(3);
  ip.setFillColor(sf::Color::Red);
  points_.push_back(ip);
}

void Graph::add_rp(sf::CircleShape rp)
{
  rp.setRadius(3);
  rp.setFillColor(sf::Color::Blue);
  points_.push_back(rp);
}

void Graph::add_xlabel(std::string s)
{
  sf::Text label{s, font_, 20};
  label.setFillColor(sf::Color::Black);
  label.setPosition(ConvertCoordinates(sf::Vector2f(x_axis_[1].position.x - origin_.x + 10, 5), origin_));
  x_label_ = label;
}

void Graph::add_ylabel(std::string s)
{
  sf::Text label{s, font_, 20};
  label.setFillColor(sf::Color::Black);
  label.setPosition(ConvertCoordinates(sf::Vector2f(-20, origin_.y - y_axis_[1].position.y + 20), origin_));
  y_label_ = label;
}
