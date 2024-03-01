#include "gameOfLife.h"

GameOfLife::GameOfLife() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // Создание SFML окна
    cells.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false)); // Изменение размера сетки ячеек
    srand(time(nullptr)); // Инициализация генератора случайных чисел
    placeGrass(); // Размещение начальной травы
    text.setFillColor(sf::Color::Black); // Установка цвета текста
    text.setStyle(sf::Text::Bold); // Делаем текст жирным
    text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // Позиционирование текста
}

void GameOfLife::run() {
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

void GameOfLife::placeGrass() {
    grassCells.resize(GRID_SIZE, std::vector<Grass>(GRID_SIZE)); // Изменение размера сетки травы
    for (int i = 0; i < NUM_GRASS; ++i) { // Цикл для размещения травы
        int x = rand() % GRID_SIZE; // Случайное значение x
        int y = rand() % GRID_SIZE; // Случайное значение y
        cells[x][y] = true; // Установка ячейки для содержания травы
        grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // Установка продолжительности жизни для травы
    }
}

void GameOfLife::update() {
    for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y]) { // Если ячейка содержит что то (сейчас это пока что трава)
                grassCells[x][y].decreaseLifeSpan(); // Уменьшаем продолжительность жизни травы
                if (!grassCells[x][y].isAlive()) { // Если трава умерла
                    cells[x][y] = false; // Удаляем траву из ячейки
                    int cnt_baby = rand()%10;//всего 24 соседа, пусть трава может сделать макс 10 детей
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
    sf::Event event; // Событие SFML
    while (window.pollEvent(event)) { // Проверка событий
        if (event.type == sf::Event::Closed) // Если окно закрыто
            window.close(); // Закрываем окно
    }
}

void GameOfLife::render() {
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

void GameOfLife::updateText(int cycleCount) {
    text.setString(std::to_string(cycleCount)); // Устанавливаем текст для отображения количества циклов
    text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // Центрируем текст
}