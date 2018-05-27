#include <define.hh>
#include <scene.hh>
#include <triangle.hh>
#include <ball.hh>
#include <plane.hh>

#include <queue>
#include <string>

#ifdef DEBUG_OUT
#include <iostream>
#endif

namespace Canyon {
	void Scene::load(std::istream& fin) {
		for (auto it: this->objects) {
			delete &(*it);
		}
		this->objects.clear();
		std::string obj_name;
		while (fin >> obj_name) {
			if (obj_name == "triangle") {
				Triangle* t(new Triangle);
				fin >> t->a >> t->b >> t->c >> t->col >> t->smooth;
				this->objects.push_back(t);
			} else if (obj_name == "ball") {
				Ball* b(new Ball);
				fin >> b->c >> b->r >> b->col >> b->smooth >> b->alpha >> b->n;
				this->objects.push_back(b);
			}
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
			Object* res_obj;
			for (auto it: this->objects) {
				Object* o(it);
				Point3 q(o->rayCrossPoint(r));
				if (!q.isNaN()) {
					if (p.isNaN() || sgn((q - p) * (q - r.p)) < 0) {
						p = q;
						res_obj = o;
					}
				}
			}
			if (!p.isNaN()) {
				if (res_obj->col.isSource()) {
					result = result + r.c * res_obj->col;
				} else {
					std::vector<Ray> out_rays(res_obj->rayCrossOut(r));
					for (auto out_ray: out_rays) {
						if (out_ray.c.visible()) {
							rays.push(out_ray);
						}
					}
				}
			}
		}
		return result;
	}
};
