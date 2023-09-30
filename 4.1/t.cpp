#include <stdexcept>
#include "t.h"
using namespace std;

Transform::Transform(const Shape* shape)
{
	if (shape == nullptr)
	{
		throw invalid_argument{ "nullptr passed!" };
	}
	else
	{
		_shape = move(shape->clone());
	}
}

unique_ptr<Shape> Transform::shift(float x, float y, float z)
{
	for (auto& node : _shape->_nodes)
	{
		node.X += x;
		node.Y += y;
		node.Z += z;
	}
	return move(_shape);
}

unique_ptr<Shape> Transform::scale(float f)
{
	for (auto& node : _shape->_nodes)
	{
		node.X *= f;
		node.Y *= f;
		node.Z *= f;
	}
	return move(_shape);
}

unique_ptr<Shape> Transform::scale_X(float f)
{
	for (auto& node : _shape->_nodes)
	{
		node.X *= f;
	}
	return move(_shape);
}

unique_ptr<Shape> Transform::scale_Y(float f)
{
	for (auto& node : _shape->_nodes)
	{
		node.Y *= f;
	}
	return move(_shape);
}

unique_ptr<Shape> Transform::scale_Z(float f)
{
	for (auto& node : _shape->_nodes)
	{
		node.Z *= f;
	}
	return move(_shape);
}