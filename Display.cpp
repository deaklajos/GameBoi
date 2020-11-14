#include "Display.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <windows.h>
#include <tchar.h>

#include <CommCtrl.h>

#include <iostream>

#include "MMU.h"

#define WIDTH 160
#define HEIGHT 144
#define NAME "GameBoi"

LRESULT CALLBACK mySubClassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	bool isKeyDown = uMsg == WM_KEYDOWN;
	bool isKeyUp = uMsg == WM_KEYUP;

	// only one key for now
	if (isKeyDown || isKeyUp)
	{
		JoyPad newval;
		switch (wParam) {
		case VK_UP:
			newval.notPressedUpOrSelect = isKeyUp;
			newval.notSelectedDirection = isKeyUp;
			joypad = newval;
			break;

		case VK_DOWN:
			newval.notPressedDownOrStart = isKeyUp;
			newval.notSelectedDirection = isKeyUp;
			joypad = newval;
			break;

		case VK_LEFT:
			newval.notPressedLeftOrB = isKeyUp;
			newval.notSelectedDirection = isKeyUp;
			joypad = newval;
			break;

		case VK_RIGHT:
			newval.notPressedRightOrA = isKeyUp;
			newval.notSelectedDirection = isKeyUp;
			joypad = newval;
			break;

		case 'M':
			newval.notPressedUpOrSelect = isKeyUp;
			newval.notSelectedButton = isKeyUp;
			joypad = newval;
			break;

		case 'N':
			newval.notPressedDownOrStart = isKeyUp;
			newval.notSelectedButton = isKeyUp;
			joypad = newval;
			break;

		case 'Q':
			newval.notPressedRightOrA = isKeyUp;
			newval.notSelectedButton = isKeyUp;
			joypad = newval;
			break;

		case 'W':
			newval.notPressedLeftOrB = isKeyUp;
			newval.notSelectedButton = isKeyUp;
			joypad = newval;
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
	cv::Mat resized;
	cv::resize(frameBuffer, resized, {}, 4, 4, cv::INTER_NEAREST);
	cv::imshow(NAME, resized);
	/*char key = static_cast<char>(*/cv::waitKey(1)/*)*/;
	//if (key == 27) { std::cout << "Exiting..." << std::endl; break; }
}

void Display::Update(uint8_t x, uint8_t y, uint8_t value) {
	frameBuffer.at<uint8_t>(y, x) = value;
}
