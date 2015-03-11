#ifndef _Point_h_
#define _Point_h_

struct Point
{
	float x, y;

	Point(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	Point()
	{
		x = 0;
		y = 0;
	}

	Point operator+(Point& Other)
	{
		Point Temp;
		Temp.x = x + Other.x;
		Temp.y = y + Other.y;
		return Temp;
	}

	Point operator-(Point& Other)
	{
		Point Temp;
		Temp.x = x - Other.x;
		Temp.y = y - Other.y;
		return Temp;
	}

	Point operator*(Point& Other)
	{
		Point Temp;
		Temp.x = x * Other.x;
		Temp.y = y * Other.y;
		return Temp;
	}

	void operator+=(Point& Other)
	{
		x += Other.x;
		y += Other.y;
	}

	void operator-=(Point& Other)
	{
		x -= Other.x;
		y -= Other.y;
	}

};

#endif