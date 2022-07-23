#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

GameObject::GameObject(const std::string& name):
	m_Name(name)
{
}
GameObject::~GameObject() = default;

void GameObject::FixedUpdate()
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->Update();
	}
}

void GameObject::LateUpdate()
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->Render();
	}
}

void GameObject::MarkForDestruction()
{
	m_MarkedDestroy = true;
}

bool GameObject::IsMarkedForDestruction() const
{
	return m_MarkedDestroy;
}
void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 1.f);
}
void GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y,z);
}
const Transform& GameObject::GetTransform() const
{
	// TODO: insert return statement here
	return m_Transform;
}
void GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

const std::string& GameObject::GetName() const
{
	return m_Name;
}
void GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
}

GameObject* GameObject::GetParent() const
{
	return m_Parent;
}

size_t GameObject::GetChildCount() const
{
	return m_Children.size();
}

GameObject* GameObject::GetChildAt(int index) const
{
	return m_Children[index];
}

void GameObject::RemoveChild(int index)
{
	// check if this is the best way to remove 
	m_Children.erase(m_Children.begin() + index);
}

void GameObject::AddChild(GameObject* go)
{
	m_Children.push_back(go);
}