#pragma once
#include "DataTypes.h"
	class Transform final
	{
	public:
		Transform();

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		const float2& GetScale() const;
		void SetScale(const float2& scale);

		float GetRotation() const;
		void SetRotation(float rotation);
	private:
		glm::vec3 m_Position;
		float2 m_Scale;
		float m_Rotation;
	};
