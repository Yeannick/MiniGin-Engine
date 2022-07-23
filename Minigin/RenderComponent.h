#pragma once
#include "BaseComponent.h"
class RenderComponent : public BaseComponent
{
public :
	RenderComponent(const std::weak_ptr<GameObject>& owner, const float2& pivot, const float2& rotatePivot);
	virtual ~RenderComponent() = default;
	RenderComponent(const RenderComponent & other) = delete;
	RenderComponent(RenderComponent && other) = delete;
	RenderComponent& operator=(const RenderComponent & other) = delete;
	RenderComponent& operator=(RenderComponent && other) = delete;

	void SetPivot(const float2& pivot) { m_Pivot = pivot; }
	void SetRotationPivot(const float2& rotationpivot) { m_RotationPivot = rotationpivot; }

protected :

	bool m_NeedsUpdate = true;
	float2 m_Pivot;
	float2 m_RotationPivot;



};

