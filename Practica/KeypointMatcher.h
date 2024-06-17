#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

class KeypointMatcher {
private:
	float ratio_thresh;
	cv::Ptr<cv::SIFT> detector;
	std::vector<cv::KeyPoint> keypoints_object, keypoints_scene;
	cv::Mat descriptors_object, descriptors_scene;
	cv::Ptr<cv::DescriptorMatcher> matcher;
	std::vector<std::vector<cv::DMatch>> knn_matches;
	std::vector<cv::DMatch> good_matches;
	std::vector<cv::Point2f> obj;
	std::vector<cv::Point2f> scene;
	std::vector<cv::Point2f> obj_corners;
	std::vector<cv::Point2f> scene_corners;
	cv::Mat img_scene_gray, homography;

public:
	KeypointMatcher(float ratio_thresh, cv::Mat& img_object);

	void Set_Threshlod(float ratio_thresh);

	void Set_Image_Object(cv::Mat& img_object);

	bool Match(cv::Mat& src, cv::Mat& dst);
};

