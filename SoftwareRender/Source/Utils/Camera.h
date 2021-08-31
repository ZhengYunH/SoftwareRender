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
		const Matrix& Transform() 
		{
			return mTransform_;
		}
		const Matrix& WorldToProj()
		{
			return mWorldToProj_;
		}
		const Vector3 Translation() 
		{ 
			return Vector3({ mTransform_[3][0], mTransform_[3][1], mTransform_[3][2] });
		}
		void Translation(const Vector3& translation) 
		{ 
			mTransform_[3][0] = translation[0];
			mTransform_[3][1] = translation[1];
			mTransform_[3][2] = translation[2];
		}
		void LookAt(Vector3 trans, Vector3 dir, Vector3 Up);

	private:
		// update mWorldToView_ & mViewToProj_
		void _UpdateMatrix();
		void _UpdateWorldToView();
		void _UpdateViewToProj();

	private:
		Matrix mTransform_;
		bool mIsDirty_{ true };
		
		float mFieldOfView_{45.f};

		float mAspect_{ 1.0f };

		float mNear_{0.5};
		float mFar_{5000};

		Matrix mWorldToView_;
		Matrix mViewToProj_;
		Matrix mWorldToProj_;
	};
}