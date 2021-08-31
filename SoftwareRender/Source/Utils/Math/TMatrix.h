#pragma once
#include <vector>
#include <cassert>
#include <initializer_list>
#include <iostream>

#include "TVec.h"

namespace ZYH
{
	template <typename _DataType, size_t _nRow, size_t _nCol>
	class TMatrix
	{
	public: // ctor & dtor
		TMatrix() { initData(); }
		TMatrix(const _DataType* data) 
		{ 
			initData();
			_mDataIdx = 0;
			while (_mDataIdx < _nRow * _nCol)
				Input(data[_mDataIdx]);
		}
		TMatrix(const std::initializer_list<_DataType> data)
		{
			assert(data.size() == _nRow * _nCol);
			initData();
			_mDataIdx = 0;

			for (auto d : data)
				Input(d);
		}

	public: // iostream
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

	public: // method
		void Input(_DataType data)
		{
			size_t idx = _mDataIdx;
			assert(idx < _nRow * _nCol);

			mData_[idx / _nRow][idx % _nRow] = data;
			++_mDataIdx;
		}

		TMatrix Transpose()
		{
			TMatrix< _DataType, _nCol, _nRow> result;
			for (size_t j = 0; j < _nCol; j++)
				for (size_t i = 0; i < _nRow; i++)
					result[j][i] = (*this)[i][j];
			return result;
		}

	public: // operation
		std::vector<_DataType>& operator [](size_t idx) { return idx < _nRow ? mData_[idx] : mData_[_nRow - 1]; }
		const std::vector<_DataType>& operator [](size_t idx) const { return idx < _nRow ? mData_[idx] : mData_[_nRow - 1]; }

		TMatrix operator * (const TMatrix& rMat)
		{
			assert(nCol() == rMat.nRow());
			TMatrix<_DataType, nRow(), rMat.nCol()> ret;
			const TMatrix& lMat = (*this);
			for (size_t i = 0; i < nRow(); ++i)
				for (size_t j = 0; j < rMat.nCol(); ++j)
				{
					ret[i][j] = (_DataType)0;
					for (size_t k = 0; k < nCol(); ++k)
					{
						ret[i][j] += lMat[i][k] * rMat[k][i];
					}
				}
			return ret;
		}
		TMatrix operator * (const TVec<_nCol, _DataType>& rVec)
		{
			TVec<_nRow, _DataType> ret;
			const TMatrix& lMat = (*this);
			for (size_t i = 0; i < nRow(); ++i)
			{
				ret[i] = (_DataType)0;
				for (size_t j = 0; j < nCol(); ++j)
				{
					ret[i] += lMat[i][j] * rVec[j];
				}
			}
		}

	protected:
		size_t nRow() { return _nRow; }
		size_t nCol() { return _nCol; }

	protected:
		void initData()
		{
			mData_.resize(_nRow);
			for (auto& rowData : mData_)
				rowData.resize(_nCol);
		}

		size_t _mDataIdx;
		// TODO: convert to TVec<TVec<_DataType>>
		std::vector<std::vector<_DataType>> mData_;

	};
}

