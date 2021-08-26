#include "progress_bar.h"

float HueToRGB(float v1, float v2, float vH) {
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
}

void HSLToRGB(Color hsl, Color rgb) {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;

	unsigned char H = hsl[0];
	float S = (float)hsl[1] / 255;
	float L = (float)hsl[2] / 255;

	if (S == 0)
	{
		r = g = b = (unsigned char)(L * 255);
	}
	else
	{
		float v1, v2;
		float hue = (float)H / 255;

		v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
		v1 = 2 * L - v2;

		r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
		g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
		b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
	}

	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}
