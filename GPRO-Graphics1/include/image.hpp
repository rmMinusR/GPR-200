#pragma once

#include "color.hpp"

#include <ostream>

class Image final
{
private:
	Color* const pixels;

	inline int _ind(int x, int y) const;
	//Used only by binary output mode
	//static constexpr bool is_illegal(const char& c) { return c == 11; }

public:
	const int width;
	const int height;
	const float color_space;
	static constexpr int DEFAULT_COLOR_SPACE = 255;

	Image(const int& w, const int& h);
	Image(const int& w, const int& h, const float& c);
	
	~Image();

	inline Color& pixel_at(int x, int y) const { return pixels[_ind(x, y)]; }

	void write_to(std::ostream& out);
};

