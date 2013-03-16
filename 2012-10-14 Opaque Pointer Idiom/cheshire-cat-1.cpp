#include <iostream>
#include "opaque-pointer-1.h"

CheshireCat::Private::hover(int lat, int lon) {
	std::cout << "Cheshire Cat hovers to (" << lat << "," << lon << ")" << std::endl;
}

CheshireCat::Private::smile() {
	std::cout << "Cheshire Cat smiles :-)" << std::endl;
}

CheshireCat::Private::setVisibility(bool visible) {
	std::cout << "Cheshire Cat " << visible ? "appears" : "disappears" << std::endl;
}

CheshireCat::CheshireCat() : d(new CheshireCat::Private) {}
CheshireCat::~CheshireCat() { delete d; }

CheshireCat::hover() { d->hover(); }
CheshireCat::smile() { d->smile(); }
CheshireCat::appear() { d->setVisibility(true); }
CheshireCat::disappear() { d->setVisibility(false); }

