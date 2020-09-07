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
	color.hpp

	Defines the Color class, which can use 1.0 (normalized) colors
	and 255.0 (default serialized) color scales alike. Color can work with
	all float3 operators, as well as providing color-specific utility getters
	for properties like hue, saturation, and value.
*/

#include "rawdata.hpp"

//Really just a fancier interface sitting on top of a float3. Provides references
//for RGB, and also adds factory initializers and HSV utility methods.
struct Color final : public float3 {
public:
	float &r, &g, &b;

	//RGB factory initializer
	static Color FromRGB(const float& _r, const float& _g, const float& _b, const float& scale = 1);
	//HSV factory initializer. HSV will be clamped/wrapped to 0~1.
	static Color FromHSV(float h, float s, float v);

	float GetHue() const;
	float GetSaturation() const;
	float GetValue() const;

	inline float GetScale() const;
	inline void SetScale(float newScale); //Only changes scale.
	Color RemapScale(float newScale); //Changes scale, and remaps color values to match.

	Color& operator=(const float3& rhs);
	Color& operator=(const Color& rhs);

	//Cast conversion. Allows float3's operators to still work, including the mildly dangerous *=
	//Also allows unsafe, unchecked conversions between Color and Vector3.
	Color(const float3& base);

	//Copy constructor, because C++ implicitly deletes it otherwise.
	inline Color(const Color& cpy) : Color((const float3&)cpy) {}

	//Default constructor: Black, color scale = 1.0
	Color();
private:
	Color(const float& _r, const float& _g, const float& _b, const float& _scale = 1);

	float _scale; //Usually 1.0 for runtime colors, and 255.0 for serialized colors
};