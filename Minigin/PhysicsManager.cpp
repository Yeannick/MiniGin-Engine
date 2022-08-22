#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include <algorithm>


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
