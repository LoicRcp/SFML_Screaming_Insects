//
// Created by loicr on 13/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_TARGET_H
#define SFML_SCREAMING_INSECTS_TARGET_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>

class Target {
private:
    enum Type {base, food};
    sf::Vector2f position;
    float radius = 100;
    sf::CircleShape shape;

public:
    Target(sf::Vector2f position, bool base);
    void display(sf::RenderWindow* window);

};



Target::Target(sf::Vector2f position, bool base) {
    Target::position = position - sf::Vector2f(radius, radius);
    Target::shape = sf::CircleShape(radius);
    Target::shape.setPosition(Target::position.x, Target::position.y);
    if (base) Target::shape.setFillColor(sf::Color::Blue);
    else Target::shape.setFillColor(sf::Color::Green);
}

void Target::display(sf::RenderWindow *window) {
    window->draw(Target::shape);
}




#endif //SFML_SCREAMING_INSECTS_TARGET_H
