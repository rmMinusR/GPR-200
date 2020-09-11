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
	int viewport_width;
	int viewport_height;

	readonly_attr<float> aspect_ratio{
		[this](float& state) -> float {
			return float(viewport_height)/viewport_width;
		}
	};

	float fov;

	Camera(const int& w, const int& h, const float& fov);

	inline Ray prepareTracer(const int& px_x, const int& px_y) const;

	//Render a vector of Traceable elements. THESE MUST BE ON THE HEAP
	//otherwise polymorphism will fail to take effect.
	Image render(std::vector<Traceable*>) const;
};