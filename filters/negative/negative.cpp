#include "negative.h"

void Negative(Image& base_img) {
    uint32_t base_height = base_img.GetHeight();
    uint32_t base_width = base_img.GetWidth();
    std::vector<std::vector<Pixel>> base_matrix = base_img.GetMatrix();
    for (size_t y = 0; y < base_height; ++y) {
        for (size_t x = 0; x < base_width; ++x) {
            base_matrix[y][x].r = 1 - base_matrix[y][x].r;
            base_matrix[y][x].g = 1 - base_matrix[y][x].g;
            base_matrix[y][x].b = 1 - base_matrix[y][x].b;
        }
    }
    base_img.ChangeMatrix(base_matrix);
}
