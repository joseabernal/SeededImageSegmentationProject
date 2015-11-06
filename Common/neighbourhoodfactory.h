#ifndef NEIGHBOURHOOD_FACTORY_H
#define NEIGHBOURHOOD_FACTORY_H

#include "neighbourhood.h"

#include "Exceptions/userinputexception.h"

class NeighbourhoodFactory {
    private:

    public:
        enum NeighbourhoodType {N8, N4};

        static Neighbourhood createNeighbourhood(NeighbourhoodType type);
};

#endif