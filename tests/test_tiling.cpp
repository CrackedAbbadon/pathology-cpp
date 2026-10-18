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

int main() {
  test_small_image();
  std::cout << "[PASS] test_small_image\n";
  test_large_image();
  std::cout << "[PASS] test_large_image\n";

  std::cout << "All tests passed!\n";
}
