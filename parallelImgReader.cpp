//
// Created by Benelli, Bindini on 26/03/21.
//

#include "parallelImgReader.h"

static cv::Mat *images;
static std::vector<std::string> imgNames;
static int numThreads;

void parallelRead(std::vector<std::string> &imgNames_, int numThreads_){
    images = new cv::Mat[imgNames_.size()];
    imgNames = imgNames_;
    numThreads = numThreads_;

    // Create and allocate handles
    auto *threadHandles = (pthread_t *) malloc(numThreads * sizeof(pthread_t));

    // Create pthreads
    for (long i = 0; i < numThreads; i++)
        pthread_create(&threadHandles[i], nullptr, imgRead, (void *) i);

    // Join pthreads
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threadHandles[i], nullptr);
    }

    // Deallocate heap memory
    free(threadHandles);
}

cv::Mat *parallelGetImages(){
    return images;
}

void *imgRead(void *index) {
    long myIndex = (long) index;
    //printf("Starting Thread-%ld\n",myIndex);
    for (long i = myIndex; i < imgNames.size(); i += numThreads){
        //printf("Thread-%ld reads %ld-th image\n", myIndex, i);
        images[i] = cv::imread(imgNames[i]);
    }
    return nullptr;
}