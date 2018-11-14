TARGET=raytracer
SOURCES += src/main.cpp \
           #src/Particle.cpp\
           #src/Emitter.cpp
    src/Ray.cpp \
    src/Sphere.cpp

HEADERS+= include/Ray.h \
          include/Sphere.h \
          include/Vec3.h \

INCLUDEPATH += include
cache()
