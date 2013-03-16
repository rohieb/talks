#include <iostream>
#include "opaque-pointer.h"

CheshireCat::hover(int lat, int lon) {
	std::cout << "Cheshire Cat hovers to (" << lat << "," << lon << ")" << std::endl;
}

CheshireCat::smile() {
	std::cout << "Cheshire Cat smiles :-)" << std::endl;
}

CheshireCat::appear() {
	std::cout << "Cheshire Cat appears" << std::endl;
}
CheshireCat::disappear() {
	std::cout << "Cheshire Cat disppears" << std::endl;
}

