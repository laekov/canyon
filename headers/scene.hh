#ifndef SCENE_HH
#define SCENE_HH

#include <object.hh>

#include <istream>
#include <vector>

namespace Canyon {
	class Scene {
		public:
			std::vector<Object> triangles;
			void load(std::istream&);
			Colors getRayResult(Ray);
	};
};

#endif
