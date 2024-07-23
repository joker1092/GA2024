#include "framework.h"
#include "Utill.h"

namespace Utill {
	float Clamp(float value, float min, float max)
	{
		if (value < min) return min;
		if (value > max) return max;
		float dist = abs(value - max);
		float closest = min;
		for (int i = min; i < max; i++)
		{
			if (abs(value - i) < dist)
			{
				dist = abs(value - i);
				closest = i;
			}
		}
		return closest;
	}

	float Distance(D2D_POINT_2F p1, D2D_POINT_2F p2)
	{
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}
};
