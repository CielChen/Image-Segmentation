/*------------------------------------------------------
function��ͼ��ָ�
reference��Efficient Graph-Based Image Segmentation,IJCV 2004,MIT
ԭ�ĵĴ�����Linux��ʵ�֣��ָ�ΪWindowsʵ�֣��ο���http://blog.csdn.net/ttransposition/article/details/38024605
------------------------------------------------------*/
#include <vector>  
#include <ctime>  
#include "opencv2/opencv.hpp"  
#include "segmentimage.h"  
  
using namespace std;  
using namespace cv;  
// Computer Vision A Reference Guide  
int main()  
{  
    const char* imagename = "F:\\Code\\Image Segmentation\\data\\RGB\\20170228111043_scene.jpg"; 
	//const char* imagename = "F:\\Code\\Image Segmentation\\data\\RGB\\HoloLens2.jpg"; 
    //���ļ��ж���ͼ��  
    Mat img = imread(imagename);  
  
    //�������ͼ��ʧ��  
    if (img.empty())  
    {  
        fprintf(stderr, "Can not load image %s\n", imagename);  
        return -1;  
    }  
  
    //��ʾͼ��  
    imshow("image", img);  
    //cvtColor(img, img, CV_BGR2Lab);// May be using lab color space will be better  
    Mat gray;  
    cvtColor(img, gray, CV_BGR2GRAY);  
    img.convertTo(img,CV_32FC3);  
  
    float sigma = 0.5;  
    float k = 500;  
    int min_size = 100;  
    int num_ccs;  
    clock_t tt = clock();  
    Mat result = segment_image(img, sigma, k, min_size, &num_ccs);  
  
  
    tt = clock() - tt;  
    float process_time = (float)tt / CLOCKS_PER_SEC;  
    cout << "get " << num_ccs << " components" << endl;  
  
    cout << "process time: " << process_time<<endl;  
    imshow("process result", result);  
	imwrite("F:\\Code\\Image Segmentation\\data\\segment\\20170228111043_scene.bmp",result);
      
    cvtColor(gray, gray, CV_GRAY2BGR);  
    imshow("overlay result", gray*0.25 + result*0.75);   //overlay��ɫ�����
	imwrite("F:\\Code\\Image Segmentation\\data\\segment\\20170228111043_scene_overlay.bmp",gray*0.25 + result*0.75);
  
    //�˺����ȴ�������������������ͷ���  
    waitKey();  
  
    return 0;  
  
}  