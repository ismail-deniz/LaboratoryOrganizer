// Ýsmail Emre Deniz - 21901913

#ifndef __CHEMICAL_H
#define __CHEMICAL_H

#include <iostream>
using namespace std;

class Chemical {
public:
	Chemical();
	Chemical(int chemId, bool isComb);
	int getId();
	bool isCombustable();
private:
	int id;
	bool isCombust;
};

#endif