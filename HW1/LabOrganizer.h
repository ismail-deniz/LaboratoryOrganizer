// Ýsmail Emre Deniz - 21901913

#ifndef __LABORGANIZER_H
#define __LABORGANIZER_H

#include <iostream>
using namespace std;
#include "Cabinet.h"


class LabOrganizer {
public:
	LabOrganizer();
	LabOrganizer(const LabOrganizer& lab);
	~LabOrganizer();
	LabOrganizer& operator=(const LabOrganizer& right);
	void addCabinet(int id, int rows, int columns);
	void removeCabinet(int id);
	void listCabinets();
	void cabinetContents(int id);
	void placeChemical(int cabinetId, string location, string chemType, int chemID);
	void findChemical(int id);
	void removeChemical(int id);

private:
	Cabinet* listOfCabinets;
	int listSize;
	int findCabinetIndex(int cabId);
	void findNearestSuitable(int row, int col, int cabinetId, string*& resultArr, int& arrSize);
	// ...
	//you may define additional member functions and data members, if necessary
};

#endif