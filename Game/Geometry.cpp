#include "Geometry.h"

Point::Point() {}

Point::Point(double x, double y) : x(x), y(y) {}



Vector::Vector(double x, double y) : x(x), y(y) {}

Vector Vector::operator*(double k)
{
	return Vector(x * k, y * k);
}

Vector Vector::operator+(Vector v2)
{
	return Vector(x + v2.x, y + v2.y);
}

double Vector::abs()
{
	return std::sqrt(x * x + y * y);
}



Segment::Segment() {}

Segment::Segment(Point p1, Point p2) : p1(p1), p2(p2) {}


/*
struct Point
{
	double x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
};

struct Line
{
	Point p1, p2;
	double length, projection_x, projection_y;
	Line() {}
	Line(Point p1, Point p2) : p1(p1), p2(p2)
	{
		length = pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 1 / 2.0);
		projection_x = std::fabs(p2.x - p1.x);
		projection_y = std::fabs(p2.y - p1.y);
	}
};

struct Segment
{
	Point p1, p2;
	double length, projection_x, projection_y;
	Segment() {}
	Segment(Point p1, Point p2) : p1(p1), p2(p2)
	{
		length = pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2), 1 / 2.0);
		projection_x = std::fabs(p2.x - p1.x);
		projection_y = std::fabs(p2.y - p1.y);
	}
};


Point intersection(Segment AB, Line CD)
{
	Point P(AB.p2.x + (CD.p2.x - AB.p1.x), AB.p2.y + (CD.p2.y - AB.p1.y));
	Segment DP(CD.p2, P);
	double h1 = std::fabs(DP.projection_x * CD.projection_y - DP.projection_y * CD.projection_x);
	double h2 = std::fabs(CD.projection_x * AB.projection_y - CD.projection_y * AB.projection_x) / AB.length;

}
*/