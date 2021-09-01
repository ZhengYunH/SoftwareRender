#include "Camera.h"
namespace ZYH
{
	void Camera::LookAt(Vector3 trans, Vector3 dir, Vector3 up)
	{
		dir.normalize();
		up.normalize();
		auto bN = up.cross(dir);
		auto normal = dir.cross(bN);
		mTransform_[0][0] = bN[0]; mTransform_[0][1] = bN[1]; mTransform_[0][2] = bN[2]; mTransform_[0][3] = 0;
		mTransform_[1][0] = normal[0]; mTransform_[1][1] = normal[1]; mTransform_[1][2] = normal[2]; mTransform_[1][3] = 0;
		mTransform_[2][0] = dir[0]; mTransform_[2][1] = dir[1]; mTransform_[2][2] = dir[2]; mTransform_[2][3] = 0;
		mTransform_[3][0] = trans[0]; mTransform_[3][1] = trans[1]; mTransform_[3][2] = trans[2]; mTransform_[3][3] = 1;
		_UpdateMatrix();
	}
	void Camera::_UpdateMatrix()
	{
		_UpdateWorldToView();
		_UpdateViewToProj();
		mWorldToProj_ = mWorldToView_;
		mWorldToProj_.PostMultiply(mViewToProj_);
	}
	void Camera::_UpdateWorldToView()
	{
		mWorldToView_ = mTransform_.Transpose();
		mWorldToView_[0][3] = 0.f;
		mWorldToView_[1][3] = 0.f;
		mWorldToView_[2][3] = 0.f;
		mWorldToView_[3][3] = 1.f;
		mWorldToView_[3][0] = -(Translation().dot(mTransform_.getAxis(AXIS::X)));
		mWorldToView_[3][1] = -(Translation().dot(mTransform_.getAxis(AXIS::Y)));
		mWorldToView_[3][2] = -(Translation().dot(mTransform_.getAxis(AXIS::Z)));
	}
	void Camera::_UpdateViewToProj()
	{
		float f = 1.0f / tanf(mFieldOfView_ * 0.5f);
		mViewToProj_ = Matrix(
			{
				f / mAspect_, 0.f, 0.f, 0.f,
				0.f, f, 0.f, 0.f,
				0.f, 0.f, (mNear_ + mFar_) / (mFar_ - mNear_), -mNear_ * mFar_ / (mFar_ - mNear_),
				0.f, 0.f, 1.0f, 0.f
			});
	}
}

