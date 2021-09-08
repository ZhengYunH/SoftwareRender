#include "Renderer.h"
#include "../Utils/Math/Constant.h"
#include "../Utils/Geometry/Geometry.h"

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
		CollectPrimitives();
		UpdateCamera();
		UpdateGeometry();

		HDC hDC = GetDC(hWnd);
		BitBlt(hDC, 0, 0, mWidth_, mHeight_, mTempDC_, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hDC);
	}
	void Renderer::UpdateCamera()
	{
		
	}
	void Renderer::UpdateGeometry()
	{
		for (auto& ro : mRenderObjects_)
		{
			ro->Draw(this, RENDER_MODE::WIRE_FRAME);
			delete ro;
		}
		mRenderObjects_.clear();
	}
	void Renderer::CollectPrimitives()
	{
		std::vector<Vector3> vertices{ Vector3(-1,0,2), Vector3(0,1,2), Vector3(1,0,2) };
		std::vector<uint32_t> indexs {0, 1, 2};
		new PrimitivesRenderObject(this, vertices, indexs);
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
	void Renderer::DrawPixel(Vector2u point, const ZRGB& color)
	{
		DrawPixel(point.X(), point.Y(), color);
	}
	void Renderer::DrawPixel(uint32_t x, uint32_t y, const ZRGB& color)
	{
		if (x >= mWidth_ || y >= mHeight_)
			return;
		mFrameBuffer_[(mHeight_ - y) * mWidth_ + x] = color;
	}
	void Renderer::DrawLine(Vector2u p1, Vector2u p2, const ZRGB& color)
	{
		mRasterizer_.DrawLine(p1, p2, color, this);
	}
	Vector2u Renderer::GetScreenPoint(Vector3& p)
	{
		auto x = uint32_t((p.X() + 1.f) * mWidth_ / 2.0f);
		auto y = uint32_t((p.Y() + 1.f) * mHeight_ / 2.0f);
		return Vector2u(x, y);
	}
	void Renderer::HandleEvent(UINT message)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
			mMouseState_ = 1;
			break;
		case WM_RBUTTONDOWN:
			mMouseState_ = 2;
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
			mMouseState_ = 0;
			break;
		case WM_MOUSEMOVE:
			if (mMouseState_ == 1)
				mCamera_.Translation(mCamera_.Translation() + Vector3(0.1f, 0, 0));
			if (mMouseState_ == 2)
				mCamera_.Translation(mCamera_.Translation() + Vector3(-0.1f, 0, 0));
		}
	}
	void Renderer::_InitCamera()
	{
		mCamera_.SetPerspectiveForLH(
			PI * 0.25f,
			mWidth_ / (float)mHeight_,
			0.1f,
			5000.f
		);
		mCamera_.LookAt(Vector3(0, 0, 0), Vector3({ 0, 0, 1 }), Vector3({ 0, 1, 0 }));
	}
}
