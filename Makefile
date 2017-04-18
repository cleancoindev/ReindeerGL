OBJECTS=GLMath.o float3.o float2.o mat4.o Quaternion.o Shaders.o ObjectContainer.o OpenGL.o ObjectsBase.o Objects.o
OUT=test

make: main.cpp $(OBJECTS)
	g++ -o $(OUT) -std=c++11 -O2 main.cpp $(OBJECTS) -lGLEW -lGLU -lglut -lGL -lSOIL

clean:
	rm *.o
	rm $(OUT)

OpenGL.o: OpenGL.cpp
	g++ -c -o OpenGL.o --std=c++11 -O2 OpenGL.cpp

GLMath.o: GLMath.cpp
	g++ -c -o GLMath.o --std=c++11 -O2 GLMath.cpp

ObjectContainer.o: ObjectContainer.cpp
	g++ -c -o ObjectContainer.o --std=c++11 -O2 ObjectContainer.cpp

OpenGL.o: OpenGL.cpp
	g++ -c -o OpenGL.o --std=c++11 -O2 OpenGL.cpp

Objects.o: Objects.cpp ObjectsBase.o
	g++ -c -o Objects.o --std=c++11 -O2 Objects.cpp

ObjectsBase.o: ObjectsBase.cpp
	g++ -c -o ObjectsBase.o --std=c++11 -O2 ObjectsBase.cpp

float3.o: float3.cpp
	g++ -c -o float3.o --std=c++11 -O2 float3.cpp

float2.o: float2.cpp
	g++ -c -o float2.o --std=c++11 -O2 float2.cpp

mat4.o: mat4.cpp
	g++ -c -o mat4.o --std=c++11 -O2 mat4.cpp

Quaternion.o: Quaternion.cpp
	g++ -c -o Quaternion.o --std=c++11 -O2 Quaternion.cpp

Shaders.o: Shaders.cpp
	g++ -c -o Shaders.o --std=c++11 -O2 Shaders.cpp

Text2D.o: Text2D.cpp
	g++ -c -o Text2D.o --std=c++11 -O2 Text2D.cpp
