#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"

using namespace std;

/**
* Klasa obs³uguj¹ca wygl¹d graficzny aplikacji.
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
	~Graphics();
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};