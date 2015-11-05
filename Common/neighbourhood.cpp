#include "neighbourhood.h"

Neighbourhood::Neighbourhood(const vector< Point2i >& neighbourPositionsIn) {
    neighbourPositions = neighbourPositionsIn;
}

Neighbourhood::~Neighbourhood() { }

Point2i Neighbourhood::operator() (const unsigned int& idx) const {
    if (idx >= neighbourPositions.size()) {
        throw UserInputException("Trying to access to an invalid position");
    }

    return neighbourPositions.at(idx);
}

unsigned int Neighbourhood::size() const {
    return neighbourPositions.size();
}