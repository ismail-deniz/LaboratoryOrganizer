// Ýsmail Emre Deniz - 21901913

#include <iostream>
using namespace std;

#include "LabOrganizer.h"
#include "Cabinet.h"
#include "Chemical.h"

LabOrganizer::LabOrganizer() {
	listSize = 0;
	listOfCabinets = NULL;
}

LabOrganizer::LabOrganizer(const LabOrganizer& lab) {
	listSize = lab.listSize;
	listOfCabinets = new Cabinet[listSize];
	for (int i = 0; i < listSize; i++) {
		listOfCabinets[i] = lab.listOfCabinets[i];
	}
}

LabOrganizer& LabOrganizer::operator=(const LabOrganizer& right) {
	if (this != &right) {
		if (listOfCabinets) {
			// delete left
			delete[] listOfCabinets;
		}
		listSize = right.listSize;
		listOfCabinets = new Cabinet[listSize];
		for (int i = 0; i < listSize; i++) {
			listOfCabinets[i] = right.listOfCabinets[i];
		}

		return *this;
	}
}

LabOrganizer::~LabOrganizer() {
	delete[] listOfCabinets;
}

void LabOrganizer::addCabinet(int id, int rows, int columns) {
	// if its the first cabinet that is added
	if (listSize == 0) {
		Cabinet* newCab = new Cabinet(id, rows, columns);

		listOfCabinets = new Cabinet[1];
		listOfCabinets[0] = *(newCab);
		listSize = 1;
		cout << "Added a cabinet: ID " << id << " and dimensions " << rows << " to " << columns << endl;
		
		delete newCab;
		return;
	}

	// checking the input
	if (findCabinetIndex(id) != -1) {
		cout << "Cannot add the cabinet: ID " << id << " already in the system" << endl;
		return;
	}
	else if (rows > 9 || rows < 1 || columns > 9 || columns < 1) {
		cout << "Cannot add the cabinet: dimensions are out of bounds" << endl;
		return;
	}


	Cabinet* newList;
	
	newList = new Cabinet[listSize + 1];

	for (int i = 0; i < listSize; i++) {
		newList[i] = listOfCabinets[i];
	}

	Cabinet* newCab = new Cabinet(id, rows, columns);

	newList[listSize] = *(newCab);
	listSize++;

	cout << "Added a cabinet: ID " << id << " and dimensions " << rows << " to " << columns << endl;

	delete[] listOfCabinets;
	delete newCab;

	listOfCabinets = newList;
	return;
}

void LabOrganizer::removeCabinet(int id) {
	int removedIndex = findCabinetIndex(id);

	//checking input 
	if (removedIndex == -1) {
		cout << "Cabinet " << id << " does not exist in the system" << endl;
		return;
	}

	// remove every chemical in the cabinet
	Cabinet* cab = listOfCabinets + removedIndex;
	if (cab->getNoOfEmptySlots() != (cab->getHeight() * cab->getWidth())) { // cabinet is not empty
		for (int i = 0; i < cab->getHeight(); i++) {
			for (int j = 0; j < cab->getWidth(); j++) {
				if (cab->getChemical(i, j).getId() != -1) {
					removeChemical(cab->getChemical(i, j).getId());
				}
			}
		}
	}

	// if its the last cabinet that is removed (no more cabinets)
	if (listSize == 1) {
		delete[] listOfCabinets;
		listSize = 0;
		cout << "Cabinet " << id << " has been removed" << endl;
	}

	Cabinet* temp;

	temp = listOfCabinets;
	listOfCabinets = new Cabinet[listSize - 1];

	int k = 0;
	for (int i = 0; i < listSize; i++) {
		if (i != removedIndex) {
			listOfCabinets[k] = temp[i];
			k++;
		}
	}
	listSize--;

	cout << "Cabinet " << id << " has been removed" << endl;

	delete[] temp;
	return;
}

void LabOrganizer::listCabinets() {
	if (listSize == 0) {
		return;
	}

	cout << "List of all cabinets:" << endl;

	for (int i = 0; i < listSize; i++) {
		cout << "ID: " << listOfCabinets[i].getId();
		cout << ", Dim: " << listOfCabinets[i].getHeight() << "x" << listOfCabinets[i].getWidth();
		cout << ", Number of empty slots: " << listOfCabinets[i].getNoOfEmptySlots() << endl;
	}
}

void LabOrganizer::cabinetContents(int id) {
	int index = findCabinetIndex(id);

	if (index != -1) {
		listOfCabinets[index].displayCabinet();
	}
	else {
		cout << "Cabinet " << id << " is not in the system" << endl;
	}
}

void LabOrganizer::findChemical(int id) {
	string location = "";

	for (int i = 0; i < listSize; i++)
		if (listOfCabinets[i].findChem(id, location)) {
			cout << "Chemical " << id << " is at location " << location << " in cabinet " << listOfCabinets[i].getId() << endl;
			return;
		}

	cout << "Chemical " << id << " is not in the system" << endl;
	return;
}

void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int chemID) {
	string chemLocation; // just to call the findChem() function
	// checks if is there a chem with the input id
	for (int i = 0; i < listSize; i++)
		if (listOfCabinets[i].findChem(chemID, chemLocation)) {
			cout << "Chemical with ID " << chemID << " already exists in the system" << endl;
			return;
		}

	int index = findCabinetIndex(cabinetId); // returns -1 if it is not found

	bool isChemComb = false;
	if (chemType == "combustive")
		isChemComb = true;

	string* possibleLocations;
	int possibleSize;

	if (index > -1) {
		// checks if input location is valid
		if (location[0] - 65 >= listOfCabinets[index].getHeight() || location[1] - 49 >= listOfCabinets[index].getWidth()) {
			cout << "Location is out of bounds!" << endl;
			return;
		}

		// checks if location is empty
		if (listOfCabinets[index].isEmpty(location[0] - 65, location[1] - 49)) { 
			// checks if location is suitable
			if (!isChemComb || (listOfCabinets[index].isSuitable(location[0] - 65, location[1] - 49))) { 
				listOfCabinets[index].placeChemical(location[0] - 65, location[1] - 49, Chemical(chemID, isChemComb));

				chemType[0] = chemType[0] - 32; // Make the first letter capital
				cout << chemType << " chemical with ID " << chemID << " has been placed at the location ";
				cout << location << " in cabinet " << cabinetId << endl;
				return;
			}
			else {
				// cannot place combustive
				cout << "Location " << location << " in cabinet " << cabinetId << " is not suitable for a combustive material. ";
				cout << "Nearest possible locations for this chemical: ";

				// find nearest suitable
				listOfCabinets[index].findNearestSuitable(isChemComb, location[0] - 65, location[1] - 49, possibleLocations, possibleSize);
				if (possibleSize == 0) {
					cout << "None! Try another cabinet." << endl;
					return;
				}
				for (int i = 0; i < possibleSize; i++) {
					cout << possibleLocations[i];
					if (i != possibleSize - 1)
						cout << ", ";
				}
				cout << "." << endl;
				delete[] possibleLocations;
				return;
			}
		}
		else {
			// is occuiped
			cout << "Location " << location << " in cabinet " << cabinetId << " is occupied. ";
			cout << "Nearest possible locations for this chemical: ";

			// find nearest suitable
			listOfCabinets[index].findNearestSuitable(isChemComb, location[0] - 65, location[1] - 49, possibleLocations, possibleSize);
			if (possibleSize == 0) {
				cout << "None! Try another cabinet." << endl;
				return;
			}
			for (int i = 0; i < possibleSize; i++) {
				cout << possibleLocations[i];
				if (i != possibleSize - 1)
					cout << ", ";
			}
			cout << "." << endl;
			delete[] possibleLocations;
			return;
		}
	}
	else {
		cout << "Cabinet with id " << cabinetId << " does not exist" << endl;
		return;
	}

}

int LabOrganizer::findCabinetIndex(int cabId) {
	for (int i = 0; i < listSize; i++) {
		if (cabId == listOfCabinets[i].getId())
			return i;
	}

	return -1;
}

void LabOrganizer::removeChemical(int id) {
	string location = "";
	bool found = false;

	for (int i = 0; i < listSize; i++) {
		if (listOfCabinets[i].findChem(id, location)) {
			listOfCabinets[i].removeChemical(id);
			cout << "Chemical " << id << " removed from cabinet ";
			cout << listOfCabinets[i].getId() << endl;
			found = true;
			return;
		}
	}

	if (!found) {
		cout << "Chemical " << id << " is not in the system" << endl;
		return;
	}
}

