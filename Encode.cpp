#include <iostream>
#include <fstream>
#include "ImageEncoder.h"
#include "Encode.h"

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void encode(string image_name, string message, string output_image_name) {

	// Stores original image
	Mat image = imread(image_name);
	if (image.empty()) {
		cout << "Image Error\n";
		exit(-1);
	}

	// char to work on variable
	char ch;
	// starting char position
	int c = 0;
	// reads the first char from the message string
	ch = message[c];
	// contains information about which bit of char to work on
	int bit_count = 0;
	// to check whether file has ended
	bool last_null_char = false;
	// to check if the whole message is encoded or not
	bool encoded = false;

	// iterate over all pixels in the image
	for (int row = 0; row < image.rows; row++) {
		for (int col = 0; col < image.cols; col++) {
			// iterate through all 3 color channel for each pixel
			for (int color = 0; color < 3; color++) {
				// stores the pixel details
				Vec3b pixel = image.at<Vec3b>(Point(row, col));

				// if bit is 1 : change LSB of present color value to 1.
				// if bit is 0 : change LSB of present color value to 0.
				// stores the char on the bit if it's not set
				if (isBitSet(ch, 7 - bit_count))
					pixel.val[color] |= 1;
				else
					pixel.val[color] &= ~1;

				// update the image with the changed pixel values
				image.at<Vec3b>(Point(row, col)) = pixel;

				// increment bit_count to work on next bit
				bit_count++;

				// if last_null_char is true and bit_count is 8, then message is successfully encoded
				if (last_null_char && bit_count == 8) {
					encoded = true;
					goto OUT;
				}

				// if bit_count is 8 we pick the next char from the string and work on it
				if (bit_count == 8) {
					bit_count = 0;
					c++;
					ch = message[c];

					// if end of string is encountered insert NULL char to the image
					if (ch == '\0') {
						last_null_char = true;
						ch = '\0';
					}
				}

			}
		}
	}
OUT:;

	// whole message was not encoded
	if (!encoded) {
		cout << "Message too big. Try with larger image.\n";
		exit(-1);
	}

	// writes the stegnographic image
	imwrite(output_image_name, image);

	return;
}