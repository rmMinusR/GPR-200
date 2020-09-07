#include "color.hpp"

#include <cmath>

//TODO move to separate file
//Boilerplate linear interpolate
constexpr float Lerp(const float& a, const float& b, const float& t) {
	return (1-t)*b + t*a;
}

constexpr float Clamp01(const float& x) {
	return (x>1)?1:( (x<0)?0:x );
}

float Wrap01(float x) {
		 if (x > 1) while (x > 1) x--;
	else if (x < 0) while (x < 0) x++;
	return x;
}

#ifndef PI
#define PI 3.14159265f
#endif

Color Color::FromRGB(const float& _r, const float& _g, const float& _b, const float& scale)
{
	return Color(_r, _g, _b, scale);
}

Color Color::FromHSV(float h, float s, float v)
{
	//Arg normalization
	h = Wrap01(h);
	s = Clamp01(s);
	v = Clamp01(v);

	//From first principles.
	
	//Hue:
	//r = 1-Clamp01( 2-|6(h-1/2)| ) //Easier than wrapping the equation...
	//g =   Clamp01( 2-|6(h-1/3)| )
	//b =   Clamp01( 2-|6(h-2/3)| )

	float r = 1-Clamp01( 2-abs(6*(h-1/2.0f)) );
	float g =   Clamp01( 2-abs(6*(h-1/3.0f)) );
	float b =   Clamp01( 2-abs(6*(h-2/3.0f)) );

	//Saturation:
	//x = 1-s+s*x

	r = 1-s + s*r;
	g = 1-s + s*g;
	b = 1-s + s*b;

	//Value:
	r *= v;
	g *= v;
	b *= v;

	return Color(r, g, b, 1);
}

float Color::GetHue() const
{
	//From first principles.
	float hi = GetValue();
	float lo = 1-GetSaturation();
	Color tmp = (*this-Color(lo,lo,lo))/(hi-lo); //Remap color to be hue-pure

	//Piecewise find hue. Inefficient and messy.

	       if(tmp.r==tmp.GetValue() && tmp.g > 0) {
		//0/6 <= h < 1/6
		return (tmp.g / tmp.r + 0) / 6;

	} else if(tmp.g==tmp.GetValue() && tmp.r > 0) {
		//1/6 <= h < 2/6
		return (tmp.r / tmp.g + 1) / 6;

	} else if(tmp.g==tmp.GetValue() && tmp.b > 0) {
		//2/6 <= h < 3/6
		return (tmp.b / tmp.g + 2) / 6;

	} else if(tmp.b==tmp.GetValue() && tmp.g > 0) {
		//3/6 <= h < 4/6
		return (tmp.g / tmp.b + 3) / 6;

	} else if(tmp.b==tmp.GetValue() && tmp.r > 0) {
		//4/6 <= h < 5/6
		return (tmp.r / tmp.b + 4) / 6;

	} else {// if(tmp.r==tmp.GetValue() && tmp.b > 0) {
		//5/6 <= h < 6/6
		return (tmp.b / tmp.r + 5) / 6;
	}
}

float Color::GetSaturation() const
{
	float least = r;
	if (least > g) least = g;
	if (least > b) least = b;
	return 1-least;
}

float Color::GetValue() const
{
	float most = r;
	if (most < g) most = g;
	if (most < b) most = b;
	return most;
}

inline float Color::GetScale() const
{
	return _scale;
}

inline void Color::SetScale(float newScale)
{
	_scale = newScale;
}

Color Color::RemapScale(float newScale)
{
	float rescaleFactor = newScale * _scale;
	return Color(r*rescaleFactor, g*rescaleFactor, b*rescaleFactor, newScale); //Stack-allocated. TODO Is this OK?
} 

Color::Color(const float3& base) : float3(base), r{ x }, g{ y }, b{ z }, _scale{ 1.0 }
{ }

Color::Color() : Color(0, 0, 0, 1)
{ }

Color::Color(const float& _r, const float &_g, const float& _b, const float& _scale) : float3(_r, _g, _b), r{ x }, g{ y }, b{ z }, _scale{ _scale }
{ }