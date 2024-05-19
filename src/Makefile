CXX=g++
INCLUDE=-I../godot-cpp/include  -I../godot-cpp/gen/include -I../godot-cpp/gdextension
LIBRARY=-L../godot-cpp/bin -lgodot-cpp.linux.template_release.x86_64
DEFINES=-D TYPED_METHOD_BIND

all:
	$(CXX) eliza-gdextension.cpp -c -Wall $(INCLUDE) $(DEFINES) -std=c++20 -fPIC -o eliza-gdextension.o 
	$(CXX) -shared eliza-gdextension.o -Wall $(LIBRARY) -fPIC -o eliza-gdextension.linux.release.x86_64.so
	cp eliza-gdextension.linux.release.x86_64.so ../demo/bin
