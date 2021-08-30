#pragma once
#include "TVec.h"
namespace ZYH
{
	template <typename _DataType>
	using TVec2 = TVec<2, _DataType>;
	template <typename _DataType>
	using TVec3 = TVec<3, _DataType>;
	template <typename _DataType>
	using TVec4 = TVec<4, _DataType>;

	using Vector2 = TVec2<float>;
	using Vector3 = TVec3<float>;
	using Vector4 = TVec4<float>;

	using Vector3i = TVec3<int>;
	using Vector3d = TVec3<double>;

	using Vector4i = TVec4<int>;
	using Vector4d = TVec4<double>;
}