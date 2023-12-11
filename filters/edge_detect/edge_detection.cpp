#include "edge_detection.h"

void EdgeDetect(Image& img, double threshold) {
    GrayShades(img);
    const std::vector<int> matrix_vector = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    uint32_t base_height = img.GetHeight();
    uint32_t base_width = img.GetWidth();
    std::vector<std::vector<Pixel>> base_matrix = img.GetMatrix();
    std::vector<std::vector<Pixel>> matrix_new = img.GetMatrix();
    for (int64_t y = 0; y < base_height; ++y) {
        for (int64_t x = 0; x < base_width; ++x) {
            double val_new = ApplyMatrix(base_matrix, x, y, base_height, base_width, matrix_vector, "red");
            if (val_new > threshold) {
                val_new = 1;
            } else {
                val_new = 0;
            }
            matrix_new[y][x].r = val_new;
            matrix_new[y][x].b = val_new;
            matrix_new[y][x].g = val_new;
        }
    }
    img.ChangeMatrix(matrix_new);
}
