#pragma once

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

	Camera(Image& viewport, const float& fov);

	inline Ray prepareTracer(const int& px_x, const int& px_y) const;

	//Render a vector of Traceable elements. THESE MUST BE ON THE HEAP
	//otherwise polymorphism will fail to take effect.
	void render(std::vector<Traceable*>) const;
};