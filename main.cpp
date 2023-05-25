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
extern const int HEIGHT = 800;
extern const int MAX_FOOD;
extern const int MAX_BASE;
extern int CUR_FOOD;
extern int CUR_BASE;

#define OBJ_NUMBER 400


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

    Target** food_targets_list = new Target*[MAX_FOOD];
    Target** base_targets_list = new Target*[MAX_BASE];

    std::list<shout*> shoutList;

    LineContainer lineContainer;

    bool drawLines = true;

    while (window.isOpen()) {
        clear_shout_list(&shoutList);

        sf::Time dt = deltaClock.restart();
        window.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    drawLines = !drawLines;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event.mouseButton.button == sf::Mouse::Left && CUR_BASE < MAX_BASE){

                    base_targets_list[CUR_BASE] = new Target(sf::Vector2f(mousePos.x, mousePos.y),
                                                             event.mouseButton.button == sf::Mouse::Left,
                                                             event.mouseButton.button == sf::Mouse::Left ? CUR_BASE : CUR_FOOD);
                    CUR_BASE++;
                } else if (event.mouseButton.button == sf::Mouse::Right && CUR_FOOD < MAX_FOOD) {

                    food_targets_list[CUR_FOOD] = new Target(sf::Vector2f(mousePos.x, mousePos.y),
                                                             event.mouseButton.button == sf::Mouse::Left,
                                                             event.mouseButton.button == sf::Mouse::Left ? CUR_BASE : CUR_FOOD);
                    CUR_FOOD++;
                }
            }
        }


        for (int i = 0; i < CUR_BASE; ++i) {
            base_targets_list[i]->display(&window);
        }

        for (int i = 0; i < CUR_FOOD; ++i) {
            food_targets_list[i]->display(&window);
        }

        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->border_constraint();
            obj_list[i]->target_collision_detection(base_targets_list, food_targets_list);
            obj_list[i]->move(dt.asSeconds());

            obj_list[i]->display(&window);
        }


        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->insect_shout(&shoutList);
        }


        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->insect_listen(&shoutList, &lineContainer);
        }

        lineContainer.drawLines(&window, drawLines);

        window.display();

        if (false && !shoutList.empty()){
            printf("Content of shoutList:\n");
            for (auto it = shoutList.begin(); it != shoutList.end(); ++it) {
                std::cout << (*it)->toString();
            }
        }
        std::cout << "FPS: " << 1.0f / dt.asSeconds() << std::endl;
        //sf::sleep(sf::milliseconds(500));
    }

    for (int i = 0; i < CUR_BASE; ++i) {
        delete base_targets_list[i];
    }
    delete[] base_targets_list;

    for (int i = 0; i < CUR_FOOD; ++i) {
        delete food_targets_list[i];
    }
    delete[] food_targets_list;

    for (int i = 0; i < OBJ_NUMBER; ++i) {
        delete obj_list[i];
    }
    delete[] obj_list;

    return 0;
}
