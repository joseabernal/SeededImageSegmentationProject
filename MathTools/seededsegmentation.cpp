#include "seededsegmentation.h"

SeededSegmentation::SeededSegmentation(
    const Mat& inputImageIn,
    const double& betaIn,
    const double& sigmaIn) : inputImage(inputImageIn), beta(betaIn), sigma(sigmaIn) {
    if (beta < 0) {
        //TODO: This can be addressed as an exception
        cerr<<"Beta value should be positive"<<endl;
        throw 0;
    }

    if (sigma <= 0) {
        //TODO: This can be addressed as an exception
        cerr<<"Sigma value should be greater than 0"<<endl;
        throw 0;
    }
}

SeededSegmentation::~SeededSegmentation() {

}

Mat SeededSegmentation::applyThresholding(
    const Mat& image, const double& thresholdValue) {
    Mat thresholdedImage;

    threshold(image, thresholdedImage, thresholdValue, MAX_BINARY_VALUE, THRESHOLD_TYPE);

    return thresholdedImage;
}

SparseMatrix<double> SeededSegmentation::calculateLaplacian() {
    const unsigned int numberOfPixels = inputImage.cols * inputImage.rows;
    const unsigned int neighborhoodSize = 8;
    const int dy[neighborhoodSize] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dx[neighborhoodSize] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const double betasigma = -beta/sigma;

    SparseMatrix<double> w(numberOfPixels, numberOfPixels);
    SparseMatrix<double> d(numberOfPixels, numberOfPixels);
    d.reserve(VectorXi::Constant(numberOfPixels, 1));
    w.reserve(VectorXi::Constant(numberOfPixels, 8));

    for (int i = 0; i < inputImage.rows; i++) {
        for (int j = 0; j < inputImage.cols; j++) {
            double dijValue = 0;
            for (unsigned int k = 0; k < neighborhoodSize; k++) {
                if (i + dy[k] < 0 || i + dy[k] >= inputImage.rows) continue;
                if (j + dx[k] < 0 || j + dx[k] >= inputImage.cols) continue;
                double value = 
                    norm(inputImage.at<Vec3f>(i, j),
                        inputImage.at<Vec3f>(i + dy[k], j + dx[k]),
                        NORM_INF);
                value = exp(betasigma * value * value);
                value /= EPSILON;
                value = round(value);
                value *= EPSILON;
                value += EPSILON;
                dijValue += value;

                w.insert(i * inputImage.cols + j, (i + dy[k]) * inputImage.cols + (j + dx[k])) = -value;
            }

            d.insert(i * inputImage.cols + j, i * inputImage.cols + j) = dijValue;
        }
    }

    return w + d;
}

Mat SeededSegmentation::segment(
    const Mat& backgroundImage, const Mat& foregroundImage) {
    const unsigned int numberOfPixels = inputImage.cols * inputImage.rows;

    SparseMatrix<double> Is(numberOfPixels, numberOfPixels);
    VectorXd b(numberOfPixels);

    for (unsigned int i = 0; i < numberOfPixels; i++) {
        Is.insert(i, i) = backgroundImage.at<bool>(i) || foregroundImage.at<bool>(i);
        b[i] = backgroundImage.at<bool>(i) - foregroundImage.at<bool>(i);
    }

    SparseMatrix<double> laplacian = calculateLaplacian();
    SparseMatrix<double> squaredLaplacian = (laplacian * laplacian);

    SimplicialLLT < SparseMatrix<double> > solver;
    solver.compute(Is + squaredLaplacian);

    if(solver.info() != Success) {
        //TODO: This can be addressed as an exception
        cerr<<"Decomposition failed"<<endl;
        throw 0;
    }
    
    VectorXd x = solver.solve(b);

    if(solver.info() != Success) {
        //TODO: This can be addressed as an exception
        cerr<<"Solving failed"<<endl;
        throw 0;
    }

    const double backgroundValue = 1;
    const double foregroundValue = -1;
    const double threshold = (backgroundValue + foregroundValue) / 2;

    Mat final = Mat::zeros(inputImage.rows, inputImage.cols, CV_32FC1);
    for (unsigned int i = 0; i < numberOfPixels; i++) {
        final.at<float>(i) = x(i);
    }

    return applyThresholding(final, threshold);
}