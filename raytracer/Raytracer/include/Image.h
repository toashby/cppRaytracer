#ifndef IMAGE_H_
#define IMAGE_H_
#include <eigen3/Eigen/Geometry>

class Image{
public:
    Image()=default;
    Image(float width, float height);

    void setPixel(int x, int y, float r, float g, float b);


private:
    //todo add image file/class here/ needs library
    //maybe ImageMagick??
};

#endif
