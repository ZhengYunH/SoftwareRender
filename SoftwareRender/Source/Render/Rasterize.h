#pragma once
#include <stdint.h>

namespace ZYH
{
	class Renderer;

	class Rasterize
	{
	public:
		void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color, Renderer* render);
	};
}