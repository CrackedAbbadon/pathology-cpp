#include "tiling.hpp"
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include <vector>
using namespace std;

vector<cv::Mat> split_into_tiles(const cv::Mat &image, int tile_size) {
  if (image.empty()) {
    throw invalid_argument("Image is empty");
  }

  if (tile_size <= 0) {
    throw invalid_argument("tile_size must be positive");
  }
  vector<cv::Mat> tiles;
  for (int y = 0; y < image.rows; y += tile_size) {
    for (int x = 0; x < image.cols; x += tile_size) {
      int endx = (x + tile_size <= image.cols) ? tile_size : image.cols - x;
      int endy = (y + tile_size <= image.rows) ? tile_size : image.rows - y;
      cv::Rect rect(x, y, endx, endy);
      cv::Mat cropped = image(rect).clone();
      tiles.push_back(cropped);
    }
  }
  return tiles;
}
