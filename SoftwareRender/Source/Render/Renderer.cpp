#include "Renderer.h"
#include "../Utils/Math/Constant.h"

namespace ZYH
{
	Renderer::Renderer(int w, int h, HWND hWnd)
		: mWidth_(w)
		, mHeight_(h)

	{
		// create screen buffer
		HDC hDC = GetDC(hWnd);
		mTempDC_ = CreateCompatibleDC(hDC);
		ReleaseDC(hWnd, hDC);

		BITMAPINFO bi = { {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
			(DWORD)w * h * 4, 0, 0, 0, 0} };

		mTempBm_ = CreateDIBSection(mTempDC_, &bi, DIB_RGB_COLORS, (void**)&mFrameBuffer_, 0, 0);
		mOldBm_ = (HBITMAP)SelectObject(mTempDC_, mTempBm_);
		mDepthBuffer_.reset(new float[w * h]);

		_InitCamera();
		ClearBuffer();
	}
	void Renderer::Update(HWND hWnd)
	{
		ClearBuffer();
		UpdateCamera();
		HDC hDC = GetDC(hWnd);
		BitBlt(hDC, 0, 0, mWidth_, mHeight_, mTempDC_, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hDC);
	}
	void Renderer::UpdateCamera()
	{
		mCamera_.LookAt(Vector3(), Vector3({ 0, 0, 1 }), Vector3({ 0,1,0 }));
	}
	void Renderer::ClearBuffer()
	{
		for (size_t row = 0; row < mHeight_; ++row)
		{
			for (size_t col = 0; col < mWidth_; ++col)
			{
				auto idx = row * mWidth_ + col;
				mFrameBuffer_[idx] = mBGColor;
				mDepthBuffer_[idx] = 1.0f;
			}
		}
	}
	void Renderer::ShutDown()
	{
		if (mTempDC_)
		{
			if (mOldBm_)
			{
				SelectObject(mTempDC_, mOldBm_);
				mOldBm_ = nullptr;
			}
			DeleteDC(mTempDC_);
			mTempDC_ = nullptr;
		}

		if (mTempBm_)
		{
			DeleteObject(mTempBm_);
			mTempBm_ = nullptr;
		}
	}
	void Renderer::DrawPixel(uint32_t x, uint32_t y, ZRGB color)
	{
		if (x >= mWidth_ || y >= mHeight_)
			return;
		mFrameBuffer_[y * mWidth_ + x] = color;
	}
	void Renderer::_InitCamera()
	{
		mCamera_.SetPerspectiveForLH(
			PI * 0.25f,
			mWidth_ / (float)mHeight_,
			0.5f,
			5000.f
		);
	}
}
