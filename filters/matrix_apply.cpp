#include "matrix_apply.h"

namespace {
const char ZERO = 0;
const char ONE = 1;
const char TWO = 2;
const char THREE = 3;
const char FOUR = 4;
const char FIVE = 5;
const char SIX = 6;
const char SEVEN = 7;
const char EIGHT = 8;
}  // namespace

double ApplyMatrix(const std::vector<std::vector<Pixel>>& base_matrix, int64_t x, int64_t y, uint32_t base_height,
                   uint32_t base_width, const std::vector<int>& values, const std::string& color) {
    double val_new = 0;
    if (color == "red") {
        val_new = std::min(
            static_cast<double>(1),
            std::max(static_cast<double>(0),
                     values[ZERO] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))]
                                               [std::max(static_cast<int64_t>(0), (x - 1))]
                                                   .r +
                         values[ONE] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))][x].r +
                         values[TWO] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))]
                                                  [std::min(static_cast<int64_t>(base_width - 1), (x + 1))]
                                                      .r +
                         values[THREE] * base_matrix[y][std::max(static_cast<int64_t>(0), (x - 1))].r +
                         values[FOUR] * base_matrix[y][x].r +
                         values[FIVE] * base_matrix[y][std::min(static_cast<int64_t>(base_width - 1), (x + 1))].r +
                         values[SIX] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))]
                                                  [std::max(static_cast<int64_t>(0), (x - 1))]
                                                      .r +
                         values[SEVEN] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))][x].r +
                         values[EIGHT] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))]
                                                    [std::min(static_cast<int64_t>(base_width - 1), (x + 1))]
                                                        .r));
    } else if (color == "blue") {
        val_new = std::min(
            static_cast<double>(1),
            std::max(static_cast<double>(0),
                     values[ZERO] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))]
                                               [std::max(static_cast<int64_t>(0), (x - 1))]
                                                   .b +
                         values[ONE] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))][x].b +
                         values[TWO] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))]
                                                  [std::min(static_cast<int64_t>(base_width - 1), (x + 1))]
                                                      .b +
                         values[THREE] * base_matrix[y][std::max(static_cast<int64_t>(0), (x - 1))].b +
                         values[FOUR] * base_matrix[y][x].b +
                         values[FIVE] * base_matrix[y][std::min(static_cast<int64_t>(base_width - 1), (x + 1))].b +
                         values[SIX] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))]
                                                  [std::max(static_cast<int64_t>(0), (x - 1))]
                                                      .b +
                         values[SEVEN] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))][x].b +
                         values[EIGHT] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))]
                                                    [std::min(static_cast<int64_t>(base_width - 1), (x + 1))]
                                                        .b));
    } else if (color == "green") {
        val_new = std::min(
            static_cast<double>(1),
            std::max(static_cast<double>(0),
                     values[ZERO] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))]
                                               [std::max(static_cast<int64_t>(0), (x - 1))]
                                                   .g +
                         values[ONE] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))][x].g +
                         values[TWO] * base_matrix[std::max(static_cast<int64_t>(0), (y - 1))]
                                                  [std::min(static_cast<int64_t>(base_width - 1), (x + 1))]
                                                      .g +
                         values[THREE] * base_matrix[y][std::max(static_cast<int64_t>(0), (x - 1))].g +
                         values[FOUR] * base_matrix[y][x].g +
                         values[FIVE] * base_matrix[y][std::min(static_cast<int64_t>(base_width - 1), (x + 1))].g +
                         values[SIX] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))]
                                                  [std::max(static_cast<int64_t>(0), (x - 1))]
                                                      .g +
                         values[SEVEN] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))][x].g +
                         values[EIGHT] * base_matrix[std::min(static_cast<int64_t>(base_height - 1), (y + 1))]
                                                    [std::min(static_cast<int64_t>(base_width - 1), (x + 1))]
                                                        .g));
    }
    return val_new;
}
