#!/usr/bin/python3

from collections import namedtuple
from functools import reduce
from PIL import Image, ImageChops, UnidentifiedImageError
import math
import operator
import os
import subprocess
import sys
import tempfile


def calc_images_distance(image_path1, image_path2):
    with Image.open(image_path1) as image1, Image.open(image_path2) as image2:
        histogram = ImageChops.difference(image1, image2).histogram()

        return math.sqrt(reduce(operator.add, map(lambda h, i: h * (i ** 2), histogram, range(256))) / (
                float(image1.size[0]) * image1.size[1]))


class ImageProcessorTester:
    TestCase = namedtuple("TestCase", ["name", "input", "args", "eps"])

    class TestCaseFailedException(Exception):
        pass

    def __init__(self, image_processor_executable):
        self.image_processor_executable = image_processor_executable

    @staticmethod
    def fail_test_case(input, name, message):
        print("FAIL [{input}_{name}] {message}".format(input=input, name=name, message=message))
        raise ImageProcessorTester.TestCaseFailedException()

    @staticmethod
    def succeed_test_case(input, name):
        print("OK   [{input}_{name}]".format(input=input, name=name))

    def run_tests(self):

        filter_test_cases = {
            "crop": [
                ImageProcessorTester.TestCase(input="lenna", name="crop", args=["-crop", "999", "1999"], eps=0.0),
                ImageProcessorTester.TestCase(input="lenna", name="crop_crop",
                                              args=["-crop", "999", "1999", "-crop", "100", "1"],
                                              eps=0.0),
                ImageProcessorTester.TestCase(input="flag", name="crop", args=["-crop", "50", "50"], eps=0.0),
            ],
            "edge": [
                ImageProcessorTester.TestCase(input="flag", name="edge", args=["-edge", "0.1"], eps=1.0),
                ImageProcessorTester.TestCase(input="flag", name="edge_edge", args=["-edge", "0.1", "-edge", "0.5"],
                                              eps=1.0),
            ],
            "gs": [
                ImageProcessorTester.TestCase(input="lenna", name="gs", args=["-gs"], eps=1.0),
                ImageProcessorTester.TestCase(input="lenna", name="gs_gs", args=["-gs", "-gs"], eps=1.0),
                ImageProcessorTester.TestCase(input="flag", name="gs", args=["-gs"], eps=1.0),
            ],
            "neg": [
                ImageProcessorTester.TestCase(input="lenna", name="neg", args=["-neg"], eps=1.0),
                ImageProcessorTester.TestCase(input="lenna", name="neg_neg", args=["-neg", "-neg"], eps=1.0),
                ImageProcessorTester.TestCase(input="flag", name="neg", args=["-neg"], eps=1.0),
            ],
            "sharp": [
                ImageProcessorTester.TestCase(input="lenna", name="sharp", args=["-sharp"], eps=1.0),
                ImageProcessorTester.TestCase(input="lenna", name="sharp_sharp", args=["-sharp", "-sharp"], eps=1.0),
                ImageProcessorTester.TestCase(input="flag", name="sharp", args=["-sharp"], eps=1.0)
            ],
            "blur": [
                ImageProcessorTester.TestCase(input="lenna", name="blur", args=["-blur", "7.5"], eps=2.0),
                ImageProcessorTester.TestCase(input="lenna", name="blur_blur", args=["-blur", "7.5", "-blur", "3"],
                                              eps=2.0),
            ],
        }
        ok_filters = set()

        for filter_name, test_cases in filter_test_cases.items():
            try:
                for test_case in test_cases:
                    self.run_test_case(test_case)
                ok_filters.add(filter_name)
            except ImageProcessorTester.TestCaseFailedException:
                pass

        if ok_filters:
            print("-----\nTOTAL {ok_filters_count} OK FILTERS: {ok_filters}\n-----".format(
                ok_filters_count=len(ok_filters),
                ok_filters=", ".join(ok_filters)))
            return True
        else:
            print("-----\nNO OK FILTERS :(\n-----")
            return False

    def run_test_case(self, test_case):
        try:
            input_file_name = "{input}.bmp".format(input=test_case.input)
            output_file_name = "{input}_{name}.bmp".format(input=test_case.input, name=test_case.name)
            input_file = os.path.join("test_script", "data", input_file_name)
            expected_output_file = os.path.join("test_script", "data", output_file_name)

            with tempfile.NamedTemporaryFile(suffix=".bmp") as output_file:
                subprocess.check_call([self.image_processor_executable, input_file, output_file.name] + test_case.args,
                                      timeout=180)

                images_distance = calc_images_distance(expected_output_file, output_file.name)
                if images_distance > test_case.eps:
                    self.fail_test_case(test_case.input, test_case.name,
                                        "output image differs from expected with rms diff {diff}".format(
                                            diff=images_distance))

            self.succeed_test_case(test_case.input, test_case.name)
        except subprocess.CalledProcessError:
            self.fail_test_case(test_case.input, test_case.name, "image_processor finished with non-zero exit code")
        except subprocess.TimeoutExpired:
            self.fail_test_case(test_case.input, test_case.name, "timeout")
        except FileNotFoundError:
            self.fail_test_case(test_case.input, test_case.name, "output file not found")
        except UnidentifiedImageError:
            self.fail_test_case(test_case.input, test_case.name, "output file is corrupt")


if __name__ == "__main__":
    tester = ImageProcessorTester(image_processor_executable=sys.argv[1])

    print(
        "Running image_processor tests\nExecutable: {executable}".format(executable=tester.image_processor_executable))

    if not tester.run_tests():
        sys.exit(1)
