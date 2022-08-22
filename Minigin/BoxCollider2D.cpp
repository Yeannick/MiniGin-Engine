#include "MiniginPCH.h"
#include "BoxCollider2D.h"
#include "GameObject.h"
#include "Renderer.h"

BoxCollider2D::BoxCollider2D(const std::weak_ptr<GameObject>& owner, int size):
	BaseComponent(owner),
	m_Collider({0,0,size,size})
{

}

BoxCollider2D::BoxCollider2D(const std::weak_ptr<GameObject>& owner, SDL_Rect rect):
	BaseComponent(owner),
	m_Collider(rect)
{
	
}

BoxCollider2D::BoxCollider2D(const std::weak_ptr<GameObject>& owner, int w, int h):
    BaseComponent(owner),
    m_Collider({ (int)owner.lock()->GetTransform().GetPosition().x,(int)owner.lock()->GetTransform().GetPosition().y,w,h })
{
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::FixedUpdate()
{
}

void BoxCollider2D::Update()

{
	
    m_Collider.x = static_cast<int>(m_Owner.lock()->GetTransform().GetPosition().x);
    m_Collider.y = static_cast<int>(m_Owner.lock()->GetTransform().GetPosition().y);
}

void BoxCollider2D::LateUpdate()
{
}

void BoxCollider2D::Render()
{
    /*const auto pos = m_Owner.lock()->GetTransform().GetPosition();
    const SDL_Rect colWorldPos{ static_cast<int>(m_Collider.x ),static_cast<int>(m_Collider.y ),m_Collider.w,m_Collider.h };
    Renderer::GetInstance().RenderRect(colWorldPos, m_DebugColor);*/
}

bool BoxCollider2D::IsOverlapping(const BoxCollider2D* box, bool ) const
{
	if (m_Owner.expired())
	{
		return false;
	}
	// Get This GO position and use this BoxCollider Rect
	const auto pos = m_Owner.lock()->GetTransform().GetPosition();
	const SDL_Rect PositionRect{ static_cast<int>(m_Collider.x ),static_cast<int>(m_Collider.y ),m_Collider.w,m_Collider.h }; // static cast to Int not float (no .5 pixel exist so int)
	// Get the Other GO (we want to check collision with) and get that Collider Rect 
	const auto otherObjPos = box->m_Owner.lock()->GetTransform().GetPosition();
	const SDL_Rect other = box->GetBoxCollider();
	const SDL_Rect OtherColliderPositionRect{ static_cast<int>(other.x ),static_cast<int>(other.y ),other.w,other.h };

	// use the points to check if collision and return
	
    if ((PositionRect.x + PositionRect.w) <= OtherColliderPositionRect.x || (OtherColliderPositionRect.x + OtherColliderPositionRect.w) <= PositionRect.x)
    {
        return false;
    }

    // If one rectangle is under the other
    if (PositionRect.y > (OtherColliderPositionRect.y + OtherColliderPositionRect.h) || OtherColliderPositionRect.y > (PositionRect.y + PositionRect.h))
    {
        return false;
    }

    return true;
	
}

bool BoxCollider2D::IsOverlapping(const BoxCollider2D* box, bool includeBorder, std::string name)
{
	return IsOverlapping(box,includeBorder) && box->m_Owner.lock()->GetName() == name; // 
}

bool BoxCollider2D::IsOverlapping(const BoxCollider2D* box, std::string name)
{
	return box->m_Owner.lock()->GetName() == name && IsOverlapping(box) ;
}

bool BoxCollider2D::IsPointInRect(const glm::vec3& point) const
{
	const glm::vec3 Pos = m_Owner.lock()->GetTransform().GetPosition();
	SDL_Rect rect{ static_cast<int>(m_Collider.x + Pos.x), static_cast<int>(m_Collider.y + Pos.y), m_Collider.w,m_Collider.h };
	if (point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y <= rect.y + rect.h)
		return true;
	return false;
}
