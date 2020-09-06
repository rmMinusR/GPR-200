#pragma once

#include "rawdata.hpp"

//Really just a fancier interface sitting on top of a float3. Provides references
//for RGB, and also adds factory initializers and HSV utility methods.
struct Color final : public float3 {
public:
	float &r, &g, &b;

	//Factory initializers
	static Color FromRGB(const float& _r, const float& _g, const float& _b, const float& scale = 1);
	static Color FromHSV(const float& _r, const float& _g, const float& _b, const float& scale = 1);

	float GetHue() const;
	float GetSaturation() const;
	float GetValue() const;

	void SetScale(float newScale); //Only changes scale.
	void RemapScale(float newScale); //Changes scale, and remaps color values to match.

	//Cast conversion. Allows float3's operators to still work. Also allows (dangerous) conversions between Color and Vector3.
	Color(const float3& base); 

	//Default constructor: Black, color scale = 1.0
	Color();
private:
	Color(const float& _r, const float& _g, const float& _b, const float& _scale);

	float scale; //Usually 1.0 for runtime colors, and 255.0 for serialized colors
};