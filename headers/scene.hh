#ifndef SCENE_HH
#define SCENE_HH

#include <object.hh>
#include <triangle.hh>

#include <istream>
#include <vector>

namespace Canyon {
	class Scene {
		public:
			std::vector<Object*> objects;
			void load(const char*);
			Colors getRayResult(Ray);
	};
};

#endif
