#include "tiling.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: pathology <image_path>\n";
    return 1;
  }

  const cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (image.empty()) {
    cerr << "Failed to load image\n";
    return 1;
  }

  cout << "Width: " << image.cols << '\n';
  cout << "Height: " << image.rows << '\n';
  cout << "Channels: " << image.channels() << '\n';
  cout << "Bytes: " << image.total() * image.elemSize() << '\n';

  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  if (!cv::imwrite("results/grayscale.png", gray)) {
    cerr << "Failed to save output\n";
    return 1;
  }

  return 0;
}
