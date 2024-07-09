#include "AnimationAsset.h"


bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	using namespace std::literals::string_literals;
	
	if (FilePath == std::wstring(L"Background"))
	{
		int index = 0;
		std::wstring csv = 
			L"4\r\n"s+
			L"0, 0, 784, 320, 0, 0, 0.2 \r\n"s +
			L"789,  0, 1573,320 ,0,0,0.2 \r\n"s +
			L"0,325,  784,645 ,0,0,0.2 \r\n"s +
			L"789,325, 1573,645 ,0,0,0.2 \r\n"s;

		std::wstringstream csvwss(csv);

		std::wstring line;
		
		int FrameCount = 0;
		{
			std::getline(csvwss, line);
			std::wstringstream wss(line);
			wss >> FrameCount;
		}

		vMAnimations[index].Frames.resize(FrameCount);
		for (size_t i = 0; i < FrameCount; i++)
		{
			std::getline(csvwss, line);
			std::wstringstream wss(line);
			std::wstring token;
			{
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Source.left = (float)_wtoi(token.c_str());
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Source.top = (float)_wtoi(token.c_str());
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Source.right = (float)_wtoi(token.c_str());
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Source.bottom = (float)_wtoi(token.c_str());
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Center.x = (float)_wtoi(token.c_str());
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Center.y = (float)_wtoi(token.c_str());
				std::getline(wss, token, L',');
				vMAnimations[index].Frames[i].Duration = (float)_wtof(token.c_str());
			}
		}
	}
	if (FilePath == std::wstring(L"Run"))
	{
		std::wstring path = L"../Resource/" + FilePath + L".csv";
		if (LoadAnimationFromFile(1, path.c_str()) == false) {
			return false;
		}
	}
	else {
		std::wstring path = L"../Resource/" + FilePath + L".csv";
		if (LoadAnimationFromFile(0, path.c_str()) == false) {
			return false;
		}
	}

	return true;

}

bool AnimationAsset::LoadAnimationFromFile(int index, const wchar_t* filename)
{
	std::wifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "파일을 열 수 없습니다." << std::endl; 
		return false;
	}

	std::wstring line;
	int FrameCount = 0;
	{
		std::getline(file, line);
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	//vMAnimations[index].Frames.reserve(FrameCount);
	vMAnimations[index].Frames.resize(FrameCount);
	for (size_t i = 0; i < FrameCount; i++)
	{
		std::getline(file, line);
		std::wstringstream wss(line);
		std::wstring token; 
		{
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Source.left = (float)_wtoi(token.c_str());
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Source.top = (float)_wtoi(token.c_str());
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Source.right = (float)_wtoi(token.c_str());
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Source.bottom = (float)_wtoi(token.c_str());
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Center.x = (float)_wtoi(token.c_str());
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Center.y = (float)_wtoi(token.c_str());
			std::getline(wss, token, L',');
			vMAnimations[index].Frames[i].Duration = (float)_wtof(token.c_str());
		}
	}
	return true;
}
