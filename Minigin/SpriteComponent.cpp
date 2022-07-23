#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

SpriteComponent::SpriteComponent(const std::weak_ptr<GameObject>& owner, const float2& pivot, const float2& rotationPivot):
	RenderComponent(owner,pivot,rotationPivot)
{
}
void SpriteComponent::Update()
{
	if (m_NeedsUpdate)
	{
		UpdateFrame();
	}
}
void SpriteComponent::Render()
{
	if (!m_Texture)
	{
		return;
	}

	float2 Scale = m_Owner.lock()->GetTransform().GetScale();
	float3 Position = { m_Owner.lock()->GetTransform().GetPosition().x, m_Owner.lock()->GetTransform().GetPosition().y, m_Owner.lock()->GetTransform().GetPosition().z };
	float Rotation = m_Owner.lock()->GetTransform().GetRotation();

	Position.x -= (m_Pivot.x * m_FrameRect.w * Scale.x);
	Position.y -= (m_Pivot.y * m_FrameRect.h * Scale.y);

	SDL_Rect dst{};
	dst.x = static_cast<int>(Position.x);
	dst.y = static_cast<int>(Position.y);
	dst.w = static_cast<int>(m_FrameRect.w * Scale.x);
	dst.h = static_cast<int>(m_FrameRect.h * Scale.y);

	SDL_Point Pivot{};
	Pivot.x = static_cast<int>(dst.w * m_RotationPivot.x);
	Pivot.x = static_cast<int>(dst.h * m_RotationPivot.y);

	Renderer::GetInstance().AddToRenderQueue(*m_Texture, m_FrameRect, dst, Pivot, Rotation, Position.z, m_IsFlipped);

}
void SpriteComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void SpriteComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

void SpriteComponent::SetSpriteRect(int x, int y, int width, int height)
{
	SetSpriteRect({ x, y, width, height });
}

void SpriteComponent::SetSpriteRect(const SDL_Rect& rect)
{

	m_SpriteRect = rect;

	m_FrameRect.w = m_SpriteRect.w / m_Columns;
	m_FrameRect.h = m_SpriteRect.h / m_Rows;

	m_NeedsUpdate = true;
}

void SpriteComponent::SetColumnsRows(int col, int rows)
{
	SetColumns(col);
	SetRows(rows);
}

void SpriteComponent::SetColumns(int col)
{
	if (col <= 0)
		return;

	m_Columns = col;
	m_MaxFrames = m_Columns * m_Rows;

	m_FrameRect.w = m_SpriteRect.w / m_Columns;
	m_NeedsUpdate = true;
}

void SpriteComponent::SetRows(int rows)
{
	if (rows <= 0)
		return;

	m_Rows = rows;
	m_MaxFrames = m_Columns * m_Rows;

	m_FrameRect.h = m_SpriteRect.h / m_Rows;
	m_NeedsUpdate = true;
}

void SpriteComponent::SetSpriteFrame(int frameNr)
{
	m_CurrentFrame = frameNr % m_MaxFrames;
	m_NeedsUpdate = true;
}

void SpriteComponent::SetFlipped(bool flipped)
{
	m_IsFlipped = flipped;
}

int SpriteComponent::GetCurrentFrame()
{
	return m_CurrentFrame;
}

std::shared_ptr<Texture2D> SpriteComponent::GetTexture() const
{
	return m_Texture;
}

void SpriteComponent::UpdateFrame()
{
	int col{ m_CurrentFrame % m_Columns };
	int row{ m_CurrentFrame / m_Columns };

	m_FrameRect.x = m_SpriteRect.x + (col * m_FrameRect.w);
	m_FrameRect.y = m_SpriteRect.y + (row * m_FrameRect.h);

	m_NeedsUpdate = false;
}
