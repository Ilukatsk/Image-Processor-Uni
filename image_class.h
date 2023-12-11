#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

const char FILE_HEADER_SIZE = 14;
const char INFO_HEADER_SIZE = 40;

struct Pixel {
    double r = 0;
    double g = 0;
    double b = 0;
};

class Image {
    using ImageMatrix = std::vector<std::vector<Pixel>>;
    using FileHeader = unsigned char[FILE_HEADER_SIZE];
    using InfoHeader = unsigned char[INFO_HEADER_SIZE];
    FileHeader file_header_;
    InfoHeader info_header_;
    uint32_t width_;
    uint32_t height_;
    uint32_t padding_size_;
    ImageMatrix image_matrix_ = {};

public:
    explicit Image(const std::string path);
    void Export(const std::string path);
    void ChangeWidth(const uint32_t& width);
    void ChangeHeight(const uint32_t& height);
    void ChangeHeaderSize();
    void ChangeMatrix(ImageMatrix& new_mat);
    uint32_t GetHeight() const;
    uint32_t GetWidth() const;
    std::vector<std::vector<Pixel>> GetMatrix() const;
};
