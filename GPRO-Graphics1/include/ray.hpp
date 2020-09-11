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
	ray.hpp

	Defines the Ray class, which describes a Ray. Heavily based on
	`Line` by myself in `rm's Bukkit Common API` (private codebase
	available upon request)
*/

#include "vector.hpp"
#include "matrix.hpp"

struct Ray final {
public:
	Vector3 origin, direction;
	
	Ray() = default;
	inline Ray(const Vector3& _origin, const Vector3& _direction) : origin{ _origin }, direction{ _direction } {};

	inline Vector3 GetByT(const float& t) const { return origin + (t*direction); }
	inline Vector3 GetByDist(const float& d) const { return origin + direction.WithMagnitude(d); }

	inline Ray operator*(const matrix& mat) const { return Ray(mat.TransformPoint(origin), mat.TransformVector(direction)); }
};