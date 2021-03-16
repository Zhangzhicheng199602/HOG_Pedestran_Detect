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

	//---------------------------读入训练样本图片路径和类别-------------------------------------
	
	std::vector<std::string> imagePath; //图片路径
	std::vector<int> imageClass; //图片类别
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
				//读取样本类别
				imageClass.push_back(atoi(buffer.c_str()));
			} else {
				//读取图像路径
				imagePath.push_back(std::string(FILEPATH) + buffer);
			}
		}
		
	}

	trainingData.close();

	//-----------------------------------获取样本的 HOG 特征-----------------------------------------

	//样本数量
	int numOfSample = numOfLine / 2;

	//样本特征向量矩阵 n x 3780
	//一行一个 3780 维的 HOG 特征向量 （一行一个样本的特征）
	cv::Mat featureVectorOfSample(numOfSample, 3780, CV_32FC1);

	//样本的类别矩阵 n x 1
	cv::Mat classOfSample(numOfSample, 1, CV_32SC1);

	cv::Mat convertedImg;
	cv::Mat trainImg;

	for (std::vector<std::string>::size_type i = 0; i < imagePath.size(); i++) {

		std::cout << "Processing: " << imagePath[i] << std::endl;
		//读取训练样本图片
		cv::Mat src = cv::imread(imagePath[i], -1);

		if (src.empty()) {
			std::cout << "can not load the image:" << imagePath[i] << std::endl;
			continue;
		}

		cv::resize(src, trainImg, cv::Size(64, 128));

		//指定窗口大小，block大小，block滑动增量，cell大小，bin数量
		cv::HOGDescriptor hog(cv::Size(64, 128), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);

		//用来保存 HOG 特征
		std::vector<float> descriptors;

		//计算 HOG 特征
		hog.compute(trainImg, descriptors);

		//HOG 特征维数
		std::cout << "hog feature vector: " << descriptors.size() << std::endl;

		//将得到的HOG特征放入样本特征向量矩阵
		for (std::vector<float>::size_type j = 0; j < descriptors.size(); j++)
		{
			featureVectorOfSample.at<float>(i, j) = descriptors[j];
		}
		//将特征对应的类别放入样本类别矩阵
		classOfSample.at<int>(i, 0) = imageClass[i];
	}

	//size返回值 [列 x 行]
	std::cout << "size of featureVectorOfSample: " << featureVectorOfSample.size() << std::endl;
	std::cout << "size of classOfSample: " << classOfSample.size() << std::endl;

	//-------------------------------使用SVM分类器训练------------------------------------------------
	//设置参数
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();

	//C_SVC : C类支持向量分类机,n类分组 (n >= 2)，允许用异常值惩罚因子C进行不完全分类
	svm->setType(cv::ml::SVM::C_SVC);

	//LINEAR 线性内核。没有任何向映射至高维空间，线性区分（或回归）在原始特征空间中被完成，这是最快的选择
	svm->setKernel(cv::ml::SVM::LINEAR);

	//
	svm->setTermCriteria(cv::TermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON));

	//训练SVM
	svm->train(featureVectorOfSample, cv::ml::ROW_SAMPLE, classOfSample);

	//保存训练好的分类器（其中包含了SVM的参数，支持向量，α和rho）
	svm->save(std::string(FILEPATH) + "classifier.xml");
	
	/*
	SVM训练完成后得到的XML文件里面，有一个数组，叫做support vector，还有一个数组，叫做alpha,有一个浮点数，叫做rho;
	将alpha矩阵同support vector相乘，注意，alpha*supportVector,将得到一个行向量，将该向量前面乘以-1。之后，再该行向量的最后添加一个元素rho。
	如此，变得到了一个分类器，利用该分类器，直接替换opencv中行人检测默认的那个分类器（cv::HOGDescriptor::setSVMDetector()），
	*/
	//获取支持向量
	cv::Mat supportVector = svm->getSupportVectors();

	//获取alpha和rho
	cv::Mat alpha;
	cv::Mat svIndex;
	float rho = svm->getDecisionFunction(0, alpha, svIndex);

	//转换类型:这里一定要注意，需要转换为32的
	cv::Mat alpha2;
	alpha.convertTo(alpha2, CV_32FC1);

	//结果矩阵，两个矩阵相乘
	cv::Mat result(1, 3780, CV_32FC1);
	result = alpha2 * supportVector;

	//乘以-1，这里为什么会乘以-1？
	//注意因为svm.predict使用的是alpha*sv*another-rho，如果为负的话则认为是正样本，在HOG的检测函数中，使用rho+alpha*sv*another(another为-1)
	//for (int i = 0;i < 3780;i++)
		//result.at<float>(0, i) *= -1;

	//将分类器保存到文件，便于HOG识别
	//这个才是真正的判别函数的参数(ω)，HOG可以直接使用该参数进行识别
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