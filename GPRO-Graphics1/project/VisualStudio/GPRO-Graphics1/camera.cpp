#include "camera.hpp"

#include <cmath>
#include "moremath.inl"

#include <vector>

Camera::Camera(const int& w, const int& h, const float& fov) :
	viewport_width{ w },
	viewport_height{ h },
	fov{ fov }
{ }

inline Ray Camera::prepareTracer(const int& px_x, const int& px_y) const
{
	float nrm_x = fmap((float)px_x, 0.0f, (float)viewport_width , -0.5f, 0.5f);
	float nrm_y = fmap((float)px_y, 0.0f, (float)viewport_height, -0.5f, 0.5f);
	
	float glob_x = tanf(fov*nrm_x);
	float glob_y = tanf(fov*nrm_y);

	return Ray(
		Vector3::zero(),
		Vector3(glob_x, glob_y, 0)
	);
}

Image Camera::render(std::vector<Traceable*> objects) const
{
	Image out(viewport_width, viewport_height);
	
	for (int x = 0; x < out.width; x++) for (int y = 0; y < out.height; y++) {
		Ray ray = prepareTracer(x, y);

		std::vector<trace_hit> all_hits;

		//Trace for all objects
		for (int i = 0; i < objects.size(); i++) {
			std::vector<trace_hit> cur_hits = objects[i]->trace(ray);
			//Copy all trace points into all_hits
			for (int j = 0; j < cur_hits.size(); j++) all_hits.push_back(cur_hits[i]);
		}

		if (all_hits.size() > 0) {
			trace_hit* closest = &all_hits[0];

			//Sort and find the trace_hit closest to the camera (occlusion)
			for (int i = 1; i < all_hits.size(); i++) {
				if (all_hits[i].position.GetMagnitude() < closest->position.GetMagnitude()) closest = &all_hits[i];
			}
			
			out.pixel_at(x, y) = closest->color;
		}
		else {
			Vector3 nrd = ray.direction.Normalize();
			out.pixel_at(x, y) = Color::FromRGB(nrd.x, nrd.y, nrd.z);
		}
	}

	return out;
}
