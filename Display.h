#pragma once

#include <cstdint>
#include <opencv2/core.hpp>

class Display
{
public:
	Display();
	void Show();
	void Update(uint8_t x, uint8_t y, uint8_t value);

private:
	cv::Mat frameBuffer;
};

