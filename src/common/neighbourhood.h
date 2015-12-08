#ifndef NEIGHBOURHOOD_H
#define NEIGHBOURHOOD_H

#include <vector>

#include <opencv2/core/core.hpp>

#include "src/exceptions/userinputexception.h"

using std::vector;
using cv::Point2i;

/**
 * This class represents a neighbourhood of size rows x cols. The pixels in
 * the neighbourhood are by default inactive. Thus, the pixels to consider in the
 * neighbourhood should be set to active.
 *
 * @author Jose Bernal
 */
class Neighbourhood
{
    private:
        /**
         * Vector of points containing the neighbour positions. 
         * In the case of a 8-neighbourhood, the expected positions are:
         * (-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)
         */
        vector< Point2i > neighbourPositions;

    public:

        /**
         * Default constructor
         */
        Neighbourhood();

        /**
         * Parametrized constructor
         * 
         * @param neighbourPositions neighbour positions to take into account.
         */
        Neighbourhood(const vector< Point2i >& neighbourPositions);

        /**
         * Class destructor
         */
        ~Neighbourhood();

        /**
         * Returns the neighbour position at the index idx. If the idx is out
         * of bounds, an UserInputException is thrown.
         *
         * @param idx index of the neighbour position to get
         *
         * @return the position of the idx-th neighbour
         */
        Point2i operator() (const unsigned int idx) const;

        /**
         * Returns the size of the neighbourhood. If the neighbourhood is 3x3, 
         * the expected size is 8.
         *
         * @return the size of the neightbourhood
         */
        unsigned int size() const;
};

#endif