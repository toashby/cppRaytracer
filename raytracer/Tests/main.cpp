#include <iostream>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Geometry>

#include "Vec3.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Cube.h"
#include "Geometry.h"
#include "Image.h"
#include "Light.h"
#include "Load.h"
#include "Material.h"
#include "Object.h"
#include "Render.h"
#include "Scene.h"
#include "Settings.h"
#include "Triangle.h"

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);

    //std::cout<<"Raytracer Tests\n";

    return RUN_ALL_TESTS();
}

TEST(Vec3,userCtor){
    Vec3 a;
    EXPECT_FLOAT_EQ(a.x,0.0f);
    EXPECT_FLOAT_EQ(a.y,0.0f);
    EXPECT_FLOAT_EQ(a.z,0.0f);
}

TEST(Vec3,defaultCtor){
    Vec3 a={-0.1f, 0.2f, 1.5f};
    EXPECT_FLOAT_EQ(a.x,-0.1f);
    EXPECT_FLOAT_EQ(a.y,0.2f);
    EXPECT_FLOAT_EQ(a.z,1.5f);
}

TEST(Sphere,defaultCtor){
    Sphere s;
    EXPECT_FLOAT_EQ(s.getRadius(),0.0f);
}

TEST(Sphere,userCtor){
    Sphere s(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 4.0f);
    EXPECT_FLOAT_EQ(s.getRadius(),4.0f);
}

TEST(Sphere, hit){
    Sphere s(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 4.0f);
    Ray r(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    float t;
    Eigen::Vector3f q;
    EXPECT_TRUE(s.hit(r.getPosition(), r.getDirection(), t, q));

}

TEST(Sphere, miss){
    Sphere s(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 4.0f);
    Ray r(Eigen::Vector3f(5.0f, 5.0f, 5.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    float t;
    Eigen::Vector3f q;
    EXPECT_FALSE(s.hit(r.getPosition(), r.getDirection(), t, q));

}

TEST(Camera,defaultCtor){
    Camera c;
}

TEST(Cube,defaultCtor){
    Cube c;
}

TEST(Geometry,defaultCtor){
    Geometry g;
}

TEST(Image,defaultCtor){
    Image img;
}

TEST(Light,defaultCtor){
    Light l;
}

TEST(Load,defaultCtor){
    Load l;
}

TEST(Material,defaultCtor){
    Material m;
}

TEST(Ray,defaultCtor){
    Ray r;
}

TEST(Render,defaultCtor){
    //Render r; //no constructor yet
}

TEST(Scene,defaultCtor){
    Scene s;
}

TEST(Settings,defaultCtor){
    Settings s;
}

TEST(Triangle,defaultCtor){
    //Triangle t(Eigen::Vector3f(0.0f,0.0f,0.0f), Eigen::Vector3f(2.0f,2.0f,2.0f), Eigen::Vector3f(1.0f,0.0f,0.0f));
}
