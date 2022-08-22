#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <string>
enum class RectSide 
{
	Left,Right,Top,Bottom
};
class BoxCollider2D final : public BaseComponent
{
public:
	BoxCollider2D(const std::weak_ptr<GameObject>& owner, int size);
	BoxCollider2D(const std::weak_ptr<GameObject>& owner , SDL_Rect rect);
	BoxCollider2D(const std::weak_ptr<GameObject>& owner , int w , int h);
	~BoxCollider2D() override;

	BoxCollider2D(const BoxCollider2D& other) = delete;
	BoxCollider2D(BoxCollider2D&& other) noexcept = delete;
	BoxCollider2D& operator=(const BoxCollider2D& other) = delete;
	BoxCollider2D& operator=(BoxCollider2D&& other) noexcept = delete;

	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	bool IsOverlapping(const BoxCollider2D* box, bool includeBorder = false)const;
	bool IsOverlapping(const BoxCollider2D* box, bool includeBorder , std::string name);
	bool IsOverlapping(const BoxCollider2D* box, std::string name);


	bool IsPointInRect(const glm::vec3& point)const;

	SDL_Point GetCenter() const { return { m_Collider.x + m_Collider.w / 2, m_Collider.y + m_Collider.h / 2 }; }
	SDL_Rect GetBoxCollider() const { return m_Collider; }
	void SetBoxCollider(SDL_Rect col) { m_Collider = col; }
	void SetColor(const SDL_Color& color) { m_DebugColor = color; }

	std::shared_ptr<GameObject> GetGameObject() { return m_Owner.lock(); }
private:
	SDL_Rect m_Collider{};
	SDL_Color m_DebugColor{ 0,255,0,1 };
};

