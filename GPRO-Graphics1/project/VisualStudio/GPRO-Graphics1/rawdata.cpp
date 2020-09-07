#include "rawdata.hpp"

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
	rawdata.cpp

	Contains basic boilerplate data types such as float4 and int3. All member
	variables are given deliberately vague names, which are accessed by
	reference as RGB or XYZ in children.

	These are loosely based on:
	 - `vec3` by Dan Buckstein in his starter framework
	 - `vec3` by Peter Shirley in `Ray Tracing in One Weekend`
	 - `Vector3` by myself, in `rm's Bukkit Common API` (private codebase available upon request)
	 - `Vector` and `Quaternion` by Unity Technologies
*/

#pragma region int3

//Data IO

int3::int3() : int3(0, 0, 0)
{ }

int3::int3(int _x, int _y, int _z) : val0(_x), val1(_y), val2(_z)
{ }

int3::int3(float _x, float _y, float _z) : int3((int)_x, (int)_y, (int)_z)
{ }

int3::int3(const int3& cpy) : val0(cpy.val0), val1(cpy.val1), val2(cpy.val2)
{ }

int3& int3::operator=(const int3& rhs)
{
	this->val0 = rhs.val0;
	this->val1 = rhs.val1;
	this->val2 = rhs.val2;
	return *this;
}

int3& int3::operator+=(const int3& rhs) { return *this = *this + rhs; }
int3& int3::operator-=(const int3& rhs) { return *this = *this - rhs; }
int3& int3::operator*=(const float& rhs) { return *this = *this * rhs; }
int3& int3::operator/=(const float& rhs) { return *this = *this / rhs; }

//Math operators

inline int3 int3::operator+(const int3& rhs) const
{
	return int3(this->val0 + rhs.val0, this->val1 + rhs.val1, this->val2 + rhs.val2);
}

inline int3 int3::operator-(const int3& rhs) const
{
	return int3(this->val0 - rhs.val0, this->val1 - rhs.val1, this->val2 - rhs.val2);
}

inline int3 int3::operator*(const float& rhs) const
{
	return int3(this->val0 * rhs, this->val1 * rhs, this->val2 * rhs);
}

//Allows float*int3 as well
int3 operator*(const float& lhs, const int3& rhs) { return rhs * lhs; }

inline int3 int3::operator/(const float& rhs) const
{
	return int3(this->val0 / rhs, this->val1 / rhs, this->val2 / rhs);
}

#pragma endregion int3

#pragma region float3

//Data IO

float3::float3() : val0(0), val1(0), val2(0)
{ }

float3::float3(float _x, float _y, float _z) : val0(_x), val1(_y), val2(_z)
{ }

float3::float3(const float3& cpy) : val0(cpy.val0), val1(cpy.val1), val2(cpy.val2)
{ }

float3& float3::operator=(const float3& rhs)
{
	this->val0 = rhs.val0;
	this->val1 = rhs.val1;
	this->val2 = rhs.val2;
	return *this;
}

float3& float3::operator+=(const float3& rhs) { return *this = *this + rhs; }
float3& float3::operator-=(const float3& rhs) { return *this = *this - rhs; }
float3& float3::operator*=(const float& rhs) { return *this = *this * rhs; }
float3& float3::operator/=(const float& rhs) { return *this = *this / rhs; }

//Math operators

inline float3 float3::operator-() const
{
	return float3(-val0, -val1, -val2);
}

inline float3 float3::operator+(const float3& rhs) const
{
	return float3(this->val0 + rhs.val0, this->val1 + rhs.val1, this->val2 + rhs.val2);
}

inline float3 float3::operator-(const float3& rhs) const
{
	return float3(this->val0 - rhs.val0, this->val1 - rhs.val1, this->val2 - rhs.val2);
}

inline float3 float3::operator*(const float& rhs) const
{
	return float3(this->val0 * rhs, this->val1 * rhs, this->val2 * rhs);
}

//Allows float*float3 as well
float3 operator*(const float& lhs, const float3& rhs) { return rhs * lhs; }

inline float3 float3::operator/(const float& rhs) const
{
	return float3(this->val0 / rhs, this->val1 / rhs, this->val2 / rhs);
}

#pragma endregion float3

#pragma region float4

//Data IO

float4::float4() : val0(0), val1(0), val2(0), val3(0)
{ }

float4::float4(float _w, float _x, float _y, float _z) : val0(_w), val1(_x), val2(_y), val3(_z)
{ }

float4::float4(const float4& cpy) : val0(cpy.val0), val1(cpy.val1), val2(cpy.val2), val3(cpy.val3)
{ }

float4& float4::operator=(const float4& rhs)
{
	this->val1 = rhs.val1;
	this->val2 = rhs.val2;
	this->val3 = rhs.val3;
	return *this;
}

float4& float4::operator+=(const float4& rhs) { return *this = *this + rhs; }
float4& float4::operator-=(const float4& rhs) { return *this = *this - rhs; }
float4& float4::operator*=(const float& rhs) { return *this = *this * rhs; }
float4& float4::operator/=(const float& rhs) { return *this = *this / rhs; }

//Math operators

inline float4 float4::operator+(const float4& rhs) const
{
	return float4(this->val0+rhs.val0, this->val1+rhs.val1, this->val2+rhs.val2, this->val3+rhs.val3);
}

inline float4 float4::operator-(const float4& rhs) const
{
	return float4(this->val0-rhs.val0, this->val1-rhs.val1, this->val2-rhs.val2, this->val3-rhs.val3);
}

inline float4 float4::operator*(const float& rhs) const
{
	return float4(this->val0 * rhs, this->val1 * rhs, this->val2 * rhs, this->val3 * rhs);
}

//Allows float*float4 as well
float4 operator*(const float& lhs, const float4& rhs) { return rhs * lhs; }

inline float4 float4::operator/(const float& rhs) const
{
	return float4(this->val0 / rhs, this->val1 / rhs, this->val2 / rhs, this->val3 / rhs);
}

#pragma endregion float4