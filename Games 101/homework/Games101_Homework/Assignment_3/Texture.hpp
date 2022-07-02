//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    Eigen::Vector3f getColorBilinear(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;

        auto u_img_2 = u_img;
        auto v_img_2 = v_img;
        auto s{ 0.0f };
        auto t{ 0.0f };
        if (round(u_img) > u_img) {
            u_img_2++;
            s = (u_img - floor(u_img)) - 0.5;
        }
        else {
            u_img_2--;
            s = 0.5 - (u_img - floor(u_img));
        }
        if (round(v_img) > v_img) {
            v_img_2++;
            t = (v_img - floor(v_img)) - 0.5;
        }
        else {
            v_img_2--;
            t = 0.5 - (v_img - floor(v_img));
        }
        
        auto u00 = image_data.at<cv::Vec3b>(v_img, u_img);
        auto u10 = image_data.at<cv::Vec3b>(v_img, u_img_2);
        auto u01 = image_data.at<cv::Vec3b>(v_img_2, u_img);
        auto u11 = image_data.at<cv::Vec3b>(v_img_2, u_img_2);
        Eigen::Vector3f u0{
            std::lerp(u00[0], u10[0], s),
            std::lerp(u00[1], u10[1], s),
            std::lerp(u00[2], u10[2], s),
        };
		Eigen::Vector3f u1{
	        std::lerp(u01[0], u11[0], s),
	        std::lerp(u01[1], u11[1], s),
	        std::lerp(u01[2], u11[2], s),
		};
        Eigen::Vector3f color{
            std::lerp(u0[0], u1[0], t),
            std::lerp(u0[1], u1[1], t),
            std::lerp(u0[2], u1[2], t),
        };

        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
