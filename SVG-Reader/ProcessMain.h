#ifndef ProcessMain_h
#define ProcessMain_h
#pragma once


#include "resource.h"
#include "SVGReader.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam);


VOID OnPaint(HDC hdc);


#endif
