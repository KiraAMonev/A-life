#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "SFML/Graphics.hpp" // ���������� ���������� SFML ��� �������
#include "Grass.h" // ���������� ������������ ���� ��� ������ Grass
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int WINDOW_WIDTH = 800; // ������ �������� ����
const int WINDOW_HEIGHT = 800; // ������ �������� ����
const int CELL_SIZE = 8; // ������ ������ ������ � �����
const int GRID_SIZE = WINDOW_WIDTH / CELL_SIZE; // ������ ����� �� ������ ������ ���� � ������� ������
const int NUM_GRASS = 300; // ���������� �����, ������� ����� ��������� � ������
const int GRASS_LIFE_SPAN = 5; // ����������������� ����� ����� � ������
const int MAX_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;
class GameOfLife {
public:
    GameOfLife();
    void run();

private:
    sf::RenderWindow window; // ���� SFML
    std::vector<std::vector<bool>> cells; // ����� �����, �������������� ��������� ����
    std::vector<std::vector<Grass>> grassCells; // ����� �����, �������������� ����� � ������������������ �����
    sf::Font font; // ����� ��� ������
    sf::Text text; // ����� ��� ����������� �������� ������

    void placeGrass();
    void update();
    void processEvents();
    void render();
    void updateText(int cycleCount);
};

#endif // !GAMEOFLIFE_H
