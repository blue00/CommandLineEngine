#include "mathf.h"
#include <limits> // for infinity

namespace Mathf
{
	std::vector<Point> Raytrace(int x0, int y0, int x1, int y1)
	{
		std::vector<Point> points;

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
			Point newPoint;
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

	std::vector<Point> Raytrace(float x0, float y0, float x1, float y1)
	{
		std::vector<Point> points;

		float dx = fabs(x1 - x0);
		float dy = fabs(y1 - y0);

		int x = int(floor(x0));
		int y = int(floor(y0));

		int n = 1;
		int x_inc, y_inc;
		float error;

		if (dx == 0)
		{
			x_inc = 0;
			error = std::numeric_limits<double>::infinity();
		}
		else if (x1 > x0)
		{
			x_inc = 1;
			n += int(floor(x1)) - x;
			error = (floor(x0) + 1 - x0) * dy;
		}
		else
		{
			x_inc = -1;
			n += x - int(floor(x1));
			error = (x0 - floor(x0)) * dy;
		}

		if (dy == 0)
		{
			y_inc = 0;
			error -= std::numeric_limits<float>::infinity();
		}
		else if (y1 > y0)
		{
			y_inc = 1;
			n += int(floor(y1)) - y;
			error -= (floor(y0) + 1 - y0) * dx;
		}
		else
		{
			y_inc = -1;
			n += y - int(floor(y1));
			error -= (y0 - floor(y0)) * dx;
		}

		for (; n > 0; --n)
		{
			Point newPoint;
			newPoint.x = x;
			newPoint.y = y;
			points.push_back(newPoint);

			if (error > 0)
			{
				y += y_inc;
				error -= dx;
			}
			else
			{
				x += x_inc;
				error += dy;
			}
		}

		return points;
	}
}