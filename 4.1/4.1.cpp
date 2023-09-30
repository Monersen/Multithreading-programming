#include <memory>
#include <format>
#include <iostream>
#include "shape.h"
#include "t.h"
using namespace std;

int main()
{
	// line
	Node l_null{ 1.0f, 2.0f, 3.0f };
	Node l_one{ 4.0f, 5.0f, 6.0f };
	unique_ptr<Shape> shape{ make_unique<Line>(l_null, l_one) };
	cout << format("line area: {:19.1f}\n", shape->area());
	cout << format("line volume: {:17.1f}\n", shape->volume());
	// rectangle
	Node r_null{ 1.0f, 1.0f, 0.0f };
	Node r_one{ 5.0f, 1.0f, 0.0f };
	Node r_two{ 5.0f, 5.0f, 0.0f };
	Node r_three{ 1.0f, 5.0f, 0.0f };
	shape.reset(new Rectangle(r_null, r_one, r_two, r_three));
	cout << format("\nrectangle area: {:15.1f}\n", shape->area());
	cout << format("rectangle volume: {:12.1f}\n", shape->volume());
	// parallelepiped
	Node p_null{ 1.0f, 1.0f, 1.0f };
	Node p_one{ 5.0f, 1.0f, 1.0f };
	Node p_two{ 5.0f, 5.0f, 1.0f };
	Node p_three{ 1.0f, 5.0f, 1.0f };
	Node p_four{ 1.0f, 1.0f, 7.0f };
	Node p_five{ 5.0f, 1.0f, 7.0f };
	Node p_six{ 5.0f, 5.0f, 7.0f };
	Node p_seven{ 1.0f,5.0f, 7.0f };
	shape.reset(new Parallelepiped(p_null,
		p_one,
		p_two,
		p_three,
		p_four,
		p_five,
		p_six,
		p_seven));
	cout << format("\nparallelepiped area: {:10.1f}\n", shape->area());
	cout << format("parallelepiped volume: {:8.1f}\n", shape->volume());
	cout << "\nscale parallelepiped up to 10 times\n";
	try
	{
		Transform transform(shape.get());
		auto transformed_shape{ transform.scale(10.0f) };
		cout << format("new parallelepiped area: {:8.1f}\n", transformed_shape->area());
		cout << format("new parallelepiped volume: {:5.1f}\n", transformed_shape->volume());
	}
	catch (const invalid_argument& ex)
	{
		cout << ex.what() << '\n';
	}
	Node c_centre{ 5.0f, 5.0f, 5.0f };
	shape.reset(new Circle(c_centre, 10));
	cout << format("\ncircle area: {:19.1f}\n", shape->area());
	cout << format("circle volume: {:15.1f}\n", shape->volume());
	shape.reset(new Cylinder(c_centre, 10, 100));
	cout << format("\ncylinder area: {:18.1f}\n", shape->area());
	cout << format("cylinder volume: {:17.1f}\n", shape->volume());
	return 0;
}