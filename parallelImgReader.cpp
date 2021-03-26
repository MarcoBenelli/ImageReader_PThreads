//
// Created by luca on 26/03/21.
//

#include "parallelImgReader.h"

cv::Mat *images_;
std::vector<std::string> imgNames_;
int numThreads_;
int numImgs_;

void parallelRead(cv::Mat *images, std::vector<std::string> &imgNames, int numThreads, int numImgs){
    images_ = images;
    imgNames_ = imgNames;
    numThreads_ = numThreads;
    numImgs_ = numImgs;

    // Create and allocate handles
    auto *threadHandles = (pthread_t *) malloc(numThreads_ * sizeof(pthread_t));

    // Create pthreads
    for (long i = 0; i < numThreads_; i++)
        pthread_create(&threadHandles[i], nullptr, imgRead, (void *) i);

    // Join pthreads
    for (int i = 0; i < numThreads_; i++) {
        pthread_join(threadHandles[i], nullptr);
    }

    // Deallocate heap memory
    free(threadHandles);
}

void *imgRead(void *index) {
    long myIndex = (long) index;
    printf("Starting Thread-%ld\n",myIndex);
    for (long i = myIndex; i < numImgs_; i += numThreads_){
        printf("Thread-%ld reads %ld-th image\n", myIndex, i);
        images_[i] = cv::imread(imgNames_[i]);
    }
    return nullptr;
}