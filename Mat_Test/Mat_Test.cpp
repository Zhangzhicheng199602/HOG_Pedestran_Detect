#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
//int flags 4字节 共32位 从低到高(最高位称为32位，最低位称为1位)
void printMatMember(cv::Mat& img) {
	std::cout << "Mat.dims(维度）: " << img.dims << std::endl;
	std::cout << "Mat.rows(矩阵行数）: " << img.rows << std::endl;
	std::cout << "Mat.cols(矩阵列数）: " << img.cols << std::endl;
	std::cout << "Mat.size(矩阵大小）: " << img.size << std::endl;
	std::cout << "Mat.channels(矩阵拥有的通道数）: " << img.channels() << std::endl;
	std::cout << "Mat.elemSize(矩阵一个元素占用的字节数）: " << img.elemSize() << std::endl;
	std::cout << "Mat.elemSize1(矩阵一个通道占用的字节数）: " << img.elemSize1() << std::endl;
	std::cout << "Mat.step[i] : " << img.step[0] << "," << img.step[1] << std::endl;
	std::cout << "Mat.stepl(i) : " << img.step1(0) << "," << img.step1(1) << std::endl;
	//std::cout << "img(Python风格显示)=:" << std::endl << cv::format(img, cv::Formatter::FMT_PYTHON) << ";" << std::endl;
	std::cout << std::endl;
}

int main() {
	cv::Mat img = cv::imread("test.jpeg");
	
	return 0;
}