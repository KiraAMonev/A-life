#include "animal.h"
#include "gameOfLife.h"
Animal::Animal() : lifeSpan(0), satiety(0), sex(0) {};
static const int FULL_SATIETY = 100;
void Animal::setLifeSpan(int lifeSpan) { //установка продолжительности жизни
	this->lifeSpan = lifeSpan;
}

void Animal::setSatiety(int satiety) { //установка сытости
	this->satiety = satiety;
}

int Animal::getSatiety() const { //получение сытости
	return satiety;
}

void Animal::decreaseSatiety() { //уменьшение сытости на единицу
	--satiety;
}

void Animal::setSex() { //установление пола
	sex = randomSex();
}

int Animal::getSex() const { //получение пола
	return sex;
}

bool Animal::isAlive() const { //проверка на жизнь
	if (lifeSpan > 0 && lifeSpan+satiety > 0)
		return true;
	else
		return false;
}

bool Animal::possibilityOfReproduction() const
{
	if (lifeSpan <= ADULT_AGE_HERBIVORE)
		return true;
	return false;
}

bool Animal::isHungry() const {
	if (getSatiety() <= HUNGRY_SATIETY) {
		return true;
	}
	return false;
}

int Animal::randomSex() {
	// Создание генератора случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1); // Равномерное распределение чисел в диапазоне [-1, 1]

	// Генерация случайного числа и возвращение его
	return dis(gen);

}