#include "animal.h"
#include "gameOfLife.h"
Animal::Animal() : lifeSpan(0), satiety(0), sex(0) {};
static const int FULL_SATIETY = 100;
void Animal::setLifeSpan(int lifeSpan) { //��������� ����������������� �����
	this->lifeSpan = lifeSpan;
}

void Animal::setSatiety(int satiety) { //��������� �������
	this->satiety = satiety;
}

int Animal::getSatiety() const { //��������� �������
	return satiety;
}

void Animal::decreaseSatiety() { //���������� ������� �� �������
	--satiety;
}

void Animal::setSex() { //������������ ����
	sex = randomSex();
}

int Animal::getSex() const { //��������� ����
	return sex;
}

bool Animal::isAlive() const { //�������� �� �����
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
	// �������� ���������� ��������� �����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1); // ����������� ������������� ����� � ��������� [-1, 1]

	// ��������� ���������� ����� � ����������� ���
	return dis(gen);

}