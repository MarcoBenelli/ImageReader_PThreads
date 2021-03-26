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
void parallelRead(cv::Mat *images, std::vector<std::string> &imgNames, int numThreads);

#endif //IMAGEREADER_PTHREADS_PARALLELIMGREADER_H