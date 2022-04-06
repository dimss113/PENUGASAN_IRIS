#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int hmin = 0, smin = 35, vmin = 0;
int hmax = 41, smax = 255, vmax = 255;

int main(int argc, char** argv) {
    string path = "Resources/bola.jpg";
    Mat img = imread(path);
    Mat imgResize, imgHSV, imgFlip, imgEdit, mask;
    Point2f center;
    float radius;
    rotate(img, imgEdit, ROTATE_90_CLOCKWISE);
    resize(imgEdit, imgResize, Size(700, 1200));
    cvtColor(imgResize, imgHSV, COLOR_BGR2HSV);

    //namedWindow("Trackbars", (800, 800));
    //createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    //createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    //createTrackbar("sat Min", "Trackbars", &smin, 255);
    //createTrackbar("sat Max", "Trackbars", &smax, 255);
    //createTrackbar("Val Min", "Trackbars", &vmin, 255);
    //createTrackbar("Val Max", "Trackbars", &vmax, 255);
   
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++) {
        vector<Point>contours_lagi;
        contours_lagi = contours[i];
        minEnclosingCircle(contours_lagi, center, radius);
        if (radius >= 90 && radius <= 180) {
            circle(imgResize, center, radius, Scalar(255, 0, 0), 3);
            printf("x= %.2f, y= %.2f, rad= %.2f\n\n", center.x, center.y, radius);
        }
    }
    
    /*imshow("Image", img);*/
    /*imshow("Image HSV", imgHSV);*/
    /*imshow("Image Mask", mask);*/
    /*imshow("Image Edit", imgEdit);*/
    imshow("Image", imgResize);
    waitKey(0);

    //while (true) {

    //    
    //    Scalar lower(hmin, smin, vmin);
    //    Scalar upper(hmax, smax, vmax);
    //    inRange(imgHSV, lower, upper, mask);

    //    vector<vector<Point>> contours;
    //    vector<Vec4i> hierarchy;
    //    findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    //    for (int i = 0; i < contours.size(); i++) {
    //        vector<Point>contours_lagi;
    //        contours_lagi = contours[i];
    //        minEnclosingCircle(contours_lagi, center, radius);
    //        if (radius >= 90 && radius <= 180) {
    //            circle(imgResize, center, radius, Scalar(255, 0, 0), 3);
    //            printf("x= %.2f, y= %.2f, rad= %.2f\n\n", center.x, center.y, radius);
    //        }
    //    }
    //    
    //    /*imshow("Image", img);*/
    //    /*imshow("Image HSV", imgHSV);*/
    //    imshow("Image Mask", mask);
    //    /*imshow("Image Edit", imgEdit);*/
    //    imshow("Image", imgResize);
    //    waitKey(1);
    //}
    return 0;

}