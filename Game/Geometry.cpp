#include "pch.h"
#include "Geometry.h"



Point::Point(double x, double y) : x(x), y(y) {}

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(Point p1, Point p2)
{
	x = p2.x - p1.x;
	y = p2.y - p1.y;
}

Vector Vector::operator * (double k)
{
	return Vector(x * k, y * k);
}

Vector Vector::operator / (double k)
{
	return Vector(x / k, y / k);
}

Vector Vector::operator + (Vector v2)
{
	return Vector(x + v2.x, y + v2.y);
}

double Vector::abs()
{
	return std::sqrt(x * x + y * y);
}

Vector Vector::normalize(double k)
{
	return Vector(x * k / abs(), y * k / abs());
}

Point Point::operator + (Vector v2)
{
	return Point(x + v2.x, y + v2.y);
}


Segment::Segment() {}

Segment::Segment(Point p1, Point p2) : p1(p1), p2(p2) {}

Vector Segment::vectorize()
{
	return Vector(p2.x - p1.x, p2.y - p1.y);
}



Line::Line() {}

Line::Line(Point p1, Point p2) : p1(p1), p2(p2) {}

Vector Line::vectorize()
{
	return Vector(p2.x - p1.x, p2.y - p1.y);
}

double dotProduct(Vector v1, Vector v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

double crossProduct(Vector v1, Vector v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

double distance(Line line, Point p)
{
	return crossProduct(Vector(p, line.p1), Vector(p, line.p2)) / line.vectorize().abs();
}

Point intersection(Line AB, Line CD)
{
	if (crossProduct(AB.vectorize(), CD.vectorize()) == 0) return Point(NO_POINT_X, NO_POINT_X);
	double h1 = distance(Line(CD.p2, CD.p2 + AB.vectorize()), CD.p1);
	double h2 = distance(AB, CD.p1);
	Vector CtoD = CD.vectorize() * h2 / h1;
	return Point(CD.p1.x + CtoD.x, CD.p1.y + CtoD.y);
}