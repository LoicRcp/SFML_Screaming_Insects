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
    float getRadius() const;
    enum Type {base, food};
    Target(sf::Vector2f position, bool base, int id);
    void display(sf::RenderWindow* window);
    const sf::Vector2f &getPosition() const;
    int getId() const;
    Type getType() const;
private:
    Type type;
    sf::Vector2f position;
    float radius = 20;
    sf::CircleShape shape;
    int id;
};



Target::Target(sf::Vector2f position, bool base, int id) {
    Target::position = position;
    Target::shape = sf::CircleShape(radius);
    Target::shape.setPosition(Target::position.x, Target::position.y);
    Target::shape.setOrigin(Target::radius, Target::radius);
    Target::id = id;
    Target::type = base ? Target::base : Target::food;
    if (base) {
        Target::shape.setFillColor(sf::Color::Blue);
    }
    else {
        Target::shape.setFillColor(sf::Color::Yellow);
    }
}

void Target::display(sf::RenderWindow *window) {
    window->draw(Target::shape);
}

const sf::Vector2f &Target::getPosition() const {
    return position;
}

float Target::getRadius() const {
    return radius;
}

Target::Type Target::getType() const {
    return type;
}

int Target::getId() const {
    return id;
}

#endif //SFML_SCREAMING_INSECTS_TARGET_H
