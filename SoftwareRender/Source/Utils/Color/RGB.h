#pragma once
#include <stdint.h>

namespace ZYH
{
	struct ZRGB
	{
		ZRGB(uint8_t r, uint8_t g, uint8_t b) : R(r), G(g), B(b){}
		ZRGB(uint32_t rgb) : R(uint8_t(rgb >> 16)), G(uint8_t(rgb >> 8)), B(uint8_t(rgb)) {}
		operator uint32_t(){ return (R << 16) | (G << 8) | B; }
		
		uint8_t R;
		uint8_t G;
		uint8_t B;
	};
}