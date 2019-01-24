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
    Sphere s = Sphere(Eigen::Vector3f(0,0,-1), 0.5, new lambertian(Eigen::Vector3f(0.8f, 0.3f, 0.3f)));
    EXPECT_FLOAT_EQ(s.m_radius,0.5f);
}

TEST(Sphere, hit){ //Test a ray which goes through a sphere
    Sphere s(Eigen::Vector3f(10.0f, 10.0f, 10.0f), 4.0f, new lambertian(Eigen::Vector3f(0.8f, 0.3f, 0.3f)));
    Ray r(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    hit_record rec;
    EXPECT_TRUE(s.hit(r, 0, 1000, rec));
}

TEST(Sphere, miss){ //test a ray which misses a sphere
    Sphere s(Eigen::Vector3f(0.0f, 0.0f, 1.0f), 4.0f, new lambertian(Eigen::Vector3f(0.8f, 0.3f, 0.3f)));
    Ray r(Eigen::Vector3f(5.0f, 5.0f, 5.0f), Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    hit_record rec;
    EXPECT_FALSE(s.hit(r, 0, 1000, rec));
}

TEST(Cube,defaultCtor){
    Cube c = Cube(new metal(Eigen::Vector3f(0.8f, 0.2f, 0.2f), 0.02f), Eigen::Vector3f(-1,0,-3), Eigen::Vector3f(-1.5,3,2), Eigen::Vector3f(-2,0,-1));//big back
    EXPECT_FLOAT_EQ(c.vert1(1), 3);
}

TEST(lambertian,defaultCtor){
    lambertian l = lambertian(Eigen::Vector3f(0.8f, 0.3f, 0.3f));
    EXPECT_FLOAT_EQ(l.m_albedo(0),0.8f);
    EXPECT_FLOAT_EQ(l.m_albedo(1),0.3f);
    EXPECT_FLOAT_EQ(l.m_albedo(2),0.3f);
}

TEST(metal, defaultCtor){
    metal m = metal(Eigen::Vector3f(0.8f, 0.3f, 0.3f), 0.5);
    EXPECT_FLOAT_EQ(m.m_albedo(0),0.8f);
    EXPECT_FLOAT_EQ(m.m_albedo(1),0.3f);
    EXPECT_FLOAT_EQ(m.m_albedo(2),0.3f);
}

TEST(Ray,defaultCtor){
    Ray r(Eigen::Vector3f(0.8f, 0.3f, 0.3f), Eigen::Vector3f(1.8f, 1.3f, 1.3f));
    EXPECT_FLOAT_EQ(r.m_origin(0),0.8f);
    EXPECT_FLOAT_EQ(r.m_origin(1),0.3f);
    EXPECT_FLOAT_EQ(r.m_origin(2),0.3f);

    EXPECT_FLOAT_EQ(r.m_direction(0),1.8f);
    EXPECT_FLOAT_EQ(r.m_direction(1),1.3f);
    EXPECT_FLOAT_EQ(r.m_direction(2),1.3f);
}

TEST(Scene,defaultCtor){
    Scene s;
    s.m_numSamples = 25;
    EXPECT_EQ(s.m_numSamples, 25);

    s.m_resx = 200;
    EXPECT_EQ(s.m_resx, 200);

    s.m_resy = 400;
    EXPECT_EQ(s.m_resy, 400);
}

