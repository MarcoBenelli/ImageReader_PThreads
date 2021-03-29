//
// Created by Benelli, Bindini on 26/03/21.
//

#ifndef IMAGEREADER_PTHREADS_PARALLELIMGREADER_H
#define IMAGEREADER_PTHREADS_PARALLELIMGREADER_H

#include <opencv2/highgui.hpp>
#include <pthread.h>

// Thread function
void *imgRead(void *index);

// Parallel image reader using pthreads
void parallelRead(std::vector<std::string> &imgNames_, int numThreads_);

// Getter for images
cv::Mat *parallelGetImages();

#endif //IMAGEREADER_PTHREADS_PARALLELIMGREADER_H