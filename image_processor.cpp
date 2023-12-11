#include "filters/crop/crop_filter.h"
#include "filters/gray_shades/gray_shades.h"
#include "filters/negative/negative.h"
#include "filters/sharp/sharp.h"
#include "filters/edge_detect/edge_detection.h"
#include "filters/floyd_steinberg/dithering.h"

namespace {
const char POW_1 = 2;
const char POW_2 = 4;
const char POW_3 = 8;
const char POW_4 = 16;
const char POW_5 = 32;
const char POW_6 = 64;
const int POW_7 = 128;
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Filters list:" << std::endl;
        std::cout << "Crop:           |  -crop  |  width[int > 0]                |  height[int > 0]  |" << std::endl;
        std::cout << "Edge Detection: |  -edge  |  threshold[float]              |" << std::endl;
        std::cout << "Dithering:      |  -d     |  color_range[power of 2 != 1 and less than 256]  |" << std::endl;
        std::cout << "Graystyle:      |  -gs    |" << std::endl;
        std::cout << "Negative:       |  -neg   |" << std::endl;
        std::cout << "Sharpening:     |  -sharp |" << std::endl;
        return 0;
    }
    std::string input_loc = static_cast<std::string>(argv[1]);
    std::string output_loc = static_cast<std::string>(argv[2]);
    if (input_loc.substr(input_loc.size() - 4, 4) != ".bmp") {
        std::cout << "No input file location given." << std::endl;
        return -1;
    }
    if (output_loc.substr(output_loc.size() - 4, 4) != ".bmp") {
        std::cout << "No output file location given." << std::endl;
        return -1;
    }
    Image image(input_loc);
    size_t i = 3;
    size_t max_size = static_cast<size_t>(argc);
    while (i < max_size) {
        std::string temp = static_cast<std::string>(argv[i]);
        if (temp[0] == '-') {
            if (temp == "-gs") {
                std::cout << "Applying gray shades filter" << std::endl;
                GrayShades(image);
                std::cout << "Filter successfully applied" << std::endl;
            } else if (temp == "-sharp") {
                std::cout << "Applying sharp filter" << std::endl;
                Sharp(image);
                std::cout << "Filter successfully applied" << std::endl;
            } else if (temp == "-neg") {
                std::cout << "Applying negative filter" << std::endl;
                Negative(image);
                std::cout << "Filter successfully applied" << std::endl;
            } else if (temp == "-edge") {
                if (i + 1 < max_size) {
                    std::string threshold = static_cast<std::string>(argv[i + 1]);
                    if ((std::stod(threshold) <= 1) && (std::stod(threshold) >= 0)) {
                        std::cout << "Applying edge detection filter" << std::endl;
                        // add check to ensure that threshold value were given correctly
                        EdgeDetect(image, std::stod(threshold));
                        std::cout << "Filter successfully applied" << std::endl;
                    } else {
                        std::cout << "Incorrect threshold value" << std::endl;
                        return -1;
                    }
                } else {
                    std::cout << "No threshold value is given." << std::endl;
                    return -1;
                }
                i += 1;
            } else if (temp == "-crop") {
                if (i + 2 < max_size) {
                    std::string width = static_cast<std::string>(argv[i + 1]);
                    std::string height = static_cast<std::string>(argv[i + 2]);
                    bool width_incor = false;
                    bool height_incor = false;
                    if (std::stoi(width) <= 0) {
                        width_incor = true;
                        std::cout << "Width is zero or less." << std::endl;
                    }
                    if (std::stoi(height) <= 0) {
                        height_incor = true;
                        std::cout << "Height is zero or less." << std::endl;
                    }
                    if (width_incor || height_incor) {
                        return -1;
                    }
                    std::cout << "Applying crop filter" << std::endl;
                    Crop(image, std::stoi(width), std::stoi(height));
                    std::cout << "Filter successfully applied" << std::endl;
                } else {
                    std::cout << "No width or height values were given" << std::endl;
                }
                i += 2;
            } else if (temp == "-d") {
                if (i + 1 < max_size) {
                    std::string range = static_cast<std::string>(argv[i + 1]);
                    if ((std::stoi(range) != POW_1) && (std::stoi(range) != POW_2) && (std::stoi(range) != POW_3) &&
                        (std::stoi(range) != POW_4) && (std::stoi(range) != POW_5) && (std::stoi(range) != POW_6) &&
                        (std::stoi(range) != POW_7)) {
                        std::cout << "Incorrect color range" << std::endl;
                        return -1;
                    }
                    std::cout << "Applying dithering filter" << std::endl;
                    Dithering(image, std::stoi(range));
                    std::cout << "Filter successfully applied" << std::endl;
                    i += 1;
                } else {
                    std::cout << "No color range given" << std::endl;
                }
            } else {
                std::cout << "Filer does not exist." << std::endl;
                return -1;
            }
            i += 1;
        } else {
            std::cout << "Incorrect input." << std::endl;
            return -1;
        }
    }
    image.Export(output_loc);
    return 0;
}
