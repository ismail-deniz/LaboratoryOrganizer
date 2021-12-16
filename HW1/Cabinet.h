// Ýsmail Emre Deniz - 21901913

#ifndef __CABINET_H
#define __CABINET_H

#include <iostream>
using namespace std;
#include "Chemical.h"

class Cabinet {
public:
	Cabinet();
	Cabinet(int cabinetId, int rows, int columns);
	~Cabinet();
	Cabinet& operator= (const Cabinet cab);
	Cabinet(const Cabinet& cab);
	int getId();
	void placeChemical(int rowPlace, int colPlace, Chemical chem);
	bool findChem(int chemId, string& location);
	bool isSuitable(int rowPlace, int colPlace);
	bool isEmpty(int rowPlace, int colPlace);
	int getNoOfEmptySlots();
	int getHeight();
	int getWidth();
	void displayCabinet();
	void removeChemical(int id);
	void findNearestSuitable(bool isCombust, int row, int col, string*& resultArr, int& arrSize);
	Chemical getChemical(int row, int col);

private:
	int id;
	int height;
	int width;
	Chemical** slots;
	bool checkrange(int col1, int col2, int row1, int row2);
};

#endif