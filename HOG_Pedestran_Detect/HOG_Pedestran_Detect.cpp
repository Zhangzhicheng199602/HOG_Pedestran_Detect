#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FILEPATH "D:\\WorkPlace\\VisualStudio\\HOG_Pedestran_Detect\\HOG_Pedestran_Detect\\Pedestrians64x128\\"

void Train();
//void Detect();

int main() {

	Train();

	//Detect();

	return 0;
}

void Train() {

	//---------------------------����ѵ������ͼƬ·�������-------------------------------------
	
	std::vector<std::string> imagePath; //ͼƬ·��
	std::vector<int> imageClass; //ͼƬ���
	std::string buffer;
	std::ifstream trainingData(std::string(FILEPATH) + "TrainData.txt");

	if (!trainingData.is_open()) {
		std::cout << "file open failed" << std::endl;
	}

	int numOfLine = 0;
	while (!trainingData.eof()) {

		std::getline(trainingData, buffer);

		//std::cout << buffer << std::endl;

		if (!buffer.empty()) {

			numOfLine++;

			if (numOfLine % 2 == 0) {
				//��ȡ�������
				imageClass.push_back(atoi(buffer.c_str()));
			} else {
				//��ȡͼ��·��
				imagePath.push_back(std::string(FILEPATH) + buffer);
			}
		}
		
	}

	trainingData.close();

	//-----------------------------------��ȡ������ HOG ����-----------------------------------------

	//��������
	int numOfSample = numOfLine / 2;

	//���������������� n x 3780
	//һ��һ�� 3780 ά�� HOG �������� ��һ��һ��������������
	cv::Mat featureVectorOfSample(numOfSample, 3780, CV_32FC1);

	//������������ n x 1
	cv::Mat classOfSample(numOfSample, 1, CV_32SC1);

	cv::Mat convertedImg;
	cv::Mat trainImg;

	for (std::vector<std::string>::size_type i = 0; i < imagePath.size(); i++) {

		std::cout << "Processing: " << imagePath[i] << std::endl;
		//��ȡѵ������ͼƬ
		cv::Mat src = cv::imread(imagePath[i], -1);

		if (src.empty()) {
			std::cout << "can not load the image:" << imagePath[i] << std::endl;
			continue;
		}

		cv::resize(src, trainImg, cv::Size(64, 128));

		//ָ�����ڴ�С��block��С��block����������cell��С��bin����
		cv::HOGDescriptor hog(cv::Size(64, 128), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);

		//�������� HOG ����
		std::vector<float> descriptors;

		//���� HOG ����
		hog.compute(trainImg, descriptors);

		//HOG ����ά��
		std::cout << "hog feature vector: " << descriptors.size() << std::endl;

		//���õ���HOG������������������������
		for (std::vector<float>::size_type j = 0; j < descriptors.size(); j++)
		{
			featureVectorOfSample.at<float>(i, j) = descriptors[j];
		}
		//��������Ӧ������������������
		classOfSample.at<int>(i, 0) = imageClass[i];
	}

	//size����ֵ [�� x ��]
	std::cout << "size of featureVectorOfSample: " << featureVectorOfSample.size() << std::endl;
	std::cout << "size of classOfSample: " << classOfSample.size() << std::endl;

	//-------------------------------ʹ��SVM������ѵ��------------------------------------------------
	//���ò���
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();

	//C_SVC : C��֧�����������,n����� (n >= 2)���������쳣ֵ�ͷ�����C���в���ȫ����
	svm->setType(cv::ml::SVM::C_SVC);

	//LINEAR �����ںˡ�û���κ���ӳ������ά�ռ䣬�������֣���ع飩��ԭʼ�����ռ��б���ɣ���������ѡ��
	svm->setKernel(cv::ml::SVM::LINEAR);

	//
	svm->setTermCriteria(cv::TermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON));

	//ѵ��SVM
	svm->train(featureVectorOfSample, cv::ml::ROW_SAMPLE, classOfSample);

	//����ѵ���õķ����������а�����SVM�Ĳ�����֧������������rho��
	svm->save(std::string(FILEPATH) + "classifier.xml");
	
	/*
	SVMѵ����ɺ�õ���XML�ļ����棬��һ�����飬����support vector������һ�����飬����alpha,��һ��������������rho;
	��alpha����ͬsupport vector��ˣ�ע�⣬alpha*supportVector,���õ�һ������������������ǰ�����-1��֮���ٸ���������������һ��Ԫ��rho��
	��ˣ���õ���һ�������������ø÷�������ֱ���滻opencv�����˼��Ĭ�ϵ��Ǹ���������cv::HOGDescriptor::setSVMDetector()����
	*/
	//��ȡ֧������
	cv::Mat supportVector = svm->getSupportVectors();

	//��ȡalpha��rho
	cv::Mat alpha;
	cv::Mat svIndex;
	float rho = svm->getDecisionFunction(0, alpha, svIndex);

	//ת������:����һ��Ҫע�⣬��Ҫת��Ϊ32��
	cv::Mat alpha2;
	alpha.convertTo(alpha2, CV_32FC1);

	//������������������
	cv::Mat result(1, 3780, CV_32FC1);
	result = alpha2 * supportVector;

	//����-1������Ϊʲô�����-1��
	//ע����Ϊsvm.predictʹ�õ���alpha*sv*another-rho�����Ϊ���Ļ�����Ϊ������������HOG�ļ�⺯���У�ʹ��rho+alpha*sv*another(anotherΪ-1)
	//for (int i = 0;i < 3780;i++)
		//result.at<float>(0, i) *= -1;

	//�����������浽�ļ�������HOGʶ��
	//��������������б����Ĳ���(��)��HOG����ֱ��ʹ�øò�������ʶ��
	std::ofstream ofile;
	ofile.open(std::string(FILEPATH) + "HOG_SVM.txt");
	for (int i = 0; i < 3780; i++)
	{
		ofile << result.at<float>(0, i) << std::endl;
	}
	ofile << rho;
	ofile.close();
}

void printImgPath(const std::vector<std::string> &path) {
	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i] << std::endl;
	}
}