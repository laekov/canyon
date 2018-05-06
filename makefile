cc = g++ -g -Iheaders
headers = $(wildcard headers/*.hh)
objects = $(headers:headers/%.hh=obj/%.o)
sources = $(headers:headers/%.hh=src/%.cc)
testsrc = $(wildcard test/*.cc)
# cvopt := $(shell pkg-config --libs opencv --cflags) -mmacosx-version-min=10.9
cvopt = 

tests = $(testsrc:test/%.cc=bin/%)

default : mkdir $(objects) bin/main

bin/% : src/%.cc $(objects)
	$(cc) $(cvopt) $< $(objects) -o $@

obj/camera.o : src/camera.cc headers/camera.hh $(headers)
	$(cc) $(cvopt) -c $< -o $@

obj/%.o : src/%.cc headers/%.hh  $(headers)
	$(cc) -c $< -o $@

mkdir :
	@if [ ! -d obj ]; then mkdir obj; fi
	@if [ ! -d bin ]; then mkdir bin; fi
clean :
	rm -rf obj bin
