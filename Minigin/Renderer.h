#pragma once
#include "Singleton.h"
#include "DataTypes.h"
#include "Texture2D.h"


	
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	struct RenderInfo
	{
		RenderInfo(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst, const SDL_Point& center, float rotation = 0.f, float depth = 0.f, bool flipped = false)
		{
			sdl_Texture = texture.GetSDLTexture();
			srcRect = src;
			dstRect = dst;
			pivot = center;
			rotation = rotation;
			depth = depth;
			IsFlipped = flipped;
		}
		SDL_Texture* sdl_Texture;
		SDL_Rect srcRect;
		SDL_Rect dstRect;
		SDL_Point pivot;
		float rotation;
		float depth;
		bool IsFlipped;
	};
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() ;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float4 srcRect, float4 dstRect, bool isFlipped) const;

		void AddToRenderQueue(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst, const SDL_Point& center, float rotation = 0.f, float depth = 0.f, bool flipped = false);
		void AddToRenderQueue(const Texture2D& texture, float x, float y, float rotation = 0.f, float depth = 0.f);

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	
	private:
		std::vector<RenderInfo> m_RenderQueue;

		void RenderQueue();
	};


