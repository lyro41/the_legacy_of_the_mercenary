#pragma once
#ifndef  GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <cstdlib>

class Vector;

class Point
{

public:
	double x, y;

	Point(double x = 0, double y = 0);
	Point operator + (Vector v2);
	bool operator == (Point p2);
	bool operator != (Point p2);
};

class Vector
{

public:
	double x, y;

	Vector(double x = 0, double y = 0);
	Vector(Point p1, Point p2);
	Vector operator * (double k);
	Vector operator / (double k);
	Vector operator + (Vector v2);
	double abs();
	Vector normalize(double k);
};

class Segment
{

public:
	Point p1, p2;

	Segment();
	Segment(Point p1, Point p2);
	Vector vectorize();
};

class Line
{

public:
	Point p1, p2;

	Line();
	Line(Point p1, Point p2);
	Vector vectorize();
};

double distance(Line line, Point p);

Point intersection(Line AB, Line CD);

double dotProduct(Vector v1, Vector v2);

double crossProduct(Vector v1, Vector v2);

const double NO_POINT_X = -738264;

#endif // GEOMETRY_H
