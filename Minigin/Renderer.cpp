#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <algorithm>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render() 
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	RenderQueue();
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, float4 srcRect, float4 dstRect, bool isFlipped) const
{
	SDL_Rect source{
	(int)srcRect.x,
	(int)srcRect.y,
	(int)srcRect.z,
	(int)srcRect.w
	};

	SDL_Rect dest{
	(int)dstRect.x,
	(int)dstRect.y,
	(int)dstRect.z,
	(int)dstRect.w
	};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (isFlipped)
		flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &source, &dest, 0.f, NULL, flip);

}

void Renderer::AddToRenderQueue(const Texture2D& texture, const SDL_Rect& src, const SDL_Rect& dst, const SDL_Point& center, float rotation, float depth, bool flipped)
{
	m_RenderQueue.push_back(RenderInfo{ texture, src, dst, center, rotation, depth, flipped });
}

void Renderer::AddToRenderQueue(const Texture2D& texture, float x, float y, float rotation, float depth)
{
	SDL_Rect src{};
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &src.w, &src.h);

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = src.w;
	dst.h = src.h;

	SDL_Point center{};
	center.x = static_cast<int>(src.w * 0.5f);
	center.y = static_cast<int>(src.h * 0.5f);

	AddToRenderQueue(texture, src, dst, center, rotation, depth);
}

void Renderer::RenderQueue()
{
	// Sort Queue based on its depth value
	auto depthSort = [](const RenderInfo& a, const RenderInfo& b)
	{
		return a.depth < b.depth;
	};

	std::sort(m_RenderQueue.begin(), m_RenderQueue.end(), depthSort);

	for (auto render : m_RenderQueue)
	{
		SDL_RendererFlip flip = render.IsFlipped ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE; // set flip 
		//RenderTexture(render.sdl_Texture, &render.srcRect, &render.dstRect, render.IsFlipped);
		SDL_RenderCopyEx(GetSDLRenderer(), render.sdl_Texture, &render.srcRect, &render.dstRect, render.rotation, &render.pivot, flip);
	}

	m_RenderQueue.clear();
}
