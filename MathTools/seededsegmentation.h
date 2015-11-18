#ifndef SEEDED_SEGMENTATION_H
#define SEEDED_SEGMENTATION_H

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <Eigen/Sparse>

#include "Common/neighbourhood.h"
#include "Common/neighbourhoodfactory.h"
#include "Exceptions/mathexception.h"
#include "Exceptions/userinputexception.h"

using Eigen::SparseMatrix;
using Eigen::VectorXd;
using namespace cv;

/**
 * This class segment a given input image using the laplacian seeded segmentation
 * proposed for Casaca et al.
 *
 * @see Laplacian Coordinates for Seeded Image Segmentation in https://sites.google.com/site/wallacecoc/publications
 *
 * @author Jose Bernal
 */
class SeededSegmentation
{
    private:

        /**
         * Max binary value constant to use in the thresholding method.
         */
        static const unsigned int MAX_BINARY_VALUE = 1;

        /**
         * Threshold type to use in the thresholding method.
         */
        static const unsigned int THRESHOLD_TYPE = 1;

        /**
         * Epsilon value to use in calculations.
         */
        static const double EPSILON = 0.0000001;

        /**
         * Applies a certain threshold on the image.
         * 
         * @param image image to process
         * @param threshold threshold value
         *
         * @return a binary image in which 0 represents foreground and 1 background.
         */
        Mat applyThresholding(const Mat& image, const double threshold);

        /**
         * Transforms the vector x from the system Ax = b into a image containing
         * the segmentation.
         *
         * @param x vector to be interpretated
         * @param rows rows of the original image
         * @param cols columns of the original image
         * 
         * @return a binary image in which 0 represents foreground and 1 background.
         */
        Mat interpretSolution(
            const VectorXd& x, const unsigned int rows, const unsigned int cols);

        /**
         * Solves the system Ax = b. 
         *
         * @param A sparse matrix
         * @param b vector b
         * 
         * @return the solution vector, x.
         */
        VectorXd solveSystem(const SparseMatrix<double>& A, const VectorXd& b);

        /**
         * Calculates the laplacian matrix.
         *
         * @param inputImage image to be segmented
         * @param beta corresponds to a tuning constant weighting the neighborhood
         * @param sigma corresponds to the maximum value among the all diferences.
         *     A different value can be received but it should be positive.
         * @param neighbourhood neighbourhood to use to calculate the laplacian matrix.
         *
         * @return a sparse matrix representing the laplacian
         */
        SparseMatrix<double> calculateLaplacian(
            const Mat& inputImage,
            const double beta,
            const double sigma,
            const Neighbourhood& neighbourhood);

    protected:

    public:

        /**
         * Default constructor.
         */
        SeededSegmentation();

        /**
         * Class destructor
         */
        ~SeededSegmentation();

        /**
         * Segment method receives 2 matrixes of type Mat and returns the
         * corresponding segmentation given the input, background and
         * foreground images.
         *
         * @param inputImage Image to be segmented.
         * @param backgroundImage Matrix Mat containing the background image.
         *         This matrix should contain 0 if the pixel belongs to the
         *        background and 1 otherwise.
         * @param foregroundImage Matrix Mat containing the foreground image.
         *         This matrix should contain 0 if the pixel belongs to the
         *        foreground and 1 otherwise.
         * @param neighbourhood neighbourhood to use to calculate the laplacian matrix.
         * @param beta corresponds to a tuning constant weighting the neighborhood
         * @param sigma corresponds to the maximum value among the all diferences.
         *         A different value can be received but it should be positive.
         *
         * @return A binary matrix Mat containing the segmented image. This
         *        matrix will contain 0 if the pixel belongs to the
         *        foreground and 1 otherwise.
         */
        Mat segment(
            const Mat& inputImage,
            const Mat& backgroundImage,
            const Mat& foregroundImage,
            const Neighbourhood& neighbourhood,
            const double beta,
            const double sigma = 0.1);
};

#endif 