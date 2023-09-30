#pragma once
#include "shape.h"
using namespace std;

class Transform
{
public:
	Transform(const Shape* shape);
	unique_ptr<Shape> shift(float x, float y, float z);
	unique_ptr<Shape> scale(float f);
	unique_ptr<Shape> scale_X(float f);
	unique_ptr<Shape> scale_Y(float f);
	unique_ptr<Shape> scale_Z(float f);
private:
	unique_ptr<Shape> _shape;
};