#include <define.hh>
#include <curverot.hh>
#include <double.hh>

#include <iostream>

namespace Canyon {
	Point3 CurveRot::rayCrossPoint(Ray ray, void* tmp_addr) {
		Vector uv(this->v.unify());
		Poly equ;
		if (!sgn(ray.d * uv)) {
			double proj_len((ray.p - this->a) * uv);
			Point3 q(this->a + uv * proj_len);
			equ = this->x;
			equ[0] -= proj_len;
		} else {
			// (rx(t) + s)^2 = (y(t))^2
			Vector r(ray.d * (1. / (ray.d * uv)) - uv);
			Vector s(ray.p - this->a + ray.d * ((this->a * uv) / (ray.d * uv) -
					 (ray.p * uv) / (ray.d * uv)));
			// c2 (x(t))^2 + c1 x(t) + c0 = (y(t))^2
			double c2(r * r);
			double c1(r * s * 2.);
			double c0(s * s);
			equ = Poly(this->x.sqr() * c2 + this->y * c1 + c0 - this->y.sqr());
		}
		std::vector<double> sols(equ.getZeroPoints());
		Point3 closest_p(ERROR_POINT);
		for (auto i: sols) {
			double x(this->x(i));
			Point3 p_q(this->a + uv * x);
			double k((p_q * uv - ray.p * uv) / (ray.d * uv));
			Point3 crp(ray.p + k * ray.d);
			double len_const((crp - ray.p) * ray.d);
			if (sgn(len_const) > 0 && (closest_p.isNaN() ||
						len_const < ((closest_p - ray.p) * ray.d))) {
				closest_p = crp;
				if (tmp_addr) {
					*(double*)tmp_addr = i;
				}
			}
		}
		return closest_p;
	}

	std::vector<Ray> CurveRot::rayCrossOut(Ray ray) {
		std::vector<Ray> out_rays;
		double cros_t;
		Point3 p(this->rayCrossPoint(ray, (void*)&cros_t));
		if (!p.isNaN()) {
			Vector bx(this->v.unify());
			double x(this->x(cros_t));
			Point3 q(bx * x + this->a);
			Vector by((p - q).unify());
			Vector nf(bx * this->x.df(cros_t) + by * this->y.df(cros_t));
			this->getReflectAndRefracRay(ray, out_rays, nf, p);
			this->getDiffuseRay(ray, out_rays, nf, p);
		}
		return out_rays;
	}

	bool CurveRot::pointIn(Point3 p) {
		Vector uv(this->v.unify());
		double proj_len((p - this->a) * uv);
		double dist((p - (this->a + uv * proj_len)).len());
		Poly equ(this->x);
		equ[0] -= proj_len;
		auto sovs(equ.getZeroPoints());
		int cnt_out(0);
		for (auto i: sovs) {
			if (sgn(this->y(i) - dist) >= 0) {
				++ cnt_out;
			}
		}
		return cnt_out & 1;
	}

	void CurveRot::read(std::istream& fin) {
		fin >> this->a >> this->v >> this->col >> this->smooth >>
			this->alpha >> this->ray_n >> this->n;
		// Read point coordinators and transform to poly format
		double *x(new double[n]);
		double *y(new double[n]);
		for (int i = 0; i < n; ++ i) {
			fin >> x[i] >> y[i];
			if (i) {
				x[i] -= x[0];
			}
		}
		x[0] = 0.;
		double rat(this->v.len() / x[n - 1]);
		for (int i = 0; i < n; ++ i) {
			x[i] *= rat;
			y[i] *= rat;
		}
		Poly *px = new Poly[n];
		Poly *py = new Poly[n];
		Poly t(1);
		t[1] = 1., t[0] = 0;
		Poly mt(1);
		mt[1] = -1., mt[0] = 1.;
		for (int i = 0; i < n; ++ i) {
			px[i][0] = x[i];
			py[i][0] = y[i];
		}
		for (int i = 1; i < n; ++ i) {
			for (int j = 0; j + i < n; ++ j) {
				px[j] = px[j] * t + px[j + 1] * mt;
				py[j] = py[j] * t + py[j + 1] * mt;
			}
		}
		this->x = px[0];
		this->y = py[0];
		delete [] px;
		delete [] py;
	}
};
