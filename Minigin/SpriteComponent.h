#pragma once
#include "RenderComponent.h"
#include "Texture2D.h"
#include "BaseComponent.h"
#include "DataTypes.h"
#include "SDL.h"


class SpriteComponent : public RenderComponent
{
public:
	SpriteComponent(const std::weak_ptr<GameObject>& owner, const float2& pivot = float2{ 0.0f, 0.0f }, const float2& rotationPivot = float2{ 0.5f, 0.5f });
	virtual ~SpriteComponent() = default;

	SpriteComponent(const SpriteComponent & other) = delete;
	SpriteComponent(SpriteComponent && other) = delete;
	SpriteComponent& operator=(const SpriteComponent & other) = delete;
	SpriteComponent& operator=(SpriteComponent && other) = delete;

	void Update()override;
	void Render()override;
	void FixedUpdate()override {};
	void LateUpdate()override {};

	void SetTexture(const std::string& filename);
	void SetTexture(std::shared_ptr<Texture2D> texture);

	void SetSpriteRect(int x, int y, int width, int height);
	void SetSpriteRect(const SDL_Rect& rect);
	void SetFrameRect(int x, int y, int width, int height);

	void SetColumnsRows(int col, int rows);
	void SetColumns(int col);
	void SetRows(int rows);

	void SetSpriteFrame(int frameNr);

	void SetFlipped(bool flipped);

	int GetCurrentFrame();
	std::shared_ptr<Texture2D> GetTexture() const;
private:
	void UpdateFrame();
	std::shared_ptr<Texture2D> m_Texture{};

	SDL_Rect m_SpriteRect{};
	SDL_Rect m_FrameRect{};

	int m_Columns = 1;
	int m_Rows = 1;
	int m_MaxFrames = 1;
	int m_CurrentFrame = 0;

	bool m_IsFlipped = false;
};

