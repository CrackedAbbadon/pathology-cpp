#include "tiling.hpp"
#include <cstddef>
#include <filesystem>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

double procent(int number, int percent) {
  return (static_cast<double>(number) * percent) / 100.0;
}

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

bool is_background(const cv::Mat &tile) {
  if (tile.empty()) {
    throw invalid_argument("Image is empty");
  }
  if (tile.type() != CV_8UC3) {
    throw std::invalid_argument("Expected a 8-bit 3-channel BGR image");
  }
  const size_t pixels = static_cast<size_t>(tile.rows) * tile.cols;
  int count_white = 0;
  for (int y = 0; y < tile.rows; ++y) {
    const uchar *row = tile.ptr<uchar>(y);

    for (int x = 0; x < tile.cols; ++x) {
      bool white = true;

      for (int c = 0; c < tile.channels(); ++c) {
        uchar channel = row[x * tile.channels() + c];

        if (channel < 220) {
          white = false;
          break;
        }
      }

      if (white) {
        count_white++;
      }
    }
  }
  double result = static_cast<double>(count_white) / pixels;
  return result >= 0.8;
}

vector<cv::Mat> filter_tiles(const vector<cv::Mat> &tiles) {
  vector<cv::Mat> filtered;
  for (const cv::Mat &tile : tiles) {
    if (!is_background(tile)) {
      filtered.push_back(tile);
    }
  }
  return filtered;
}

void save_tiles(const vector<cv::Mat> &tiles) {
  filesystem::create_directories("data");

  for (size_t i = 0; i < tiles.size(); ++i) {
    string path = "data/tile_" + std::to_string(i) + ".png";

    if (!cv::imwrite(path, tiles[i])) {
      throw std::runtime_error("Failed to save image: " + path);
    }
  }
}
