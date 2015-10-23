#ifndef SEEDED_SEGMENTATION_H
#define SEEDED_SEGMENTATION_H

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <Eigen/Sparse>

#include "Exceptions/mathexception.h"
#include "Exceptions/userinputexception.h"

using namespace cv;
using Eigen::SparseMatrix;
using Eigen::VectorXd;

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
		static const unsigned int MAX_BINARY_VALUE = 255;

		/**
		 * Threshold type to use in the thresholding method.
		 */
		static const unsigned int THRESHOLD_TYPE = 1;

		/**
		 * Epsilon value to use in calculations.
		 */
		static const double EPSILON = 0.0000001;

		/**
		 * Image to be segmented
		 */
		const Mat inputImage;

		/**
		 * The value of beta to use to determine the weights of neighbours
		 */
		const double beta;

		/**
		 * The value of sigma to use to determine the weights of neighbours
		 */
		const double sigma;

		/**
		 * Applies a certain threshold on the image.
		 * 
		 * @param image image to process
		 * @param threshold threshold value
		 *
		 * @return a binary image in which 0 represents foreground and 1 background.
		 */
		Mat applyThresholding(const Mat& image, const double& threshold);

		/**
		 * Calculates the laplacian matrix.
		 *
		 * @return a sparse matrix
		 */
		SparseMatrix<double> calculateLaplacian();

	protected:

	public:

		/**
		 * Default constructor.
		 *
		 * @param inputImage Image to be segmented.
		 * @param beta corresponds to a tuning constant weighting the neighborhood
		 * @param sigma corresponds to the maximum value among the all diferences.
		 * 		A different value can be received but it should be positive.
		 * 
		 * @return A binary matrix Mat containing the segmented image. This
		 *		matrix will contain 0 if the pixel belongs to the foreground and
		 *		1 otherwise.
		 */
		SeededSegmentation(
			const Mat& inputImage,
			const double& beta,
			const double& sigma);

		/**
		 * Class destructor
		 */
		~SeededSegmentation();

		/**
		 * Segment method receives 2 matrixes of type Mat and returns the
		 * corresponding segmentation given the input, background and
		 * foreground images.
		 *
		 * @param backgroundImage Matrix Mat containing the background image.
		 * 		This matrix should contain 0 if the pixel belongs to the
		 *		background and 1 otherwise.
		 * @param foregroundImage Matrix Mat containing the foreground image.
		 * 		This matrix should contain 0 if the pixel belongs to the
		 *		foreground and 1 otherwise.
		 *
		 * @return A binary matrix Mat containing the segmented image. This
		 *		matrix will contain 0 if the pixel belongs to the
		 *		foreground and 1 otherwise.
		 */
		Mat segment(const Mat& backgroundImage, const Mat& foregroundImage);
};

#endif 