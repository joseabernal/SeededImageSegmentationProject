[![Stories in Ready](https://badge.waffle.io/maxbernal/SeededImageSegmentationProject.png?label=ready&title=Ready)](https://waffle.io/maxbernal/SeededImageSegmentationProject)

# SeededImageSegmentationProject
The seeded segmentation implementation presented in this project is based on the paper
"Laplacian Coordinates for Seeded Image Segmentation, W. Casaca, L.G. Nonato, G. Taubin.
IEEE Conference on Computer Vision and Pattern Recognition (IEEE CVPR 2014), IEEE Press,
pp. 384-391, 2014".

## System requirements

The following libraries should be correctly installed in the system in order 
to compile the source code:
* Linux (preferred)
* Qt >= 4.8.0
* Eigen >= 3.2.0
* OpenCV >= 2.4.8
* Pkg-config >= 0.26
* GTest >= 1.6.1
* CMake >= 3.2.0

## Compilation

### Linux

To compile the source code, the following steps should be followed:
* Open the console in the folder containing the project.
* Run "cmake ." to generate the Makefile. Verify that the Makefile is created.
* Run "make". Verify that there is no error while compiling and also
that a SeededImageSegmentationProject file is created.
* To run the application, you should run ./main in "../bin/"
