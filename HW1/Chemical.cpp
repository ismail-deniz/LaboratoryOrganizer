// Ýsmail Emre Deniz - 21901913

#include <iostream>
using namespace std;

#include "Chemical.h"

Chemical::Chemical() { // empty chemical
	id = -1;
	isCombust = false;
}

Chemical::Chemical(int chemId, bool isComb) {
	id = chemId;
	isCombust = isComb;
}

int Chemical::getId() {
	return id;
}

bool Chemical::isCombustable() {
	return isCombust;
}
