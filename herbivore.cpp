#include "herbivore.h"
#include "gameOfLife.h"
Herbivore::Herbivore() : lifeSpan(0), satiety(0), sex(0) {};
static const int FULL_SATIETY = 100;
void Herbivore::setLifeSpan(int lifeSpan) { //установка продолжительности жизни
	this->lifeSpan = lifeSpan;
}

void Herbivore::setSatiety(int satiety) { //установка сытости
	this->satiety = satiety;
}

int Herbivore::getLifeSpan() const { //получение продолжительнотси жизни
	return lifeSpan;
}

int Herbivore::getSatiety() const { //получение сытости
	return satiety;
}

void Herbivore::decreaseLifeSpan() { //уменьшение продолжительности жизни
	--lifeSpan;
}

void Herbivore::decreaseSatiety() { //уменьшение сытости на единицу
	--satiety;
}

void Herbivore::setSex() { //установление пола
	sex = rand() % 2 - 1;
}

int Herbivore::getSex() const { //получение пола
	return sex;
}

bool Herbivore::isAlive() const { //проверка на жизнь
	if (lifeSpan > 0 && satiety > 0)
		return true;
	else
		return false;
}

bool Herbivore::possibilityOfReproduction() const
{
	if (lifeSpan >= ADULT_AGE_HERBIVORE)
		return true;
}
