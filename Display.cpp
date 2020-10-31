#include "Display.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define WIDTH 160
#define HEIGHT 144
#define NAME "GameBoi"

Display::Display(): frameBuffer(cv::Mat::zeros(HEIGHT, WIDTH, CV_8UC1))
{
	cv::namedWindow(NAME);
}

void Display::Show() {
	cv::Mat resized;
	cv::resize(frameBuffer, resized, {}, 4, 4, cv::INTER_NEAREST);
	cv::imshow(NAME, resized);
	/*char key = static_cast<char>(*/cv::waitKey(10)/*)*/;
	//if (key == 27) { std::cout << "Exiting..." << std::endl; break; }
}

void Display::Update(uint8_t x, uint8_t y, uint8_t value) {
	frameBuffer.at<uint8_t>(y, x) = value;
}
