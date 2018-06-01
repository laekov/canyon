#include <object.hh>

namespace Canyon {
	const double alpha_count = .2;
	const double theta_count = .3;

	void Object::getReflectAndRefracRay(Ray ray, std::vector<Ray>& out_rays,
			                            Vector n, Point3 p) {
		if (sgn(n * ray.d) > 0) {
			n = n * -1.;
		}
		bool all_reflect(0);
		if (this->alpha > 0.) {
			double stheta(sin(acos(n * ray.d.unify())));
			if (this->pointIn(ray.p)) {
				stheta *= this->ray_n;
			} else {
				stheta /= this->ray_n;
			}
			if (stheta < 1.) {
				double theta(asin(stheta));
				Vector dn(n *(n * ray.d));
				Vector dvert(ray.d - dn);
				Vector refrac_direction(dn.unify() +
						dvert.unify() * tan(theta));
				Ray refrac(p, refrac_direction, 
						ray.c * this->col * 
						Colors(this->smooth) *
						Colors(this->alpha));
				out_rays.push_back(refrac);
			} else {
				all_reflect = 1;
			}
		}
		if (this->alpha < 1. || all_reflect) {
			Vector reflect_direction(reflectDirection(ray.d, n));
			if (sgn(n * reflect_direction) < 0) {
				reflect_direction = reflect_direction * -1.;
			}
			Ray refl(p, reflect_direction, ray.c * 
					this->col * Colors(this->smooth) *
					Colors(all_reflect ? 1. :
						   1. - this->alpha));
			out_rays.push_back(refl);
		}
	}

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
