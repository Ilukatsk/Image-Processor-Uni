add_executable(
        image_processor
        image_processor.cpp
        image_class.cpp
        filters/edge_detect/edge_detection.cpp filters/crop/crop_filter.cpp filters/floyd_steinberg/dithering.cpp
        filters/gray_shades/gray_shades.cpp filters/negative/negative.cpp filters/sharp/sharp.cpp filters/matrix_apply.cpp filters/matrix_apply.h)
