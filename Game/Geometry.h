#pragma once
#ifndef  GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cstdlib>

namespace geom
{
	class Point;
	class Segment;
	class Line;
	class Vector;
}

class Point
{

public:
	double x, y;

	Point();
	Point(double x, double y);

};

class Vector
{

public:
	double x, y;

	Vector(double x = 0, double y = 0);
	Vector operator * (double k);
	Vector operator + (Vector v2);
	double abs();
};

class Segment
{

public:
	Point p1, p2;

	Segment();
	Segment(Point p1, Point p2);
	Vector Vectorize();
};

class Line
{

public:
	Point p1, p2;
	Line();
	Line(Point p1, Point p2);
};

#endif // GEOMETRY_H
