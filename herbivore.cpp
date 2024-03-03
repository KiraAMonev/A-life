#include "herbivore.h"
#include "gameOfLife.h"
Herbivore::Herbivore() : lifeSpan(0), satiety(0), sex(0) {};
static const int FULL_SATIETY = 100;
void Herbivore::setLifeSpan(int lifeSpan) { //��������� ����������������� �����
	this->lifeSpan = lifeSpan;
}

void Herbivore::setSatiety(int satiety) { //��������� �������
	this->satiety = satiety;
}

int Herbivore::getLifeSpan() const { //��������� ����������������� �����
	return lifeSpan;
}

int Herbivore::getSatiety() const { //��������� �������
	return satiety;
}

void Herbivore::decreaseLifeSpan() { //���������� ����������������� �����
	--lifeSpan;
}

void Herbivore::decreaseSatiety() { //���������� ������� �� �������
	--satiety;
}

void Herbivore::setSex() { //������������ ����
	sex = rand() % 2 - 1;
}

int Herbivore::getSex() const { //��������� ����
	return sex;
}

bool Herbivore::isAlive() const { //�������� �� �����
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
