#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

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
	for ( auto child : m_Children )
	{
		child->FixedUpdate();
	}
}

void GameObject::Update()
{
	
	if (m_Components.size() == 0)
	{
		return;
	}
	if (IsMarkedForDestruction())
	{
		return;
	}
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		if (IsMarkedForDestruction())
		{
			return;
		}
		comp->Update();
		
	}
	if (IsMarkedForDestruction())
	{
		return;
	}
	for (auto child : m_Children)
	{
		child->Update();
		child->m_Transform.SetPosition(m_Transform.GetPosition().x + child->m_Transform.GetLocalPosition().x, m_Transform.GetPosition().y + child->m_Transform.GetLocalPosition().y, m_Transform.GetPosition().z + +child->m_Transform.GetLocalPosition().z);
	}
}

void GameObject::LateUpdate()
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->LateUpdate();
	}
	for (auto child : m_Children)
	{
		child->LateUpdate();
	}
}

void GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> comp : m_Components)
	{
		comp->Render();
	}
	for (auto child : m_Children)
	{
		child->Render();
	}
}

void GameObject::MarkForDestruction()
{
	m_MarkedDestroy = true;

	for (size_t i = 0; i < m_Children.size(); i++)
	{
		m_Children[i]->MarkForDestruction();
	}
}

bool GameObject::IsMarkedForDestruction() const
{
	return m_MarkedDestroy;
}
void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 1.f);
}
void GameObject::SetLocalPosition(float x, float y)
{
	m_Transform.SetLocalPosition(x, y, 1.f);
}
void GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y,z);
}
void GameObject::SetLocalPosition(float x, float y, float z)
{
	m_Transform.SetLocalPosition(x, y, z);
}
void GameObject::SetRotation(float angle)
{
	m_Transform.SetRotation(angle);
}
void GameObject::SetScale(float x, float y) 
{
	m_Transform.SetScale(float2{ x,y });
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
	if (parent)
	{
		m_Parent->RemoveChild(this);
		m_Parent = parent;
	}
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
	if (size_t(index) > m_Children.size())
	{
		return nullptr;
	}
	return m_Children[index];
}

GameObject* GameObject::GetChild(std::string name) const
{
	if (m_Children.empty())
	{
		return nullptr;
	}
	
	for (size_t i = 0; i < m_Children.size(); i++)
	{
		if (m_Children[i]->GetName() == name)
		{
			return m_Children[i];
		}
		
	}
	return nullptr;
}

std::vector<GameObject*> GameObject::GetChildren()
{
	return m_Children;
}

void GameObject::RemoveChild(int index)
{
	// check if this is the best way to remove 
	if (size_t(index) > m_Children.size())
	{
		return;
	}
	m_Children[index]->SetParent(nullptr);
	m_Children.erase(m_Children.begin() + index);
}

void GameObject::RemoveChild(GameObject* go)
{
	go->SetParent(nullptr);
	for (size_t i = 0; i < m_Children.size(); i++)
	{
		if (m_Children[i] == go)
		{
			m_Children.erase(std::ranges::remove(m_Children, m_Children[i]).begin());
		}
	}
}

void GameObject::AddChild(GameObject* go)
{
	go->m_Transform.SetLocalPosition(go->m_Transform.GetPosition().x, go->m_Transform.GetPosition().y, go->m_Transform.GetPosition().z);
	m_Children.push_back(go);
}