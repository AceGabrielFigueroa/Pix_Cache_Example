#include <iostream>
#include <fstream>
#include <bitset>
#include <Magick++.h>

int main() {

	clock_t start = clock();

	Magick::Image _IMG_1;
	_IMG_1.read("resources\\img1.png");
	_IMG_1.type(Magick::GrayscaleType);
	_IMG_1.depth(1);
	Magick::Pixels _VIEW_IMG_1(_IMG_1);
	const Magick::Quantum* _PIXEL_CACHE_IMG_1 = _VIEW_IMG_1.getConst(0, 0, _IMG_1.columns(), _IMG_1.rows());
	

	Magick::Image _IMG_2;
	_IMG_2.read("resources\\img2.png");
	_IMG_2.type(Magick::GrayscaleType);
	_IMG_2.depth(1);
	Magick::Pixels _VIEW_IMG_2(_IMG_2);
	const Magick::Quantum* _PIXEL_CACHE_IMG_2 = _VIEW_IMG_2.getConst(0, 0, _IMG_2.columns(), _IMG_2.rows());

	Magick::Image _IMG_3;
	_IMG_3.read("resources\\img3.png");
	_IMG_3.type(Magick::GrayscaleType);
	_IMG_3.depth(1);

	Magick::Pixels _VIEW_IMG_3(_IMG_3);
	const Magick::Quantum* _PIXEL_CACHE_IMG_3 = _VIEW_IMG_3.getConst(0, 0, _IMG_3.columns(), _IMG_3.rows());

	Magick::Image _IMG_4;
	_IMG_4.read("resources\\img4.png");
	_IMG_4.type(Magick::GrayscaleType);
	_IMG_4.depth(1);
	
	Magick::Pixels _VIEW_IMG_4(_IMG_4);
	const Magick::Quantum* _PIXEL_CACHE_IMG_4 = _VIEW_IMG_4.getConst(0, 0, _IMG_4.columns(), _IMG_4.rows());

	Magick::Image _IMG_5;
	_IMG_5.read("resources\\img5.png");
	_IMG_5.type(Magick::GrayscaleType);
	_IMG_5.depth(1);

	Magick::Pixels _VIEW_IMG_5(_IMG_5);
	const Magick::Quantum* _PIXEL_CACHE_IMG_5 = _VIEW_IMG_5.getConst(0, 0, _IMG_5.columns(), _IMG_5.rows());

	Magick::Image _IMG_6;
	_IMG_6.read("resources\\img6.png");
	_IMG_6.type(Magick::GrayscaleType);
	_IMG_6.depth(1);

	Magick::Pixels _VIEW_IMG_6(_IMG_6);
	const Magick::Quantum* _PIXEL_CACHE_IMG_6 = _VIEW_IMG_6.getConst(0, 0, _IMG_6.columns(), _IMG_6.rows());

	Magick::Image _IMG_7;
	_IMG_7.read("resources\\img7.png");
	_IMG_7.type(Magick::GrayscaleType);
	_IMG_7.depth(1);

	Magick::Pixels _VIEW_IMG_7(_IMG_7);
	const Magick::Quantum* _PIXEL_CACHE_IMG_7 = _VIEW_IMG_7.getConst(0, 0, _IMG_7.columns(), _IMG_7.rows());

	Magick::Image _IMG_8;
	_IMG_8.read("resources\\img8.png");
	_IMG_8.type(Magick::GrayscaleType);
	_IMG_8.depth(1);

	Magick::Pixels _VIEW_IMG_8(_IMG_8);
	const Magick::Quantum* _PIXEL_CACHE_IMG_8 = _VIEW_IMG_8.getConst(0, 0, _IMG_8.columns(), _IMG_8.rows());
	
	// TODO: Check if all images are ==
	// IF ==
	// THEN SET NEW IMAGE DIMENSIONS
	// ELSE
	// FIND BIGGEST LAYOUT
	// SET BIGGEST TO NEW IMAGE DIMENSIONs

	size_t width = _IMG_1.columns();
	size_t height = _IMG_1.rows();

	Magick::Image _IMG_COMBINED(Magick::Geometry(width, height), "black");

	// Allows image to be modifyable through pixel cache
	_IMG_COMBINED.modifyImage();

	Magick::Pixels _VIEW_IMG_COMBINED(_IMG_COMBINED);
	Magick::Quantum* _PIXEL_CACHE_VIEW_COMBINED = _VIEW_IMG_COMBINED.get(0, 0, width, height);

	// Look up color table
	// TODO: error check file
	std::ifstream _COLOR_TABLE_FILE("resources\\color.txt");
	Magick::Color _COLOR_TABLE[256];
	unsigned int _TEMP_C;
	
	if(_COLOR_TABLE_FILE)
		for (Magick::Color &c : _COLOR_TABLE)
		{
			_COLOR_TABLE_FILE >> _TEMP_C;
			c.quantumRed(_TEMP_C * (65535.0 / 255.0));

			_COLOR_TABLE_FILE >> _TEMP_C;
			c.quantumGreen(_TEMP_C * (65535.0 / 255.0));

			_COLOR_TABLE_FILE >> _TEMP_C;
			c.quantumBlue(_TEMP_C * (65535.0 / 255.0));	
		}

	Magick::Color _PX_COLOR;

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			uint8_t _A = *_PIXEL_CACHE_IMG_1++;
			uint8_t _B = *_PIXEL_CACHE_IMG_2++ << 1;
			uint8_t _C = *_PIXEL_CACHE_IMG_3++ << 2;
			uint8_t _D = *_PIXEL_CACHE_IMG_4++ << 3;
			uint8_t _E = *_PIXEL_CACHE_IMG_5++ << 4;
			uint8_t _F = *_PIXEL_CACHE_IMG_6++ << 5;
			uint8_t _G = *_PIXEL_CACHE_IMG_7++ << 6;
			uint8_t _H = *_PIXEL_CACHE_IMG_8++ << 7;

			_PX_COLOR = _COLOR_TABLE[(_A | _B | _C | _D | _E | _F | _G | _H)];
			*_PIXEL_CACHE_VIEW_COMBINED++ = _PX_COLOR.quantumRed();
			*_PIXEL_CACHE_VIEW_COMBINED++ = _PX_COLOR.quantumGreen();
			*_PIXEL_CACHE_VIEW_COMBINED++ = _PX_COLOR.quantumBlue();
		}
	
	_IMG_COMBINED.syncPixels();
	_IMG_COMBINED.write("TEST.png");

	// Execuatable code
	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	printf("Time elapsed in ms: %f", elapsed);

	return 0;
}