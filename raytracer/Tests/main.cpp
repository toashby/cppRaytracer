#include <iostream>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Geometry>

#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Cube.h"
#include "Geometry.h"
#include "Light.h"
#include "Material.h"
#include "Scene.h"

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);

    //std::cout<<"Raytracer Tests\n";

    return RUN_ALL_TESTS();
}

TEST(Vec3,defaultCtor){
    Eigen::Vector3f a={-0.1f, 0.2f, 1.5f};
    EXPECT_FLOAT_EQ(a(0),-0.1f);
    EXPECT_FLOAT_EQ(a(1),0.2f);
    EXPECT_FLOAT_EQ(a(2),1.5f);
}

TEST(Sphere,defaultCtor){
    Sphere s = Sphere(Eigen::Vector3f(0,0,-1), 0.5, new lambertian(Eigen::Vector3f(0.8, 0.3, 0.3)));
    EXPECT_FLOAT_EQ(s.m_radius,0.5f);
}

TEST(Sphere, hit){ //Test a ray which goes through a sphere
    Sphere s(Eigen::Vector3f(10.0f, 10.0f, 10.0f), 4.0f, new lambertian(Eigen::Vector3f(0.8, 0.3, 0.3)));
    Ray r(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    hit_record rec;
    EXPECT_TRUE(s.hit(r, 0, 1000, rec));
}

TEST(Sphere, miss){ //test a ray which misses a sphere
    Sphere s(Eigen::Vector3f(0.0f, 0.0f, 1.0f), 4.0f, new lambertian(Eigen::Vector3f(0.8, 0.3, 0.3)));
    Ray r(Eigen::Vector3f(5.0f, 5.0f, 5.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    hit_record rec;
    EXPECT_FALSE(s.hit(r, 0, 1000, rec));

}

TEST(Camera,defaultCtor){
    //Camera c;
}

TEST(Cube,defaultCtor){
    //Cube c;
}

TEST(Light,defaultCtor){
    Light l;
}

TEST(Material,defaultCtor){
    lambertian l = lambertian(Eigen::Vector3f(0.8, 0.3, 0.3));
    EXPECT_FLOAT_EQ(l.albedo(0),0.8f);
    EXPECT_FLOAT_EQ(l.albedo(1),0.3f);
    EXPECT_FLOAT_EQ(l.albedo(2),0.3f);
}

TEST(Ray,defaultCtor){
    Ray r;
}

TEST(Scene,defaultCtor){
    Scene s;
}

TEST(Triangle,defaultCtor){
    //Triangle t(Eigen::Vector3f(0.0f,0.0f,0.0f), Eigen::Vector3f(2.0f,2.0f,2.0f), Eigen::Vector3f(1.0f,0.0f,0.0f));
}
