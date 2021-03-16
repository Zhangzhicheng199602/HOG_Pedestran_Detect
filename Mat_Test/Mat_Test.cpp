#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
//int flags 4�ֽ� ��32λ �ӵ͵���(���λ��Ϊ32λ�����λ��Ϊ1λ)
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
	cv::Mat img = cv::imread("test.jpeg");
	
	return 0;
}