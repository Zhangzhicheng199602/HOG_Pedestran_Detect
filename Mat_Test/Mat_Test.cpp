#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

void MatConstructor();
void Mat_size();
void Mat_elemSize();
void Mat_elemSize1();
void Mat_step(); //测试 Mat 的 step
void Mat_step1();


//int flags 4字节 共32位 从低到高(最高位称为32位，最低位称为1位)
void printMatMember(cv::Mat& img) {
	std::cout << "Mat.flags: " << img.flags << std::endl;
	std::cout << "Mat.dims(矩阵的维度）: " << img.dims << std::endl;
	std::cout << "Mat.rows(矩阵的行数）: " << img.rows << std::endl;
	std::cout << "Mat.cols(矩阵的列数）: " << img.cols << std::endl;
	std::cout << "Mat.size(矩阵的大小）: " << img.size << std::endl;
	std::cout << "Mat.channels(矩阵元素的通道数）: " << img.channels() << std::endl;
	std::cout << "Mat.type(矩阵元素的数据类型）: " << img.type() << std::endl;
	std::cout << "Mat.depth(矩阵元素的一个通道的数据类型）: " << img.depth() << std::endl;
	//std::cout << "img(Python风格显示)=:" << std::endl << cv::format(img, cv::Formatter::FMT_PYTHON) << ";" << std::endl;
	std::cout << std::endl;
}

int main() {
	//MatConstructor();
	//Mat_size();
	//Mat_elemSize();
	//Mat_elemSize1();
	//Mat_step();
	//Mat_step1();
	return 0;
}

void MatConstructor() {
	//-----------------指定类型的二维数组------------------------

	//指定行、列、元素类型
	cv::Mat mat1(2, 3, CV_8UC3);
	std::cout << "mat1: 2行3列 " << std::endl;
	std::cout << "mat1.data: " << std::endl;
	std::cout << cv::format(mat1, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;

	//指定二维数组大小、元素类型
	cv::Mat mat2(cv::Size(2, 3), CV_8UC3);
	std::cout << "mat2: 3行2列 " << std::endl;
	std::cout << "mat2.data: " << std::endl;
	std::cout << cv::format(mat2, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;

	//指定二维数组行、列、元素类型、元素初始化值
	cv::Mat mat3(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat3: 2行2列 初始化（0，0，255）" << std::endl;
	std::cout << "mat3.data: " << std::endl;
	std::cout << cv::format(mat3, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;

	//指定二维数组大小、元素类型、元素初始化值
	cv::Mat mat4(cv::Size(2, 3), CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat4: 3行2列 初始化（0，0，255）" << std::endl;
	std::cout << "mat4.data: " << std::endl;
	std::cout << cv::format(mat4, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;
}

void Mat_size() {
	std::cout << "二维矩阵：2 行 3 列, 一个元素（最低维）/ 像素: 3字节" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.size : " << mat2.size() << std::endl;
	std::cout << "mat2.size[0] : " << mat2.size[0] << std::endl;
	std::cout << "mat2.size[1] : " << mat2.size[1] << std::endl;
	std::cout << std::endl;

	std::cout << "三维矩阵：维度从高到底的尺寸依次是：2，3，4,一个元素（最低维）/ 像素: 3字节" << std::endl;
	int sz[3] = { 2, 3, 4 }; //维都从高到低的尺寸
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "mat3.size[0] : " << mat3.size[0] << std::endl;
	std::cout << "mat3.size[1] : " << mat3.size[1] << std::endl;
	std::cout << "mat3.size[2] : " << mat3.size[2] << std::endl;
}

void Mat_elemSize() {
	std::cout << "二维矩阵：2 行 3 列, 一个元素（最低维）/ 像素: 3字节" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.elemSize : " << mat2.elemSize() << std::endl;
	std::cout << std::endl;

	std::cout << "三维矩阵：维度从高到底的尺寸依次是：2，3，4,一个元素（最低维）/ 像素: 3字节" << std::endl;
	int sz[3] = { 2, 3, 4 }; //维都从高到低的尺寸
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "mat3.elemSize : " << mat3.elemSize() << std::endl;
}

void Mat_elemSize1() {
	std::cout << "二维矩阵：2 行 3 列, 一个元素（最低维）/ 像素: 3字节(3通道共3字节)" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.elemSizel : " << mat2.elemSize1() << std::endl;
	std::cout << std::endl;

	std::cout << "二维矩阵：2 行 3 列, 一个元素（最低维）/ 像素: 1字节(单通道)" << std::endl;
	cv::Mat mat2_1(2, 3, CV_8UC1, cv::Scalar(0, 0, 255));
	std::cout << "mat2_1.elemSize1 : " << mat2_1.elemSize1() << std::endl;
	std::cout << std::endl;

	std::cout << "三维矩阵：维度从高到底的尺寸依次是：2，3，4,一个元素（最低维）/ 像素: 3字节(3通道共3字节)" << std::endl;
	int sz[3] = { 2, 3, 4 }; //维都从高到低的尺寸
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "mat3.elemSize1 : " << mat3.elemSize1() << std::endl;
}

void Mat_step() {
	//step 是指每一维对应元素(当前维度降一维的维度)的大小

	std::cout << "二维矩阵：2 行 3 列, 一个元素（最低维）3字节" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC1, cv::Scalar(0, 0, 255));
	std::cout << "mat2.step[0] : " << mat2.step[0] << std::endl;
	std::cout << "mat2.step[1] : " << mat2.step[1] << std::endl;
	std::cout << std::endl;


	std::cout << "三维矩阵：维度从高到底的尺寸依次是：2，3，4" << std::endl;
	int sz[3] = { 2, 3, 4 }; //维都从高到低的尺寸
	cv::Mat mat3(3, sz, CV_8UC1, cv::Scalar::all(0));
	std::cout << "各个维度元素的大小，从高维到低维依次是：" << std::endl;
	std::cout << "mat3.step[0] : " << mat3.step[0] << std::endl;
	std::cout << "mat3.step[1] : " << mat3.step[1] << std::endl;
	std::cout << "mat3.step[2] : " << mat3.step[2] << std::endl;
}

void Mat_step1() {
	//step 是指每一维对应元素(当前维度降一维的维度)的大小

	std::cout << "二维矩阵：2 行 3 列, 一个元素（最低维）3字节" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.step1(0) : " << mat2.step1(0) << std::endl;
	std::cout << "mat2.step1(1) : " << mat2.step1(1) << std::endl;
	std::cout << std::endl;


	std::cout << "三维矩阵：维度从高到底的尺寸依次是：2，3，4" << std::endl;
	int sz[3] = { 2, 3, 4 }; //维都从高到低的尺寸
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "各个维度元素的大小，从高维到低维依次是：" << std::endl;
	std::cout << "mat3.step1(0) : " << mat3.step1(0) << std::endl;
	std::cout << "mat3.step1(1) : " << mat3.step1(1) << std::endl;
	std::cout << "mat3.step1(2) : " << mat3.step1(2) << std::endl;
}

void test() {
	int sz[3] = { 4, 4, 4 };
	cv::Mat m(3, sz, CV_32FC3);
	cv::randu(m, -1.0f, 1.0f);

	float max = 0.0f;
	float len2;
	cv::MatConstIterator_<cv::Vec3f> it = m.begin<cv::Vec3f>();
	while (it != m.end<cv::Vec3f>()) {
		len2 = (*it)[0] * (*it)[0] + (*it)[1] * (*it)[1] + (*it)[2] * (*it)[2];
		if (len2 > max) {
			max = len2;
		}
		it++;
	}
	std::cout << max << std::endl;
}