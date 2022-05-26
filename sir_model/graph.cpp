#include "graph.hpp"




void Graph::insert_sp(sf::CircleShape sp){
    sp.setFillColor(sf::Color::Green);
    points_.push_back(sp);
}

void Graph::insert_ip(sf::CircleShape ip){
    ip.setFillColor(sf::Color::Red);
    points_.push_back(ip);
}

void Graph::insert_rp(sf::CircleShape rp){
    rp.setFillColor(sf::Color::Blue);
    points_.push_back(rp);
}