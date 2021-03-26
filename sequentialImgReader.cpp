//
// Created by Benelli, Bindini on 26/03/21.
//

#include "sequentialImgReader.h"

void sequentialRead(cv::Mat *images, std::vector<std::string> &imgNames){
    for (int i = 0; i < imgNames.size(); i++){
        //printf("Main Thread reads %d-th image\n", i);
        images[i] = cv::imread(imgNames[i]);
    }
}