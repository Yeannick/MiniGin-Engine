#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include <vector>

class Scene;

class GameObject final 
{
public:

	GameObject() = default;
	GameObject(const std::string& name);
	virtual ~GameObject();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void FixedUpdate();
	void Update() ;
	void LateUpdate();
	void Render() const ;

	void MarkForDestruction();
	bool IsMarkedForDestruction() const;
	
	void SetPosition(float x, float y);
	const Transform& GetTransform() const;

	void SetName(const std::string& name);
	const std::string& GetName() const;

	//void SetScene(Scene* scene);
	/*Scene* GetScene() const;
	void Enable(bool enabled);
	bool IsEnabled() const;*/


	// Adding Components to GameObject only if they inherit from Component class
	template<typename T>
	typename std::enable_if<std::is_base_of<BaseComponent, T>::value, bool>::type
		AddComponent(std::weak_ptr<T> component)
	{
		if (component.expired()
			|| component.use_count() != 1
			|| !GetComponent<T>().expired())
			return false;

		m_Components.push_back(component.lock());
		std::static_pointer_cast<BaseComponent>(component.lock())->OnAdditionToObject();
		return true;
	}
	// Removing Components from the gameObject , checking if they are expired else remove them
	template<typename T>
	typename std::enable_if<std::is_base_of<BaseComponent, T>::value, bool>::type
		RemoveComponent()
	{
		std::weak_ptr<T> search = GetComponent<T>();
		if (search.expired())
			return false;

		m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(), [search](std::shared_ptr<BaseComponent> rhs)
			{
				return search.lock() == rhs;
			}), m_Components.end());
		return true;
	}
	// getting a specific Component
	template<typename T>
	std::weak_ptr<T> GetComponent() const {
		std::weak_ptr<T> weak;
		for (std::shared_ptr<BaseComponent> comp : m_Components) {

			weak = std::dynamic_pointer_cast<T>(comp);
			if (weak.lock() != nullptr) {
				return weak;
			}
		}

		return weak;
	}

	// --- Parenting --- //
	void SetParent(GameObject* parent);
	GameObject* GetParent() const;

	size_t GetChildCount() const;
	GameObject* GetChildAt(int index) const;

	void RemoveChild(int index);
	void AddChild(GameObject* go);

private:
	Transform m_Transform;
	bool m_MarkedDestroy = false;
	std::string m_Name{};
	bool m_IsEnabled = true;
	std::vector<std::shared_ptr<BaseComponent>> m_Components{};

	GameObject* m_Parent = nullptr;
	std::vector<GameObject*> m_Children;
};
