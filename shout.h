//
// Created by loicr on 13/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_SHOUT_H
#define SFML_SCREAMING_INSECTS_SHOUT_H

#include "Target.h"

class shout{
private:
    Target::Type type;
    int id;
    int distance;
public:
    shout(Target::Type type, int id, int distance);
    std::string toString();
};

shout::shout(Target::Type type, int id, int distance) {
    shout::type = type;
    shout::id = id;
    shout::distance = distance;
}

std::string shout::toString() {
    return std::string("type: ") + (type == Target::Type::base ? "base" : "food") + " id: " + std::to_string(shout::id) + " distance: " + std::to_string(shout::distance) + "\n";
}


#endif //SFML_SCREAMING_INSECTS_SHOUT_H


