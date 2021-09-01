#pragma once
#include "TVec.h"
namespace ZYH
{
	template <typename _DataType>
	class TVec2 : public TVec<2, _DataType>
	{
		using TVec<2, _DataType>::TVec;
	public:
		TVec2() : TVec<2, _DataType>() {}
		TVec2(_DataType X, _DataType Y) : TVec<2, _DataType>({ X, Y }){}

	public:
		const _DataType& X() const { return (*this)[0]; }
		const _DataType& Y() const { return (*this)[1]; }
	};

	template <typename _DataType>
	class TVec3 : public TVec<3, _DataType>
	{
		using TVec<3, _DataType>::TVec;
	public:
		TVec3() : TVec<3, _DataType>() {}
		TVec3(_DataType X, _DataType Y, _DataType Z) :TVec<3, _DataType>({ X, Y, Z }){}

	public:
		const _DataType& X() const { return (*this)[0]; }
		const _DataType& Y() const { return (*this)[1]; }
		const _DataType& Z() const { return (*this)[2]; }
	};

	template <typename _DataType>
	class TVec4 : public TVec<4, _DataType>
	{
		using TVec<4, _DataType>::TVec;
	public:
		TVec4() : TVec<4, _DataType>() {}
		TVec4(_DataType X, _DataType Y, _DataType Z, _DataType W) :TVec<4, _DataType>({ X, Y, Z, W })
		{
		}

	public:
		const _DataType& X() const { return (*this)[0]; }
		const _DataType& Y() const { return (*this)[1]; }
		const _DataType& Z() const { return (*this)[2]; }
		const _DataType& W() const { return (*this)[3]; }
	};

	using Vector2ui = TVec2<uint32_t>;
	using Vector2i = TVec2<int>;
	using Vector2 = TVec2<float>;
	using Vector2d = TVec2<double>;

	using Vector3i = TVec3<int>;
	using Vector3 = TVec3<float>;
	using Vector3d = TVec3<double>;

	using Vector4i = TVec4<int>;
	using Vector4 = TVec4<float>;
	using Vector4d = TVec4<double>;

	
}