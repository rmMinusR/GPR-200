#include "rawdata.hpp"

#pragma region int3

//Data IO

int3::int3() : int3(0, 0, 0)
{ }

int3::int3(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
{ }

int3::int3(float _x, float _y, float _z) : int3((int)_x, (int)_y, (int)_z)
{ }

int3::int3(const int3& cpy) : x(cpy.x), y(cpy.y), z(cpy.z)
{ }

int3& int3::operator=(const int3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

int3& int3::operator+=(const int3& rhs) { return *this = *this + rhs; }
int3& int3::operator-=(const int3& rhs) { return *this = *this - rhs; }
int3& int3::operator*=(const float& rhs) { return *this = *this * rhs; }
int3& int3::operator/=(const float& rhs) { return *this = *this / rhs; }

//Math operators

inline int3 int3::operator+(const int3& rhs) const
{
	return int3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

inline int3 int3::operator-(const int3& rhs) const
{
	return int3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

inline int3 int3::operator*(const float& rhs) const
{
	return int3(this->x * rhs, this->y * rhs, this->z * rhs);
}

//Allows float*int3 as well
int3 operator*(const float& lhs, const int3& rhs) { return rhs * lhs; }

inline int3 int3::operator/(const float& rhs) const
{
	return int3(this->x / rhs, this->y / rhs, this->z / rhs);
}

#pragma endregion int3

#pragma region float3

//Data IO

float3::float3() : x(0), y(0), z(0)
{ }

float3::float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{ }

float3::float3(const float3& cpy) : x(cpy.x), y(cpy.y), z(cpy.z)
{ }

float3& float3::operator=(const float3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

float3& float3::operator+=(const float3& rhs) { return *this = *this + rhs; }
float3& float3::operator-=(const float3& rhs) { return *this = *this - rhs; }
float3& float3::operator*=(const float& rhs) { return *this = *this * rhs; }
float3& float3::operator/=(const float& rhs) { return *this = *this / rhs; }

//Math operators

inline float3 float3::operator+(const float3& rhs) const
{
	return float3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

inline float3 float3::operator-(const float3& rhs) const
{
	return float3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

inline float3 float3::operator*(const float& rhs) const
{
	return float3(this->x * rhs, this->y * rhs, this->z * rhs);
}

//Allows float*float3 as well
float3 operator*(const float& lhs, const float3& rhs) { return rhs * lhs; }

inline float3 float3::operator/(const float& rhs) const
{
	return float3(this->x / rhs, this->y / rhs, this->z / rhs);
}

#pragma endregion float3

#pragma region float4

//Data IO

float4::float4() : w(0), x(0), y(0), z(0)
{ }

float4::float4(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z)
{ }

float4::float4(const float4& cpy) : w(cpy.w), x(cpy.x), y(cpy.y), z(cpy.z)
{ }

float4& float4::operator=(const float4& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

float4& float4::operator+=(const float4& rhs) { return *this = *this + rhs; }
float4& float4::operator-=(const float4& rhs) { return *this = *this - rhs; }
float4& float4::operator*=(const float& rhs) { return *this = *this * rhs; }
float4& float4::operator/=(const float& rhs) { return *this = *this / rhs; }

//Math operators

inline float4 float4::operator+(const float4& rhs) const
{
	return float4(this->w+rhs.w, this->x+rhs.x, this->y+rhs.y, this->z+rhs.z);
}

inline float4 float4::operator-(const float4& rhs) const
{
	return float4(this->w-rhs.w, this->x-rhs.x, this->y-rhs.y, this->z-rhs.z);
}

inline float4 float4::operator*(const float& rhs) const
{
	return float4(this->w * rhs, this->x * rhs, this->y * rhs, this->z * rhs);
}

//Allows float*float4 as well
float4 operator*(const float& lhs, const float4& rhs) { return rhs * lhs; }

inline float4 float4::operator/(const float& rhs) const
{
	return float4(this->w / rhs, this->x / rhs, this->y / rhs, this->z / rhs);
}

#pragma endregion float4