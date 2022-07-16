#pragma once


#include <memory>
class GameObject;

class BaseComponent
{
public : 
	BaseComponent(const std::weak_ptr<GameObject>& owner): m_Owner(owner) {};

	virtual ~BaseComponent() {};
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	// functions I want to override in derived classes of BaseComponent
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;

	virtual void OnAdditionToObject() {};

protected:
	std::weak_ptr<GameObject> m_Owner; // GameObject owning this component.
	bool m_NeedsUpdate = false; 


private:

};