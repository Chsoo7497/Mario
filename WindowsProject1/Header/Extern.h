#pragma once

extern HWND g_hWnd;
static float PI = 3.141592f;
const RECT SCREEN_LINE = { 0, 0, SCREENSIZE_X, SCREENSIZE_Y };

void Output_Rectangle(const HDC& hDC, const RECT& _rect, POINT Scroll);
void Output_Rectangle(const HDC& hDC, const RECT& _rect, POINT Scroll, const COLORREF& _color);
void Output_Ellipse(const HDC& hDC, const RECT& _rect);
void Output_Ellipse(const HDC& hDC, const RECT& _rect, POINT Scroll);
void Output_Ellipse(const HDC& hDC, const RECT& _rect, POINT Scroll, const COLORREF& _color);
void GdiTransparentBlt(HDC hDC, RECT RendDomain, POINT RendScale, HDC hImage, POINT ImageScale, COLORREF _color);
void GdiTransparentBlt(HDC hDC, POINT Scroll, RECT RendDomain, POINT RendScale, HDC hImage, POINT ImageScale, COLORREF _color);