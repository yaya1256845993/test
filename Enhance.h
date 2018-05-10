#include <iostream>
#include "opencv2/opencv.hpp"
#include <omp.h>
#include <io.h>
#include <string>  
#include <list>  
#include <vector>  
#include <map>  
#include <stack>
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  

using namespace std;
using namespace cv;


const static float mbsize = 7;
const static float th0 = 1.1;

const static float pixelnum = mbsize * mbsize, center = mbsize / 2;

void EnHance(Mat& InputImg, Mat& EnhanceImg);//��ǿ��
void ThresBinary(float mean0, uchar& PixelValue);//��ֵ�ָ��ֵ����
//void icvprCcaBySeedFill(Mat& _binImg, Mat& _lableImg);//������䷨��Ǳ����ͨ��
int SeedFillNew(const Mat& _binImg, Mat& _lableImg,int& num);
//Scalar GetRandomColor();
//void LabelColor(const Mat& labelImg, Mat& colorLabelImg, int labell);