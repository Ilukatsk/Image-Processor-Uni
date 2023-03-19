#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

const size_t WIDTH_1 = 4;
const size_t WIDTH_2 = 5;
const size_t WIDTH_3 = 6;
const size_t WIDTH_4 = 7;
const size_t HEIGHT_1 = 8;
const size_t HEIGHT_2 = 9;
const size_t HEIGHT_3 = 10;
const size_t HEIGHT_4 = 11;
const char BIT_SHIFT = 8;
const char FILE_HEADER_SIZE = 14;
const char INFO_HEADER_SIZE = 40;
const char TOT_HEADER_SIZE = 54;
const uint16_t COLOR_BRIGHTNESS = 255;
const size_t SIZE_1 = 2;
const size_t SIZE_2 = 3;
const size_t SIZE_3 = 4;
const size_t SIZE_4 = 5;
const size_t SIZE_RAW_1 = 20;
const size_t SIZE_RAW_2 = 21;
const size_t SIZE_RAW_3 = 22;
const size_t SIZE_RAW_4 = 23;

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