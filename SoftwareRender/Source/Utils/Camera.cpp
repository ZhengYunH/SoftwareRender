#include "Camera.h"
namespace ZYH
{
	void Camera::LookAt(Vector3 trans, Vector3 dir, Vector3 Up)
	{
		auto bN = Up.cross(dir);
		mTransform_[0][0] = bN[0]; mTransform_[0][1] = bN[1]; mTransform_[0][2] = bN[2]; mTransform_[0][3] = 0;
		mTransform_[1][0] = Up[0]; mTransform_[1][1] = Up[1]; mTransform_[1][2] = Up[2]; mTransform_[1][3] = 0;
		mTransform_[2][0] = dir[0]; mTransform_[2][1] = dir[1]; mTransform_[2][2] = dir[2]; mTransform_[2][3] = 0;
		mTransform_[3][0] = trans[0]; mTransform_[3][1] = trans[0]; mTransform_[3][2] = trans[0]; mTransform_[3][3] = 1;
		_UpdateMatrix();
	}
	void Camera::_UpdateMatrix()
	{
	}
}

