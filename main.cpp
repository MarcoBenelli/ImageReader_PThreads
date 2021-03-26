#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <chrono>
#include <pthread.h>

// Global variables
std::string inputImgPath;
std::string outputImgPath;
cv::Mat *images;
std::vector<std::string> imgNames;
int numThreads;
int numImages;

// Thread function
void *imgRead(void *index);

int main() {
    // Erase output_images folder
    std::system("rm -f ../output_images/*");

    // Initialize variables
    inputImgPath = "../input_images/";
    outputImgPath = "../output_images/";
    imgNames = std::vector<std::string>();
    numThreads = 8;
    numImages = 0;

    // Populate imgNames vector with file names
    for (auto &p: std::filesystem::directory_iterator(inputImgPath)) {
        imgNames.emplace_back(p.path().string());
        numImages++;
    }

    // Allocate images array
    images = new cv::Mat[numImages];

    // Create and allocate handles
    pthread_t *threadHandles;
    threadHandles = (pthread_t *) malloc(numThreads * sizeof(pthread_t));

    auto start = std::chrono::system_clock::now();
    // Create pthreads
    for (long i = 0; i < numThreads; i++)
        pthread_create(&threadHandles[i], nullptr, imgRead, (void *) i);

    // Join pthreads
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threadHandles[i], nullptr);
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("Elapsed time: %ld\n", elapsed.count());

    // Write images to output_images directory
    for (int i = 0; i < numImages; i++) {
        cv::imwrite(outputImgPath + std::to_string(i) + ".jpg", images[i]);
    }

    //cv::cvtColor(images.at(i), images.at(i), cv::COLOR_BGR2GRAY);

    // Deallocate heap memory
    delete[] images;
    free(threadHandles);
    return 0;
}

void *imgRead(void *index) {
    long myIndex = (long) index;
    printf("Starting Thread-%ld\n",myIndex);
    for (long i = myIndex; i < numImages; i += numThreads){
        printf("Thread-%ld reads %ld-th image\n", myIndex, i);
        images[i] = cv::imread(imgNames[i]);
    }
    return nullptr;
}