#include "MiniginPCH.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(const std::weak_ptr<GameObject>& owner, const float2& pivot, const float2& rotatePivot):
BaseComponent(owner),
m_Pivot(pivot),
m_RotationPivot(rotatePivot)
{
}
