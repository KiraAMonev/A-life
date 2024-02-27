#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML works!"); //создание окна
    sf::CircleShape shape(100.f); //создание фигуры(круга)
    shape.setFillColor(sf::Color(0, 219, 194)); 

    while (window.isOpen()){  //основной цикл, в котором всё работает
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(41, 171, 135));
        window.draw(shape);
        window.display();
    }

    return 0;
}