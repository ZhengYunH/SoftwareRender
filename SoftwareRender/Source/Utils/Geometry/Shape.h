#pragma once
#include <vector>
#include "Geometry.h"

namespace ZYH
{
	namespace CommonShape
	{
		std::vector<Vertex> SampleBox
		{
			{{-1.f, +1.f, -1.f}, {1.f, 0.f, 0.f, 1.f}},
			{{+1.f, +1.f, -1.f}, {0.f, 1.f, 0.f, 1.f}},
			{{+1.f, -1.f, -1.f}, {0.f, 0.f, 1.f, 1.f}},
			{{-1.f, +1.f, -1.f}, {1.f, 0.f, 1.f, 1.f}},

			{{-1.f, +1.f, +1.f}, {1.f, 0.f, 1.f, 1.f}},
			{{-1.f, +1.f, +1.f}, {1.f, 0.f,	0.f, 1.f}},
			{{-1.f, +1.f, +1.f}, {1.f, 0.f, 1.f, 1.f}},
			{{-1.f, +1.f, +1.f}, {0.f, 0.f, 1.f, 1.f}},
		};
	}
}