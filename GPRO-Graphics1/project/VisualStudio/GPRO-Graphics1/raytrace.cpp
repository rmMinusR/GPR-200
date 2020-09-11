#include "raytrace.hpp"

#include "moremath.inl"

Sphere::Sphere(const Vector3& _position, const float& _radius) :
	_ltw(matrix::Translate(_position)), //Crappy way of doing this, but I don't have another (easy) option.
	radius(_radius)
{}

std::vector<trace_hit> Sphere::trace(const Ray& ray)
{
	std::vector<trace_hit> out;

	//Surprisingly, it's less time consuming to implement Matrices here and now
	//than it is to sum three trinomial squares then plug it into the quadratic
	//formula to find t.

	//Or so I thought at 2am. Anyway I have some notes in my notebook that I don't
	//feel like typing up, if you want to see them I'll post a screenshot.

	Ray local_ray = ray * (matrix)worldToLocal;
	Vector3& o = local_ray.origin;
	Vector3& d = local_ray.direction;

	quadratic solve_for_t(sq(d.x)+sq(d.y)+sq(d.z), 2*(o.x*d.x+o.y*d.y+o.z*d.z), sq(o.x)+sq(o.y)+sq(o.z)+sq(radius));

	//INTENTIONAL CASCADE OF PROGRAM FLOW
	switch (solve_for_t.getSolutionCount()) {
	case 2:
		{
			//Fetch solution #1 if it exists
			float t = solve_for_t.getSolution(1);
			if (t > 0) { //Prevent rendering stuff behind the camera!
				Vector3 s1 = local_ray.GetByT(t);
				out.push_back(trace_hit(s1, normal_at(s1), Color::FromRGB(1, 0, 0)));
			}
		}
	case 1:
		{
			//Fetch solution #0 if it exists
			float t = solve_for_t.getSolution(0);
			if (t > 0) { //Prevent rendering stuff behind the camera!
				Vector3 s0 = local_ray.GetByT(solve_for_t.getSolution(0));
				out.push_back(trace_hit(s0, normal_at(s0), Color::FromRGB(1, 0, 0)));
			}
		}
	}

	return out;
}

Vector3 Sphere::normal_at(const Vector3& pos)
{
	Vector3 pos_diff = pos - Vector3(_ltw(3, 0), _ltw(3, 1), _ltw(3, 2));
	return pos_diff.Normalize();
}