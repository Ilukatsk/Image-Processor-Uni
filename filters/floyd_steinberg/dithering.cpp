#include "dithering.h"

namespace {
const char ERR_MULT_DENOM = 16;
const char ERR_MULT_7 = 7;
const char ERR_MULT_3 = 3;
const char ERR_MULT_5 = 5;
const char ERR_MULT_1 = 1;
}  // namespace

void Dithering(Image& img, int range) {
    uint32_t base_height = img.GetHeight();
    uint32_t base_width = img.GetWidth();
    std::vector<std::vector<Pixel>> base_matrix = img.GetMatrix();
    std::reverse(base_matrix.begin(), base_matrix.end());
    for (int64_t y = 0; y < base_height; ++y) {
        for (int64_t x = 0; x < base_width; ++x) {
            Pixel old_pixel = base_matrix[y][x];
            double old_r = old_pixel.r;
            double old_g = old_pixel.g;
            double old_b = old_pixel.b;
            double new_r = static_cast<double>(std::round(range * old_r)) / static_cast<double>(range);
            double new_g = static_cast<double>(std::round(range * old_g)) / static_cast<double>(range);
            double new_b = static_cast<double>(std::round(range * old_b)) / static_cast<double>(range);
            base_matrix[y][x].r = new_r;
            base_matrix[y][x].g = new_g;
            base_matrix[y][x].b = new_b;

            double error_r = old_r - new_r;
            double error_g = old_g - new_g;
            double error_b = old_b - new_b;

            if (x + 1 < base_width) {
                double err_mult = static_cast<double>(ERR_MULT_7) / static_cast<double>(ERR_MULT_DENOM);
                base_matrix[y][x + 1].r = base_matrix[y][x + 1].r + error_r * err_mult;
                base_matrix[y][x + 1].g = base_matrix[y][x + 1].g + error_g * err_mult;
                base_matrix[y][x + 1].b = base_matrix[y][x + 1].b + error_b * err_mult;
            }
            if ((y + 1 < base_height) && (x - 1 >= 0)) {
                double err_mult = static_cast<double>(ERR_MULT_3) / static_cast<double>(ERR_MULT_DENOM);
                base_matrix[y + 1][x - 1].r = base_matrix[y + 1][x - 1].r + error_r * err_mult;
                base_matrix[y + 1][x - 1].g = base_matrix[y + 1][x - 1].g + error_g * err_mult;
                base_matrix[y + 1][x - 1].b = base_matrix[y + 1][x - 1].b + error_b * err_mult;
            }
            if (y + 1 < base_height) {
                double err_mult = static_cast<double>(ERR_MULT_5) / static_cast<double>(ERR_MULT_DENOM);
                base_matrix[y + 1][x].r = base_matrix[y + 1][x].r + error_r * err_mult;
                base_matrix[y + 1][x].g = base_matrix[y + 1][x].g + error_g * err_mult;
                base_matrix[y + 1][x].b = base_matrix[y + 1][x].b + error_b * err_mult;
            }
            if ((y + 1 < base_height) && (x + 1 < base_width)) {
                double err_mult = static_cast<double>(ERR_MULT_1) / static_cast<double>(ERR_MULT_DENOM);
                base_matrix[y + 1][x + 1].r = base_matrix[y + 1][x + 1].r + error_r * err_mult;
                base_matrix[y + 1][x + 1].g = base_matrix[y + 1][x + 1].g + error_g * err_mult;
                base_matrix[y + 1][x + 1].b = base_matrix[y + 1][x + 1].b + error_b * err_mult;
            }
        }
    }
    std::reverse(base_matrix.begin(), base_matrix.end());
    img.ChangeMatrix(base_matrix);
}
