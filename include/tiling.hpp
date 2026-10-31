#ifndef TILING_HPP
#define TILING_HPP

#include <opencv2/core.hpp>
#include <vector>

std::vector<cv::Mat> split_into_tiles(const cv::Mat &image, int tile_size);
bool is_background(const cv::Mat &tile);
std::vector<cv::Mat> filter_tiles(const std::vector<cv::Mat> &tiles);
#endif // TILING_HPP
