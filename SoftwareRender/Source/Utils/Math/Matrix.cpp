#include "Matrix.h"

namespace ZYH
{
	void Matrix::Rotate(Vector3 n, float theta)
	{
		float *data = new float[16]
		{
			(n[0] * n[0]) * (1 - cosf(theta)) + cosf(theta), (n[0] * n[1])* (1 - cosf(theta)) + n[2] * sinf(theta), (n[0] * n[2])* (1 - cosf(theta)) - n[1] * sinf(theta), 0,
			(n[0] * n[1]) * (1 - cosf(theta)) - n[2] * sinf(theta), (n[1] * n[1])* (1 - cosf(theta)) + cosf(theta), (n[1] * n[2])* (1 - cosf(theta)) + n[0] * sinf(theta), 0,
			(n[0] * n[2]) * (1 - cosf(theta)) + n[1] * sinf(theta), (n[1] * n[2])* (1 - cosf(theta)) - n[0] * sinf(theta), (n[2] * n[2])* (1 - cosf(theta)) + cosf(theta), 0,
			0.f, 0.f, 0.f, 1.f
		};
		Matrix* RMat = new Matrix(data);
		PreMultiply(*RMat);
		delete RMat;
		delete[] data;
	}
	void Matrix::RotateWithAxis(AXIS axis, float theta)
	{

		float* data;
		if (axis == AXIS::X)
		{
			data = new float[16]{
				1.f, 0.f, 0.f, 0.f,
				0.f, cosf(theta), sinf(theta), 0.f,
				0.f, -sinf(theta), cosf(theta), 0.f,
				0.f, 0.f, 0.f, 1.f
			};
		}
		else if (axis == AXIS::Y)
		{
			data = new float[16]{
				cosf(theta), 0, -sinf(theta),0,
				0, 1, 0, 0,
				sinf(theta), 0, cosf(theta),0,
				0, 0, 0, 1
			};
		}
		else
		{
			data = new float[16]{
				cosf(theta), sinf(theta), 0,0,
				-sinf(theta), cosf(theta), 0,0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		}
		Matrix* RMat = new Matrix(data);
		PreMultiply(*RMat);
		delete RMat;
		delete[] data;
	}
	void Matrix::Scale(AXIS axis, float scale)
	{
		float* data;
		if (axis == AXIS::X)
		{
			data = new float[16]
			{
				scale, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		}
		else if (axis == AXIS::Y)
		{
			data = new float[16]
			{
				1, 0, 0, 0,
				0, scale, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		}
		else
		{
			data = new float[16]
			{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, scale, 0,
				0, 0, 0, 1
			};
		}
		Matrix* RMat = new Matrix(data);
		PreMultiply(*RMat);
		delete RMat;
		delete[] data;
	}
	void Matrix::Scale(Vector3 scale)
	{
		float* data = new float[16]
		{
			scale[0], 0, 0, 0,
			0, scale[1], 0, 0,
			0, 0, scale[2], 0,
			0, 0, 0, 1
		};
		Matrix* RMat = new Matrix(data);
		PreMultiply(*RMat);
		delete RMat;
		delete[] data;
	}
	void Matrix::Scale(Vector3 n, float k)
	{
		float* data = new float[16]
		{
			1 + (k -1)* n[0] * n[0], (k - 1)*n[0] *n[1], (k - 1)* n[0] * n[2], 0,
			(k - 1)* n[0] * n[1], 1 + (k - 1) * n[1] * n[1], (k - 1)* n[1] * n[2], 0,
			(k - 1)* n[0] * n[2], (k - 1)* n[1] * n[2], 1 + (k - 1) * n[2] * n[2], 0,
			0, 0, 0, 1
		};
		Matrix* RMat = new Matrix(data);
		PreMultiply(*RMat);
		delete RMat;
		delete[] data;
	}
	Vector3 Matrix::getAxis(AXIS axis)
	{
		const auto& mat = (*this);
		if (axis == AXIS::X)
		{
			return Vector3({ mat[0][0], mat[0][1], mat[0][2] });
		}
		else if (axis == AXIS::Y)
		{
			return Vector3({ mat[1][0], mat[1][1], mat[1][2] });
		}
		else
		{
			return Vector3({ mat[2][0], mat[2][1], mat[2][2] });
		}
	}
}
