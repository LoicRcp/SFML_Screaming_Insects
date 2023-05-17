//
// Created by loicr on 13/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_SHOUT_H
#define SFML_SCREAMING_INSECTS_SHOUT_H

#include "Target.h"

class shout{
private:
    sf::Vector2f origin;
    sf::Vector2f* emitterPosition;
    int emitterId;
    Target::Type type;
    int id;
    int distance;
public:
    shout(sf::Vector2f origin, Target::Type type, int id, int distance, sf::Vector2f* emitterPosition, int emitterId);
    std::string toString();

    const sf::Vector2f &getOrigin() const;
    Target::Type getType() const;
    int getId() const;
    int getDistance() const;
    sf::Vector2f *getEmitterPosition() const;
    int getEmitterId() const;
};

shout::shout(sf::Vector2f origin, Target::Type type, int id, int distance, sf::Vector2f* emitterPosition, int emitterId) {
    shout::origin = origin;
    shout::type = type;
    shout::id = id;
    shout::distance = distance;
    shout::emitterPosition = emitterPosition;
    shout::emitterId = emitterId;
}
int shout::getEmitterId() const {
    return emitterId;
}

std::string shout::toString() {
    return std::string("type: ") + (type == Target::Type::base ? "base" : "food") + " id: " + std::to_string(shout::id) + " distance: " + std::to_string(shout::distance) + "\n";
}
const sf::Vector2f &shout::getOrigin() const {
    return origin;
}
Target::Type shout::getType() const {
    return type;
}
int shout::getId() const {
    return id;
}
sf::Vector2f *shout::getEmitterPosition() const {
    return emitterPosition;
}
int shout::getDistance() const {
    return distance;
}

#endif //SFML_SCREAMING_INSECTS_SHOUT_H


