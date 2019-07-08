#include <iostream>
#include <math.h>
#include <direct.h>
#include <stdio.h>
#include<io.h>
#include <fstream>  //ofstream类的头文件

#include "cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
const int m_threshold = 100;
char* src_dir = "G://Project//Project2//Project2//20190309//";
char* draw_dir = "G://Project//Project2//Project2//draw//";
char* qualified_dir = "G://Project//Project2//Project2//qualified//";
char* unqualified_dir = "G://Project//Project2//Project2//unqualified//";
char* abnormal_dir = "G://Project//Project2//Project2//abnormal//";

class CircularPicture {
public:

private:
	//圆心坐标、半径
	int x_pixel = 0;	
	int y_pixel = 0;
	int m_radius = 0;
	int nums_circle_indoor_point = 0;   //圆内像素的个数
	int nums_circle_indoor_point_good = 0;	//圆内无缺陷像素点的个数
	float percent_good = 0.0;	//圆的正常面积所占比例
};


int main() {
	bool getImageFileList(string dir, vector<string> &fileList);
	void circularDefectDetect(string src_dir, float threshold);

	circularDefectDetect(string(src_dir),0.2);

	waitKey(0);	
}


// 获取指定目录下所有bmp文件列表
bool getImageFileList(string dir, vector<string> &fileList)
{
	fileList.clear();
	const char *srcDir = dir.c_str();
	_finddata_t fileDir;
	intptr_t lfDir;
	char f[100] = { 0 };

	sprintf_s(f, "%s\\*.bmp", srcDir);
	if ((lfDir = _findfirst(f, &fileDir)) != -1L)
	{
		do
		{
			fileList.push_back(fileDir.name);
		} while (_findnext(lfDir, &fileDir) == 0);
		_findclose(lfDir);

		return true;
	}
	return false;
}

void circularDefectDetect(string src_dir, float threshold){

	int x_pixel = 0;
	int y_pixel = 0;
	int m_radius = 0;
	float percent_good = 0.0;
	vector<string> bmp_file_List;
	int nums_circle_indoor_point = 0;   //圆内像素的个数
	int nums_circle_indoor_point_good = 0;	//圆内无缺陷像素点的个数
	const char* draw_dir_filename = NULL;
	const char* src_dir_filename = NULL;
	const char* qualified_dir_filename = NULL;
	const char* unqualified_dir_filename = NULL;
	const char* abnormal_dir_filename = NULL;
	vector<Vec3f> circles;


	ofstream mycout("result.txt");
	getImageFileList(src_dir, bmp_file_List);
	int k = bmp_file_List.size();

	while (k--) {
		nums_circle_indoor_point = 0;   //圆内像素的个数
		nums_circle_indoor_point_good = 0;	//圆内无缺陷像素点的个数
		string tmp_src = string(src_dir) + bmp_file_List[k];
		src_dir_filename = tmp_src.c_str();
		//读取图片
		Mat src = imread(src_dir_filename);
		Mat gray;
		cvtColor(src, gray, CV_BGR2GRAY);
		Mat dst;
		medianBlur(gray, dst, 5);
		HoughCircles(dst, circles, HOUGH_GRADIENT, 1, 120, 100, 30, 0, 0);
		for (size_t i = 0; i < circles.size(); i++) {
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			//绘制圆心
			circle(src, center, 1, Scalar(0, 255, 0), 2);
			//绘制轮廓
			circle(src, center, radius, Scalar(0, 255, 0), 2);
			m_radius = radius;
			x_pixel = center.x;
			y_pixel = center.y;
		}
		IplImage* imgSrc = cvLoadImage(src_dir_filename, 0);
		uchar* pixel = NULL;
		//遍历整个图像的像素点，判断点是否在圆内，在圆内的点再判断是否为正常点
		for (int i = 0; i < imgSrc->height; i++)
		{
			for (int j = 0; j < imgSrc->width; j++)
			{
				pixel = (uchar*)(imgSrc->imageData + i*imgSrc->widthStep + j);
				if (sqrt((j - x_pixel) * (j - x_pixel) + (i - y_pixel) * (i - y_pixel)) < m_radius) {
					nums_circle_indoor_point++;
					if (((*pixel) + 0) > m_threshold)  //+0 隐式转换为整型
						nums_circle_indoor_point_good++;
				}
			}
		}
		percent_good = nums_circle_indoor_point_good / (nums_circle_indoor_point * 1.0);
		if (m_radius < ((imgSrc->width) / 4)) {
			string tmp = string(abnormal_dir) + bmp_file_List[k];
			abnormal_dir_filename = tmp.c_str();
			IplImage dest_draw = src;
			cvSaveImage(abnormal_dir_filename, &dest_draw);
		}
		else if (threshold >= (1 - percent_good)) {
			string tmp = string(qualified_dir) + bmp_file_List[k];
			qualified_dir_filename = tmp.c_str();
			IplImage dest_draw = src;
			cvSaveImage(qualified_dir_filename, &dest_draw);
		}
		else {
			string tmp = string(unqualified_dir) + bmp_file_List[k];
			unqualified_dir_filename = tmp.c_str();
			IplImage dest_draw = src;
			cvSaveImage(unqualified_dir_filename, &dest_draw);
		}

		mycout << k << " ," << bmp_file_List[k] << " 缺陷面积比例：" << 1 - percent_good << endl;

	}
	mycout.close();	//关闭txt文档
}


