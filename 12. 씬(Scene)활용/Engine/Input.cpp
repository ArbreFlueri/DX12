#include "pch.h"
#include "Input.h"

void Input::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}//초기화 시킴 이거 윈도우 핸들 값 들고오고 아무것도 안누른 None 상태를 state에 저장

void Input::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (_hwnd != hwnd)
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
			_states[key] = KEY_STATE::NONE;

		return;
	} //들고온 윈도우핸들이 초기화된 핸들이랑 다르다면 꺼지게하는 코드임.

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false) //문제 확인
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려 있으면 true
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}
}