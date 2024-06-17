#ifndef TEMPLATEMATCHER_H
#define TEMPLATEMATCHER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

class TemplateMatcher {
public:
    TemplateMatcher(const std::string& videoFilePath, const std::string& templateFilePath, double threshold);
    void match();

private:
    cv::VideoCapture video_;
    cv::Mat templateImg_;
    cv::Mat templateGray_;
    int templateWidth_;
    int templateHeight_;
    double threshold_;

    void matchFrame(const cv::Mat& frame);
};

#endif // TEMPLATEMATCHER_H