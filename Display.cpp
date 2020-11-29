#define NOMINMAX

#include "Display.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <windows.h>
#include <tchar.h>

#include <CommCtrl.h>

#include <iostream>
#include <chrono>

#include "MMU.h"

#define WIDTH 160
#define HEIGHT 144
#define NAME "GameBoi"

LRESULT CALLBACK mySubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	bool isKeyDown = uMsg == WM_KEYDOWN;
	bool isKeyUp = uMsg == WM_KEYUP;

	if (isKeyDown || isKeyUp)
	{
		switch (wParam) {
		case VK_UP:
			directionJoypad.notPressedUpOrSelect = isKeyUp;
			break;

		case VK_DOWN:
			directionJoypad.notPressedDownOrStart = isKeyUp;
			break;

		case VK_LEFT:
			directionJoypad.notPressedLeftOrB = isKeyUp;
			break;

		case VK_RIGHT:
			directionJoypad.notPressedRightOrA = isKeyUp;
			break;

		case 'M':
			buttonJoypad.notPressedUpOrSelect = isKeyUp;
			break;

		case 'N':
			buttonJoypad.notPressedDownOrStart = isKeyUp;
			break;

		case 'Q':
			buttonJoypad.notPressedRightOrA = isKeyUp;
			break;

		case 'W':
			buttonJoypad.notPressedLeftOrB = isKeyUp;
			break;
		}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

Display::Display() : frameBuffer(cv::Mat::zeros(HEIGHT, WIDTH, CV_8UC1))
{
	cv::namedWindow(NAME);
	HWND hwnd = FindWindow(NULL, _T(NAME)); // THIS IS INSANE!!!
	bool result = SetWindowSubclass(hwnd, &mySubClassProc, 1, 0);
}

void Display::Show() {
	static auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	start = end;

	double msecspassed = diff.count() * 1000.0;
	int msecs_to_wait = (int)std::min(std::max(msecspassed, 1.0), 16.0);

	cv::Mat resized;
	cv::resize(frameBuffer, resized, {}, 4, 4, cv::INTER_NEAREST);
	cv::imshow(NAME, resized);
	/*char key = static_cast<char>(*/cv::waitKey(msecs_to_wait)/*)*/;
	//if (key == 27) { std::cout << "Exiting..." << std::endl; break; }
}

void Display::Update(uint8_t x, uint8_t y, uint8_t value) {
	frameBuffer.at<uint8_t>(y, x) = value;
}
