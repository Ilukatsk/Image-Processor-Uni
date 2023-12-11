#pragma once

#include "../image_class.h"

double ApplyMatrix(const std::vector<std::vector<Pixel>>& base_matrix, int64_t x, int64_t y, uint32_t base_height,
                   uint32_t base_width, const std::vector<int>& values, const std::string& color);
