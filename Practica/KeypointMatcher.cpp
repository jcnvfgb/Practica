#include "KeypointMatcher.h"

KeypointMatcher::KeypointMatcher(float ratio_thresh, cv::Mat& img_object) {
	this->ratio_thresh = ratio_thresh;
	detector = cv::SIFT::create();
	matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
	obj_corners = std::vector<cv::Point2f>(4);
	scene_corners = std::vector<cv::Point2f>(4);

	cv::Mat img_object_gray;
	cv::cvtColor(img_object, img_object_gray, cv::COLOR_BGR2GRAY);
	detector->detectAndCompute(img_object_gray, cv::noArray(), keypoints_object, descriptors_object);
	obj_corners[0] = cv::Point2f(0, 0);
	obj_corners[1] = cv::Point2f((float)img_object.cols, 0);
	obj_corners[2] = cv::Point2f((float)img_object.cols, (float)img_object.rows);
	obj_corners[3] = cv::Point2f(0, (float)img_object.rows);
}

void KeypointMatcher::Set_Threshlod(float ratio_thresh) {
	this->ratio_thresh = ratio_thresh;
}

void KeypointMatcher::Set_Image_Object(cv::Mat& img_object) {
	cv::Mat img_object_gray;
	cv::cvtColor(img_object, img_object_gray, cv::COLOR_BGR2GRAY);
	detector->detectAndCompute(img_object_gray, cv::noArray(), keypoints_object, descriptors_object);
}

bool KeypointMatcher::Match(cv::Mat& src, cv::Mat& dst) {
	bool match_found = false;

	src.copyTo(dst);
	cv::cvtColor(src, img_scene_gray, cv::COLOR_BGR2GRAY);

	detector->detectAndCompute(img_scene_gray, cv::noArray(), keypoints_scene, descriptors_scene);
	matcher->knnMatch(descriptors_object, descriptors_scene, knn_matches, 2);

	for (size_t i = 0; i < knn_matches.size(); i++) {
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance) {
			good_matches.push_back(knn_matches[i][0]);
		}
	}

	for (size_t i = 0; i < good_matches.size(); i++) {
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}

	if (scene.size() > 3 && obj.size() > 3) {
		homography = findHomography(obj, scene, cv::RANSAC);
		if (!homography.empty()) {
			perspectiveTransform(obj_corners, scene_corners, homography);

			line(dst, scene_corners[0], scene_corners[1], cv::Scalar(0, 255, 0), 4);
			line(dst, scene_corners[1], scene_corners[2], cv::Scalar(0, 255, 0), 4);
			line(dst, scene_corners[2], scene_corners[3], cv::Scalar(0, 255, 0), 4);
			line(dst, scene_corners[3], scene_corners[0], cv::Scalar(0, 255, 0), 4);

			match_found = true;
		}
	}

	knn_matches.clear();
	good_matches.clear();
	scene.clear();
	obj.clear();
	keypoints_scene.clear();
	scene_corners.clear();

	return match_found;
}