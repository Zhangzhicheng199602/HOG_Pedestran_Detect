#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <string>
#include <vector>

void printMatMember(cv::Mat& img) {
	std::cout << "Mat.dims(ά�ȣ�: " << img.dims << std::endl;
	std::cout << "Mat.rows(����������: " << img.rows << std::endl;
	std::cout << "Mat.cols(����������: " << img.cols << std::endl;
	std::cout << "Mat.size(�����С��: " << img.size << std::endl;
	std::cout << "Mat.channels(����ӵ�е�ͨ������: " << img.channels() << std::endl;
	std::cout << "Mat.elemSize(����һ��Ԫ��ռ�õ��ֽ�����: " << img.elemSize() << std::endl;
	std::cout << "Mat.elemSize1(����һ��ͨ��ռ�õ��ֽ�����: " << img.elemSize1() << std::endl;
	std::cout << "Mat.step[i] : " << img.step[0] << "," << img.step[1] << std::endl;
	std::cout << "Mat.stepl(i) : " << img.step1(0) << "," << img.step1(1) << std::endl;
	//std::cout << "img(Python�����ʾ)=:" << std::endl << cv::format(img, cv::Formatter::FMT_PYTHON) << ";" << std::endl;
	std::cout << std::endl;
}

int main() {
	cv::Mat img = cv::imread("test1.jpg");
	printMatMember(img);
	cv::imshow("ԭͼ", img);

	//תΪ�Ҷ�ͼ
	cv::Mat img_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	printMatMember(img_gray);
	cv::imshow("�Ҷ�ͼ", img_gray);

	//�ı�ߴ�
	cv::Mat img_gray_resize;
	cv::resize(img_gray, img_gray_resize, cv::Size(64, 128));
	printMatMember(img_gray_resize);
	cv::imshow("�ߴ�任", img_gray_resize);

	//��ȡ����
	std::vector<float> descriptor;
	// ���ڴ�С         ���С            �黬������        ��Ԫ��С        �ݶȷ�����
	// winSize(64,128), blockSize(16,16), blockStride(8,8), cellSize(8, 8), nbins(9),
	// nBins��ʾ��һ����Ԫ��cell����ͳ���ݶȵķ�����Ŀ������nBins=9ʱ����һ����Ԫ��ͳ��9��������ݶ�ֱ��ͼ��ÿ������Ϊ180/9=20
	cv::HOGDescriptor hog(cv::Size(64, 128), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
	hog.compute(img_gray_resize, descriptor);

	//һ�� win(����) ���� [(64-16)/8+1] * [(128-16)/8+1] = 105 �� block
	//һ�� block ���� 4 �� cell ��һ�� win(����) ���� 105*4 = 420 �� cell
	//һ�� cell �е��ݶ�ֱ��ͼ������Ϊ 9��һ�� win(����) ���ݶ�ֱ��ͼ������Ϊ 420*9 = 3780
	//Hog����ά�� 3780
	std::cout << "hog descriptor vector size: " << descriptor.size() << std::endl;


	cv::waitKey(0);
}