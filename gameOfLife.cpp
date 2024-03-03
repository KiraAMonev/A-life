#include "gameOfLife.h"

GameOfLife::GameOfLife() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game of Life"); // Создание SFML окна
    cells.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0)); // Изменение размера сетки ячеек
    srand(time(nullptr)); // Инициализация генератора случайных чисел

    placeGrass(); // Размещение начальной травы
    placeHerbivores(); //размещение начальных травоядных
    placeText(font, text);
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
        cells[x][y] = 1; // Установка ячейки для содержания травы
        grassCells[x][y].setLifeSpan(GRASS_LIFE_SPAN); // Установка продолжительности жизни для травы
    }
}

void GameOfLife::placeHerbivores() {
    herbivoreCells.resize(GRID_SIZE, std::vector<Herbivore>(GRID_SIZE)); //изменение размера сетки травоядных
    for (int i = 0; i < NUM_HERBIVORE; ++i) { //цикл начального размещения травоядных
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        if (cells[x][y] == NOT_FILL || cells[x][y] == IS_GRASS) { //если в клетке ничего нет, то занимаем её травоядным
            grassCells[x][y].setLifeSpan(0);
            cells[x][y] = IS_HERBIVORE; //ставим флаг, что она занята травоядным
            createHerbivore(x, y);
        }
    }
}



void GameOfLife::createHerbivore(int x, int y) {
    herbivoreCells[x][y].setLifeSpan(HERBIVORES_LIFE_SPAN); //Установка жизни травоядного
    herbivoreCells[x][y].setSatiety(NORMAL_SATIETY); //Установка сытости травоядного
    herbivoreCells[x][y].setSex(); //установка пола
}

void GameOfLife::reproductionHerbivores(int x, int y) { //малое расстояние до особи вокруг, чтобы травоядные шпили-вили
        int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
        int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
        for (int i = 0; i < 8; i++){
            int n_x = x + dx[i];
            int n_y = y + dy[i];
            if (n_x > 0 && n_x < GRID_SIZE && n_y > 0 && n_y < GRID_SIZE) {
                if (cells[n_x][n_y] == IS_HERBIVORE && herbivoreCells[n_x][n_y].getSex() != herbivoreCells[x][y].getSex() && herbivoreCells[n_x][n_y].possibilityOfReproduction()) {
                    int birth_x = x + (rand() % 5 - 2);
                    int birth_y = y + (rand() % 5 - 2);
                    createHerbivore(birth_x, birth_y);
                    break;
                }
            }
        }
}


void GameOfLife::update() {
    for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y] == IS_GRASS) { 
                grassCells[x][y].decreaseLifeSpan(); // Уменьшаем продолжительность жизни травы
                if (!grassCells[x][y].isAlive()) { // Если трава умерла
                    cells[x][y] = 0; // Удаляем траву из ячейки
                    int cnt_baby = rand()%10;//всего 24 соседа, пусть трава может сделать макс 10 детей
                    for (int i = 0; i < cnt_baby; i++)
                    {
                        int new_x = x + (rand() % 5 - 2);
                        int new_y = y + (rand() % 5 - 2);
                        if (new_x < GRID_SIZE && new_x > 0 && new_y > 0 && new_y < GRID_SIZE && cells[new_x][new_y] == 0) {
                            cells[new_x][new_y] = 1;
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
                else if(herbivoreCells[x][y].possibilityOfReproduction()) { //если животное живо, то оно размножается (и пока что стоит на месте)
                    reproductionHerbivores(x, y);
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
    window.clear(sf::Color(240, 255, 240)); // Очистка окна бледно-зеленым цветом
    for (int x = 0; x < GRID_SIZE; ++x) { // Цикл по ячейкам сетки
        for (int y = 0; y < GRID_SIZE; ++y) {
            if (cells[x][y] == 1 || cells[x][y] == 2 || cells[x][y] == 3) { // Если ячейка содержит что то
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE)); // Создаем прямоугольник для ячейки
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE); // Позиционируем ячейку
                if(cells[x][y] == 1)
                    cell.setFillColor(sf::Color(34, 139, 34)); // Устанавливаем цвет травы
                else if(cells[x][y] == 2)
                    cell.setFillColor(sf::Color(160, 82, 45)); // Устанавливаем цвет травоядных
                window.draw(cell); // Рисуем ячейку с травой
            }
        }
    }
    window.draw(text); // Рисуем текст
    window.display(); // Отображаем отрисованный кадр
}

void GameOfLife::placeText(sf::Font& font, sf::Text& text) {
    font.loadFromFile("Font/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black); // Установка цвета текста
    text.setCharacterSize(35);
    text.setPosition(50, 30);
    //text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // Позиционирование текста
}

void GameOfLife::updateText(int cycleCount) {
    text.setString(std::to_string(cycleCount)); // Устанавливаем текст для отображения количества циклов
    text.setPosition(50, 30);
    //text.setPosition((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2); // Центрируем текст
}