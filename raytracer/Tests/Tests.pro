TARGET=rayTracerTests
SOURCES += main.cpp\
           ../Raytracer/src/Ray.cpp\
           ../Raytracer/src/Sphere.cpp
LIBS+= -lgtest
INCLUDEPATH += ../Raytracer/include
