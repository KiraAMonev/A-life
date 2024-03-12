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
	sex = randomSex();
}

int Herbivore::getSex() const { //��������� ����
	return sex;
}

bool Herbivore::isAlive() const { //�������� �� �����
	if (lifeSpan > 0 && lifeSpan+satiety > 0)
		return true;
	else
		return false;
}

bool Herbivore::possibilityOfReproduction() const
{
	if (lifeSpan <= ADULT_AGE_HERBIVORE)
		return true;
	return false;
}

bool Herbivore::isHungry() const {
	if (getSatiety() <= HUNGRY_SATIETY) {
		return true;
	}
	return false;
}

int Herbivore::randomSex() {
	// �������� ���������� ��������� �����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1); // ����������� ������������� ����� � ��������� [-1, 1]

	// ��������� ���������� ����� � ����������� ���
	return dis(gen);

}