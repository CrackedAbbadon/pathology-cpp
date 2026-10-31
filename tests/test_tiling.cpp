#include "tiling.hpp"
#include <cassert>
#include <iostream>

void test_small_image() {
  cv::Mat image(256, 256, CV_8UC3);

  auto tiles = split_into_tiles(image, 512);

  assert(tiles.size() == 1);
  assert(tiles[0].cols == 256);
  assert(tiles[0].rows == 256);
}

void test_large_image() {
  cv::Mat image(900, 1300, CV_8UC3);

  auto tiles = split_into_tiles(image, 512);

  assert(tiles.size() == 6);
}

void test_black_tile() {
  cv::Mat black = cv::Mat::zeros(480, 640, CV_8UC3);

  auto is_back = is_background(black);

  assert(is_back == false);
}
void test_white_tile() {
  cv::Mat white(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));

  auto is_back = is_background(white);

  assert(is_back == true);
}
void test_half_white_tile() {
  cv::Mat half = cv::Mat::zeros(512, 512, CV_8UC3);
  half(cv::Rect(0, 0, 512 / 2, 512 / 2)).setTo(cv::Scalar(255, 255, 255));

  auto is_back = is_background(half);

  assert(is_back == false);
}

void test_80_white_tile() {
  cv::Mat eighty = cv::Mat::zeros(1000, 1000, CV_8UC3);
  eighty(cv::Rect(0, 0, 800, 1000)).setTo(cv::Scalar(255, 255, 255));

  auto is_back = is_background(eighty);

  assert(is_back == true);
}
void test_79_white_tile() {
  cv::Mat seventy_nine = cv::Mat::zeros(1000, 1000, CV_8UC3);
  seventy_nine(cv::Rect(0, 0, 790, 1000)).setTo(cv::Scalar(255, 255, 255));

  auto is_back = is_background(seventy_nine);

  assert(is_back == false);
}

void test_81_white_tile() {
  cv::Mat eighty_one = cv::Mat::zeros(1000, 1000, CV_8UC3);
  eighty_one(cv::Rect(0, 0, 810, 1000)).setTo(cv::Scalar(255, 255, 255));

  auto is_back = is_background(eighty_one);

  assert(is_back == true);
}
cv::Mat make_white_tile(int size = 100) {
  return cv::Mat(size, size, CV_8UC3, cv::Scalar(255, 255, 255));
}

cv::Mat make_black_tile(int size = 100) {
  return cv::Mat(size, size, CV_8UC3, cv::Scalar(0, 0, 0));
}

void test_filter_tiles_removes_background() {
  std::vector<cv::Mat> tiles = {make_white_tile(), make_black_tile(),
                                make_white_tile()};

  auto filtered = filter_tiles(tiles);

  assert(filtered.size() == 1);
}

void test_filter_tiles_keeps_non_background() {
  std::vector<cv::Mat> tiles = {make_black_tile(), make_black_tile()};

  auto filtered = filter_tiles(tiles);

  assert(filtered.size() == 2);
}

void test_filter_tiles_all_background() {
  std::vector<cv::Mat> tiles = {make_white_tile(), make_white_tile()};

  auto filtered = filter_tiles(tiles);

  assert(filtered.empty());
}

void test_filter_tiles_empty_input() {
  std::vector<cv::Mat> tiles;

  auto filtered = filter_tiles(tiles);

  assert(filtered.empty());
}

void test_filter_tiles_threshold() {
  cv::Mat tile(10, 10, CV_8UC3, cv::Scalar(255, 255, 255));

  // 79 пикселей не белые: 21% фона
  for (int i = 0; i < 21; ++i) {
    tile.at<cv::Vec3b>(i / 10, i % 10) = cv::Vec3b(0, 0, 0);
  }

  std::vector<cv::Mat> tiles = {tile};

  auto filtered = filter_tiles(tiles);

  assert(filtered.size() == 1);
}

int main() {
  test_small_image();
  std::cout << "[PASS] test_small_image\n";
  test_large_image();
  std::cout << "[PASS] test_large_image\n";
  test_black_tile();
  std::cout << "[PASS] test_black_tile\n";
  test_white_tile();
  std::cout << "[PASS] test_white_tile\n";
  test_half_white_tile();
  std::cout << "[PASS] test_half_white_tile\n";
  test_80_white_tile();
  std::cout << "[PASS] test_80_white_tile\n";
  test_79_white_tile();
  std::cout << "[PASS] test_79_white_tile\n";
  test_81_white_tile();
  std::cout << "[PASS] test_81_white_tile\n";
  test_filter_tiles_removes_background();
  test_filter_tiles_keeps_non_background();
  test_filter_tiles_all_background();
  test_filter_tiles_empty_input();
  test_filter_tiles_threshold();
  std::cout << "[PASS] test_filter_tiles\n";

  std::cout << "All tests passed!\n";
}
