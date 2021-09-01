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
		static void Multiply(Matrix& lMat, Matrix& rMat)
		{
			for (size_t i = 0; i < lMat.nRow(); ++i)
				for (size_t j = 0; j < rMat.nCol(); ++j)
					for (size_t k = 0; k < lMat.nCol(); ++k)
					{
						lMat[i][j] += lMat[i][k] * rMat[k][j];
					}
		}

	public:
		Matrix() {}
		Matrix(const float* data) : TMatrix<float, 4, 4>(data) {}
		Matrix(TMatrix<float, 4, 4> mat) : TMatrix(mat){}

	public:
		void PreMultiply(Matrix& rMat)
		{
			Multiply(rMat, *this);
			*this = rMat;
		}

		void PostMultiply(Matrix& rMat)
		{
			Multiply(*this, rMat);
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