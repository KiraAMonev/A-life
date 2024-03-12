#ifndef HERBIVORE_H
#define HERBIVORE_H

#include <iostream>
#include <vector>
#include "grass.h"
#include <cstdlib> // Для использования функций rand() и srand()
#include <ctime>   // Для использования функции time()

#include <random>

class Herbivore {
public:
	Herbivore();
	void setLifeSpan(int lifeSpan);
	void setSatiety(int satiety);
	int getLifeSpan() const;
	int getSatiety() const;
	void decreaseLifeSpan();
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

#endif // !HERBIVORE_H
