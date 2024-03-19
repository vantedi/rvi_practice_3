//Задание 2
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Mat image = imread("C:/Users/James-Bond/Downloads/fig.png");

    if (image.empty()) {
        cout << "ошибка загрузки картинки" << endl;
        return -1;
    }

    Mat blurredImage;
    GaussianBlur(image, blurredImage, Size(3, 3), 0);

    Mat grayImage;
    cvtColor(blurredImage, grayImage, COLOR_BGR2GRAY);

    Mat edges;
    Canny(grayImage, edges, 50, 150);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours.size(); i++) {
        double peri = arcLength(contours[i], true);
        vector<Point> approx;
        approxPolyDP(contours[i], approx, 0.04 * peri, true);

        Moments M = moments(contours[i]);
        Point center(M.m10 / M.m00, M.m01 / M.m00);

        if (approx.size() == 3) {
            putText(edges, "triangle", center, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        }
        else if (approx.size() == 4) {
            putText(edges, "square", center, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        }
        else {
            putText(edges, "circle", center, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        }
    }

    namedWindow("картинка", WINDOW_NORMAL);
    namedWindow("контуры", WINDOW_NORMAL);

    resizeWindow("картинка", 600, 345);
    resizeWindow("контуры", 600, 345);

    imshow("картинка", image);
    imshow("контуры", edges);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
