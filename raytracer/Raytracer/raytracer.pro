TARGET=raytracer


# where to put the .o files
OBJECTS_DIR=obj

# core Qt Libs to use add more here if needed.
QT+=gui opengl core

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle

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
    src/BoundingBox.cpp \
    src/NGLSceneMouseControls.cpp \
    src/NGLScene.cpp \
    src/MainWindow.cpp


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
          include/BoundingBox.h \
    include/WindowParams.h \
    include/NGLScene.h \
    include/MainWindow.h \
    include/GeometryList.h

FORMS+= $$PWD/ui/MainWindow.ui

INCLUDEPATH += include
cache()

OTHER_FILES+= README.md \
              shaders/*.glsl


NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}
