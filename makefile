cc = g++ -fopenmp --std=c++11 -g -Iheaders
headers = $(wildcard headers/*.hh) 
objects = $(headers:headers/%.hh=obj/%.o)
libobjects = obj/lodepng.o
sources = $(headers:headers/%.hh=src/%.cc)
testsrc = $(wildcard test/*.cc)

tests = $(testsrc:test/%.cc=bin/%)

default : mkdir $(objects) bin/main

bin/% : src/%.cc $(objects) $(libobjects)
	$(cc) $< $(objects) $(libobjects) -o $@

obj/lodepng.o : lodepng/lodepng.cpp lodepng/lodepng.h
	$(cc) -c $< -o $@

obj/%.o : src/%.cc headers/%.hh  $(headers)
	$(cc) -c $< -o $@

mkdir :
	@if [ ! -d obj ]; then mkdir obj; fi
	@if [ ! -d bin ]; then mkdir bin; fi
clean :
	rm -rf obj bin
