#pragma once
#include "DataTypes.h"
#include "Singleton.h"
#include "BoxCollider2D.h"



struct Ray
{
	glm::vec3 Direction{ 0,0,0 };
	glm::vec3 HitPoint{ 0,0,0 };
	float Distance = 0;

	GameObject* pHitObject = nullptr;
	int MaxDistance = 1000;

	Ray() = default;
	Ray(const glm::vec3 direction, int maxDist) :Direction{ direction }, MaxDistance(maxDist){}
};

class PhysicsManager final : public Singleton<PhysicsManager>
{
	~PhysicsManager() override = default;

	PhysicsManager(const PhysicsManager& other) = delete;
	PhysicsManager(PhysicsManager&& other) noexcept = delete;
	PhysicsManager& operator=(const PhysicsManager& other) = delete;
	PhysicsManager& operator=(PhysicsManager&& other) noexcept = delete;

public:
	Ray RayCast(const glm::vec3& startPosition, const glm::vec3& direction, GameObject* pGO = nullptr, const int maxDistance = INT_MAX);

	void AddBoxCollider2D(std::shared_ptr<BoxCollider2D> box);
	void RemoveBoxCollider2D(std::shared_ptr<BoxCollider2D> box);

	bool IsOverlapping(std::shared_ptr<BoxCollider2D> box, bool includeBorders);
	bool IsOverlapping(std::shared_ptr<BoxCollider2D> box, bool includeBorders , std::string Name);
	bool IsOverlapping(std::shared_ptr<BoxCollider2D> box, std::string Name);

	std::vector<BoxCollider2D*> GetColliders(std::string name)const;
	std::vector<BoxCollider2D*> GetOverlappers(BoxCollider2D* box, bool includeBorders = false) const;
	std::vector<BoxCollider2D*> GetOverlappers(BoxCollider2D* box, bool includeBorders , std::string name) const;
	std::vector<BoxCollider2D*> GetOverlappers(BoxCollider2D* box, std::string name) const;

private:
	friend class Singleton<PhysicsManager>;
	PhysicsManager() = default;

	std::vector<std::shared_ptr<BoxCollider2D>> m_BoxColliders;

	bool IsPointInRect(std::shared_ptr<BoxCollider2D> box, const std::vector<BoxCollider2D*>& cols, glm::vec3 point)const;
};