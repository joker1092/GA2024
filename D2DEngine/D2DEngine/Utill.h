#pragma once
namespace Utill
{
	//박스의 각변의 최소,최대값을 넣고 원의 중점과 가장 가까운 점에 값을 리턴하는 함수
	float Clamp(float value, float min, float max);
	float Distance(D2D_POINT_2F p1,D2D_POINT_2F p2);
};

