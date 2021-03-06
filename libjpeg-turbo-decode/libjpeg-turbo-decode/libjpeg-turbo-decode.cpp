// libjpeg-turbo-decode.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#define TEST_COUNT 1000

int main(int argc, char *argv[])
{
	// Build Information
	//std::cout << cv::getBuildInformation() << std::endl;

	std::ifstream f(argv[1], std::ios::binary);
	if (!f.is_open())
		return  -1;

	f.seekg(0, std::ios::end);
	const unsigned int length = f.tellg();
	f.seekg(0, std::ios::beg);

	const auto buffer = new char[length];
	f.read(buffer, length);
	f.close();

	const auto data = std::vector<char>(buffer, buffer + length);

	// Test
	int64 start = 0;
	int64 end = 0;
	double total = 0;
	double avg = 0;

	start = cv::getTickCount();
	for (auto i = 0; i < TEST_COUNT; i++)
		auto ret = cv::imdecode(data, cv::IMREAD_UNCHANGED);
	end = cv::getTickCount();

	total = (end - start) * 1000 / cv::getTickFrequency();
	avg = total / TEST_COUNT;
	std::cout << "[Decode]" << std::endl;
	std::cout << "\tTotal = " << total << "[ms], Avg = " << avg << "[ms]" << std::endl;

	const auto img = cv::imdecode(data, cv::IMREAD_UNCHANGED);
    std::vector<uchar> buf( img.rows * img.cols );
	const std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, 95 };

	start = cv::getTickCount();
	for (auto i = 0; i < TEST_COUNT; i++)
		cv::imencode(".jpg", img, buf, params);
	end = cv::getTickCount();

	total = (end - start) * 1000 / cv::getTickFrequency();
	avg = total / TEST_COUNT;
	std::cout << "[Encode]" << std::endl;
	std::cout << "\tTotal = " << total << "[ms], Avg = " << avg << "[ms]" << std::endl;

	return 0;
}