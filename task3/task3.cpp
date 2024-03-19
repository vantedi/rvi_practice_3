#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Mat inputImage = imread("C:/Users/James-Bond/Downloads/text.png");

    if (inputImage.empty())
    {
        cout << "ошибка загрузки картинки" << endl;
        return -1;
    }

    Mat grayImage;
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

    Mat edges;
    Canny(grayImage, edges, 50, 150, 3);

    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat contourImage = Mat::zeros(inputImage.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(contourImage, contours, static_cast<int>(i), Scalar(148, 0, 211), 2);
    }

    imshow("картинка", inputImage);
    imshow("текст", contourImage);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
