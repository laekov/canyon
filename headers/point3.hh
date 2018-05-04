#ifndef POINT3_HH
#define POINT3_HH
class Point3 {
	public:
		double x, y, z;
		Point3(double x_ = 0, double y_ = 0, double z_ = 0): x(x_), y(y_), z(z_) {}
		Point3(const POINT3& p_): x(p_.x), y(p_.y), z(p_.z);
		double len();
		Point3 unify();
};
Point3 operator +(const Point3& a, const Point3& b);
Point3 operator -(const Point3& a, const Point3& b);
double operator *(const Point3& a, const Point3& b);
Point3 operator %(const Point3& a, const Point3& b);
#endif
