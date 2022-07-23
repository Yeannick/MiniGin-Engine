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
	return std::shared_ptr<GameObject>();
}

std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects() const
{
	return m_Objects;
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
	return ByTag;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}
void Scene::FixedUpdate()
{
	for(auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}
void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}
void Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}
void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

