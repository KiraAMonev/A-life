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
const int NUM_GRASS = 100; // ���������� �����, ������� ����� ��������� � ������
const int GRASS_LIFE_SPAN = 5; // ����������������� ����� ����� � ������

class GameOfLife {
public:
    GameOfLife() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // �������� SFML ����
        cells.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false)); // ��������� ������� ����� �����
        srand(time(nullptr)); // ������������� ���������� ��������� �����
        placeGrass(); // ���������� ��������� �����
        text.setFillColor(sf::Color::Black); // ��������� ����� ������
        text.setStyle(sf::Text::Bold); // ������ ����� ������
        text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // ���������������� ������
    }

    void run() {
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

private:
    sf::RenderWindow window; // ���� SFML
    std::vector<std::vector<bool>> cells; // ����� �����, �������������� ��������� ����
    std::vector<std::vector<Grass>> grassCells; // ����� �����, �������������� ����� � ������������������ �����
    sf::Font font; // ����� ��� ������
    sf::Text text; // ����� ��� ����������� �������� ������

    void placeGrass() {
        grassCells.resize(GRID_SIZE, std::vector<Grass>(GRID_SIZE)); // ��������� ������� ����� �����
        for (int i = 0; i < NUM_GRASS; ++i) { // ���� ��� ���������� �����
            int x = rand() % GRID_SIZE; // ��������� �������� x
            int y = rand() % GRID_SIZE; // ��������� �������� y
            cells[x][y] = true; // ��������� ������ ��� ���������� �����
            grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // ��������� ����������������� ����� ��� �����
        }
    }

    void update() {
        for (int x = 0; x < GRID_SIZE; ++x) { // ���� �� ������� �����
            for (int y = 0; y < GRID_SIZE; ++y) {
                if (cells[x][y]) { // ���� ������ �������� �����
                    grassCells[x][y].decreaseLifeSpan(); // ��������� ����������������� ����� �����
                    if (!grassCells[x][y].isAlive()) { // ���� ����� ������
                        cells[x][y] = false; // ������� ����� �� ������
                    }
                }
            }
        }
    }

    void processEvents() {
        sf::Event event; // ������� SFML
        while (window.pollEvent(event)) { // �������� �������
            if (event.type == sf::Event::Closed) // ���� ���� �������
                window.close(); // ��������� ����
        }
    }

    void render() {
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

    void updateText(int cycleCount) {
        text.setString(std::to_string(cycleCount)); // ������������� ����� ��� ����������� ���������� ������
        text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // ���������� �����
    }
};

int main() {
    GameOfLife game; // ������� ��������� ����
    game.run(); // ��������� ������� ����
    return 0;
}
