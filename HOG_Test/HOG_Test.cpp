#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <string>
#include <vector>

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
	cv::Mat img = cv::imread("test1.jpg");
	printMatMember(img);
	cv::imshow("原图", img);

	//转为灰度图
	cv::Mat img_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	printMatMember(img_gray);
	cv::imshow("灰度图", img_gray);

	//改变尺寸
	cv::Mat img_gray_resize;
	cv::resize(img_gray, img_gray_resize, cv::Size(64, 128));
	printMatMember(img_gray_resize);
	cv::imshow("尺寸变换", img_gray_resize);

	//提取特征
	std::vector<float> descriptor;
	// 窗口大小         块大小            块滑动增量        胞元大小        梯度方向数
	// winSize(64,128), blockSize(16,16), blockStride(8,8), cellSize(8, 8), nbins(9),
	// nBins表示在一个胞元（cell）中统计梯度的方向数目，例如nBins=9时，在一个胞元内统计9个方向的梯度直方图，每个方向为180/9=20
	cv::HOGDescriptor hog(cv::Size(64, 128), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
	hog.compute(img_gray_resize, descriptor);

	//一个 win(窗口) 包含 [(64-16)/8+1] * [(128-16)/8+1] = 105 个 block
	//一个 block 包含 4 个 cell ，一个 win(窗口) 包含 105*4 = 420 个 cell
	//一个 cell 中的梯度直方图的数量为 9，一个 win(窗口) 中梯度直方图的数量为 420*9 = 3780
	//Hog特征维数 3780
	std::cout << "hog descriptor vector size: " << descriptor.size() << std::endl;


	cv::waitKey(0);
}