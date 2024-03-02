#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "SFML/Graphics.hpp" // Подключаем библиотеку SFML для графики
#include "Grass.h" // Подключаем заголовочный файл для класса Grass
#include "herbivore.h"
#include <cstdlib>
#include <ctime>
#include <string>

const int WINDOW_WIDTH = 800; // Ширина игрового окна
const int WINDOW_HEIGHT = 800; // Высота игрового окна
const int CELL_SIZE = 8; // Размер каждой ячейки в сетке
const int GRID_SIZE = WINDOW_WIDTH / CELL_SIZE; // Размер сетки на основе ширины окна и размера ячейки
const int NUM_GRASS = 300; // Количество травы, которая будет размещена в начале
const int GRASS_LIFE_SPAN = 5; // Продолжительность жизни травы в циклах
const int MAX_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;

const int NUM_HERBIVORE = 200; //количество травоядных
const int HERBIVORES_LIFE_SPAN = 7; //продолжительность жизни травоядных
const int NORMAL_SATIETY = 7; //нормальное количество сытости
const int ADULT_AGE_HERBIVORE = 3; //"зрелость", то есть возраст, когда можно шпили-вили


class GameOfLife {
public:
    GameOfLife();
    void run();

private:
    sf::RenderWindow window; // Окно SFML
    std::vector<std::vector<int>> cells; // Сетка ячеек, представляющая состояние игры.
    //0-пусто 1-трава 2-травоядное 3-хищник

    std::vector<std::vector<Grass>> grassCells; // Сетка ячеек, представляющая траву с продолжительностью жизни
    std::vector<std::vector<Herbivore>> herbivoreCells;
    sf::Font font; // Шрифт для текста
    sf::Text text; // Текст для отображения счетчика циклов

    void placeGrass();
    void createHerbivore(int x, int y);
    void placeHerbivores();
    void reproductionHerbivores(int x, int y);
    void update();
    void processEvents();
    void render();
    void placeText(sf::Font& font, sf::Text& text);
    void updateText(int cycleCount);
};

#endif // !GAMEOFLIFE_H
