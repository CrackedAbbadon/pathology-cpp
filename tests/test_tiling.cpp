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

  std::cout << "All tests passed!\n";
}
