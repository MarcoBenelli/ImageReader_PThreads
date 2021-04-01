//
// Created by Benelli, Bindini on 26/03/21.
//

#include "sequentialImgReader.h"

static cv::Mat *images;

void sequentialRead(std::vector<std::string> &imgNames) {
    images = new cv::Mat[imgNames.size()];
    for (int i = 0; i < imgNames.size(); i++) {
        //printf("Main Thread reads %d-th image\n", i);
        images[i] = cv::imread(imgNames[i]);
    }
}

cv::Mat *sequentialGetImages() {
    return images;
}
