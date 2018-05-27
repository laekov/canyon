#include <object.hh>

namespace Canyon {
	const double alpha_count = .2;
	const double theta_count = .3;

	void Object::getDiffuseRay(Ray r, std::vector<Ray>& out_rays, Vector nf,
			                   Point3 cp) {
		if (this->smooth < 1.) {
			Vector u0(vertical(nf));
			Vector u1(nf % u0);
			double difc(sqrt(colorStrength(r.c) / color_visible_thres));
			int ea(alpha_count * difc);
			int et(theta_count * difc);
			double erat(log(ea * et + 3) / (ea * et));
			double cea(1. / (ea + 1));
			double cet(1. / et);
			for (int i = 0; i < ea; ++ i) {
				for (int j = 0; j < et; ++ j) {
					double theta((ea - i + randf()) * PI * .5 * cea);
					double alpha((j + randf()) * cet * PI * 2);
					Vector u(u0 * cos(alpha) + u1 * sin(alpha));
					Vector d(nf * cos(theta) + u * sin(theta));
					double weaken_rat((1. - this->smooth) * erat * cos(theta));
					out_rays.push_back(
					    Ray(cp, d, r.c * this->col * Colors(weaken_rat), 1));
				}
			}
		}
	}
};
