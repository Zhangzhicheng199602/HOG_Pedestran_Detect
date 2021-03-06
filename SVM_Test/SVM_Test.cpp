#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

int main(int argc, char** argv)
{
    // Set up training data 设置训练数据
    //设置训练数据的坐标，注意要和前面的Labels对应起来
    int labels[4] = { 1, -1, -1, -1 };
    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
    cv::Mat trainingDataMat(4, 2, CV_32F, trainingData);
    cv::Mat labelsMat(4, 1, CV_32SC1, labels);

    // Train the SVM
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, cv::ml::ROW_SAMPLE, labelsMat);
    // Data for visual representation
    int width = 512, height = 512;
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
    // Show the decision regions given by the SVM
    cv::Vec3b green(0, 255, 0), blue(255, 0, 0);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            cv::Mat sampleMat = (cv::Mat_<float>(1, 2) << j, i);
            float response = svm->predict(sampleMat);
            if (response == 1)
                image.at<cv::Vec3b>(i, j) = green;
            else if (response == -1)
                image.at<cv::Vec3b>(i, j) = blue;
        }
    }
    // Show the training data
    int thickness = -1;
    circle(image, cv::Point(501, 10), 5, cv::Scalar(0, 0, 0), thickness);
    circle(image, cv::Point(255, 10), 5, cv::Scalar(255, 255, 255), thickness);
    circle(image, cv::Point(501, 255), 5, cv::Scalar(255, 255, 255), thickness);
    circle(image, cv::Point(10, 501), 5, cv::Scalar(255, 255, 255), thickness);
    // Show support vectors
    thickness = 2;
    cv::Mat sv = svm->getUncompressedSupportVectors();
    for (int i = 0; i < sv.rows; i++)
    {
        const float* v = sv.ptr<float>(i);
        circle(image, cv::Point((int)v[0], (int)v[1]), 6, cv::Scalar(128, 128, 128), thickness);
    }
    imwrite("result.png", image);        // save the image
    imshow("SVM Simple Example", image); // show it to the user
    cv::waitKey();
    return 0;
}