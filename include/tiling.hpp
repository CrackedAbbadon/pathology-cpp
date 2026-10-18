#ifndef TILING_HPP
#define TILING_HPP

#include <opencv2/core.hpp>
#include <vector>

std::vector<cv::Mat> split_into_tiles(const cv::Mat &image, int tile_size);

#endif // TILING_HPP
