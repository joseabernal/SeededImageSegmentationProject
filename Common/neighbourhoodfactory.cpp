#include "neighbourhoodfactory.h"

Neighbourhood NeighbourhoodFactory::createNeighbourhood(
    NeighbourhoodFactory::NeighbourhoodType type) {
    switch(type){
        case NeighbourhoodFactory::N4: {
            vector<Point2i> neighbourhoodPositions(4);
            neighbourhoodPositions[0] = Point2i(-1, 0);
            neighbourhoodPositions[1] = Point2i(1, 0);
            neighbourhoodPositions[2] = Point2i(0, -1);
            neighbourhoodPositions[3] = Point2i(0, 1);

            return Neighbourhood(neighbourhoodPositions);
        }
        case NeighbourhoodFactory::N8: {
            vector<Point2i> neighbourhoodPositions(8);
            neighbourhoodPositions[0] = Point2i(-1, -1);
            neighbourhoodPositions[1] = Point2i(-1, 0);
            neighbourhoodPositions[2] = Point2i(-1, 1);
            neighbourhoodPositions[3] = Point2i(0, -1);
            neighbourhoodPositions[4] = Point2i(0, 1);
            neighbourhoodPositions[5] = Point2i(1, -1);
            neighbourhoodPositions[6] = Point2i(1, 0);
            neighbourhoodPositions[7] = Point2i(1, 1);

            return Neighbourhood(neighbourhoodPositions);
        }
    }

    throw UserInputException(
        "The entered type does not correspond to a valid value");
}