#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <chrono>

#include "sequentialImgReader.h"
#include "parallelImgReader.h"

int main() {
    std::string inputImgPath = "../input_images/";
    std::string outputImgPath = "../output_images/";
    std::vector<std::string> imgNames = std::vector<std::string>();

    // Erase output_images folder
    /*
    std::string eraseCommand = "rm -f " + outputImgPath + "*";
    std::system(eraseCommand.c_str());
     */

    // Populate imgNames vector with file names
    for (auto &p: std::filesystem::directory_iterator(inputImgPath))
        imgNames.emplace_back(p.path().string());

    cv::Mat *images;
    int numTests = 16;
    int time = 0;

    for (int i = 0; i < numTests; i++) {
        // Allocate images array
        images = new cv::Mat[imgNames.size()];

        auto start = std::chrono::system_clock::now();
        sequentialRead(images, imgNames);
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        time += elapsed.count();

        // Deallocate heap memory
        delete[] images;
    }
    printf("Elapsed time for sequential implementation: %d ms\n", time / numTests);

    for (int numThreads = 2; numThreads <= 8; numThreads++) {
        time = 0;
        for (int i = 0; i < numTests; i++) {
            // Reallocate images array
            images = new cv::Mat[imgNames.size()];

            auto start = std::chrono::system_clock::now();
            parallelRead(images, imgNames, numThreads);
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            time += elapsed.count();

            // Deallocate heap memory
            delete[] images;
        }
        printf("Elapsed time for parallel implementation with %d threads: %d ms\n", numThreads, time / numTests);
    }

    // Write images to output_images directory
    /*
     for (int i = 0; i < imgNames.size(); i++) {
        cv::imwrite(outputImgPath + std::to_string(i) + ".jpg", images[i]);
    }
     */

    return 0;
}