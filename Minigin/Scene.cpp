#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"



unsigned int Scene::m_IdCounter = 0;

std::shared_ptr<GameObject> Scene::GetGameObject(const std::string& tag) const
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->GetName() == tag)
		{
			return m_Objects[i];
		}
	}
	for (size_t i = 0; i < m_DefaultObjects.size(); i++)
	{
		if (m_DefaultObjects[i]->GetName() == tag)
		{
			return m_DefaultObjects[i];
		}
	}
	return std::shared_ptr<GameObject>();
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects() const
{
	return m_Objects;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetDefaultGameObjects() const
{
	return  m_DefaultObjects;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjectsByTag(const std::string& tag) const
{
	std::vector<std::shared_ptr<GameObject>> ByTag;

	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->GetName() == tag)
		{
			ByTag.push_back(m_Objects[i]);
		}
	}
	for (size_t i = 0; i < m_DefaultObjects.size(); i++)
	{
		if (m_DefaultObjects[i]->GetName() == tag)
		{
			ByTag.push_back(m_DefaultObjects[i]);
		}
	}
	return ByTag;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}
void Scene::AddDefault(const std::shared_ptr<GameObject>& object)
{
	m_DefaultObjects.push_back(object);
}

void Scene::Remove()
{
	for (auto& object : m_Objects)
	{
		object->MarkForDestruction();
	}
	for (auto& object : m_DefaultObjects)
	{
		object->MarkForDestruction();
	}
	m_IsMarkedDestroy = true;
}
void Scene::RemoveAll()
{
		m_Objects.clear();
}
void Scene::RemoveDefaults()
{
	for (auto& object : m_DefaultObjects)
	{
		object->MarkForDestruction();
	}
}

void Scene::FixedUpdate()
{
	for(auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
	for (auto& object : m_DefaultObjects)
	{
		object->FixedUpdate();
	}
}
void Scene::Update()
{
	//for(auto& object : m_Objects)
	//{
	//	
	//	object->Update(); /// ASK TEACHER 
	//	
	//}
	if (m_Objects.empty() && m_DefaultObjects.empty())
	{
		return;
	}
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
	}
	for (auto& object : m_DefaultObjects)
	{
		object->Update();
	}
}
void Scene::LateUpdate()
{
	
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
		if (m_Objects.empty() && m_DefaultObjects.empty())
		{
			return;
		}
	}
	if (m_Objects.empty() && m_DefaultObjects.empty())
	{
		return;
	}
	for (auto& object : m_DefaultObjects)
	{
		object->LateUpdate();
		if (m_Objects.empty() && m_DefaultObjects.empty())
		{
			return;
		}
	}
	for (auto& object : m_Objects)
	{
		if (object && object->IsMarkedForDestruction())
			m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
	}
	for (auto& object : m_DefaultObjects)
	{
		if (object && object->IsMarkedForDestruction())
			m_DefaultObjects.erase(std::remove(m_DefaultObjects.begin(), m_DefaultObjects.end(), object), m_DefaultObjects.end());
	}
}
void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();

	}
	for (const auto& object : m_DefaultObjects)
	{
		object->Render();
	}
}

