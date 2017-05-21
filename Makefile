OBJECTS=GLMath.o float3.o float2.o mat4.o Quaternion.o Shaders.o ObjectContainer.o OpenGL.o ObjectsBase.o Objects.o
OUT=test

PREFIX=/usr/local

make: ./lib/libreindeergl.a

all: test ./lib/libreindeergl.a

install:
	mkdir -p $(PREFIX)/include/reindeergl/
	cp -f ./lib/* $(PREFIX)/lib/
	cp -f ./include/* $(PREFIX)/include/reindeergl/

test: main.cpp SpringMesh.cpp SpringMesh.h $(OBJECTS)
	g++ -o $(OUT) --std=c++11 -O2 SpringMesh.cpp main.cpp $(OBJECTS) -lGLEW -lGLU -lglut -lGL -lSOIL

clean:
	rm *.o $(OUT) ./lib/*

./lib/libreindeergl.a: $(OBJECTS)
	mkdir -p ./lib
	g++ -o $(OUT) -shared $(OBJECTS) -lGLEW -lGLU -lglut -lGL -lSOIL -o ./lib/libreindeergl.so
	mkdir -p ./include
	cp -f ./*.h ./include/

OpenGL.o: OpenGL.cpp
	g++ -fPIC -c -o OpenGL.o --std=c++11 -O2 OpenGL.cpp

GLMath.o: GLMath.cpp
	g++ -fPIC -c -o GLMath.o --std=c++11 -O2 GLMath.cpp

ObjectContainer.o: ObjectContainer.cpp
	g++ -fPIC -c -o ObjectContainer.o --std=c++11 -O2 ObjectContainer.cpp

Objects.o: Objects.cpp ObjectsBase.o
	g++ -fPIC -c -o Objects.o --std=c++11 -O2 Objects.cpp

ObjectsBase.o: ObjectsBase.cpp
	g++ -fPIC -c -o ObjectsBase.o --std=c++11 -O2 ObjectsBase.cpp

float3.o: float3.cpp
	g++ -fPIC -c -o float3.o --std=c++11 -O2 float3.cpp

float2.o: float2.cpp
	g++ -fPIC -c -o float2.o --std=c++11 -O2 float2.cpp

mat4.o: mat4.cpp
	g++ -fPIC -c -o mat4.o --std=c++11 -O2 mat4.cpp

Quaternion.o: Quaternion.cpp
	g++ -fPIC -c -o Quaternion.o --std=c++11 -O2 Quaternion.cpp

Shaders.o: Shaders.cpp
	g++ -fPIC -c -o Shaders.o --std=c++11 -O2 Shaders.cpp

Text2D.o: Text2D.cpp
	g++ -fPIC -c -o Text2D.o --std=c++11 -O2 Text2D.cpp
