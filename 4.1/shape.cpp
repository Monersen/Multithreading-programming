#include <cmath>
#include <numbers>
#include "shape.h"
using namespace std;

Shape::Shape() {}

float Line::area() const
{
	return 0.0f;
}

float Line::volume() const
{
	return 0.0f;
}

unique_ptr<Shape> Line::clone() const
{
	return make_unique<Line>(*this);
}

Line::Line(Node null, Node one)
{
	_nodes.push_back(move(null));
	_nodes.push_back(move(one));
}

Rectangle::Rectangle(Node null, Node one, Node two, Node three)
{
	_nodes.push_back(move(null));
	_nodes.push_back(move(one));
	_nodes.push_back(move(two));
	_nodes.push_back(move(three));
}

float Rectangle::area() const
{
	if (_nodes[0].Z == 0.0f && _nodes[1].Z == 0.0f && _nodes[2].Z == 0.0f && _nodes[3].Z == 0.0f)
	{
		return abs(_nodes[0].X - _nodes[1].X) * abs(_nodes[0].Y - _nodes[3].Y);
	}
	else if (_nodes[0].Y == 0.0f && _nodes[1].Y == 0.0f && _nodes[2].Y == 0.0f && _nodes[3].Y == 0.0f)
	{
		return abs(_nodes[0].X - _nodes[1].X) * abs(_nodes[0].Z - _nodes[3].Z);
	}
	else
	{
		return abs(_nodes[0].Y - _nodes[1].Y) * abs(_nodes[0].Z - _nodes[3].Z);
	}
}

float Rectangle::volume() const
{
	return 0.0f;
}

unique_ptr<Shape> Rectangle::clone() const
{
	return make_unique<Rectangle>(*this);
}

Parallelepiped::Parallelepiped(Node null, Node one, Node two, Node three, Node four, Node five, Node six, Node seven) :
	Rectangle(null, one, two, three)
{
	_nodes.push_back(move(four));
	_nodes.push_back(move(five));
	_nodes.push_back(move(six));
	_nodes.push_back(move(seven));
}

float Parallelepiped::area() const
{
	float area_one{ abs(_nodes[0].X - _nodes[1].X) * abs(_nodes[0].Y - _nodes[3].Y) };
	float area_two{ abs(_nodes[0].X - _nodes[1].X) * abs(_nodes[0].Z - _nodes[4].Z) };
	float area_three{ abs(_nodes[0].Y - _nodes[3].Y) * abs(_nodes[0].Z - _nodes[0].Z) };
	return 2 * (area_one + area_two + area_three);
}

float Parallelepiped::volume() const
{
	return abs(_nodes[0].Y - _nodes[3].Y) * abs(_nodes[0].X - _nodes[1].X) * abs(_nodes[0].Z - _nodes[4].Z);
}

unique_ptr<Shape> Parallelepiped::clone() const
{
	return make_unique<Parallelepiped>(*this);
}

Circle::Circle(Node centre, float radius) : _radius(radius)
{
	_nodes.push_back(move(centre));
}

float Circle::area() const
{
	return static_cast<float>(numbers::pi * powf(_radius, 2.0f));
}

float Circle::volume() const
{
	return 0.0f;
}

unique_ptr<Shape> Circle::clone() const
{
	return make_unique<Circle>(*this);
}

Cylinder::Cylinder(Node centre, float radius, float hight) : Circle(centre, radius), _hight(hight) {}

float Cylinder::area() const
{
	return Circle::area() + 2 * _radius * _hight;
}

float Cylinder::volume() const
{
	return Circle::area() * _hight;
}

unique_ptr<Shape> Cylinder::clone() const
{
	return make_unique<Cylinder>(*this);
}