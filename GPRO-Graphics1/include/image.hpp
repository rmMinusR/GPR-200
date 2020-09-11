#pragma once

/*
	Copyright 2020 Robert S. Christensen

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	image.hpp

	Quick image class for ordered color manipulation and output.
*/

#include "color.hpp"

#define ATTR_SHORTCUTS
#include "attr.inl"

#include <ostream>

class Image final
{
private:
	//1D array dodges "pointer-to-pointer" badness
	Color* pixels;

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

	inline Color& pixel_at(int x, int y) const {
		return pixels[_ind(x, y)];
	}

	void write_to(std::ostream& out);
};

