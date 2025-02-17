#include "draw.h"

__int32_t	map(t_color red, t_color green, t_color blue)
{
	__int32_t	result;

	// result = red.value*red.R_r * pow(16, 4) + green.value*green.R_r * pow(16, 2) + blue.value*blue.R_r;
		result = (int)(red.value * red.R_r) << 16  // 赤は上位16ビット
		   | (int)(green.value * green.R_r) << 8  // 緑は中間8ビット
		   | (int)(blue.value * blue.R_r);  // 青は下位8ビット
	return (result);
}

/*
	red.value * red.R_r = 255 * 0.3 = 76.5 → 76 (int変換)
	green.value * green.R_r = 255 * 0.3 = 76.5 → 76
	blue.value * blue.R_r = 255 * 0.3 = 76.5 → 76

	result = (76 << 16) | (76 << 8) | 76
			= 0x4C4C4C (16進数表記)
			= 5000268 (10進数)

	コメントアウトのやり方での計算
	result = 76 * pow(16, 4) + 76 * pow(16, 2) + 76
			= 5000268
*/