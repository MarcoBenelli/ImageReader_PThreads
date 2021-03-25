#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <iostream>

int main(int argc, char **argv) {
    std::string input_img_path = "../input_images/";
    std::string output_img_path = "../output_images/";

    std::system("rm -f ../output_images/*");

    std::vector<cv::Mat> images = std::vector<cv::Mat>();
    for (auto &p: std::filesystem::directory_iterator(input_img_path))
        images.emplace_back(cv::imread(p.path().c_str()));

    for (int i = 0; i < images.size(); i++) {
        cv::cvtColor(images.at(i), images.at(i), cv::COLOR_BGR2GRAY);
        cv::imwrite(output_img_path + std::to_string(i) + ".jpg", images.at(i));
    }


    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    //cv::imshow("Display window", gs_image);

    cv::waitKey(0);
    return 0;
}