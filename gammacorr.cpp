#include<cv.h>
#include<highgui.h>
#include<cmath>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	const char* imagename = argc > 1 ? argv[1] : "lena.jpg";
	IplImage* img = 0;
	int h, w, step, channels, i, j, k;
	uchar *data;
    img = cvLoadImage(imagename, CV_LOAD_IMAGE_UNCHANGED);
    h = img->height;
	w = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;
	int gamma = 2;
	IplImage* trans = cvCreateImage(cvGetSize(img), 8, channels);
	int trans_step;
	trans_step = trans->widthStep;
	cvPow(img, trans, gamma);
	cvConvertScaleAbs(trans, trans, 1, 0);
	cvNamedWindow("OpenCV", CV_WINDOW_AUTOSIZE);
	cvShowImage("OpenCV", trans);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&trans);
	return 0;
}
