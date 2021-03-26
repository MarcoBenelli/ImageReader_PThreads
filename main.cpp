#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <chrono>

#include "parallelImgReader.h"

int main() {
    std::string inputImgPath = "../input_images/";
    std::string outputImgPath= "../output_images/";
    std::vector<std::string> imgNames= std::vector<std::string>();
    int numThreads = 8;
    int numImgs = 0;

    // Erase output_images folder
    std::string eraseCommand = "rm -f "+ outputImgPath + "*";
    std::system(eraseCommand.c_str());

    // Populate imgNames vector with file names
    for (auto &p: std::filesystem::directory_iterator(inputImgPath)) {
        imgNames.emplace_back(p.path().string());
        numImgs++;
    }

    // Allocate images array
    auto *images = new cv::Mat[numImgs];

    auto start = std::chrono::system_clock::now();
    parallelRead(images, imgNames, numThreads, numImgs);
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("Elapsed time: %ld\n", elapsed.count());

    // Write images to output_images directory
    for (int i = 0; i < numImgs; i++) {
        cv::imwrite(outputImgPath + std::to_string(i) + ".jpg", images[i]);
    }

    //cv::cvtColor(images.at(i), images.at(i), cv::COLOR_BGR2GRAY);

    // Deallocate heap memory
    delete[] images;
    return 0;
}
