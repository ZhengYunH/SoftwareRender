#pragma once
#include <vector>
#include <cassert>
#include <initializer_list>
#include <iostream>

namespace zyh
{
	template<int _Size, typename _DataType>
	class TVec
	{
		static _DataType dot(TVec& v1, TVec& v2)
		{
			assert(v1.size() == v2.size());
			_DataType result = v1[0] * v2[0];
			for (size_t idx = 1; idx < v1.size(); ++idx)
				result += v1[idx] * v2[idx];
			return result;
		}

	public:
		TVec() { mData_.resize(_Size); }
		TVec(std::initializer_list<_DataType> data)
		{
			for (_DataType d : data)
				mData_.push_back(d);
		}
		friend std::ostream& operator<<(std::ostream& os, const TVec& c)
		{
			for(auto d: c.mData_)
				os << d << ' '; 
			return os;
		}

		_DataType& operator [](int idx) { return idx < _Size ? mData_[idx] : mData_[_Size - 1]; }
		_DataType dot(TVec& v2) { return TVec::dot(*this, v2); }
		size_t size() { return _Size; }

	private:
		std::vector<_DataType> mData_;
	};


	template <typename _DataType>
	using TVec2 = TVec<2, _DataType>;
	template <typename _DataType>
	using TVec3 = TVec<3, _DataType>;

	using Vector3i = TVec3<int>;
	using Vector3f = TVec3<float>;
	using Vector3d = TVec3<double>;

}


