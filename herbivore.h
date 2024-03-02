#ifndef HERBIVORE_H
#define HERBIVORE_H

#include <iostream>
#include <vector>
#include "grass.h"

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

private:
	int lifeSpan;
	int satiety;
	int sex;
	bool repPossibility;
};

#endif // !HERBIVORE_H
