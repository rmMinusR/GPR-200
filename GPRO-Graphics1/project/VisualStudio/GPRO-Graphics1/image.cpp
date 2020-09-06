#include "image.hpp"

#include <stdexcept>

inline int image::ind(int x, int y) const
{
	if (x < 0 || x > width || y < 0 || y > height) throw std::invalid_argument("Index out of bounds!");
	return x+y*width;
}

image::image(int w, int h) : image(w, h, DEFAULT_COLOR_SPACE) {}

image::image(int w, int h, int c) : width(w), height(h), color_space(c), pixels(new Color[w * h])
{ }

image::~image()
{
	delete[] pixels; //Should ideally set pixels to nullptr, but that's not as important as pixels being const.
}
