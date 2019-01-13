#pragma once
#include <d3d11.h>
#include <assert.h>
#include <wrl.h>
#include "Surface.h"
#include "ChiliException.h"
#include "Colors.h"

using namespace std;

/*!
* @brief Klasa obs³uguj¹ca wygl¹d graficzny aplikacji.
*
* Domyœlnie zawarta we frameworku, zmienionan apotrzeby aplikacji.
*/
class Graphics
{
	struct FSQVertex
	{
		float x, y, z;		/*!< pozycja */
		float u, v;			/*!< po³o¿enie tekstu */
	};
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	class Exception : public ChiliException
	{
		HRESULT hr;
	public:
		Exception(HRESULT hr, const wstring& note, const wchar_t* file, unsigned int line);
		wstring GetErrorName() const;
		wstring GetErrorDescription() const;
		virtual wstring GetFullMessage() const override;
		virtual wstring GetExceptionType() const override;
	};
	Graphics(class HWNDKey& key);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame();
	void BeginFrame();
	Color GetPixel(int x, int y) const;
	void PutPixel(int x, int y, int r, int g, int b)
	{
		PutPixel(x, y, { unsigned char(r),unsigned char(g),unsigned char(b) });
	}
	void PutPixel(int x, int y, Color c);
	void DrawRect(int x0, int y0, int x1, int y1, Color c);
	void DrawRectDim(int x0, int y0, int width, int height, Color c)
	{
		DrawRect(x0, y0, x0 + width, y0 + height, c);
	}
	template<typename E>
	void DrawSprite(int x, int y, const Surface& s, E effect)
	{
		DrawSprite(x, y, s.GetRect(), s, effect);
	}
	template<typename E>
	void DrawSprite(int x, int y, const RectI& srcRect, const Surface& s, E effect)
	{
		DrawSprite(x, y, srcRect, GetScreenRect(), s, effect);
	}
	template<typename E>
	void DrawSprite(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, E effect)
	{
		assert(srcRect.left >= 0);
		assert(srcRect.right <= s.GetWidth());
		assert(srcRect.top >= 0);
		assert(srcRect.bottom <= s.GetHeight());
		if (x < clip.left)
		{
			srcRect.left += clip.left - x;
			x = clip.left;
		}
		if (y < clip.top)
		{
			srcRect.top += clip.top - y;
			y = clip.top;
		}
		if (x + srcRect.GetWidth() > clip.right)
		{
			srcRect.right -= x + srcRect.GetWidth() - clip.right;
		}
		if (y + srcRect.GetHeight() > clip.bottom)
		{
			srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}
		for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
		{
			for (int sx = srcRect.left; sx < srcRect.right; sx++)
			{
				effect(
					s.GetPixel(sx, sy),
					x + sx - srcRect.left,
					y + sy - srcRect.top,
					*this
				);
			}
		}
	}
	~Graphics();
	static constexpr int ScreenWidth = 700;
	static constexpr int ScreenHeight = 600;
	static RectI GetScreenRect();
};

#include "SpriteEffect.h"

#ifndef GOD_GRAPHICS
extern template
void Graphics::DrawSprite<SpriteEffect::Copy>(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, SpriteEffect::Copy effect);
extern template
void Graphics::DrawSprite<SpriteEffect::Chroma>(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, SpriteEffect::Chroma effect);
extern template
void Graphics::DrawSprite<SpriteEffect::Substitution>(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, SpriteEffect::Substitution effect);
#endif