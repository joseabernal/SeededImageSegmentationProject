#include "neighbourhood.h"

Neighbourhood::Neighbourhood(
    const unsigned int& rows, const unsigned int& cols) {
    if (rows <= 1 || rows % 2 != 1) {
        throw UserInputException("The number of rows should be even and > 1");
    }
    if (cols <= 1 || cols % 2 != 1) {
        throw UserInputException("The number of columns should be even and > 1");
    }

    computeNeighbourhood(rows, cols);
}

Neighbourhood::~Neighbourhood() { }

void Neighbourhood::computeNeighbourhood(
    const unsigned int& rows, const unsigned int& cols) {
    int rowLimit = ((int)rows - 1)/2;
    int colLimit = ((int)cols - 1)/2;
    for (int i = -rowLimit; i <= rowLimit; i++) {
        for (int j = -colLimit; j <= colLimit; j++) {
            if (i == 0 && j == 0) continue;

            neighbourPositions.push_back(Point2i(i, j));
        }
    }
}

Point2i Neighbourhood::operator() (const unsigned int& idx) const {
    if (idx >= neighbourPositions.size()) {
        throw UserInputException("Trying to access to an invalid position");
    }

    return neighbourPositions.at(idx);
}

unsigned int Neighbourhood::size() const {
    return neighbourPositions.size();
}