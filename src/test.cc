#include <iostream>

#include <point3.hh>
#include <plane.hh>
#include <triangle.hh>
#include <line.hh>
#include <ray.hh>

int main() {
	Canyon::Point3 O(0, 0, 0);
	Canyon::Point3 A(1, 0, 0);
	Canyon::Point3 B(0, 1, 0);
	Canyon::Triangle d(O, A, B, Canyon::Colors(0, 0, 0));
	Canyon::Ray r(Canyon::Point3(0, 0, 1), Canyon::Vector(1, 0, -1));
	Canyon::Vector rd(d.reflectDirection(r.d));
	std::cout << rd << std::endl;
}
