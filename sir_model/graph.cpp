#include "graph.hpp"
#include <SFML/Graphics.hpp>




void Graph::insert_sp(sf::CircleShape sp){
    sp.setRadius(3);
    sp.setFillColor(sf::Color::Green);
    points_.push_back(sp);
}

void Graph::insert_ip(sf::CircleShape ip){
    ip.setRadius(3);
    ip.setFillColor(sf::Color::Red);
    points_.push_back(ip);
}

void Graph::insert_rp(sf::CircleShape rp){
    rp.setRadius(3);
    rp.setFillColor(sf::Color::Blue);
    points_.push_back(rp);
}