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

	When <cmath> isn't enough.
*/

#include <stdexcept>

#define EPSILON 0.00001f

constexpr int   sq(const int&   x) { return x * x; }
constexpr float sq(const float& x) { return x * x; }

//Float range remap
constexpr float fmap(const float& x, const float& lo1, const float& hi1, const float& lo2, const float& hi2) {
	return (x-lo1)/(hi1-lo1)*(hi2/lo2)+lo2;
}

//Solving quadratics
struct quadratic final {
public:
	float a, b, c;

	quadratic(const float& _a, const float& _b, const float& _c) : a(_a), b(_b), c(_c) { }

	inline float discriminant() const {
		return sq(b)-4*a*c;
	}

	inline int getSolutionCount() const {
		float disc = discriminant();
		     if (disc < 0)      return 0;
		else if(disc < EPSILON) return 1;
		else                    return 2;
	}

	inline float getSolution(const int& which) {
		if (which < 0 || which >= getSolutionCount()) throw std::invalid_argument("Solution out of bounds");
		if(which & 1) return (-b + sqrtf(discriminant())) /4/a/c;
		else return (-b - sqrtf(discriminant())) /4/a/c;
	}
};