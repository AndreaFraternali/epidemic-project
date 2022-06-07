#include "graph.hpp"
#include <SFML/Graphics.hpp>

void Graph::add_sp(sf::CircleShape sp) {
  sp.setRadius(3);
  sp.setFillColor(sf::Color::Green);
  points_.push_back(sp);
}

void Graph::add_ip(sf::CircleShape ip) {
  ip.setRadius(3);
  ip.setFillColor(sf::Color::Red);
  points_.push_back(ip);
}

void Graph::add_rp(sf::CircleShape rp) {
  rp.setRadius(3);
  rp.setFillColor(sf::Color::Blue);
  points_.push_back(rp);
}

void Graph::add_xlabel(std::string s) {
  sf::Text label{s, font_, 20};
  label.setFillColor(sf::Color::Black);
  label.setPosition(ConvertCoordinates(sf::Vector2f(x_axis_[1].position.x - origin_.x + 10, 5), origin_));
  x_label_ = label;
}

void Graph::add_ylabel(std::string s) {
  sf::Text label{s, font_, 20};
  label.setFillColor(sf::Color::Black);
  label.setPosition(ConvertCoordinates(sf::Vector2f(-20, origin_.y - y_axis_[1].position.y + 30), origin_));
  y_label_ = label;
}
