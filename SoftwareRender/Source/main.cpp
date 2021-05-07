#include "Utils/Math/TVec.h"
#include "Utils/Math/TMatrix.h"

#include <iostream>

int main()
{
	// test for matrix
	zyh::TMatrix<float, 3, 3> mat({
		1,2,3,
		4,5,6,
		7,8,9
		});
	std::cout << mat << std::endl;
	std::cout << mat.transpose() << std::endl;

	// test for vector
	zyh::TVec3<float> vec1({ 1, 2, 3 });
	zyh::TVec3<float> vec2({ 1, 2, 3 });
	std::cout << vec1 << std::endl;
	std::cout << vec1.dot(vec2) << std::endl;

}
