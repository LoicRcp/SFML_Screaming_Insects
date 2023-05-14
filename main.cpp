#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "insect.h"
#include "Target.h"
#include <ctime>
#include <SFML/System/Clock.hpp>
#include <list>
#include "shout.h"

extern const int WIDTH = 1200;
extern const int HEIGHT = 1200;

#define OBJ_NUMBER 2

void clear_shout_list(std::list<shout*>* shoutList) {
    for (auto it = shoutList->begin(); it != shoutList->end(); ++it) {
        delete *it;
    }
    shoutList->clear();
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Screaming Insects");
    sf::Clock deltaClock;

    Insect** obj_list = new Insect*[OBJ_NUMBER];
    for (int i = 0; i < OBJ_NUMBER; ++i) {
        obj_list[i] = new Insect(i, sf::Vector2f(rand() % WIDTH, rand() % HEIGHT));
    }

    int targetsNumber = 0;
    int baseNumber = 0;
    int foodNumber = 0;
    Target** targetsList = new Target*[2];

    std::list<shout*> shoutList;

    while (window.isOpen()) {
        clear_shout_list(&shoutList);

        sf::Time dt = deltaClock.restart();
        window.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (targetsNumber < 2) {
                    event.mouseButton.button == sf::Mouse::Left ? baseNumber++ : foodNumber++;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    targetsList[targetsNumber] = new Target(sf::Vector2f(mousePos.x, mousePos.y),
                                                            event.mouseButton.button == sf::Mouse::Left,
                                                            event.mouseButton.button == sf::Mouse::Left ? baseNumber : foodNumber);
                    targetsNumber++;
                }
            }
        }


        for (int i = 0; i < targetsNumber; ++i) {
            targetsList[i]->display(&window);
        }

        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->border_constraint();
            obj_list[i]->move(dt.asSeconds());

            obj_list[i]->display(&window);
        }

        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->insect_shout(&shoutList);
        }
        window.display();

        if (!shoutList.empty()){
            printf("Content of shoutList:\n");
            for (auto it = shoutList.begin(); it != shoutList.end(); ++it) {
                std::cout << (*it)->toString();
            }
        }
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
