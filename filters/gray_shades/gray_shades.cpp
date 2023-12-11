#include "gray_shades.h"

namespace {
const float VAL_FOR_RED = 0.299;
const float VAL_FOR_GREEN = 0.587;
const float VAL_FOR_BLUE = 0.114;
}  // namespace

void GrayShades(Image& base_img) {
    uint32_t base_height = base_img.GetHeight();
    uint32_t base_width = base_img.GetWidth();
    std::vector<std::vector<Pixel>> base_matrix = base_img.GetMatrix();
    for (size_t y = 0; y < base_height; ++y) {
        for (size_t x = 0; x < base_width; ++x) {
            double new_val = (base_matrix[y][x].r * VAL_FOR_RED) + (base_matrix[y][x].b * VAL_FOR_BLUE) +
                             (base_matrix[y][x].g * VAL_FOR_GREEN);
            base_matrix[y][x].r = new_val;
            base_matrix[y][x].g = new_val;
            base_matrix[y][x].b = new_val;
        }
    }
    base_img.ChangeMatrix(base_matrix);
}
