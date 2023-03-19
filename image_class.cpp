#include "image_class.h"

Image::Image(const std::string path) {
    std::ifstream image;
    image.open(path, std::ios::in | std::ios::binary);
    if (!image.is_open()) {
        std::cout << "Unable to read file" << std::endl;
        return;
    }
    std::cout << "File successfully opened" << std::endl;
    image.read(reinterpret_cast<char*>(file_header_), FILE_HEADER_SIZE);
    image.read(reinterpret_cast<char*>(info_header_), INFO_HEADER_SIZE);
    width_ = info_header_[WIDTH_1] + (info_header_[WIDTH_2] << BIT_SHIFT) + (info_header_[WIDTH_3] << BIT_SHIFT * 2) +
             (info_header_[WIDTH_4] << BIT_SHIFT * 3);
    height_ = info_header_[HEIGHT_1] + (info_header_[HEIGHT_2] << BIT_SHIFT) +
              (info_header_[HEIGHT_3] << BIT_SHIFT * 2) + (info_header_[HEIGHT_4] << BIT_SHIFT * 3);
    padding_size_ = (4 - (width_ * 3) % 4) % 4;
    unsigned char temp[3];
    for (size_t y = 0; y < height_; ++y) {
        std::vector<Pixel> temp_vec;
        for (size_t x = 0; x < width_; ++x) {
            image.read(reinterpret_cast<char*>(temp), 3);
            Pixel pixel = {static_cast<double>(temp[2]) / static_cast<double>(COLOR_BRIGHTNESS),
                           static_cast<double>(temp[1]) / static_cast<double>(COLOR_BRIGHTNESS),
                           static_cast<double>(temp[0]) / static_cast<double>(COLOR_BRIGHTNESS)};
            temp_vec.push_back(pixel);
        }
        image.read(reinterpret_cast<char*>(temp), padding_size_);
        image_matrix_.push_back(temp_vec);
    }
}

void Image::Export(const std::string path) {
    std::ofstream image_out;
    image_out.open(path, std::ios::out | std::ios::binary);
    if (!image_out.is_open()) {
        std::cout << "Was unable to find output location" << std::endl;
        return;
    }
    image_out.write(reinterpret_cast<char*>(file_header_), FILE_HEADER_SIZE);
    image_out.write(reinterpret_cast<char*>(info_header_), INFO_HEADER_SIZE);
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            unsigned char red = static_cast<unsigned char>(image_matrix_[y][x].r * COLOR_BRIGHTNESS);
            unsigned char blue = static_cast<unsigned char>(image_matrix_[y][x].b * COLOR_BRIGHTNESS);
            unsigned char green = static_cast<unsigned char>(image_matrix_[y][x].g * COLOR_BRIGHTNESS);
            unsigned char pixel[3] = {blue, green, red};
            image_out.write(reinterpret_cast<char*>(pixel), 3);
        }
        if (padding_size_ == 1) {
            unsigned char tmp[1] = {0};
            image_out.write(reinterpret_cast<char*>(tmp), padding_size_);
        } else if (padding_size_ == 2) {
            unsigned char tmp[2] = {0, 0};
            image_out.write(reinterpret_cast<char*>(tmp), padding_size_);
        } else if (padding_size_ == 3) {
            unsigned char tmp[3] = {0, 0, 0};
            image_out.write(reinterpret_cast<char*>(tmp), padding_size_);
        }
    }
    std::cout << "File successfully closed" << std::endl;
    image_out.close();
}

void Image::ChangeWidth(const uint32_t& width) {
    width_ = width;
    info_header_[WIDTH_1] = width;
    info_header_[WIDTH_2] = width >> BIT_SHIFT;
    info_header_[WIDTH_3] = width >> BIT_SHIFT * 2;
    info_header_[WIDTH_4] = width >> BIT_SHIFT * 3;
    padding_size_ = (4 - (width_ * 3) % 4) % 4;
    ChangeHeaderSize();
}

void Image::ChangeHeight(const uint32_t& height) {
    height_ = height;
    info_header_[HEIGHT_1] = height;
    info_header_[HEIGHT_2] = height >> BIT_SHIFT;
    info_header_[HEIGHT_3] = height >> BIT_SHIFT * 2;
    info_header_[HEIGHT_4] = height >> BIT_SHIFT * 3;
    ChangeHeaderSize();
}

void Image::ChangeHeaderSize() {
    uint32_t tot_size = height_ * (width_ * 3 + padding_size_) + TOT_HEADER_SIZE;
    file_header_[SIZE_1] = tot_size;
    file_header_[SIZE_2] = tot_size >> BIT_SHIFT;
    file_header_[SIZE_3] = tot_size >> BIT_SHIFT * 2;
    file_header_[SIZE_4] = tot_size >> BIT_SHIFT * 3;
    uint32_t raw_size = tot_size - TOT_HEADER_SIZE;
    info_header_[SIZE_RAW_1] = raw_size;
    info_header_[SIZE_RAW_2] = raw_size >> BIT_SHIFT;
    info_header_[SIZE_RAW_3] = raw_size >> BIT_SHIFT * 2;
    info_header_[SIZE_RAW_4] = raw_size >> BIT_SHIFT * 3;
}

void Image::ChangeMatrix(ImageMatrix& new_mat) {
    image_matrix_ = new_mat;
}

uint32_t Image::GetHeight() const {
    return height_;
}

uint32_t Image::GetWidth() const {
    return width_;
}

std::vector<std::vector<Pixel>> Image::GetMatrix() const {
    return image_matrix_;
}
// todo: check that file is actually bmp(probably just check last 4 characters of the path and compare them with .bmp)
// todo: check that file is 24-bit(infoheader[12] + infoheader[13] << 8 should be equal to 24)
// for filters I'll probably make them fuctions that accept class image and return class image