#pragma once

struct float2
{
	float x, y;

	float2 operator+= (float2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}
}; 
struct float3
{
	float x, y, z;
};
struct float4
{
	float x, y, z, w;
};