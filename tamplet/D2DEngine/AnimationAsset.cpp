#include <fstream>
#include <sstream>

#include "AnimationAsset.h"


bool AnimationAsset::setAnimation(const wchar_t* strBitmapFilePath,State state)
{
	
	std::wifstream file(strBitmapFilePath);
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
	}
	std::wstring line;			// ������ ���ڿ�	
	FRAME_INFO frame;
	//Motion motion;
	int count = 0;
	{
		getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		//wss >> motion.FrameCount;
		wss >> count;
	}

	//for (int j = 0; j < motion.FrameCount; j++)
	for (int j = 0; j < count; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			//motion.Frames[j].Source.left = _wtoi(token.c_str());
			frame.sourceRect.left = _wtoi(token.c_str());
			getline(wss, token, L',');
			//motion.Frames[j].Source.top = _wtoi(token.c_str());
			frame.sourceRect.top = _wtoi(token.c_str());
			getline(wss, token, L',');
			//motion.Frames[j].Source.right = _wtoi(token.c_str());
			frame.sourceRect.right = _wtoi(token.c_str());
			getline(wss, token, L',');
			//motion.Frames[j].Source.bottom = _wtoi(token.c_str());
			frame.sourceRect.bottom = _wtoi(token.c_str());
			getline(wss, token, L',');
			//motion.Frames[j].CenterX = _wtoi(token.c_str());
			frame.pCenter.x = _wtoi(token.c_str());
			getline(wss, token, L',');
			//motion.Frames[j].CenterY = _wtoi(token.c_str());
			frame.pCenter.y = _wtoi(token.c_str());

			/*motion.Frames[j].Size.cx = motion.Frames[j].Source.right - motion.Frames[j].Source.left + 1;
			motion.Frames[j].Size.cy = motion.Frames[j].Source.bottom - motion.Frames[j].Source.top + 1;*/
		}
		Animations[state].push_back(frame);
	}
	//motion.IsLoop = IsLoop;

	//m_motions[m_motionCount] = motion;

	//m_motionCount++;
    return false;
}
