#ifndef SCENE_HH
#define SCENE_HH

#include <object.hh>
#include <triangle.hh>

#include <istream>
#include <vector>

namespace Canyon {
	class Scene {
		public:
			std::vector<Triangle> triangles;
			void load(std::istream&);
			Colors getRayResult(Ray);
	};
};

#endif
