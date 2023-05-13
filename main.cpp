#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "insect.h"
#include "Target.h"
#include <ctime>
#include <SFML/System/Clock.hpp>

#define WIDTH 1200
#define HEIGHT 1200
#define OBJ_NUMBER 1

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Screaming Insects");
    sf::Clock deltaClock;

    Insect** obj_list = new Insect*[OBJ_NUMBER];
    for (int i = 0; i < OBJ_NUMBER; ++i) {
        obj_list[i] = new Insect(sf::Vector2f(rand() % WIDTH, rand() % HEIGHT));
    }

    int targetsNumber = 0;
    Target** targetsList = new Target*[2];

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        window.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (targetsNumber < 2) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    targetsList[targetsNumber] = new Target(sf::Vector2f(mousePos.x, mousePos.y), event.mouseButton.button == sf::Mouse::Left);
                    targetsNumber++;
                }
            }
        }

        for (int i = 0; i < targetsNumber; ++i) {
            targetsList[i]->display(&window);
        }

        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->move(dt.asSeconds());
            obj_list[i]->display(&window);
        }

        window.display();
    }

    for (int i = 0; i < targetsNumber; ++i) {
        delete targetsList[i];
    }
    delete[] targetsList;

    for (int i = 0; i < OBJ_NUMBER; ++i) {
        delete obj_list[i];
    }
    delete[] obj_list;

    return 0;
}
