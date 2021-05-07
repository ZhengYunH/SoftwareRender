#pragma once
#include <vector>
#include <cassert>
#include <initializer_list>
#include <iostream>

template<int dimension, typename _DataType>
class TVec;

namespace zyh
{
	template <typename _DataType, size_t _nRow, size_t _nCol>
	class TMatrix
	{
	public:

		TMatrix() { initData(); }
		TMatrix(std::initializer_list<_DataType> data)
		{
			assert(data.size() == _nRow * _nCol);
			initData();
			_mDataIdx = 0;

			for (auto d : data)
				input(d);
		}

		friend std::ostream& operator<<(std::ostream& os, const TMatrix& c)
		{
			for (size_t i = 0; i < _nRow; i++)
			{
				for (size_t j = 0; j < _nCol; j++)
					os << c.mData_[i][j] << ' ';
				os << std::endl;
			}
			return os;
		}
		friend std::istream& operator>>(std::istream& is, TMatrix& c);

		std::vector<_DataType>& operator [](size_t idx){ return idx < _nRow ? mData_[idx] : mData_[_nRow - 1];}

		void input(_DataType data)
		{
			size_t idx = _mDataIdx;
			assert(idx < _nRow * _nCol);

			mData_[idx / _nRow][idx % _nRow] = data;
			++_mDataIdx;
		}

		TMatrix transpose()
		{
			TMatrix< _DataType, _nCol, _nRow> result;
			for (size_t j = 0; j < _nCol; j++)
				for (size_t i = 0; i < _nRow; i++)
					result[j][i] = (*this)[i][j];
			return result;
		}

	protected:
		size_t nRow() { return _nRow; }
		size_t nCol() { return _nCol; }

	private:
		void initData()
		{
			mData_.resize(_nRow);
			for (auto& rowData : mData_)
				rowData.resize(_nCol);
		}

		size_t _mDataIdx;
		std::vector<std::vector<_DataType>> mData_;

	};
}

