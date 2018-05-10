#include "Enhance.h"

void EnHance(Mat& InputImg,Mat& EnhanceImg)
{
	float mean;

	for (int i = 0; i < InputImg.rows-mbsize; i++)
	{
		for (int j = 0; j < InputImg.cols-mbsize; j++)
		{
			int sum = 0;
			for (int h = i; h < i + mbsize; h++)
			{
				uchar *InputImgRow = InputImg.ptr<uchar>(h);//��ʾָ���h+1�еĵ�һ��Ԫ�ص�ָ�룻
				for (int w = j; w < j+mbsize; w++)
					sum += InputImgRow[w];
			}  /*7*7�Ҷ�ֵ�ĺ�*/

			mean = sum / pixelnum;    /*7*7��ֵ*/

			mean = (int)(mean * 10000) / 10000.0;	/*����4λС��*/

			uchar PixelValue = InputImg.at<uchar>(i + center, j + center); /*��ǰ7*7�����ĵ��ֵ*/
			ThresBinary(mean, PixelValue);        /*PixelValue��ֵ�ָ�*/
			
			EnhanceImg.at<uchar>(i + center, j + center) = PixelValue;    /*��ǿͼ*/

		}
	}
}
void ThresBinary(float mean0, uchar& PixelValue)    /*��ֵ�ָ��ֵ��*/
{
	uchar PixelValue0 = PixelValue;

	if (PixelValue0 >= mean0 + th0) PixelValue = 255;//const static float th0 = 1.1;
	else PixelValue = 0;
}

int SeedFillNew(const Mat& _binImg, Mat& _lableImg,int& num)//������䷨�·���
{
	
	//FILE *fid = NULL;

	// fid = fopen("en37-4C-4-1.txt", "a");
	if (_binImg.empty() ||_binImg.type() != CV_8UC1)
	{
		return 0;//ԭ����return;
	}

	_lableImg.release();
	_binImg.convertTo(_lableImg, CV_32SC1);//ת���������ͣ�

	int label = 0; 

	int rows = _binImg.rows;
	int cols = _binImg.cols;

	Mat mask(rows, cols, CV_8UC1);
	mask.setTo(0);
	int *lableptr;
	for (int i = 0; i < rows; i++)
	{
		int* data = _lableImg.ptr<int>(i);
		uchar *masKptr = mask.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{   
		
			if (data[j] == 255 && mask.at<uchar>(i, j) != 1)
			{   
				int s = 0;//�Լ����
				mask.at<uchar>(i, j) = 1;
				std::stack<std::pair<int, int>> neighborPixels;
				neighborPixels.push(std::pair<int, int>(i, j)); // pixel position: <i,j>  
				++label; //begin with a new label  
				while (!neighborPixels.empty())
				{
					//get the top pixel on the stack and label it with the same label  
					std::pair<int, int> curPixel = neighborPixels.top();
					int curY = curPixel.first;
					int curX = curPixel.second;
					_lableImg.at<int>(curY, curX) = label;
					s++;//�Լ���ӣ�

					//pop the top pixel  
					neighborPixels.pop();

					//push the 4-neighbors(foreground pixels)  

					if (curX - 1 >= 0)
					{
						if (_lableImg.at<int>(curY, curX - 1) == 255 && mask.at<uchar>(curY, curX - 1) != 1) //leftpixel  
						{
							neighborPixels.push(std::pair<int, int>(curY, curX - 1));
							mask.at<uchar>(curY, curX - 1) = 1;
						}
					}
					if (curX + 1 <= cols - 1)
					{
						if (_lableImg.at<int>(curY, curX + 1) == 255 && mask.at<uchar>(curY, curX + 1) != 1)
							// right pixel  
						{
							neighborPixels.push(std::pair<int, int>(curY, curX + 1));
							mask.at<uchar>(curY, curX + 1) = 1;
						}
					}
					if (curY - 1 >= 0)
					{
						if (_lableImg.at<int>(curY - 1, curX) == 255 && mask.at<uchar>(curY - 1, curX) != 1)
							// up pixel  
						{
							neighborPixels.push(std::pair<int, int>(curY - 1, curX));
							mask.at<uchar>(curY - 1, curX) = 1;
						}
					}
					if (curY + 1 <= rows - 1)
					{
						if (_lableImg.at<int>(curY + 1, curX) == 255 && mask.at<uchar>(curY + 1, curX) != 1)
							//down pixel  
						{
							neighborPixels.push(std::pair<int, int>(curY + 1, curX));
							mask.at<uchar>(curY + 1, curX) = 1;
						}
					}
				}
			   //cout << "��" << label << "����ͨ�����Ϊ��" << s << endl;//�Լ���ӣ�
			  // fprintf(fid, "%d\n", s);
			   if (s >= 50)
				   ++num;

			}
		}
	}
	//fclose(fid);
	//cout << "��ͨ���������50����ĿΪ:" << num << endl;
	return label;
}