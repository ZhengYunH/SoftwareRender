#pragma once
#include <algorithm>
#include <stdint.h>
#include "../Utils/Math/Vector.h"

namespace ZYH
{
	class Renderer;

	class Rasterize
	{
	public:
		void DrawLine(const Vector2u& p1, const Vector2u& p2, uint32_t color, Renderer* render);
	};
}