#include "vector.hpp"

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
	vector.cpp

	Defines the Vector3 class, which stores XYZ position. Works with all
	float3 operators, as well as providing vector-specific utility functions
	like dot, cross, magnitude and angle.

	Strongly based on:
	 - `Vector3` by myself, in `rm's Bukkit Common API` (private codebase available upon request)
	 - `Vector` by Unity Technologies
*/

#include <cmath>

Vector3::Vector3(const float& _x, const float& _y, const float& _z) : float3(_x, _y, _z), x{ val0 }, y{ val1 }, z{ val2 }
{ }

Vector3::Vector3(const float3& base) : float3(base), x{ val0 }, y{ val1 }, z{ val2 }
{ }

Vector3 Vector3::operator=(const float3& _rhs)
{
	//UNSAFE! But gives us access to internal values. Just don't try any
	//function calls, there's no telling what will happen.
	const Vector3* const rhs = reinterpret_cast<const Vector3* const>(&_rhs);

	this->val0 = rhs->val0;
	this->val1 = rhs->val1;
	this->val2 = rhs->val2;
	return *this;
}

Vector3 Vector3::operator=(const Vector3& rhs)
{
	this->val0 = rhs.val0;
	this->val1 = rhs.val1;
	this->val2 = rhs.val2;
	return *this;
}

float Vector3::GetMagnitude() const
{
	return sqrtf(x*x+y*y+z*z);
}

Vector3 Vector3::WithMagnitude(const float& m) const
{
	return (*this) * (m / GetMagnitude());
}

Vector3 Vector3::WithBoundedMagnitude(const float& min, const float& max) const
{
	return GetMagnitude() < min ? WithMagnitude(min) : (GetMagnitude() > max ? WithMagnitude(max) : Vector3(*this));
}

Vector3 Vector3::Normalize() const
{
	return (*this) / GetMagnitude();
}

float Vector3::Dot(const Vector3& other) const
{
	return x*other.x + y*other.y + z*other.z;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(
		this->y*other.z - this->z*other.y,
		this->z*other.x - this->x*other.z,
		this->x*other.y - this->y*other.x
	);
}

float Vector3::Angle(const Vector3& other) const
{
	//a dot b = |a|*|b| * cos(ang)
	//(a dot b) / (|a|*|b|) = cos(ang)
	//ang = acos( (a dot b) / (|a|*|b|)

	return acosf(this->Dot(other) / (this->GetMagnitude() * other.GetMagnitude()) );
}
