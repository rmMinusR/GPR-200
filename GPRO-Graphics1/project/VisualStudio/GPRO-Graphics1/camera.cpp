#include "camera.hpp"

#include <cmath>
#include "moremath.inl"

#include <vector>
#include <iostream>
#include <iomanip> /* setprecision */

Camera::Camera(Image& viewport, const float& fov) :
	viewport{ &viewport },
	fov{ fov }
{ }

inline Ray Camera::prepareTracer(const int& px_x, const int& px_y) const
{
	float nrm_x = fmap((float)px_x, 0.0f, (float)viewport->width , -0.5f, 0.5f);
	float nrm_y = fmap((float)px_y, 0.0f, (float)viewport->height, -0.5f, 0.5f);
	
	float glob_x = tanf(fov*nrm_x);
	float glob_y = tanf(fov*nrm_y);

	return Ray(
		Vector3::zero(),
		Vector3(glob_x, glob_y, 0)
	);
}

void Camera::render(std::vector<Traceable*> objects) const
{
	std::vector<trace_hit> all_hits; //Reset between traces
	for (int y = 0; y < viewport->height; y++) {
		//Show a progress bar of sorts
		std::cout << std::setprecision(2) << y/float(viewport->height)*100 << "% ... ";

		for (int x = 0; x < viewport->width; x++) {
			Ray ray = prepareTracer(x, y);

			/*
			//Trace for all objects
			for (int i = 0; i < objects.size(); i++) {
				std::vector<trace_hit> cur_hits = objects[i]->trace(ray);
				//Copy all trace points into all_hits
				for (int j = 0; j < cur_hits.size(); j++) all_hits.push_back(cur_hits[i]);
			}
			*/
			all_hits = objects[0]->trace(ray);
			
			//*
			if (all_hits.size() > 0) {
				trace_hit* closest = &all_hits[0];

				//Sort and find the trace_hit closest to the camera (occlusion)
				for (int i = 1; i < all_hits.size(); i++) {
					if (all_hits[i].position.GetMagnitude() < closest->position.GetMagnitude()) closest = &all_hits[i];
				}

				viewport->pixel_at(x, y) = closest->color;
			}
			else {
				//Ray hit nothing, fill with sky
				Color sky = Color::FromRGB(0, fmap(float(y), 0, float(viewport->height), 0, 1), 1);
				viewport->pixel_at(x, y) = sky;
			}
			// */

			//if (all_hits.size() == 2) viewport->pixel_at(x, y) = Color::FromRGB(  0,   0, 255, 255);
			//if (all_hits.size() == 1) viewport->pixel_at(x, y) = Color::FromRGB(  0, 255,   0, 255);
			//if (all_hits.size() == 0) viewport->pixel_at(x, y) = Color::FromRGB(255,   0,   0, 255);

			all_hits.clear();
		}
	}
}
