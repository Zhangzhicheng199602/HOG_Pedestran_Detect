#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

void MatConstructor();
void Mat_size();
void Mat_elemSize();
void Mat_elemSize1();
void Mat_step(); //���� Mat �� step
void Mat_step1();


//int flags 4�ֽ� ��32λ �ӵ͵���(���λ��Ϊ32λ�����λ��Ϊ1λ)
void printMatMember(cv::Mat& img) {
	std::cout << "Mat.flags: " << img.flags << std::endl;
	std::cout << "Mat.dims(�����ά�ȣ�: " << img.dims << std::endl;
	std::cout << "Mat.rows(�����������: " << img.rows << std::endl;
	std::cout << "Mat.cols(�����������: " << img.cols << std::endl;
	std::cout << "Mat.size(����Ĵ�С��: " << img.size << std::endl;
	std::cout << "Mat.channels(����Ԫ�ص�ͨ������: " << img.channels() << std::endl;
	std::cout << "Mat.type(����Ԫ�ص��������ͣ�: " << img.type() << std::endl;
	std::cout << "Mat.depth(����Ԫ�ص�һ��ͨ�����������ͣ�: " << img.depth() << std::endl;
	//std::cout << "img(Python�����ʾ)=:" << std::endl << cv::format(img, cv::Formatter::FMT_PYTHON) << ";" << std::endl;
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
	//-----------------ָ�����͵Ķ�ά����------------------------

	//ָ���С��С�Ԫ������
	cv::Mat mat1(2, 3, CV_8UC3);
	std::cout << "mat1: 2��3�� " << std::endl;
	std::cout << "mat1.data: " << std::endl;
	std::cout << cv::format(mat1, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;

	//ָ����ά�����С��Ԫ������
	cv::Mat mat2(cv::Size(2, 3), CV_8UC3);
	std::cout << "mat2: 3��2�� " << std::endl;
	std::cout << "mat2.data: " << std::endl;
	std::cout << cv::format(mat2, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;

	//ָ����ά�����С��С�Ԫ�����͡�Ԫ�س�ʼ��ֵ
	cv::Mat mat3(2, 2, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat3: 2��2�� ��ʼ����0��0��255��" << std::endl;
	std::cout << "mat3.data: " << std::endl;
	std::cout << cv::format(mat3, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;

	//ָ����ά�����С��Ԫ�����͡�Ԫ�س�ʼ��ֵ
	cv::Mat mat4(cv::Size(2, 3), CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat4: 3��2�� ��ʼ����0��0��255��" << std::endl;
	std::cout << "mat4.data: " << std::endl;
	std::cout << cv::format(mat4, cv::Formatter::FMT_PYTHON) << std::endl;
	std::cout << std::endl;
}

void Mat_size() {
	std::cout << "��ά����2 �� 3 ��, һ��Ԫ�أ����ά��/ ����: 3�ֽ�" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.size : " << mat2.size() << std::endl;
	std::cout << "mat2.size[0] : " << mat2.size[0] << std::endl;
	std::cout << "mat2.size[1] : " << mat2.size[1] << std::endl;
	std::cout << std::endl;

	std::cout << "��ά����ά�ȴӸߵ��׵ĳߴ������ǣ�2��3��4,һ��Ԫ�أ����ά��/ ����: 3�ֽ�" << std::endl;
	int sz[3] = { 2, 3, 4 }; //ά���Ӹߵ��͵ĳߴ�
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "mat3.size[0] : " << mat3.size[0] << std::endl;
	std::cout << "mat3.size[1] : " << mat3.size[1] << std::endl;
	std::cout << "mat3.size[2] : " << mat3.size[2] << std::endl;
}

void Mat_elemSize() {
	std::cout << "��ά����2 �� 3 ��, һ��Ԫ�أ����ά��/ ����: 3�ֽ�" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.elemSize : " << mat2.elemSize() << std::endl;
	std::cout << std::endl;

	std::cout << "��ά����ά�ȴӸߵ��׵ĳߴ������ǣ�2��3��4,һ��Ԫ�أ����ά��/ ����: 3�ֽ�" << std::endl;
	int sz[3] = { 2, 3, 4 }; //ά���Ӹߵ��͵ĳߴ�
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "mat3.elemSize : " << mat3.elemSize() << std::endl;
}

void Mat_elemSize1() {
	std::cout << "��ά����2 �� 3 ��, һ��Ԫ�أ����ά��/ ����: 3�ֽ�(3ͨ����3�ֽ�)" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.elemSizel : " << mat2.elemSize1() << std::endl;
	std::cout << std::endl;

	std::cout << "��ά����2 �� 3 ��, һ��Ԫ�أ����ά��/ ����: 1�ֽ�(��ͨ��)" << std::endl;
	cv::Mat mat2_1(2, 3, CV_8UC1, cv::Scalar(0, 0, 255));
	std::cout << "mat2_1.elemSize1 : " << mat2_1.elemSize1() << std::endl;
	std::cout << std::endl;

	std::cout << "��ά����ά�ȴӸߵ��׵ĳߴ������ǣ�2��3��4,һ��Ԫ�أ����ά��/ ����: 3�ֽ�(3ͨ����3�ֽ�)" << std::endl;
	int sz[3] = { 2, 3, 4 }; //ά���Ӹߵ��͵ĳߴ�
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "mat3.elemSize1 : " << mat3.elemSize1() << std::endl;
}

void Mat_step() {
	//step ��ָÿһά��ӦԪ��(��ǰά�Ƚ�һά��ά��)�Ĵ�С

	std::cout << "��ά����2 �� 3 ��, һ��Ԫ�أ����ά��3�ֽ�" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC1, cv::Scalar(0, 0, 255));
	std::cout << "mat2.step[0] : " << mat2.step[0] << std::endl;
	std::cout << "mat2.step[1] : " << mat2.step[1] << std::endl;
	std::cout << std::endl;


	std::cout << "��ά����ά�ȴӸߵ��׵ĳߴ������ǣ�2��3��4" << std::endl;
	int sz[3] = { 2, 3, 4 }; //ά���Ӹߵ��͵ĳߴ�
	cv::Mat mat3(3, sz, CV_8UC1, cv::Scalar::all(0));
	std::cout << "����ά��Ԫ�صĴ�С���Ӹ�ά����ά�����ǣ�" << std::endl;
	std::cout << "mat3.step[0] : " << mat3.step[0] << std::endl;
	std::cout << "mat3.step[1] : " << mat3.step[1] << std::endl;
	std::cout << "mat3.step[2] : " << mat3.step[2] << std::endl;
}

void Mat_step1() {
	//step ��ָÿһά��ӦԪ��(��ǰά�Ƚ�һά��ά��)�Ĵ�С

	std::cout << "��ά����2 �� 3 ��, һ��Ԫ�أ����ά��3�ֽ�" << std::endl;
	cv::Mat mat2(2, 3, CV_8UC3, cv::Scalar(0, 0, 255));
	std::cout << "mat2.step1(0) : " << mat2.step1(0) << std::endl;
	std::cout << "mat2.step1(1) : " << mat2.step1(1) << std::endl;
	std::cout << std::endl;


	std::cout << "��ά����ά�ȴӸߵ��׵ĳߴ������ǣ�2��3��4" << std::endl;
	int sz[3] = { 2, 3, 4 }; //ά���Ӹߵ��͵ĳߴ�
	cv::Mat mat3(3, sz, CV_8UC3, cv::Scalar::all(0));
	std::cout << "����ά��Ԫ�صĴ�С���Ӹ�ά����ά�����ǣ�" << std::endl;
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