#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "SFML/Graphics.hpp" // Подключаем библиотеку SFML для графики
#include "Grass.h" // Подключаем заголовочный файл для класса Grass
#include <vector>
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
class GameOfLife {
public:
    GameOfLife();
    void run();

private:
    sf::RenderWindow window; // Окно SFML
    std::vector<std::vector<bool>> cells; // Сетка ячеек, представляющая состояние игры
    std::vector<std::vector<Grass>> grassCells; // Сетка ячеек, представляющая траву с продолжительностью жизни
    sf::Font font; // Шрифт для текста
    sf::Text text; // Текст для отображения счетчика циклов

    void placeGrass();
    void update();
    void processEvents();
    void render();
    void updateText(int cycleCount);
};

#endif // !GAMEOFLIFE_H
