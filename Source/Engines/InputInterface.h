#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <atltypes.h>
#include <tchar.h>  

class IInput 
{
public:
	virtual void VOnKeyDown(WPARAM wParam, HWND hWnd) 
	{
		TCHAR keyDownText[100] = _T("");
		_stprintf(keyDownText, _T("WM_KEYDOWN: %c\n"), (wchar_t)wParam);

		HDC hdc = GetDC(hWnd);
		TextOut(hdc, 10, 30, keyDownText, sizeof(keyDownText));
		
	}
	virtual void VOnKeyUp(WPARAM wParam, HWND hWnd)
	{
		TCHAR keyUpText[100] = _T("");
		_stprintf(keyUpText, _T("WM_KEYUP: %c\n"), (wchar_t)wParam);

		HDC hdc = GetDC(hWnd);
		TextOut(hdc, 10, 50, keyUpText, sizeof(keyUpText));
		ReleaseDC(hWnd, hdc);
	}
	void VOnChar(WPARAM wParam, HWND hWnd)
	{
		TCHAR charText[100] = _T("");
		_stprintf(charText, _T("WM_CHAR: %c\n"), (wchar_t)wParam);

		HDC hdc = GetDC(hWnd);
		TextOut(hdc, 10, 10, charText, sizeof(charText));
		ReleaseDC(hWnd, hdc);
	}

	virtual void VOnPointerMove(LPARAM lParam, HWND hWnd)
	{
		int curMosePosX = GET_X_LPARAM(lParam);
		int curMosePosY = GET_Y_LPARAM(lParam);
		TCHAR mosueMoveText[100] = _T("");
		_stprintf(mosueMoveText, _T("mouse x-pos: %d, mouse y-pos: %d\n"), curMosePosX, curMosePosY);

		HDC hdc = GetDC(hWnd);
		TextOut(hdc, 10, 70, mosueMoveText, sizeof(mosueMoveText));
		ReleaseDC(hWnd, hdc);
	}
	virtual void VOnPointerButtonDown(LPARAM lParam, HWND hWnd)
	{
		int curMosePosX = GET_X_LPARAM(lParam);
		int curMosePosY = GET_Y_LPARAM(lParam);
		TCHAR mouseDownText[100] = _T("");
		_stprintf(mouseDownText, _T("LMouse Down x-pos: %d, LMouse Down y-pos: %d\n"), curMosePosX, curMosePosY);
		
		HDC hdc = GetDC(hWnd);
		TextOut(hdc, 10, 90, mouseDownText, sizeof(mouseDownText));
		ReleaseDC(hWnd, hdc);
	}
	virtual void VOnPointerButtonUp(LPARAM lParam, HWND hWnd)
	{
		int curMosePosX = GET_X_LPARAM(lParam);
		int curMosePosY = GET_Y_LPARAM(lParam);
		TCHAR mouseUpText[100] = _T("");
		_stprintf(mouseUpText, _T("LMouse UP x-pos: %d, LMouse Up y-pos: %d\n"), curMosePosX, curMosePosY);
		
		HDC hdc = GetDC(hWnd);
		TextOut(hdc, 10, 110, mouseUpText, sizeof(mouseUpText));
		ReleaseDC(hWnd, hdc);
	}
};