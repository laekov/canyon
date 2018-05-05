#include <define.hh>
#include <scene.hh>
#include <triangle.hh>

#include <queue>

#ifdef DEBUG_OUT
#include <iostream>
#endif

namespace Canyon {
	void Scene::load(std::istream& fin) {
		this->triangles.clear();
		Triangle t;
		while (fin >> t.a >> t.b >> t.c >> t.col) {
			this->triangles.push_back(t);
		}
	}

	Colors Scene::getRayResult(Ray init_r) {
		std::queue<Ray> rays;
		rays.push(init_r);
		Colors result;
		while (!rays.empty()) {
			Ray r(rays.front());
			rays.pop();
			Point3 p(ERROR_POINT);
			Triangle* res_obj;
			for (std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++ it) {
				Point3 q(it->rayCrossPoint(r));
				if (!q.isNaN()) {
					if (p.isNaN() || sgn((q - p) * (q - r.p)) < 0) {
						p = q;
						res_obj = &(*it);
					}
				}
			}
#ifdef DEBUG_OUT
			if (res_obj->col.isSource()) {
				std::cerr << "Light! " << res_obj->a << std::endl;
			}
			std::cerr << "Cross! " << p << std::endl;
#endif
			if (!p.isNaN()) {
				if (res_obj->col.isSource()) {
					result = result + r.c * res_obj->col;
#ifdef DEBUG_OUT
					std::cerr << "Light! " << result << std::endl;
#endif
				} else {
					std::vector<Ray> out_rays(res_obj->rayCrossOut(r));
					for (std::vector<Ray>::iterator out_ray = out_rays.begin(); out_ray != out_rays.end(); ++ out_ray) {
						out_ray->c = r.c;
						out_ray->darker(res_obj->col);
						if (out_ray->c.visible()) {
							rays.push(*out_ray);
						}
					}
				}
			}
		}
		return result;
	}
};
