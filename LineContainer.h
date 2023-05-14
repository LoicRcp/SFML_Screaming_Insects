//
// Created by loicr on 14/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_LINECONTAINER_H
#define SFML_SCREAMING_INSECTS_LINECONTAINER_H


#include <list>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class LineContainer {
private:
    std::list<sf::VertexArray> lines;

public:
    void addLine(const sf::VertexArray& line) {
        lines.push_back(line);
    }

    void drawLines(sf::RenderWindow* window, bool draw) {
        for (auto it = lines.begin(); it != lines.end();) {
            if (draw) window->draw(*it);

            // Reduce alpha by 10 for all vertices in the line
            for (int i = 0; i < it->getVertexCount(); ++i) {
                sf::Color c = (*it)[i].color;
                c.a -= 10;
                (*it)[i].color = c;
            }

            // Remove line if alpha <= 0
            if ((*it)[0].color.a <= 11) {
                it = lines.erase(it);
            } else {
                ++it;
            }
        }
    }
};



#endif //SFML_SCREAMING_INSECTS_LINECONTAINER_H
