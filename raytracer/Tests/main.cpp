#include <iostream>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Geometry>

#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Cube.h"
#include "Geometry.h"
#include "Image.h"
#include "Light.h"
#include "Load.h"
#include "Material.h"
#include "Scene.h"
#include "Settings.h"
#include "Triangle.h"

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);

    //std::cout<<"Raytracer Tests\n";

    return RUN_ALL_TESTS();
}

TEST(Vec3,userCtor){
    Eigen::Vector3f a;
    EXPECT_FLOAT_EQ(a(0),0.0f);
    EXPECT_FLOAT_EQ(a(1),0.0f);
    EXPECT_FLOAT_EQ(a(2),0.0f);
}

TEST(Vec3,defaultCtor){
    Eigen::Vector3f a={-0.1f, 0.2f, 1.5f};
    EXPECT_FLOAT_EQ(a(0),-0.1f);
    EXPECT_FLOAT_EQ(a(1),0.2f);
    EXPECT_FLOAT_EQ(a(2),1.5f);
}

TEST(Sphere,defaultCtor){
    //Sphere s;
    //EXPECT_FLOAT_EQ(s.getRadius(),0.0f);
}

TEST(Sphere,userCtor){
    //Sphere s(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 4.0f);
    //EXPECT_FLOAT_EQ(s.getRadius(),4.0f);
}

TEST(Sphere, hit){ //Test a ray which goes through a sphere
    Sphere s(Eigen::Vector3f(10.0f, 10.0f, 10.0f), 4.0f, new lambertian(Eigen::Vector3f(0.8, 0.3, 0.3)));
    Ray r(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    float t;
    Eigen::Vector3f q;
    //EXPECT_TRUE(s.hit(r));
    //ASSERT_NE(t, 0);

}

TEST(Sphere, miss){ //test a ray which misses a sphere
    Sphere s(Eigen::Vector3f(0.0f, 0.0f, 1.0f), 4.0f, new lambertian(Eigen::Vector3f(0.8, 0.3, 0.3)));
    Ray r(Eigen::Vector3f(5.0f, 5.0f, 5.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    float t;
    Eigen::Vector3f q;
    //EXPECT_FALSE(s.hit(r));

}

TEST(Camera,defaultCtor){
    //Camera c;
}

TEST(Cube,defaultCtor){
    //Cube c;
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
    //Material m;
}

TEST(Ray,defaultCtor){
    Ray r;
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
