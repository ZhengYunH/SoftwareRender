#pragma once
#include <vector>
#include <cassert>
#include <initializer_list>
#include <iostream>

namespace ZYH
{
	template<int _Size, typename _DataType>
	class TVec
	{
		static _DataType dot(const TVec& v1, const TVec& v2)
		{
			assert(v1.size() == v2.size());
			_DataType result = (_DataType)0;
			for (size_t idx = 0; idx < v1.size(); ++idx)
				result += v1[idx] * v2[idx];
			return result;
		}

		static TVec<_Size, _DataType> cross(const TVec& v1, const TVec& v2);

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
		inline size_t size() { return _Size; }
		inline _DataType absSqr() { return TVec::dot(*this, *this); }
		inline _DataType abs() { return std::sqrt(absSqr()); }
		void normalize() 
		{
			auto abs = this->abs();
			for (auto& d : mData_)
				d /= abs;
		}
		TVec<_Size, _DataType> getNormalized()
		{
			TVec<_Size, _DataType> ret(*this);
			ret.normalize();
			return ret;
		}

	private:
		std::vector<_DataType> mData_;
	};
}


