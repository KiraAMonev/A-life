#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <vector>
#include "grass.h"
#include <cstdlib> // ��� ������������� ������� rand() � srand()
#include <ctime>   // ��� ������������� ������� time()

#include <random>

class Animal : public Grass
{
public:
	Animal();
	void setLifeSpan(int lifeSpan);
	void setSatiety(int satiety);
	int getSatiety() const;
	void decreaseSatiety();
	void setSex();
	int getSex() const;
	bool isAlive() const;
	bool isHungry()	const;
	bool possibilityOfReproduction()const;


private:
	int randomSex();
	int lifeSpan;
	int satiety;
	int sex;
};

#endif // !ANIMAL_H
