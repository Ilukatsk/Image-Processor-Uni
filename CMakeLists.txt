add_executable(
    image_processor
    image_processor.cpp
        image_class.cpp image_class.h Filters/Crop/crop_filter.cpp Filters/Crop/crop_filter.h
        Filters/GrayShades/gray_shades.cpp Filters/GrayShades/gray_shades.h Filters/Negative/negative.cpp
        Filters/Negative/negative.h Filters/Sharp/sharp.cpp Filters/Sharp/sharp.h Filters/EdgeDetect/edge_detection.cpp
        Filters/EdgeDetect/edge_detection.h Filters/Floyd_Steinberg/dithering.cpp Filters/Floyd_Steinberg/dithering.h)
