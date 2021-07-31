#pragma comment(lib,"opencv_world453.lib")
#define USE_UNIFIED_MEM
#define down_scale 10 // DON'T EDIT
#define pixel_reaction_sum 1000 // DON'T EDIT
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "ScreenShoter.h"
#include <opencv2/cudawarping.hpp>
#include <opencv2/core/mat.hpp>
#include <tchar.h>
#include <chrono>
#include <Atlbase.h>
#include <comdef.h>
#include <memory>
#include <algorithm>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3d11.h>
#include <DXGIType.h>
#include <dxgi1_2.h>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3d9.lib")
#pragma comment(lib, "dxgi.lib")
typedef const cv::_InputArray& InputArray;





auto get_time() // Time ms
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
}



class DetectingArrow
{
	std::vector<std::pair<cv::Scalar, cv::Scalar>> _filters;//First - low_pass ; Second - High_pass
	int _arrow_num;
public:
	DetectingArrow(std::vector<std::pair<cv::Scalar, cv::Scalar>> Filters, int arrow_num)
	{
		_filters = Filters;
		_arrow_num = arrow_num;
	}
	cv::Mat FilterImage(cv::Mat Input, int downscale_factor)
	{
		cv::Rect new_size = { _arrow_num * 160 / down_scale, 0, 160 / down_scale, Input.rows };
		Input = Input(new_size);
		cv::Mat Additional, Output;
		Output = cv::Mat::zeros(Input.rows, Input.cols, CV_8UC1);

		for (auto& Filter : _filters)
		{
			cv::inRange(Input, Filter.first, Filter.second, Additional);
			cv::add(Additional, Output, Output);
		}
		return Output;
	}
};

class ArrowHandler
{
	const enum Arrow_IDs
	{
		ARR_LEFT = VK_LEFT,
		ARR_RIGHT = VK_RIGHT,
		ARR_DOWN = VK_DOWN,
		ARR_UP = VK_UP
	};

	std::unordered_map<int, DetectingArrow> Arrows = {
		{
			ARR_LEFT,
			DetectingArrow({
				{cv::Scalar(147, 147, 194), cv::Scalar(165, 161, 206)},
				{cv::Scalar(150, 85, 165), cv::Scalar(155, 95, 175)}
			},0)
		},
		{
			ARR_RIGHT,
			DetectingArrow({
				{cv::Scalar(172, 187, 243), cv::Scalar(187, 205, 253)},
				{cv::Scalar(170, 125, 200), cv::Scalar(180, 135, 210)}
			},3)
		},
		{
			ARR_UP,
			DetectingArrow({
				{cv::Scalar(56, 236, 246), cv::Scalar(59, 255, 253)},
				{cv::Scalar(60, 175, 210), cv::Scalar(65, 185, 220)}
			},2)
		},
		{
			ARR_DOWN,
			DetectingArrow({
				{cv::Scalar(85, 245, 255), cv::Scalar(95, 255, 255)}, {cv::Scalar(87, 185, 215), cv::Scalar(108, 195, 225)}
			},1)
		}
	};
	int TrashHold;

	void SendOutput(cv::Mat InputMatrix, HWND GameWindow, char VK)
	{
		SendMessageA(GameWindow, cv::sum(InputMatrix)[0] > TrashHold ? WM_KEYDOWN : WM_KEYUP, VK, 1);
	}

public:
	ArrowHandler(int new_trashhold) : TrashHold(new_trashhold) {};

	void ProcessImage(cv::Mat& Input, HWND gameWindow, int downscale_factor)
	{
		for (auto& [arrow_id, arrow_instance] : Arrows)
		{
			SendOutput(arrow_instance.FilterImage(Input, down_scale), gameWindow, arrow_id);
		}
	}
};

void Cut_screenshot_to_arrow_zone(cv::Mat& Input, int downscale_factor, HWND game_window)
{
	RECT gameRect;
	GetWindowRect(game_window, &gameRect);
	try
	{
		Input = Input({ gameRect.left, gameRect.top, gameRect.right - gameRect.left, gameRect.bottom - gameRect.top });
		cv::resize(Input, Input, cv::Size{ 192, 108 });
		Input = Input({ 1920 / downscale_factor / 2 + int(100 / downscale_factor), int(120 / downscale_factor), 1920 / downscale_factor / 2 - int(310 / downscale_factor), 1080 / downscale_factor / 4 - int(160 / downscale_factor) });
	}
	catch (cv::Exception& e)
	{
		std::cout << e.msg << std::endl; // output exception message
	}
}

std::string WStringToString(const std::wstring& wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return std::string(wstr.begin(), wstr.end());
}

int main(void)
{

	HWND game_window = FindWindowA(nullptr, "Friday Night Funkin'");
	DXScreenShoter11 screen_shot_manager;
	screen_shot_manager.Init();
	ArrowHandler arrow_handler(pixel_reaction_sum);
	while (game_window = FindWindowA(nullptr, "Friday Night Funkin'"))
	{
		cv::Mat src = screen_shot_manager.Take();
		cv::Mat hsv_src;
		static auto last_time = get_time();
		std::cout << (get_time() - last_time).count() << " ms " << '\n'; // Print time between note scan in ms 10 ms & - = Good
		last_time = get_time();
		Cut_screenshot_to_arrow_zone(src, down_scale, game_window);
		cv::cvtColor(src, hsv_src, cv::COLOR_BGR2HSV); // Apply color filters
		arrow_handler.ProcessImage(hsv_src, game_window, down_scale); // Render cutted zone

	}
	return 0;
}
