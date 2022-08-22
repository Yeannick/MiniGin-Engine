#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include <algorithm>

Ray PhysicsManager::RayCast(const glm::vec3& startPosition, const glm::vec3& direction, GameObject* pGO, const int maxDistance)
{
    const auto Direction = glm::normalize(direction);

    Ray ray = Ray(Direction, maxDistance);
    ray.HitPoint = startPosition;

    std::vector<BoxCollider2D*> colliders;

    if (pGO)
    {
        std::vector<GameObject*> objects{ pGO };
		size_t checkedCount= 0 ;

		while (objects.size() == checkedCount)
		{
			for (const auto& obj : objects)
			{
				if (obj->GetChildCount() != 0)
				{
					const auto children{ obj->GetChildren() };
					for (const auto& child : children)
					{
						objects.emplace_back(child);
					}
				}
				++checkedCount;
			}
		}
		for (const auto& obj : objects)
		{
			const auto BoxComp = obj->GetComponent<BoxCollider2D>();
			if (BoxComp.lock())
				colliders.push_back(BoxComp.lock().get());
		}
	}


	while (ray.MaxDistance >= glm::distance(ray.HitPoint, startPosition))
	{
		ray.HitPoint += Direction;
		for (const auto& col : m_BoxColliders)
		{
			if (IsPointInRect(col, colliders, ray.HitPoint))
			{
				ray.Distance = glm::distance(ray.HitPoint, startPosition);
				ray.pHitObject = col->GetGameObject().get();

				return ray;
			}
		}
	}
	return ray;
}

void PhysicsManager::AddBoxCollider2D(std::shared_ptr<BoxCollider2D> box)
{
	m_BoxColliders.push_back(box);
}

void PhysicsManager::RemoveBoxCollider2D(std::shared_ptr<BoxCollider2D> box)
{
	for (size_t i = 0; i < m_BoxColliders.size(); ++i)
	{
		if (m_BoxColliders.at(i) == box)
		{
			m_BoxColliders.erase(m_BoxColliders.begin() + i);
			return;
		}
	}
}

bool PhysicsManager::IsOverlapping(std::shared_ptr<BoxCollider2D> box, bool includeBorders)
{
	for (const std::shared_ptr<BoxCollider2D> box2d : m_BoxColliders)
	{
		if (box2d == box)
		{
			continue;
		}
		if (box2d->IsOverlapping(box.get(), includeBorders))
		{
			return true;
		}
	}
    return false;
}

bool PhysicsManager::IsOverlapping(std::shared_ptr<BoxCollider2D> box, bool includeBorders, std::string Name)
{
	for (const std::shared_ptr<BoxCollider2D> box2d : m_BoxColliders)
	{
		if (box2d == box)
		{
			continue;
		}
		if (box2d->IsOverlapping(box.get(),includeBorders ,Name))
		{
			return true;
		}
	}
	return false;
}

bool PhysicsManager::IsOverlapping(std::shared_ptr<BoxCollider2D> box, std::string Name)
{
	std::string name = Name;
	std::vector<std::shared_ptr<BoxCollider2D>>::iterator it = std::find_if(m_BoxColliders.begin(), m_BoxColliders.end(), [name](const std::shared_ptr<BoxCollider2D>& b)
		{

			return b->GetGameObject()->GetName() == name;
		});

	
	for (const std::shared_ptr<BoxCollider2D> box2d : m_BoxColliders)
	{
		if (box2d == *it)
		{
			return box2d->IsOverlapping(box.get());
		}
		/*if (box2d == box)
		{
			continue;
		}
		if (box2d->IsOverlapping(box.get(), Name))
		{
			return true;
		}*/
	}
	return false;
}

std::vector<BoxCollider2D*> PhysicsManager::GetColliders(std::string name) const
{
	std::vector<BoxCollider2D*> colliders;

	for (const std::shared_ptr<BoxCollider2D> Col : m_BoxColliders)
	{
		if (Col->GetGameObject()->GetName() == name)
		{
			colliders.push_back(Col.get());
		}
	}
	return colliders;
}

std::vector<BoxCollider2D*> PhysicsManager::GetOverlappers(BoxCollider2D* box, bool includeBorders) const
{
	std::vector<BoxCollider2D*> colliders;

	for (const std::shared_ptr<BoxCollider2D> Col : m_BoxColliders)
	{
		if (Col.get() == box)
		{
			continue;
		}
		if (Col->IsOverlapping(box,includeBorders))
		{
			colliders.push_back(Col.get());
		}
	}
	return colliders;
}

std::vector<BoxCollider2D*> PhysicsManager::GetOverlappers(BoxCollider2D* box, bool includeBorders, std::string name) const
{
	std::vector<BoxCollider2D*> colliders;

	for (const std::shared_ptr<BoxCollider2D> Col : m_BoxColliders)
	{
		if (Col.get() == box)
		{
			continue;
		}
		if (Col->IsOverlapping(box, includeBorders,name))
		{
			colliders.push_back(Col.get());
		}
	}
	return colliders;
}

std::vector<BoxCollider2D*> PhysicsManager::GetOverlappers(BoxCollider2D* box, std::string name) const
{
	std::vector<BoxCollider2D*> colliders;

	for (const std::shared_ptr<BoxCollider2D> Col : m_BoxColliders)
	{
		if (Col.get() == box)
		{
			continue;
		}
		if (Col->IsOverlapping(box, name))
		{
			colliders.push_back(Col.get());
		}
	}
	return colliders;
}

bool PhysicsManager::IsPointInRect(std::shared_ptr<BoxCollider2D> box, const std::vector<BoxCollider2D*>& cols, glm::vec3 point) const
{
	for (const auto& box2d : cols)
	{
		if ( box2d == box.get())
		{
			return false;
		}

	}
	return box->IsPointInRect(point);
	
}
