#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <chrono>
#include <unistd.h>

#include "sequentialImgReader.h"
#include "parallelImgReader.h"

int main() {
    std::string inputImgPath = "../input_images/";
    //std::string outputImgPath = "../output_images/";
    std::vector<std::string> imgNames = std::vector<std::string>();
    int numTests = 16;
    long maxNumThreads = sysconf(_SC_NPROCESSORS_CONF);

    // Erase output_images folder
    /*
    std::string eraseCommand = "rm -f " + outputImgPath + "*";
    std::system(eraseCommand.c_str());
     */

    // Populate imgNames vector with file names
    for (auto &p: std::filesystem::directory_iterator(inputImgPath))
        imgNames.emplace_back(p.path().string());

    cv::Mat *images;
    int time = 0;

    for (int i = 0; i < numTests; i++) {

        auto start = std::chrono::system_clock::now();
        sequentialRead(imgNames);
        images = sequentialGetImages();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        time += elapsed.count();

        // Deallocate heap memory
        delete[] images;
    }
    printf("Elapsed time for sequential implementation: %d ms\n", time / numTests);

    for (int numThreads = 1; numThreads <= maxNumThreads; numThreads++) {
        time = 0;
        for (int i = 0; i < numTests; i++) {
            auto start = std::chrono::system_clock::now();
            parallelRead(imgNames, numThreads);
            images = parallelGetImages();
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            time += elapsed.count();

            // Deallocate heap memory
            delete[] images;
        }
        printf("Elapsed time for parallel implementation with %d threads: %d ms\n", numThreads, time / numTests);
    }

    // Write images to output_images directory
    //cv::imwrite(outputImgPath + std::to_string(i) + ".jpg", images[i]);

    return 0;
}