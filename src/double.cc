#include <double.hh>

int sgn(const double& x) {
	return x < -eps ? -1 : (x > eps ? 1 : 0);
}

double sqr(const double& x) {
	return x * x;
}
