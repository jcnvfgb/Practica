#include "TemplateMatcher.h"
#include <iostream>

TemplateMatcher::TemplateMatcher(const std::string& videoFilePath, const std::string& templateFilePath, double threshold)
    : video_(cv::VideoCapture(videoFilePath)), templateImg_(cv::imread(templateFilePath, cv::IMREAD_COLOR)),
    templateGray_(), templateWidth_(templateImg_.cols), templateHeight_(templateImg_.rows), threshold_(threshold) {
    if (!video_.isOpened()) {
        throw std::runtime_error("Could not open video file");
    }
    if (templateImg_.empty()) {
        throw std::runtime_error("Could not load template image");
    }
    cv::cvtColor(templateImg_, templateGray_, cv::COLOR_BGR2GRAY);
}

void TemplateMatcher::match() {
    cv::Mat frame;
    while (video_.read(frame)) {
        matchFrame(frame);
    }
}

void TemplateMatcher::matchFrame(const cv::Mat& frame) {
    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

    cv::Mat result;
    cv::matchTemplate(frameGray, templateGray_, result, cv::TM_CCOEFF_NORMED);

    std::vector<cv::Point> points;

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            if (result.at<float>(i, j) >= 0.6) {
                bool flag = true;
                for (int k = 0; k < points.size(); k++) {
                    if (points[k].x > j - templateGray_.cols && points[k].x < j + templateGray_.cols
                        && points[k].y > i - templateGray_.rows && points[k].y < i + templateGray_.rows) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    points.push_back(cv::Point(j, i));
                }
            }
        }
    }

    system("cls");

    for (int i = 0; i < points.size(); i++) {
        std::cout << points[i].x << "\t" << points[i].y << "\n";
        cv::rectangle(frame, points[i], cv::Point(points[i].x + templateGray_.cols, points[i].y + templateGray_.rows), cv::Scalar(255, 0, 0), 2);
    }

    points.clear();

    // Отображаем обнаруженное изображение
    //if (max_val >= 0.6) {
    //  cv::rectangle(frame, max_loc, cv::Point(max_loc.x + template_image.cols, max_loc.y + template_image.rows), cv::Scalar(255, 0, 0), 2);
    //}

    // Отображаем кадр

    cv::imshow("Template Matcher", frame);
    cv::waitKey(30);
}