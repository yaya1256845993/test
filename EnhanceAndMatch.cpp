//#include "ImageMatch.h"
#include "Enhance.h"

int main()
{
	/*预处理*/
	Mat ref = imread("56C.jpg");
	Mat ref1(ref.rows, ref.cols, CV_8UC1, Scalar::all(0));
	Mat EnhanceRef(ref.rows, ref.cols, CV_8UC1, Scalar::all(0));
	cv::cvtColor(ref, ref1, CV_BGR2GRAY); /*转换为单通道图像*/
	EnHance(ref1, EnhanceRef);
	ref1 = EnhanceRef;
	//imwrite("en31-4C-4.bmp", ref1);	
	//	imshow("Enhancedimage", ref1);
	//	waitKey(10);
	
	int cn=0;
	Mat labelImg;
	int count = SeedFillNew(ref1, labelImg, cn);
	cout << "连通域总数cout:" << count<< endl;
	cout << "连通域面积大于50的数目为:" << cn << endl;

}