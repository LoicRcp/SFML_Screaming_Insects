//
// Created by loicr on 10/03/2023.
//

#ifndef SFML_SCREAMING_INSECTS_H
#define SFML_SCREAMING_INSECTS_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

#define SPEED 100

class Insect {
private:
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::CircleShape shape;
    float shout_radius = 50;
public:
    Insect(sf::Vector2f position);
    void display(sf::RenderWindow* window);
    void move(float dt);

};

Insect::Insect(sf::Vector2f position) {
    Insect::position = position;
    Insect::direction = sf::Vector2f(cos(rand()%360) * SPEED , sin(rand()%360) * SPEED);
    Insect::shape = sf::CircleShape(5);
    Insect::shape.setPosition(position.x, position.y);
}

void Insect::display(sf::RenderWindow *window) {
    window->draw(Insect::shape);
}

void Insect::move(float dt){
    Insect::position+=Insect::direction * dt;
    Insect::shape.setPosition(Insect::position.x, Insect::position.y);
}




#endif //SFML_SCREAMING_INSECTS_H