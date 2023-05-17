//
// Created by loicr on 14/05/2023.
//

#ifndef SFML_SCREAMING_INSECTS_LINECONTAINER_H
#define SFML_SCREAMING_INSECTS_LINECONTAINER_H


#include <list>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "Line.h"

class LineContainer {
private:
    std::list<Line> lines;

public:
    void addLine(const Line line) {
        lines.push_back(line);
    }

    void drawLines(sf::RenderWindow* window, bool draw) {
        for (auto it = lines.begin(); it != lines.end();) {
                it->update();
                if (!it->display(window, draw))
                    it = lines.erase(it);
                else
                    ++it;
        }
    }
};



#endif //SFML_SCREAMING_INSECTS_LINECONTAINER_H
