#include "gameOfLife.h"

GameOfLife::GameOfLife() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // �������� SFML ����
    cells.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false)); // ��������� ������� ����� �����
    srand(time(nullptr)); // ������������� ���������� ��������� �����
    placeGrass(); // ���������� ��������� �����
    text.setFillColor(sf::Color::Black); // ��������� ����� ������
    text.setStyle(sf::Text::Bold); // ������ ����� ������
    text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // ���������������� ������
}

void GameOfLife::run() {
    sf::Clock clock; // �������� SFML �����
    sf::Time elapsed; // ��������� �����
    int cycleCount = 0; // ������� ������
    while (window.isOpen()) { // �������� ������� ����
        elapsed += clock.restart(); // ���������� ����� � ���������� ���������� �������
        processEvents(); // ��������� �������
        if (elapsed.asMilliseconds() >= 1000) { // ���� ������ ���� �������
            update(); // ���������� ��������� ����
            elapsed = sf::Time::Zero; // ����� ���������� �������
            ++cycleCount; // ���������� �������� ������
            updateText(cycleCount); // ���������� ������ � ����������� ������
        }
        render(); // ��������� ��������� ����
    }
}

void GameOfLife::placeGrass() {
    grassCells.resize(GRID_SIZE, std::vector<Grass>(GRID_SIZE)); // ��������� ������� ����� �����
    for (int i = 0; i < NUM_GRASS; ++i) { // ���� ��� ���������� �����
        int x = rand() % GRID_SIZE; // ��������� �������� x
        int y = rand() % GRID_SIZE; // ��������� �������� y
        cells[x][y] = true; // ��������� ������ ��� ���������� �����
        grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // ��������� ����������������� ����� ��� �����
    }
}

void GameOfLife::update() {
    for (int x = 0; x < GRID_SIZE; ++x) { // ���� �� ������� �����
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y]) { // ���� ������ �������� ��� �� (������ ��� ���� ��� �����)
                grassCells[x][y].decreaseLifeSpan(); // ��������� ����������������� ����� �����
                if (!grassCells[x][y].isAlive()) { // ���� ����� ������
                    cells[x][y] = false; // ������� ����� �� ������
                    int cnt_baby = rand()%10;//����� 24 ������, ����� ����� ����� ������� ���� 10 �����
                    for (int i = 0; i < cnt_baby; i++)
                    {
                        int new_x = x + (rand() % 5 - 2);
                        int new_y = y + (rand() % 5 - 2);
                        if (new_x < GRID_SIZE && new_x > 0 && new_y > 0 && new_y < GRID_SIZE && cells[new_x][new_y] == false) {
                            cells[new_x][new_y] = true;
                            grassCells[new_x][new_y].setLifeSpan(GRASS_LIFE_SPAN);
                        }
                    }
                    
                }
            }
        }
    }
}

void GameOfLife::processEvents() {
    sf::Event event; // ������� SFML
    while (window.pollEvent(event)) { // �������� �������
        if (event.type == sf::Event::Closed) // ���� ���� �������
            window.close(); // ��������� ����
    }
}

void GameOfLife::render() {
    window.clear(sf::Color::White); // ������� ���� ����� ������
    for (int x = 0; x < GRID_SIZE; ++x) { // ���� �� ������� �����
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y]) { // ���� ������ �������� �����
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE)); // ������� ������������� ��� ������
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE); // ������������� ������
                cell.setFillColor(sf::Color::Green); // ������������� ���� �����
                window.draw(cell); // ������ ������ � ������
            }
        }
    }
    window.draw(text); // ������ �����
    window.display(); // ���������� ������������ ����
}

void GameOfLife::updateText(int cycleCount) {
    text.setString(std::to_string(cycleCount)); // ������������� ����� ��� ����������� ���������� ������
    text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // ���������� �����
}