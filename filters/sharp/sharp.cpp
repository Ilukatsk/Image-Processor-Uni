#include "sharp.h"

void Sharp(Image& img) {
    const std::vector<int> matrix_vector = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    uint32_t base_height = img.GetHeight();
    uint32_t base_width = img.GetWidth();
    std::vector<std::vector<Pixel>> base_matrix = img.GetMatrix();
    std::vector<std::vector<Pixel>> matrix_new = img.GetMatrix();
    for (int64_t y = 0; y < base_height; ++y) {
        for (int64_t x = 0; x < base_width; ++x) {
            double red_new = ApplyMatrix(base_matrix, x, y, base_height, base_width, matrix_vector, "red");
            double blue_new = ApplyMatrix(base_matrix, x, y, base_height, base_width, matrix_vector, "blue");
            double green_new = ApplyMatrix(base_matrix, x, y, base_height, base_width, matrix_vector, "green");
            matrix_new[y][x].r = red_new;
            matrix_new[y][x].b = blue_new;
            matrix_new[y][x].g = green_new;
        }
    }
    img.ChangeMatrix(matrix_new);
}
