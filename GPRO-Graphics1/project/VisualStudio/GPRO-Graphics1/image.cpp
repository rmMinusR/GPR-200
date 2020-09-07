#include "image.hpp"

#include <stdexcept>

inline int Image::_ind(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height) throw std::invalid_argument("Index out of bounds!");
	return x+y*width;
}

Image::Image(const int& w, const int& h) : Image(w, h, DEFAULT_COLOR_SPACE) {}

Image::Image(const int& w, const int& h, const float& c) : width(w), height(h), color_space(c), pixels(new Color[w * h])
{ }

Image::~Image()
{
	delete[] pixels; //Should ideally set pixels to nullptr, but pixels should stay const.
}

void Image::write_to(std::ostream& out)
{
	if (!out.good()) throw std::invalid_argument("File is not open!");

	//Allow binary write mode (doesn't work!)
	//bool use_binary = false;// color_space < 256;

	//Write header

	//out << (use_binary?"P6":"P3") << " ";
	out << "P3" << " ";
	out << width << " " << height << " ";
	out << color_space << " ";

	//Write data

	/*if(use_binary) {
		//Binary write mode
		for (int x = 0; x < width; x++) for (int y = 0; y < height; y++) {
			Color c = pixel_at(x, y);
			//Print using 2-byte 565
			char r = (int)(c.r); if (is_illegal(r)) r--;
			char g = (int)(c.g); if (is_illegal(g)) g--;
			char b = (int)(c.b); if (is_illegal(b)) b--;
			out << r << g << b;
		}
	}
	else /**/{
		//ASCII write mode, uses more space but has unbounded maximum color space
		for (int x = 0; x < width; x++) for (int y = 0; y < height; y++) {
			Color& c = pixel_at(x, y);
			out << (int)(c.r) << " " << (int)(c.g) << " " << (int)(c.b) << " ";
		}
	}
}
