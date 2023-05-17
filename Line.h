//
// Created by loicr on 16/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_LINE_H
#define SFML_SCREAMING_INSECTS_LINE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "insect.h"

class Line {
private:
    sf::Vector2f* origin;
    sf::Vector2f* destination;
    sf::Color color;
    std::optional<sf::VertexArray> line;
    uint8_t alphaReduction = 10;
    float thickness = 4;
    float thicknessReduction = thickness/(255.0f/alphaReduction);
public:
    Line(sf::Vector2f* emitterPosition, sf::Vector2f* receiverPosition, Target::Type shout_target_type);
    void update();
    bool display(sf::RenderWindow* window, bool draw);
};


Line::Line(sf::Vector2f* emitterPosition, sf::Vector2f* receiverPosition, Target::Type shout_target_type) {
    Line::origin = emitterPosition;
    Line::destination = receiverPosition;
    Line::color =
            shout_target_type == Target::Type::food ? sf::Color(253, 255, 112, 255) : sf::Color(110, 227, 250, 255);
}

void Line::update() {
    sf::VertexArray line_(sf::TriangleStrip, 4);
    sf::Vector2f direction = *Line::origin - *Line::destination;
    sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (Line::thickness / 2.f) * unitPerpendicular;

    line_[0].position = *Line::destination - offset;
    line_[1].position = *Line::origin - offset;
    line_[2].position = *Line::destination + offset;
    line_[3].position = *Line::origin + offset;

    line_[0].color = Line::color;
    line_[1].color = Line::color;
    line_[2].color = Line::color;
    line_[3].color = Line::color;

    if (Line::color.a <= alphaReduction) {
        Line::line = std::nullopt;
    } else {
        Line::line = line_;
        Line::color.a -= alphaReduction;
        Line::thickness -= Line::thicknessReduction;
    }
}

bool Line::display(sf::RenderWindow* window, bool draw) {
    if (!Line::line.has_value()) {
        return false;
    }
    if (draw)
    window->draw(Line::line.value());
    return true;
}


#endif //SFML_SCREAMING_INSECTS_LINE_H
