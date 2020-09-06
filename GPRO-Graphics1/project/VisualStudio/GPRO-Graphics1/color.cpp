#include "color.hpp"

Color::Color(const float3& base) : float3(base), r{ x }, g{ y }, b{ z }, scale{ 1.0 }
{ }

Color::Color() : Color(0, 0, 0, 1)
{ }

Color::Color(const float& _r, const float &_g, const float& _b, const float& _scale) : float3(_r, _g, _b), r{ x }, g{ y }, b{ z }, scale{ _scale }
{ }