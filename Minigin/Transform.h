#pragma once
#include "DataTypes.h"
#include "glm/glm.hpp"
	class Transform final
	{
	public:
		Transform();

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetPosition(float x, float y, float z);
		void SetLocalPosition(float x, float y, float z);

		const float2& GetScale() const;
		void SetScale(const float2& scale);

		float GetRotation() const;
		void SetRotation(float rotation);
	private:
		void UpdateWorldPosition();

		glm::vec3 m_Position;
		glm::vec3 m_LocalPosition;
		float2 m_Scale = {1.f,1.f};
		float m_Rotation = 0.f;
		bool m_PositionIsDirty = false;
	};
