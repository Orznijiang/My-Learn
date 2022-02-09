#include <cmath>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

int main(){
    Eigen::Vector3f p(2.0, 1.0, 1.0);
    Eigen::Matrix3f mat;
    mat <<
        std::cos(45.0f / 180.0f * M_PI), -std::sin(45.0f / 180.0f * M_PI), 1.0,
        std::sin(45.0f / 180.0f * M_PI), std::cos(45.0f / 180.0f * M_PI), 2.0,
        0.0, 0.0, 1.0;
    std::cout << mat * p << std::endl;
    return 0;
}
