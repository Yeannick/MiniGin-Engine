#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::FixedUpdate()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->FixedUpdate();
	}
	/*for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}*/
}

void SceneManager::Update()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Update();
	}
	/*for(auto& scene : m_Scenes)
	{
		scene->Update();
	}*/
}

void SceneManager::LateUpdate()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->LateUpdate();
	}
	/*for (auto& scene : m_Scenes)
	{
		scene->LateUpdate();
	}*/
}

void SceneManager::Render()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Render();
	}
	/*for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}*/
}

//Scene& SceneManager::CreateScene(const std::string& name)
//{
//	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
//	m_Scenes.push_back(scene);
//	return *scene;
//}

void SceneManager::LoadScene(const std::string& name)
{
	
if (!m_LevelFunc.contains(name))
return;
const auto& scene = std::shared_ptr<Scene>(new Scene(name));
if (m_pActiveScene && m_LevelFunc[name].first) // .first holds boolean if the default needs to be hold
{
	const auto objects{ m_pActiveScene->GetDefaultGameObjects() };
	for (const auto& obj : objects)
	{
		scene->AddDefault(obj);
	}
}
m_LevelFunc[name].second(*scene);

m_pActiveScene = scene;

}

void SceneManager::SetSpawnLevelFunc(std::function<void(Scene&)> func, const std::string& LevelName, bool keepDefault)
{
	m_LevelFunc[LevelName] = std::pair(keepDefault, func);
}
