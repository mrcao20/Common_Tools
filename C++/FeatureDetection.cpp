#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2\xfeatures2d.hpp>
#include <windows.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int matchesThreshold = 20;
size_t featureNum = 0;
extern int roomNum;
string pictureName;

void readme();
Point2f find(Mat& img_object1, Mat& img_object2, Mat& img_scene);
Mat surf(int i, Mat& img_object, Mat& img_scene);
bool refineMatchesWithHomography(const std::vector<cv::KeyPoint>& queryKeypoints,const std::vector<cv::KeyPoint>& trainKeypoints,  
	float reprojectionThreshold,std::vector<cv::DMatch>& matches,cv::Mat& homography);
Point2f findPoint(Mat& img_object, Mat& img_matches, Mat& homography, int i);
Point2f find(Mat& img_character, Mat& img_scene);

Point2f find(Mat& img_character, Mat& img_scene)
{
	Mat H1;
	Point2f img_character_point;
	H1 = surf(0, img_character, img_scene);
	if(!H1.data){
		return Point2f(-1, -1);
	}
	img_character_point = findPoint(img_character, img_scene, H1, 1);
	return img_character_point;
}

bool refineMatchesWithHomography(const std::vector<cv::KeyPoint>& queryKeypoints,const std::vector<cv::KeyPoint>& trainKeypoints,  
float reprojectionThreshold,std::vector<cv::DMatch>& matches,cv::Mat& homography)  
{  
    const int minNumberMatchesAllowed = 8;  
    if (matches.size() < minNumberMatchesAllowed)  
        return false;  
    // Prepare data for cv::findHomography    
    std::vector<cv::Point2f> srcPoints(matches.size());  
    std::vector<cv::Point2f> dstPoints(matches.size());  
    for (size_t i = 0; i < matches.size(); i++)  
    {  
        srcPoints[i] = trainKeypoints[matches[i].trainIdx].pt;  
        dstPoints[i] = queryKeypoints[matches[i].queryIdx].pt;  
        //srcPoints[i] = trainKeypoints[i].pt;  
        //dstPoints[i] = queryKeypoints[i].pt;  
    }  
    // Find homography matrix and get inliers mask    
    std::vector<unsigned char> inliersMask(srcPoints.size());  
    homography = cv::findHomography(srcPoints,dstPoints,CV_FM_RANSAC,reprojectionThreshold,inliersMask);  
    std::vector<cv::DMatch> inliers;  
    for (size_t i = 0; i<inliersMask.size(); i++)  
    {  
        if (inliersMask[i])  
            inliers.push_back(matches[i]);  
    }  
    matches.swap(inliers);  
    return matches.size() > minNumberMatchesAllowed;  
}  

Mat surf(int i, Mat& img_object, Mat& img_scene)
{
	if( !img_object.data || !img_scene.data )
	{ std::cout<< " --(!) Error reading images " << std::endl; return Mat(); }

  Ptr<FeatureDetector> detector = FastFeatureDetector::create(20);

  std::vector<KeyPoint> keypoints_object, keypoints_scene;
  keypoints_object.resize(1000);
  keypoints_scene.resize(1000);
  detector->detect( img_object, keypoints_object );
  detector->detect( img_scene, keypoints_scene );

  Ptr<SURF>extractor = SURF::create();

  Mat descriptors_object, descriptors_scene;
  
  extractor->compute( img_object, keypoints_object, descriptors_object );
  extractor->compute( img_scene, keypoints_scene, descriptors_scene );
  

  FlannBasedMatcher matcher;

  std::vector< DMatch > matches;
  matcher.match( descriptors_object, descriptors_scene, matches );
  
  Mat homography;
  
  refineMatchesWithHomography(keypoints_object, keypoints_scene, 2.0, matches, homography);

  if(matches.size() < matchesThreshold){
	  return Mat();
  }
  featureNum = matches.size();
  cout << "roomNum:" << roomNum << " " << pictureName << ":" << featureNum << endl;

  //Mat img_matches;
  //drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
  //             matches, img_matches, Scalar::all(-1), Scalar::all(-1),
  //             vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
  ////imwrite( "test.jpg", img_matches );
  //imshow("aaa", img_matches);
  //waitKey();
  
  std::vector<Point2f> obj;
  std::vector<Point2f> scene;

  for( int i = 0; i < matches.size(); i++ )
  {
    obj.push_back( keypoints_object[ matches[i].queryIdx ].pt );
    scene.push_back( keypoints_scene[ matches[i].trainIdx ].pt );
  }
  
  Mat H = findHomography( obj, scene, CV_RANSAC );

  return H;
}

Point2f findPoint(Mat& img_object, Mat& img_scene, Mat& homography, int i)
{
  std::vector<Point2f> obj_corners(4);
  obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
  obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
  std::vector<Point2f> scene_corners(4);
  
  perspectiveTransform( obj_corners, scene_corners, homography);
  
  if(i == 0)
  {
	 scene_corners[2] -= Point2f(0, 21);
	 scene_corners[3] -= Point2f(0, 21);
  }

  return (scene_corners[2] + scene_corners[3]) / 2;
}