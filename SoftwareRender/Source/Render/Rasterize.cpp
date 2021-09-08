#include "Rasterize.h"
#include "Renderer.h"

namespace ZYH
{
	void Rasterize::DrawLine(const Vector2u& p1, const Vector2u& p2, uint32_t color, Renderer* render)
	{
		if (p1.X() == p2.X() && p1.Y() == p2.Y())
			render->DrawPixel(p1, color);
		else if (p1.X() == p2.X())
		{
			auto x = p1.X();
			auto minY = min(p1.Y(), p2.Y());
			auto maxY = max(p1.Y(), p2.Y());
			for (uint32_t y = minY; y < maxY; ++y)
				render->DrawPixel(x, y, color);
		}
		else
		{
			// Bresenham
			uint32_t diff = 0;
			uint32_t dx = std::abs(int(p1.X()) - int(p2.X()));
			uint32_t dy = std::abs(int(p1.Y()) - int(p2.Y()));
			if (dx > dy)
			{
				Vector2u pStart = p1;
				Vector2u pEnd = p2;
				if (pStart.X() > pEnd.X())
					std::swap(pStart, pEnd);
				for (uint32_t x = pStart.X(), y = pStart.Y(); x < pEnd.X(); ++x)
				{
					render->DrawPixel(x, y, color);
					diff += dy;
					if (diff >= dx)
					{
						diff -= dx;
						y += (pStart.Y() < pEnd.Y()) ? 1 : -1;
					}
				}
				render->DrawPixel(pEnd.X(), pEnd.Y(), color);
			}
			else
			{
				Vector2u pStart = p1;
				Vector2u pEnd = p2;
				if (pStart.Y() > pEnd.Y())
					std::swap(pStart, pEnd);
				for (uint32_t y = pStart.Y(), x = pStart.X(); y < pEnd.Y(); ++y)
				{
					render->DrawPixel(x, y, color);
					diff += dx;
					if (diff >= dy)
					{
						diff -= dy;
						x += (pStart.X() < pEnd.X()) ? 1 : -1;
					}
				}
				render->DrawPixel(pEnd.X(), pEnd.Y(), color);
			}

		}

		
	}
}

