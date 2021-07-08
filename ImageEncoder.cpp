#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "ImageEncoder.h"
#include "Encode.h"
#include "Decode.h"

using namespace cv;

int main()
{
    std::string image_path = "sample.png";
	std::string image_message = "A beautifully hidden message.";
	std::string output_image_path = "sample_hidden.png";

	std::cout << "Encoding message... " << std::endl;
	std::cout << image_message << std::endl;

	encode(image_path, image_message, output_image_path);

	std::cout << "Decoding message... " << std::endl;

	decode(output_image_path);

	std::cout << '\n';

    return 0;
}

// Checks whether the bit is set or not at a particular position.
// Returns true if set
// Returns false if not set
bool isBitSet(char ch, int pos) {
	// 7 6 5 4 3 2 1 0
	ch = ch >> pos;
	if (ch & 1)
		return true;
	return false;
}