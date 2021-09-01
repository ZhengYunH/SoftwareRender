#pragma once
#include <windows.h>
#include <memory>
#include "../Utils/Color/RGB.h"
#include "../Utils/Camera.h"
#include "Rasterize.h"

namespace ZYH
{
	class Renderer
	{
	public:
		Renderer(int w, int h, HWND hWnd);
		void Update(HWND hWnd);
		void UpdateCamera();
		void UpdateGeometry();

		void ClearBuffer();
		void ShutDown();
		void DrawPixel(Vector2ui point, const ZRGB& color);
		void DrawPixel(uint32_t x, uint32_t y, const ZRGB& color);
		void DrawLine(Vector2ui p1, Vector2ui p2, const ZRGB& color);

	public:
		uint32_t mWidth_;
		uint32_t mHeight_;

		HDC mTempDC_{ nullptr };
		HBITMAP mTempBm_{ nullptr };
		HBITMAP mOldBm_{ nullptr };
		uint32_t* mFrameBuffer_{ nullptr };
		std::shared_ptr<float[]> mDepthBuffer_{ nullptr };

		uint32_t mBGColor{ ZRGB(123, 195, 221) };

		// TODO: Double Buffering


	private:
		void _InitCamera();
		Rasterize rasterizer;

	private:
		Camera mCamera_;
	};
}