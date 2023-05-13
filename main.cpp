#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "insect.h"
#include <ctime>
#include <SFML/System/Clock.hpp>

#define WIDTH 1200
#define HEIGHT 1200
#define OBJ_NUMBER 1


int main() {

    srand((unsigned int)time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Screaming Insects");
    sf::Clock deltaClock;

    Insect** obj_list = (Insect**)malloc(sizeof(Insect)*OBJ_NUMBER);
    for (int i = 0; i < OBJ_NUMBER; ++i) {
        obj_list[i] = new Insect(sf::Vector2f(rand()%WIDTH, rand()%HEIGHT));
    }



    while (window.isOpen()){
        sf::Time dt = deltaClock.restart();
        window.clear(sf::Color::Black);

        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        for (int i = 0; i < OBJ_NUMBER; ++i) {
            obj_list[i]->move(dt.asSeconds());
            obj_list[i]->display(&window);
        }

        window.display();
    }
    return 0;
}
