#include "crop_filter.h"

void Crop(Image& base_img, uint32_t width, uint32_t height) {
    uint32_t base_height = base_img.GetHeight();
    uint32_t base_width = base_img.GetWidth();
    std::vector<std::vector<Pixel>> base_matrix = base_img.GetMatrix();
    std::reverse(base_matrix.begin(), base_matrix.end());
    if (height < base_height) {
        base_img.ChangeHeight(height);
        for (size_t y = 0; y < base_height - height; ++y) {
            base_matrix.pop_back();
        }
    }
    if (width < base_width) {
        base_img.ChangeWidth(width);
        for (auto& item : base_matrix) {
            for (size_t x = 0; x < base_width - width; ++x) {
                item.pop_back();
            }
        }
    }
    base_img.ChangeHeaderSize();
    std::reverse(base_matrix.begin(), base_matrix.end());
    base_img.ChangeMatrix(base_matrix);
}
