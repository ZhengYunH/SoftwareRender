#pragma once
#include "Math/Matrix.h"
#include "Math/Vector.h"

namespace ZYH
{
	class Camera
	{
	public:
		Camera() {}

		void SetPerspectiveForLH(float _fov, float _aspect, float _near, float _far)
		{
			mFieldOfView_ = _fov; mAspect_ = _aspect; mNear_ = _near; mFar_ = _far;
		}

		const Matrix& WorldToProj() { return mWorldToProj_; }
		Vector3 Translation();
		void Translation(Vector3 translation);

		
		void LookAt(Vector3 translation, Vector3 direction, Vector3 Up);

	private:
		// update mWorldToView_ & mViewToProj_
		void _UpdateMatrix();

	private:
		Matrix mTransform_;
		
		float mFieldOfView_{45.f};

		float mAspect_{ 1.0f };

		float mNear_{0.5};
		float mFar_{5000};

		Matrix mWorldToView_;
		Matrix mViewToProj_;
		Matrix mWorldToProj_;
	};
}