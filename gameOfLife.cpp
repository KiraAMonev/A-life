#include "gameOfLife.h"

GameOfLife::GameOfLife() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // �������� SFML ����
    cells.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0)); // ��������� ������� ����� �����
    srand(time(nullptr)); // ������������� ���������� ��������� �����

    placeGrass(); // ���������� ��������� �����
    placeHerbivores(); // ���������� ��������� ����������
    placeText(font, text);
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
        cells[x][y] = IS_GRASS; // ��������� ������ ��� ���������� �����
        grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // ��������� ����������������� ����� ��� �����
    }
}

void GameOfLife::placeHerbivores() {
    herbivoreCells.resize(GRID_SIZE, std::vector<Herbivore>(GRID_SIZE)); // ��������� ������� ����� ����������
    for (int i = 0; i < NUM_HERBIVORE; ++i) { // ���� ���������� ���������� ����������
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        if (cells[x][y] == NOT_FILL || cells[x][y] == IS_GRASS) { // ���� � ������ ������ ���, �� �������� � ����������
            grassCells[x][y].setLifeSpan(0);
            cells[x][y] = IS_HERBIVORE; // ������ ����, ��� ��� ������ ����������
            createHerbivore(x, y);
        }
    }
}

void GameOfLife::createHerbivore(int x, int y) {
    herbivoreCells[x][y].setLifeSpan(HERBIVORES_LIFE_SPAN); // ��������� ����� �����������
    herbivoreCells[x][y].setSatiety(NORMAL_SATIETY); // ��������� ������� �����������
    herbivoreCells[x][y].setSex(); // ��������� ����
}

void GameOfLife::reproductionHerbivores(int x, int y) {
    int cnt_baby = rand() % 4;
    int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
    int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
    for (int i = 0; i < 8; i++) {
        int n_x = x + dx[i];
        int n_y = y + dy[i];
        if (n_x >= 0 && n_x < GRID_SIZE && n_y >= 0 && n_y < GRID_SIZE) {
            if (cells[n_x][n_y] == IS_HERBIVORE && herbivoreCells[n_x][n_y].getSex() != herbivoreCells[x][y].getSex() && herbivoreCells[n_x][n_y].possibilityOfReproduction()) {
                for (int j = 0; j < cnt_baby; j++)
                {
                    int birth_x = x + (rand() % 5 - 2);
                    int birth_y = y + (rand() % 5 - 2);
                    if (birth_x >= 0 && birth_x < GRID_SIZE && birth_y >= 0 && birth_y < GRID_SIZE && (cells[birth_x][birth_y] == NOT_FILL || cells[birth_x][birth_y] == IS_GRASS)) {
                        cells[birth_x][birth_y] = IS_HERBIVORE;
                        createHerbivore(birth_x, birth_y);
                    }
                }
                
            }
        }
    }
}

void GameOfLife::update() {
    for (int x = 0; x < GRID_SIZE; ++x) { // ���� �� ������� �����
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y] == IS_GRASS) {
                grassCells[x][y].decreaseLifeSpan(); // ��������� ����������������� ����� �����
                if (!grassCells[x][y].isAlive()) { // ���� ����� ������
                    cells[x][y] = NOT_FILL; // ������� ����� �� ������
                    // ��������� ����� ����
                    for (int i = 0; i < 10; ++i) {
                        int new_x = x + (rand() % 5 - 2);
                        int new_y = y + (rand() % 5 - 2);
                        if (new_x >= 0 && new_x < GRID_SIZE && new_y >= 0 && new_y < GRID_SIZE && cells[new_x][new_y] == NOT_FILL) {
                            cells[new_x][new_y] = IS_GRASS;
                            grassCells[new_x][new_y].setLifeSpan(GRASS_LIFE_SPAN);
                        }
                    }
                }
            }
            else if (cells[x][y] == IS_HERBIVORE) {
                herbivoreCells[x][y].decreaseLifeSpan();
                herbivoreCells[x][y].decreaseSatiety();
                if (!herbivoreCells[x][y].isAlive()) {
                    cells[x][y] = NOT_FILL;
                }
                else if (herbivoreCells[x][y].possibilityOfReproduction()) {
                    reproductionHerbivores(x, y);
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
    window.clear(sf::Color(240, 255, 240)); // ������� ���� ������-������� ������
    for (int x = 0; x < GRID_SIZE; ++x) { // ���� �� ������� �����
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y] == IS_GRASS || cells[x][y] == IS_HERBIVORE) { // ���� ������ �������� ���-��
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE)); // ������� ������������� ��� ������
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE); // ������������� ������
                if (cells[x][y] == IS_GRASS)
                    cell.setFillColor(sf::Color(34, 139, 34)); // ������������� ���� �����
                else if (cells[x][y] == IS_HERBIVORE)
                    cell.setFillColor(sf::Color(160, 82, 45)); // ������������� ���� ����������
                window.draw(cell); // ������ ������ � ������ ��� �����������
            }
        }
    }
    window.draw(text); // ������ �����
    window.display(); // ���������� ������������ ����
}

void GameOfLife::placeText(sf::Font& font, sf::Text& text) {
    font.loadFromFile("Font/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black); // ��������� ����� ������
    text.setCharacterSize(35);
    text.setPosition(50, 30);
}

void GameOfLife::updateText(int cycleCount) {
    text.setString(std::to_string(cycleCount)); // ������������� ����� ��� ����������� ���������� ������
    text.setPosition(50, 30);
}
