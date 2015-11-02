#include "seededsegmentation.h"

SeededSegmentation::SeededSegmentation() {

}

SeededSegmentation::~SeededSegmentation() {

}

Mat SeededSegmentation::applyThresholding(
    const Mat& image, const double& thresholdValue) {
    Mat thresholdedImage;

    threshold(
        image, thresholdedImage, thresholdValue, MAX_BINARY_VALUE, THRESHOLD_TYPE);

    return thresholdedImage;
}

SparseMatrix<double> SeededSegmentation::calculateLaplacian(
    const Mat& inputImage,
    const double& beta,
    const double& sigma,
    const Neighbourhood& neighbourhood) {
    const unsigned int numberOfPixels = inputImage.cols * inputImage.rows;
    const unsigned int pixelsInWindow = neighbourhood.size() + 1;
    const double betasigma = -beta/sigma;

    SparseMatrix<double> w(numberOfPixels, numberOfPixels);
    SparseMatrix<double> d(numberOfPixels, numberOfPixels);
    d.reserve(
        VectorXd::Constant(numberOfPixels, pixelsInWindow - neighbourhood.size()));
    w.reserve(VectorXd::Constant(numberOfPixels, neighbourhood.size()));

    for (int i = 0; i < inputImage.rows; i++) {
        for (int j = 0; j < inputImage.cols; j++) {
            double dijValue = 0;
            for (unsigned int k = 0; k < neighbourhood.size(); k++) {
                Point2i pos = neighbourhood(k);
                if (i + pos.y < 0 || i + pos.y >= inputImage.rows) continue;
                if (j + pos.x < 0 || j + pos.x >= inputImage.cols) continue;
                double value = 
                    norm(inputImage.at<Vec3f>(i, j),
                        inputImage.at<Vec3f>(i + pos.y, j + pos.x),
                        cv::NORM_INF);
                value = exp(betasigma * value * value);
                value /= EPSILON;
                value = round(value);
                value *= EPSILON;
                value += EPSILON;
                dijValue += value;

                w.insert(
                    i * inputImage.cols + j,
                    (i + pos.y) * inputImage.cols + (j + pos.x)) = -value;
            }

            d.insert(i * inputImage.cols + j, i * inputImage.cols + j) = dijValue;
        }
    }

    return w + d;
}

Mat SeededSegmentation::segment(
    const Mat& inputImage,
    const Mat& backgroundImage,
    const Mat& foregroundImage,
    const double& beta,
    const double& sigma) {
    if (beta < 0) {
        throw UserInputException("Beta value should be positive");
    }

    if (sigma <= 0) {
        throw UserInputException("Sigma value should be greater than 0");
    }

    const Neighbourhood neighbourhood(3, 3);
    const unsigned int pixelsInWindow = neighbourhood.size() + 1;
    const unsigned int numberOfPixels = inputImage.cols * inputImage.rows;

    SparseMatrix<double> Is(numberOfPixels, numberOfPixels);
    Is.reserve(
        VectorXd::Constant(numberOfPixels, pixelsInWindow - neighbourhood.size()));
    VectorXd b(numberOfPixels);

    for (unsigned int i = 0; i < numberOfPixels; i++) {
        Is.insert(i, i) = 
            backgroundImage.at<bool>(i) || foregroundImage.at<bool>(i);
        b[i] = backgroundImage.at<bool>(i) - foregroundImage.at<bool>(i);
    }

    SparseMatrix<double> laplacian =
        calculateLaplacian(inputImage, beta, sigma, neighbourhood);

    VectorXd x = solveSystem(Is + laplacian * laplacian, b);

    return interpretSolution(x, inputImage.rows, inputImage.cols);
}

VectorXd SeededSegmentation::solveSystem(
    const SparseMatrix<double>& A, const VectorXd& b) {
    Eigen::SimplicialLLT < SparseMatrix<double> > solver;
    solver.compute(A);

    if(solver.info() != Eigen::Success) {
        throw MathException("Decomposition failed");
    }
    
    VectorXd x = solver.solve(b);

    if(solver.info() != Eigen::Success) {
        throw MathException("Solving failed");
    }

    return x;
}

Mat SeededSegmentation::interpretSolution(
    const VectorXd& x, const unsigned int& rows, const unsigned int& cols) {
    const double backgroundValue = 1;
    const double foregroundValue = -1;
    const double threshold = (backgroundValue + foregroundValue) / 2;

    Mat final = Mat::zeros(rows, cols, CV_32FC3);
    for (unsigned int i = 0; i < x.size(); i++) {
        final.at<Vec3f>(i) = cv::Point3f(x(i), x(i), x(i));
    }

    return applyThresholding(final, threshold);
}