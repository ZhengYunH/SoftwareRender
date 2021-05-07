#pragma once
#include "TMatrix.h"
#include "TVec.h"



namespace zyh
{
	template <typename _DataType>
	class TMatrix3x3 : public TMatrix<_DataType, 3, 3>
	{
	public:
		TMatrix3x3() : TMatrix<_DataType, 3, 3>() {}
		TMatrix3x3 operator * (TMatrix3x3& rMat)
		{
			TMatrix3x3& lMat = *this;
			TMatrix3x3 dst;
			for (size_t i = 0; i < 3; i++)
				for (size_t j = 0; j < 3; j++)
				{
					res[i][j] = lMat[i][0] * rMat[0][i] + lMat[i][1] * rMat[1][i] + lMat[i][2] * rMat[2][i];
				}
			return dst;
		}
	};
}