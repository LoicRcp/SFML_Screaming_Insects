//
// Created by loicr on 13/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_TARGET_H
#define SFML_SCREAMING_INSECTS_TARGET_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>

extern const int MAX_FOOD = 10;
extern const int MAX_BASE = 10;
int CUR_FOOD = 0;
int CUR_BASE = 0;

class Target {
public:
    enum Type {base, food};
    Target(sf::Vector2f position, bool base, int id);
    void display(sf::RenderWindow* window);
private:
    Type type;
    sf::Vector2f position;
    float radius = 100;
    sf::CircleShape shape;
    int id;
};



Target::Target(sf::Vector2f position, bool base, int id) {
    Target::position = position - sf::Vector2f(radius, radius);
    Target::shape = sf::CircleShape(radius);
    Target::shape.setPosition(Target::position.x, Target::position.y);
    Target::id = id;
    Target::type = base ? Target::base : Target::food;
    if (base) {
        Target::shape.setFillColor(sf::Color::Blue);
        CUR_BASE++;
    }
    else {
        Target::shape.setFillColor(sf::Color::Green);
        CUR_FOOD++;
    }
}

void Target::display(sf::RenderWindow *window) {
    window->draw(Target::shape);
}




#endif //SFML_SCREAMING_INSECTS_TARGET_H
