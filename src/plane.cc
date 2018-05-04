#include "point3.hh"
#include "plane.hh"
#include "line.hh"

double lineCrossPlaneRatio(Line l, Plane p) {
	Vector nf(p.n.unify());
	double d((p.p - l.p) * nf);
	double lv_dot_nf(l.v * nf);
	return d / lv_dot_nf;
}

Point3 lineCrossPlane(Line l, Plane p) {
	double r(lineCrossPlaneRatio(l, p));
	return l.p + l.v * r;
}
