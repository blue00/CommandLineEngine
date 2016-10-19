#include "mathf.h"

namespace Mathf
{
	std::vector<Point> Raytrace(int x0, int y0, int x1, int y1)
	{
		std::vector<Mathf::Point> points;

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int x = x0;
		int y = y0;
		int n = 1 + dx + dy;
		int x_inc = (x1 > x0) ? 1 : -1;
		int y_inc = (y1 > y0) ? 1 : -1;
		int error = dx - dy;
		dx *= 2;
		dy *= 2;

		for (; n > 0; --n)
		{
			Mathf::Point newPoint;
			newPoint.x = x;
			newPoint.y = y;
			points.push_back(newPoint);

			if (error > 0)
			{
				x += x_inc;
				error -= dy;
			}
			else
			{
				y += y_inc;
				error += dx;
			}
		}

		return points;
	}
}