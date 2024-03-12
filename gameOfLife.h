#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "SFML/Graphics.hpp" // ���������� ���������� SFML ��� �������
#include "Grass.h" // ���������� ������������ ���� ��� ������ Grass
#include "herbivore.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

const int WINDOW_WIDTH = 800; // ������ �������� ����
const int WINDOW_HEIGHT = 800; // ������ �������� ����
const int CELL_SIZE = 8; // ������ ������ ������ � �����
const int GRID_SIZE = WINDOW_WIDTH / CELL_SIZE; // ������ ����� �� ������ ������ ���� � ������� ������

const int NOT_FILL = 0;
const int IS_GRASS = 1;
const int IS_HERBIVORE = 2;
const int IS_PREDATOR = 3;

const int NUM_GRASS = 300; // ���������� �����, ������� ����� ��������� � ������
const int GRASS_LIFE_SPAN = 5; // ����������������� ����� ����� � ������
const int MAX_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;

const int NUM_HERBIVORE = 200; //���������� ����������
const int HERBIVORES_LIFE_SPAN = 20; //����������������� ����� ����������
const int NORMAL_SATIETY = 10; //���������� ���������� �������
const int HUNGRY_SATIETY = 8; //�������, ����� ����� ���� �����
const int ADULT_AGE_HERBIVORE = 8; //"��������", �� ���� �������, ����� ����� �����-����
const int GRASS_RESTORING_SATIETY = 1; //������� ��������������� ��������


class GameOfLife {
public:
    GameOfLife();
    void run();

private:
    sf::RenderWindow window; // ���� SFML
    std::vector<std::vector<int>> cells; // ����� �����, �������������� ��������� ����.
    //0-����� 1-����� 2-���������� 3-������

    std::vector<std::vector<Grass>> grassCells; // ����� �����, �������������� ����� � ������������������ �����
    std::vector<std::vector<Herbivore>> herbivoreCells;
    sf::Font font; // ����� ��� ������
    sf::Text text; // ����� ��� ����������� �������� ������

    void placeGrass();
    void createHerbivore(int x, int y);
    void placeHerbivore();
    void reproductionHerbivore(int x, int y);
    void eatingHerbivore(int x, int y);
    void update();
    void processEvents();
    void render();
    void placeText(sf::Font& font, sf::Text& text);
    void updateText(int cycleCount);
    std::pair<int, int> bfs(std::vector<std::vector<Herbivore>> herbivoreCells, std::vector<std::vector<int>> grid, int startX, int startY, int curSex, int& dir_x, int& dir_y);
    int randomDirection(); 
};

#endif // !GAMEOFLIFE_H
