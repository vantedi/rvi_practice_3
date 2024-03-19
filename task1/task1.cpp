//Задание 1
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Mat image = imread("C:/Users/James-Bond/Downloads/гном.jpg");

    if (image.empty()) {
        cout << "ошибка загрузки картинки" << endl;
        return -1;
    }

    Mat blurredImage;
    GaussianBlur(image, blurredImage, Size(5, 5), 0);

    Mat grayImage;
    cvtColor(blurredImage, grayImage, COLOR_BGR2GRAY);

    Mat edges;
    Canny(grayImage, edges, 50, 150);

    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat contoursImage = Mat::zeros(edges.rows, edges.cols, CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(255, 255, 255);
        drawContours(contoursImage, contours, static_cast<int>(i), color, 2);
    }

    namedWindow("картинка", WINDOW_NORMAL);
    namedWindow("контуры", WINDOW_NORMAL);

    resizeWindow("картинка", 600, 524);
    resizeWindow("контуры", 600, 524);

    imshow("картинка", image);
    imshow("контуры", contoursImage);

    waitKey(0);

    destroyAllWindows();

    return 0;
}
