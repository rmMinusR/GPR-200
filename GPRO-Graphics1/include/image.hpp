#pragma once

#include "color.hpp"

class image
{
private:
	Color* const pixels;

	inline int ind(int x, int y) const;

public:
	const int width;
	const int height;
	const int color_space;
	static constexpr int DEFAULT_COLOR_SPACE = 255;

	image(int w, int h);
	image(int w, int h, int c);
	
	~image();

	inline Color& pixel_at(int x, int y) const { return pixels[ind(x, y)]; }

};

