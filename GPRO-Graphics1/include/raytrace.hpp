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
	raytrace.hpp

	Toolset for actual raytracing. Defines trace_hit, Traceable, Sphere.
	NOTE: Anything inheriting from Traceable should usually be on the heap!
*/

#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include "color.hpp"

#define ATTR_SHORTCUTS
#include "attr.inl"

#include <vector>

struct trace_hit final {
public:
	Vector3 position;
	Vector3 normal;
	Color color;

	trace_hit(const Vector3& pos, const Vector3& nrm, const Color& color) : position{ pos }, normal{ nrm }, color{ color } { }
};

class Traceable {
public:
	virtual Vector3 normal_at(const Vector3& pos) = 0;
	virtual std::vector<trace_hit> trace(const Ray& ray) = 0;
};

class Sphere : public Traceable {
private:
	inline Sphere() : Sphere(Vector3::zero(), 1) {}

	matrix _ltw; //Probably overkill.
public:
	attr<matrix> localToWorld{&_ltw};
	attr<matrix> worldToLocal{&_ltw,
		attr_get(matrix) {
			return _state.Inverse();
		},
		attr_set(matrix) {
			_state = value.Inverse();
		}
	};

	float radius;

	Sphere(const Vector3& _position, const float& _radius);
	Sphere(const Sphere& cpy) = delete; //I could write this if I wanted to. Too bad I don't

	virtual std::vector<trace_hit> trace(const Ray& ray) override;
	virtual Vector3 normal_at(const Vector3& pos) override;
};