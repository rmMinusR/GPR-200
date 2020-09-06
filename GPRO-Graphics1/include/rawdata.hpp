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
	rawdata.h
	Contains basic boilerplate data types such as float4 and int3.
	These are vaguely based on:
	 - `vec3` by Dan Buckstein in his starter framework.
	 - `vec3` by Peter Shirley in `Ray Tracing in One Weekend`
	 - `Vector3` by myself, in `rm's Bukkit Common API` (private codebase available upon request)
	 - `Vector` by Unity Technologies
*/

#include "pointlesskw.h"

//TODO add int2, float2

struct float3;

//Used primarily for RGB color data.
struct int3 {
protected:
	//Member variables
	int x, y, z;

	explicit int3(); //Zero ctor
	explicit int3(int _x, int _y, int _z); //Component ctor
	explicit int3(float _x, float _y, float _z); //Conversion-component ctor
	implicit int3(const int3& cpy); //Copy ctor

public:
	inline int3 operator+(const int3& rhs) const;
	inline int3 operator-(const int3& rhs) const;
	inline int3 operator*(const float& rhs) const; //Mul by scalar
	friend int3 operator*(const float& lhs, const int3& rhs); //Mul by scalar backwards (calls int3*float)
	inline int3 operator/(const float& rhs) const;

	int3& operator=(const int3& rhs);
	int3& operator+=(const int3& rhs);
	int3& operator-=(const int3& rhs);
	int3& operator*=(const float& rhs);
	int3& operator/=(const float& rhs);

};

//Used primarily for vectors in Euclidean space, and fresh RGB color data.
struct float3 {
protected:
	//Member variables
	float x, y, z;

	explicit float3(); //Zero ctor
	explicit float3(float _x, float _y, float _z); //Component ctor
	implicit float3(const float3& cpy); //Copy ctor

public:
	inline float3 operator+(const float3& rhs) const;
	inline float3 operator-(const float3& rhs) const;
	inline float3 operator*(const float& rhs) const; //Mul by scalar
	friend float3 operator*(const float& lhs, const float3& rhs); //Mul by scalar backwards (calls float3*float)
	inline float3 operator/(const float& rhs) const;

	float3& operator=(const float3& rhs);
	float3& operator+=(const float3& rhs);
	float3& operator-=(const float3& rhs);
	float3& operator*=(const float& rhs);
	float3& operator/=(const float& rhs);

};

//Used primarily for quaternion rotations, and fresh RGBA color data.
struct float4 {
protected:
	//Member variables
	float w, x, y, z;

	explicit float4(); //Zero ctor
	explicit float4(float _w, float _x, float _y, float _z); //Component ctor
	implicit float4(const float4& cpy); //Copy ctor

public:
	inline float4 operator+(const float4& rhs) const;
	inline float4 operator-(const float4& rhs) const;
	inline float4 operator*(const float& rhs) const; //Mul by scalar
	friend float4 operator*(const float& lhs, const float4& rhs); //Mul by scalar backwards (calls float4*float)
	inline float4 operator/(const float& rhs) const;

	float4& operator=(const float4& rhs);
	float4& operator+=(const float4& rhs);
	float4& operator-=(const float4& rhs);
	float4& operator*=(const float& rhs);
	float4& operator/=(const float& rhs);

};