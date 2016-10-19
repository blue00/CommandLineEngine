#pragma once

#include <vector>

namespace Mathf
{
	struct Point
	{
		int x;
		int y;
	};

	struct PointF
	{
		float x;
		float y;
	};

	std::vector<Point> Raytrace(int x0, int y0, int x1, int y1);
}