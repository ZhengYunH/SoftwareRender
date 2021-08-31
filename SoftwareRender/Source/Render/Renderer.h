#pragma once
#include <windows.h>
#include <memory>
#include "../Utils/Color/RGB.h"
#include "../Utils/Camera.h"


namespace ZYH
{
	class Renderer
	{
	public:
		Renderer(int w, int h, HWND hWnd);
		void Update(HWND hWnd);
		void UpdateCamera();
		void ClearBuffer();
		void ShutDown();
		void DrawPixel(uint32_t x, uint32_t y, ZRGB color);

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

	private:
		Camera mCamera_;
	};
}