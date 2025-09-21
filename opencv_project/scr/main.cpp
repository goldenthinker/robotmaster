#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    Mat img1= imread("test_image.png");
    Mat img2= imread("test_image.png");
    Mat img3= imread("test_image.png");
    Mat img4= imread("test_image.png");
    Mat img5= imread("test_image.png");
    Mat img6= imread("test_image.png");
    Mat img7= imread("test_image.png");
    Mat img8= imread("test_image.png");
    Mat img9= imread("test_image.png");
    Mat img10= imread("test_image.png");
    Mat img11= imread("test_image.png");
    Mat img12= imread("test_image.png");
    Mat img13= imread("test_image.png");
    Mat img14= imread("test_image.png");
    Mat img15= imread("test_image.png");
    Mat img16= imread("test_image.png");
    if(img1.empty())
    {
        std::cout<<"Could not read the image: test_image.jpg"<< std::endl;
        return -1;
    }
    Mat gray;
    cvtColor(img1, gray, COLOR_BGR2GRAY);
    imshow("grey picture", gray);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opgrey_picture.png", gray);
    waitKey(0);

    Mat hsv, mask;
    cvtColor(img2, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(0, 100, 100), Scalar(0, 255, 255), mask);
    imshow("红色掩膜", mask);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opred_mask.png", mask);
    waitKey(0);
    Mat blurImg;
    blur(img3,blurImg,Size(5,5));
    imshow("均值滤波",blurImg);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opmean_blur.png", blurImg);
    waitKey(0);
    Mat gaussianImg;
    GaussianBlur(img4,gaussianImg,Size(5,5),1.5);
    imshow("高斯滤波",gaussianImg);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opgaussian_blur.png", gaussianImg);
    waitKey(0);
    //下面用hsv提取红色区域
    Mat hsv2;
    cvtColor(img5, hsv2, COLOR_BGR2HSV);
    Mat mask1, mask2, mask3;
    inRange(hsv2, Scalar(0, 100, 100), Scalar(10, 255, 255), mask1);
    inRange(hsv2, Scalar(160, 100, 100), Scalar(180, 255, 255), mask2);
    bitwise_or(mask1, mask2, mask3);
    Mat redRegion;
    bitwise_and(img5, img5, redRegion, mask3);
    imshow("红色区域", redRegion);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opred_region.png", redRegion);
    waitKey(0);
    //以下为寻找红色区域的轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask3, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat contourImg = img6.clone();
    drawContours(contourImg, contours, -1, Scalar(0, 255, 0), 2);
    imshow("红色外轮廓", contourImg);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opred_contours.png", contourImg);
    waitKey(0);
    //以下为寻找红色bounding box
    Mat boxImg = img7.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        Rect box = boundingRect(contours[i]);
        rectangle(boxImg, box, Scalar(0, 255, 0), 2);
    }
    imshow("红色外接矩形", boxImg);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opred_bounding_box.png", boxImg);
    waitKey(0);
    //以下计算红色轮廓面积
    double totalArea = 0.0;
    for (size_t i = 0; i < contours.size(); i++) {
        totalArea += contourArea(contours[i]);
    }
    cout << "红色区域总面积: " << totalArea << endl;
    //提取高亮部分并做灰度化/二值化/膨胀/腐蚀处理
    Mat hsv3;
    cvtColor(img8, hsv, COLOR_BGR2HSV);

    vector<Mat> channels;
    split(hsv, channels);
    Mat v = channels[2]; // V 通道表示亮度

    // 提取高亮区域 (比如 V > 200)
    Mat highlightMask;
    threshold(v, highlightMask, 200, 255, THRESH_BINARY);

    // 2. 灰度化（原图转灰度）
    Mat gray2;
    cvtColor(img8, gray, COLOR_BGR2GRAY);

    // 3. 二值化（基于灰度图）
    Mat binary;
    threshold(gray, binary, 128, 255, THRESH_BINARY);

    // 4. 膨胀（在二值图上操作）
    Mat dilated;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(binary, dilated, kernel);

    // 5. 腐蚀（在膨胀结果上操作）
    Mat eroded;
    erode(dilated, eroded, kernel);

    // 显示结果
    imshow("高亮区域掩码", highlightMask);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/ophighlight_mask.png", highlightMask);
    imshow("灰度图", gray);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opgrey_picture2.png", gray);
    imshow("二值化", binary);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opbinary.png", binary);
    imshow("膨胀", dilated);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opdilated.png", dilated);
    imshow("腐蚀", eroded);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/operoded.png", eroded);

    waitKey(0);
    //图像旋转35度
    Point2f center(img8.cols / 2.0F, img8.rows / 2.0F);//旋转中心点
    Mat rotMat =getRotationMatrix2D(center, 35, 1.0);//scale为缩放因子，1.0表示不缩放
    Mat rotatedImg;
    warpAffine(img8, rotatedImg, rotMat, img8.size());
    imshow("旋转后的图像", rotatedImg);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/oproated_image.png", rotatedImg);
    waitKey(0);
    //图像裁减为原图左上角1/4
    Rect roi(0, 0, img9.cols / 2, img9.rows / 2);
    Mat croppedImg = img9(roi);
    imshow("裁剪后的图像", croppedImg);
    imwrite("/home/zhanruixuan/repos/code/opencv_project/resources/opcropped_image.png", croppedImg);
    waitKey(0);

    return 0;
}
