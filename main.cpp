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
const int NUM_GRASS = 100; // Количество травы, которая будет размещена в начале
const int GRASS_LIFE_SPAN = 5; // Продолжительность жизни травы в циклах

class GameOfLife {
public:
    GameOfLife() {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // Создание SFML окна
        cells.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false)); // Изменение размера сетки ячеек
        srand(time(nullptr)); // Инициализация генератора случайных чисел
        placeGrass(); // Размещение начальной травы
        text.setFillColor(sf::Color::Black); // Установка цвета текста
        text.setStyle(sf::Text::Bold); // Делаем текст жирным
        text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // Позиционирование текста
    }

    void run() {
        sf::Clock clock; // Создание SFML часов
        sf::Time elapsed; // Прошедшее время
        int cycleCount = 0; // Счетчик циклов
        while (window.isOpen()) { // Основной игровой цикл
            elapsed += clock.restart(); // Перезапуск часов и добавление прошедшего времени
            processEvents(); // Обработка событий
            if (elapsed.asMilliseconds() >= 1000) { // Если прошла одна секунда
                update(); // Обновление состояния игры
                elapsed = sf::Time::Zero; // Сброс прошедшего времени
                ++cycleCount; // Увеличение счетчика циклов
                updateText(cycleCount); // Обновление текста с количеством циклов
            }
            render(); // Отрисовка состояния игры
        }
    }

private:
    sf::RenderWindow window; // Окно SFML
    std::vector<std::vector<bool>> cells; // Сетка ячеек, представляющая состояние игры
    std::vector<std::vector<Grass>> grassCells; // Сетка ячеек, представляющая траву с продолжительностью жизни
    sf::Font font; // Шрифт для текста
    sf::Text text; // Текст для отображения счетчика циклов

    void placeGrass() {
        grassCells.resize(GRID_SIZE, std::vector<Grass>(GRID_SIZE)); // Изменение размера сетки травы
        for (int i = 0; i < NUM_GRASS; ++i) { // Цикл для размещения травы
            int x = rand() % GRID_SIZE; // Случайное значение x
            int y = rand() % GRID_SIZE; // Случайное значение y
            cells[x][y] = true; // Установка ячейки для содержания травы
            grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // Установка продолжительности жизни для травы
        }
    }

    void update() {
        for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
            for (int y = 0; y < GRID_SIZE; ++y) {
                if (cells[x][y]) { // Если ячейка содержит траву
                    grassCells[x][y].decreaseLifeSpan(); // Уменьшаем продолжительность жизни травы
                    if (!grassCells[x][y].isAlive()) { // Если трава умерла
                        cells[x][y] = false; // Удаляем траву из ячейки
                    }
                }
            }
        }
    }

    void processEvents() {
        sf::Event event; // Событие SFML
        while (window.pollEvent(event)) { // Проверка событий
            if (event.type == sf::Event::Closed) // Если окно закрыто
                window.close(); // Закрываем окно
        }
    }

    void render() {
        window.clear(sf::Color::White); // Очистка окна белым цветом
        for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
            for (int y = 0; y < GRID_SIZE; ++y) {
                if (cells[x][y]) { // Если ячейка содержит траву
                    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE)); // Создаем прямоугольник для ячейки
                    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE); // Позиционируем ячейку
                    cell.setFillColor(sf::Color::Green); // Устанавливаем цвет травы
                    window.draw(cell); // Рисуем ячейку с травой
                }
            }
        }
        window.draw(text); // Рисуем текст
        window.display(); // Отображаем отрисованный кадр
    }

    void updateText(int cycleCount) {
        text.setString(std::to_string(cycleCount)); // Устанавливаем текст для отображения количества циклов
        text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // Центрируем текст
    }
};

int main() {
    GameOfLife game; // Создаем экземпляр игры
    game.run(); // Запускаем игровой цикл
    return 0;
}
