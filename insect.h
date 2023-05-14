//
// Created by loicr on 10/03/2023.
//

#ifndef SFML_SCREAMING_INSECTS_H
#define SFML_SCREAMING_INSECTS_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <list>
#include "shout.h"
#include "Target.h"

#define SPEED 100

extern int CUR_BASE;
extern int CUR_FOOD;
extern const int WIDTH;
extern const int HEIGHT;

class Insect {
private:
    int id;
    sf::Vector2f position;
    sf::Vector2f direction;
    int radius = 5;
    sf::CircleShape shape;
    float shout_radius = 50;
    float* food_distance = (float*)malloc(sizeof(float)*MAX_FOOD);
    float* base_distance = (float*)malloc(sizeof(float)*MAX_BASE);

    Target::Type seeking = Target::food;
    int food_seeking_id = 0;
    int base_seeking_id = 0;
    bool shout_base = false;
public:
    Insect(int id, sf::Vector2f position);
    void display(sf::RenderWindow* window);
    void move(float dt);
    void insect_shout(std::list<shout*>* shoutList);
    void border_constraint();
    void target_collision_detection(Target** targetsList, int targets_number, sf::RenderWindow& window);
};

Insect::Insect(int id, sf::Vector2f position) {
    Insect::id = id;
    Insect::position = position;
    Insect::direction = sf::Vector2f(cos(rand()%360) * SPEED , sin(rand()%360) * SPEED);
    Insect::shape = sf::CircleShape(Insect::radius);
    Insect::shape.setPosition(position.x, position.y);
    Insect::shape.setOrigin(Insect::radius, Insect::radius);

    for (int i = 0; i < MAX_FOOD; ++i){
        food_distance[i] = 1000;
    }
    for (int i = 0; i < MAX_BASE; ++i) {
        base_distance[i] = 1000;
    }
}

void Insect::display(sf::RenderWindow *window) {
    window->draw(Insect::shape);
}

void Insect::move(float dt){
    Insect::position+=Insect::direction * dt;
    Insect::shape.setPosition(Insect::position.x, Insect::position.y);
    for (int i = 0; i < CUR_FOOD; ++i){
        food_distance[i]++;
    }
    for (int i = 0; i < CUR_BASE; ++i) {
        base_distance[i]++;
    }
}

void Insect::insect_shout(std::list<shout*>* shoutList){
    if (CUR_FOOD != 0 && CUR_BASE != 0){
        Target::Type to_shout = shout_base ? Target::base : Target::food;
        int seek_id = shout_base ? Insect::base_seeking_id : Insect::food_seeking_id;
        int distance = shout_base ? base_distance[base_seeking_id] : food_distance[food_seeking_id];
        shoutList->push_back(new shout(to_shout,
                                      seek_id,
                                      distance));
        if (shout_base) {
            Insect::base_seeking_id = Insect::base_seeking_id + 1 % CUR_BASE;
        } else {
            Insect::food_seeking_id = Insect::food_seeking_id + 1 % CUR_FOOD;
        }
        shout_base = !shout_base;
    }
}

void Insect::border_constraint(){
    if (Insect::position.x > WIDTH || Insect::position.x < 0){
        Insect::direction.x *= -1;
    }
    if (Insect::position.y > HEIGHT || Insect::position.y < 0){
        Insect::direction.y *= -1;
    }
}

void Insect::target_collision_detection(Target** targetsList, int targets_number, sf::RenderWindow& window) {
    for (int i = 0; i < targets_number; i++){
        sf::Vector2f target_pos = targetsList[i]->getPosition();
        float distance = sqrt(pow(target_pos.x-Insect::position.x, 2) + pow(target_pos.y-Insect::position.y, 2));
        if (distance < targetsList[i]->getRadius() + Insect::radius){
            Target::Type target_type = targetsList[i]->getType();

            if (target_type == Target::Type::base){
                base_distance[targetsList[i]->getId()] = 0;
            } else {
                food_distance[targetsList[i]->getId()] = 0;
            }

            if (target_type == seeking){
                Insect::direction = -Insect::direction;
                Insect::seeking = (Insect::seeking == Target::Type::food) ? Target::Type::base : Target::Type::food;
            }
        }
    }
}



#endif //SFML_SCREAMING_INSECTS_H