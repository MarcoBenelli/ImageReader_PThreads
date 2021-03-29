//
// Created by Benelli, Bindini on 26/03/21.
//

#ifndef IMAGEREADER_PTHREADS_SEQUENTIALIMGREADER_H
#define IMAGEREADER_PTHREADS_SEQUENTIALIMGREADER_H

#include <opencv2/highgui.hpp>

// Sequential image reader
void sequentialRead(std::vector<std::string> &imgNames);

// Getter for images
cv::Mat *sequentialGetImages();

#endif //IMAGEREADER_PTHREADS_SEQUENTIALIMGREADER_H