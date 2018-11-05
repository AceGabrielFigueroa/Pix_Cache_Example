#include <Magick++.h> 
#include <iostream> 

using namespace std;
using namespace Magick;

int reference(int argc, char **argv)
{
	InitializeMagick(*argv);

	// Create base image 
	Image image(Geometry(1000, 1000), "white");

	// Sets the image to type 'Grayscale'
	// This sets the Image to having 1 color channel
	image.type(GrayscaleType);

	// Sets the number of bits of each pixel
	// This will set each pixel to having 1 bit.
	image.depth(1);

	// Ensure that there is only one reference to underlying image 
	// If this is not done, then image pixels will not be modified.
	image.modifyImage();

	// Allocate pixel view 
	Pixels view(image);

	// Set all pixels in region anchored at 38x36, 196x162 box
	//( [38, 196+38), [36, 162+36) )
	size_t columns = 196; size_t rows = 162;
	Color green("green");
	Quantum *pixels = view.get(38, 36, columns, rows);
	for (ssize_t row = 0; row < rows; ++row)
		for (ssize_t column = 0; column < columns; ++column)
			*pixels++ = QuantumRange * green.quantumRed();

	// Save changes to image.
	view.sync();

	image.write("logo.png");
}