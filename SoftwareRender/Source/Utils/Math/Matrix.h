#pragma once
#include "TMatrix.h"
#include "Vector.h"



namespace ZYH
{
	using Matrix4x3 = TMatrix<float, 4, 3>;
	using Matrix4x4 = TMatrix<float, 4, 4>;
	using Matrix3x3 = TMatrix<float, 3, 3>;
	
	enum class AXIS: uint8_t
	{
		X=0,
		Y,
		Z
	};

	class Matrix: public TMatrix<float, 4, 4>
	{
	public:
		static Matrix Multiply(Matrix& lMat, Matrix& rMat)
		{
			Matrix ret;
			for (size_t i = 0; i < lMat.nRow(); ++i)
				for (size_t j = 0; j < lMat.nCol(); ++j)
					for (size_t k = 0; k < rMat.nRow(); ++k)
					{
						ret[i][j] += lMat[i][k] * rMat[k][j];
					}
			return ret;
		}

	public:
		Matrix() {}
		Matrix(const float* data) : TMatrix<float, 4, 4>(data) {}
		Matrix(TMatrix<float, 4, 4> mat) : TMatrix(mat){}

	public:
		void PreMultiply(Matrix& rMat)
		{
			*this = Multiply(rMat, *this);
		}

		void PostMultiply(Matrix& rMat)
		{
			*this = Multiply(*this, rMat);
		}

		void Rotate(Vector3 n, float theta);
		void RotateWithAxis(AXIS axis, float theta);

		void Scale(AXIS axis, float scale);
		void Scale(Vector3 scale);
		void Scale(Vector3 n, float scale);
	
		Vector3 getAxis(AXIS axis);

	public:
		Vector3 operator *(const Vector3& point);
		Vector4 operator *(const Vector4& point);
	};

}