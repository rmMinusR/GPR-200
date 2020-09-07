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
	vector.hpp

	Defines the Vector3 class, which stores XYZ position. Works with all
	float3 operators, as well as providing vector-specific utility functions
	like dot, cross, magnitude and angle.

	Strongly based on:
	 - `Vector3` by myself, in `rm's Bukkit Common API` (private codebase available upon request)
	 - `Vector` by Unity Technologies
*/

#include "rawdata.hpp"

//Fancy interface sitting on top of a float3.
//Provides vector math utility functions.
struct Vector3 final : public float3 {
public:
	float &x, &y, &z;

	//Main constructor that should be used wherever possible.
	Vector3(const float& _x, const float& _y, const float& _z);
	
	//Quick-reference shortcuts
	inline static const Vector3    zero() { return Vector3(0, 0, 0); }
	inline static const Vector3     one() { return Vector3(1, 1, 1); }

	inline static const Vector3   right() { return Vector3( 1,  0,  0); }
	inline static const Vector3    left() { return Vector3(-1,  0,  0); }
	inline static const Vector3      up() { return Vector3( 0,  1,  0); }
	inline static const Vector3    down() { return Vector3( 0, -1,  0); }
	inline static const Vector3 forward() { return Vector3( 0,  0,  1); }
	inline static const Vector3    back() { return Vector3( 0,  0, -1); }

	//Mostly for array initialization. Should not be used.
	inline Vector3() : Vector3(0,0,0) {}

	//Cast conversion. Allows float3's operators to still work, including the mildly dangerous *=
	//Also allows unsafe, unchecked conversions between Color and Vector3.
	Vector3(const float3& base);
	
	//Copy constructor, because C++ implicitly deletes it otherwise.
	inline Vector3(const Vector3& cpy) : Vector3((const float3&)cpy) {}

	//Make it behave like Unity's Vector3's operator=
	Vector3 operator=(const float3& rhs);
	Vector3 operator=(const Vector3& rhs);

	//Pythagorean
	float GetMagnitude() const;
	Vector3 WithMagnitude(const float& m) const;
	Vector3 WithBoundedMagnitude(const float& min, const float& max) const;
	Vector3 Normalize() const;

	//Trigonometry
	float Dot(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;
	float Angle(const Vector3& other) const;
};