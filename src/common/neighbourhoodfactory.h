#ifndef NEIGHBOURHOOD_FACTORY_H
#define NEIGHBOURHOOD_FACTORY_H

#include "neighbourhood.h"

#include "src/exceptions/userinputexception.h"

/**
 * This factory class is in charge of generating instances of the Neighbourhoods.
 * There are basically two types of neighbourhoods N8 (8 neighbours) and N4 (4 neighbours).
 * 
 * @author Jose Bernal
 */
class NeighbourhoodFactory {
    private:

    public:
        /**
         * This enum represents the possible neighbourhood types that can be build
         * using this factory class. Using N8 will create a 8-neighbours and
         * N4 a 4-neighbours.
         */
        enum NeighbourhoodType {N8, N4};

        /**
         * Creates the neighbourhood based on the given type.
         * 
         * @param type the NeighbourhoodType to use
         * 
         * @return a Neighbourhood instance of the given type
         */
        static Neighbourhood createNeighbourhood(const NeighbourhoodType type);
};

#endif
