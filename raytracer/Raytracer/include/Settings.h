#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <eigen3/Eigen/Geometry>
#include <vector>

class Settings
{
public:
    Settings()=default;

    unsigned int getSamples();
    unsigned int detBounceDepth();
    unsigned int getWidth();
    unsigned int getHeight();

private:
    unsigned int m_samples;
    unsigned int m_bounceDepth;
    unsigned int m_width;
    unsigned int m_height;
};

#endif
