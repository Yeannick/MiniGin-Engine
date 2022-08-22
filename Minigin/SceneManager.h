#pragma once
#include "Singleton.h"
#include <vector>
#include <map>
#include <functional>

	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		//Scene& CreateScene(const std::string& name);

		void LoadScene(const std::string& name);
		void SetSpawnLevelFunc(std::function<void(Scene&)> func, const std::string& LevelName, bool keepDefault = true);

		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render();

		Scene& GetScene() const { return *m_pActiveScene.get(); }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_pActiveScene;
		std::map<std::string, std::pair<bool, std::function<void(Scene&)>>> m_LevelFunc{};
	};
