#pragma once

#include "rawdata.hpp"

using color = float3; //TODO make actual color class, sitting on top of polyfloat

class image
{
private:
	color* const pixels;

	inline int ind(int x, int y) const;

public:
	const int width;
	const int height;
	const int color_space;
	static constexpr int DEFAULT_COLOR_SPACE = 255;

	image(int w, int h);
	image(int w, int h, int c);
	
	~image();

	inline color& pixel_at(int x, int y) const { return pixels[ind(x, y)]; }

};

