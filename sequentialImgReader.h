//
// Created by Benelli, Bindini on 26/03/21.
//

#ifndef IMAGEREADER_PTHREADS_SEQUENTIALIMGREADER_H
#define IMAGEREADER_PTHREADS_SEQUENTIALIMGREADER_H

#include <opencv2/highgui.hpp>

// Sequential image reader
void sequentialRead(cv::Mat *images, std::vector<std::string> &imgNames);

#endif //IMAGEREADER_PTHREADS_SEQUENTIALIMGREADER_H