// Ýsmail Emre Deniz - 21901913

#include <iostream>
using namespace std;

#include "Cabinet.h"
#include "Chemical.h"

Cabinet::Cabinet(const Cabinet& cab) {
	id = cab.id;
	height = cab.height;
	width = cab.width;
	slots = new Chemical * [height];
	for (int i = 0; i < height; i++) {
		slots[i] = new Chemical[width];
		for (int j = 0; j < width; j++) {
			slots[i][j] = cab.slots[i][j];
		}
	}
}

Cabinet::Cabinet() {
	id = -1;
	height = 0;
	width = 0;
	slots = NULL;
}

Cabinet::Cabinet(int cabinetId, int rows, int columns) {
	id = cabinetId;
	height = rows;
	width = columns;

	slots = new Chemical*[height];
	for (int i = 0; i < height; i++)
		slots[i] = new Chemical[width];
}
Cabinet& Cabinet::operator=(const Cabinet right) {
	if (&right != this) { // to avoid self-assignment
		// delete left
		if (slots) {
			for (int i = 0; i < height; i++) {
				if (slots[i])
					delete[] slots[i];
			}
			delete[] slots;
		}

		id = right.id;
		height = right.height;
		width = right.width;
		slots = new Chemical * [height];
		for (int i = 0; i < height; i++) {
			slots[i] = new Chemical[width];
			for (int j = 0; j < width; j++) {
				slots[i][j] = right.slots[i][j];
			}
		}
	}
	return *this; 
}


Cabinet::~Cabinet() {
	if (slots) {
		for (int i = 0; i < height; i++) {
			if (slots[i])
				delete[] slots[i];
		}
		delete[] slots;
	}
}

int Cabinet::getId() {
	return id;
}

void Cabinet::placeChemical(int rowPlace, int colPlace, Chemical chem) {
	// check the input on the laborganizer class
	slots[rowPlace][colPlace] = chem;
}

bool Cabinet::findChem(int chemId, string& location) {
	location = "";
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (slots[i][j].getId() == chemId) {
				location += i + 65; // i + ascii 'A'
				location += j + 49; // j + ascii '1'
				return true;
			}

	return false;
}

bool Cabinet::isSuitable(int rowPlace, int colPlace) {
	return checkrange(rowPlace - 1, rowPlace + 1, colPlace - 1, colPlace + 1);
}

bool Cabinet::isEmpty(int rowPlace, int colPlace) {
	return (slots[rowPlace][colPlace].getId() == -1);
}

bool Cabinet::checkrange(int row1, int row2, int col1, int col2) {
	if (row1 <= -1)
		row1 = 0;
	if (row2 >= height)
		row2 = height - 1;
	if (col1 <= -1)
		col1 = 0;
	if (col2 >= width)
		col2 = width - 1;

	for (int i = row1; i < row2 + 1; i++) {
		for (int k = col1; k < col2 + 1; k++) {
			if (slots[i][k].isCombustable())
				return false;
		}
	}

	return true;
}

int Cabinet::getNoOfEmptySlots() {
	int noOfEmptySlots = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (slots[i][j].getId() == -1) {
				noOfEmptySlots++;
			}
		}
	}

	return noOfEmptySlots;
}

int Cabinet::getHeight() {
	return height;
}
int Cabinet::getWidth() {
	return width;
}

void Cabinet::displayCabinet() {
	// print header info
	cout << "ID: " << id << ", " << height << "x" << width;
	cout << ", empty: " << this->getNoOfEmptySlots() << ".";
	cout << " Chemicals: ";
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (slots[i][j].getId() != -1) {
				cout << char(i + 65) << char(j + 49) << ": ";
				cout << slots[i][j].getId() << ", ";
			}
		}
	}
	cout << endl;

	// print table
	cout << "  ";
	for (int i = 0; i < width; i++) {
		cout << (i + 1) << " ";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		cout << char(i + 65) << " ";
		for (int j = 0; j < width; j++) {
			if (slots[i][j].getId() == -1) {
				cout << "+ ";
			}
			else if (slots[i][j].isCombustable()){
				cout << "c ";
			}
			else {
				cout << "r ";
			}
		}
		cout << endl;
	}
}

void Cabinet::removeChemical(int id) {
	string location = "";

	if (findChem(id, location)) {
		Chemical* empty = new Chemical();
		slots[location[0] - 65][location[1] - 49] = *(empty);

		delete empty;
		return;
	}
}

void Cabinet::findNearestSuitable(bool isCombust, int row, int col, string*& resultArr, int& arrSize) {
	string resultStr = "";
	arrSize = 0;
	int distance = 1;
	bool found = false;

	// firstly create a string by adding the possible locations one after another

	// while suitable place is not found and the distance from the input location is in bounds
	while (!found && !(row + distance > height - 1  && row - distance < 0 && col + distance > width - 1 && col - distance < 0)) {
		for (int i = -(distance); i <= distance; i++) {
			if (i == -(distance) || i == distance) { // upper and lower side of the square 
				for (int j = -(distance); j <= distance; j++) { // should check every place between the distance values
					if ((i + row) > -1 && (i + row) < height && (j + col) > -1 && (j + col) < width)
						if (this->isEmpty(i + row, j + col) && (!isCombust|| this->isSuitable(i + row, j + col) )) {
							resultStr += i + row + 65;
							resultStr += j + col + 49;
							found = true;
						}
				}
			}
			else { // middle part of the square, so it is enough to check only the leftmost and rightmost value in the square
				if ((i + row) > -1 && (i + row) < height && (-distance + col) > -1 && (-distance + col) < width) { // leftmost
					if (this->isEmpty(i + row, col - distance) && (!isCombust || this->isSuitable(i + row, col - distance))) {
						resultStr += i + row + 65;
						resultStr += col - distance + 49;
						found = true;
					}
				}
				if ((i + row) > -1 && (i + row) < height && (distance + col) > -1 && (distance + col) < width) { // rightmost
					if (this->isEmpty(i + row, col + distance) && (!isCombust || this->isSuitable(i + row, col + distance))) {
						resultStr += i + row + 65;
						resultStr += col + distance + 49;
						found = true;
					}
				}

			}
		}
		distance++;
	}

	// secondly divide the created string to the strings of length 2 (1 location string) and create a location array
	if (resultStr == "") {
		resultArr = NULL;
		arrSize = 0;
	}

	arrSize = resultStr.length() / 2;
	resultArr = new string[arrSize];

	for (int k = 0; k < arrSize; k++) {
		resultArr[k] = resultStr[2 * k];
		resultArr[k] += resultStr[(2 * k) + 1];
	}
}

Chemical Cabinet::getChemical(int row, int col) {
	if (row < height || row > -1 || col < width || col > -1) {
		return slots[row][col];
	}
}