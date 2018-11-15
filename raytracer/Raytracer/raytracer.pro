TARGET=raytracer
SOURCES += src/main.cpp \
    src/Ray.cpp \
    src/Sphere.cpp \
    src/Render.cpp \
    src/Load.cpp \
    src/Light.cpp \
    src/Camera.cpp \
    src/Object.cpp \
    src/Settings.cpp \
    src/Image.cpp \
    src/Scene.cpp \
    src/Material.cpp \
    src/Cube.cpp \
    src/Geometry.cpp \
    src/Triangle.cpp \
    src/BoundingBox.cpp


HEADERS+= include/Ray.h \
          include/Sphere.h \
          include/Vec3.h \
          include/Render.h \
          include/Load.h \
          include/Light.h \
          include/Camera.h \
          include/Object.h \
          include/Settings.h \
          include/Image.h \
          include/Scene.h \
          include/Material.h \
          include/Cube.h \
          include/Geometry.h \
          include/Triangle.h \
          include/BoundingBox.h


INCLUDEPATH += include
cache()
