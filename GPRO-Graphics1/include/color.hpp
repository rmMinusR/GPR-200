#pragma once

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

	//Cast conversion. Allows float3's operators to still work, including the mildly dangerous *=
	//Also allows unsafe, unchecked conversions between Color and Vector3.
	Color(const float3& base);

	//Default constructor: Black, color scale = 1.0
	Color();
private:
	Color(const float& _r, const float& _g, const float& _b, const float& _scale = 1);

	float _scale; //Usually 1.0 for runtime colors, and 255.0 for serialized colors
};