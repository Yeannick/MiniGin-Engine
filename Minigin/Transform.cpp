#include "MiniginPCH.h"
#include "Transform.h"

Transform::Transform() :
	m_Position{ 0.f,0.f,0.f },
	m_Scale{ 1.f,1.f },
	m_Rotation{ 0.f }
{
}
void Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

const float2& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(const float2& scale)
{
	m_Scale = scale;
}
float Transform::GetRotation()const
{
	return m_Rotation;
}
void Transform::SetRotation(float rotation)
{
	m_Rotation = rotation;
}