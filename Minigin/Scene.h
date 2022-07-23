#pragma once
#include "SceneManager.h"
class GameObject;

	
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove();
		bool IsMarkedDestroy() { return m_IsMarkedDestroy; }

		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::shared_ptr<GameObject> GetGameObject(const std::string& tag) const; // Get GameObject by Tag , if no tag given or tag not found returns nothing
		std::vector<std::shared_ptr<GameObject>> GetGameObjects()const; // Get All of the objects in a scene
		std::vector<std::shared_ptr<GameObject>> GetGameObjectsByTag(const std::string& tag) const;
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
		bool m_IsMarkedDestroy = false;
	};


