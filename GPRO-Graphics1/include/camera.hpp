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
	moremath.inl

	Pretty standard camera object. Cannot be transformed by a Matrix
	because I'm out of time.
*/

#include "ray.hpp"
#include "raytrace.hpp"
#include "color.hpp"
#include "image.hpp"

#define ATTR_SHORTCUTS
#include "attr.inl"

#include <vector>

class Camera final {
public:
	Image* viewport;

	float fov;

	//Uses *radians, not degrees*
	Camera(Image& viewport, const float& fov_radians);

	//Makes a ray from image coordinates
	inline Ray prepareTracer(const int& px_x, const int& px_y) const;

	//Render a vector of Traceable elements. THESE MUST BE ON THE HEAP
	//otherwise polymorphism will fail to take effect.
	void render(std::vector<Traceable*>) const;
};