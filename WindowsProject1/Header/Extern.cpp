#include "framework.h"
#include "Extern.h"

HWND g_hWnd = nullptr;

void Output_Rectangle(const HDC& hDC, const RECT& _rect, POINT Scroll)
{
	Rectangle(hDC, _rect.left - Scroll.x + SCREENCENTER_X, _rect.top - Scroll.y + SCREENCENTER_Y, _rect.right - Scroll.x + SCREENCENTER_X, _rect.bottom - Scroll.y + SCREENCENTER_Y);
}

void Output_Rectangle(const HDC& hDC, const RECT& _rect, POINT Scroll, const COLORREF& _color)
{
	HBRUSH brush = CreateSolidBrush(_color);
	HBRUSH brushPrev = (HBRUSH)SelectObject(hDC, brush);
	Rectangle(hDC, _rect.left - Scroll.x + SCREENCENTER_X, _rect.top - Scroll.y + SCREENCENTER_Y, _rect.right - Scroll.x + SCREENCENTER_X, _rect.bottom - Scroll.y + SCREENCENTER_Y);
	SelectObject(hDC, brushPrev);
	DeleteObject(brush);
	DeleteObject(brushPrev);
}

void Output_Ellipse(const HDC& hDC, const RECT& _rect)
{
	Ellipse(hDC, _rect.left, _rect.top, _rect.right, _rect.bottom);
}

void Output_Ellipse(const HDC& hDC, const RECT& _rect, POINT Scroll)
{
	Ellipse(hDC, _rect.left - Scroll.x + SCREENCENTER_X, _rect.top - Scroll.y + SCREENCENTER_Y, _rect.right - Scroll.x + SCREENCENTER_X, _rect.bottom - Scroll.y + SCREENCENTER_Y);
}

void Output_Ellipse(const HDC& hDC, const RECT& _rect, POINT Scroll, const COLORREF& _color)
{
	HBRUSH brush = CreateSolidBrush(_color);
	HBRUSH brushPrev = (HBRUSH)SelectObject(hDC, brush);
	Ellipse(hDC, _rect.left - Scroll.x + SCREENCENTER_X, _rect.top - Scroll.y + SCREENCENTER_Y, _rect.right - Scroll.x + SCREENCENTER_X, _rect.bottom - Scroll.y + SCREENCENTER_Y);
	SelectObject(hDC, brushPrev);
	DeleteObject(brush);
	DeleteObject(brushPrev);
}

void GdiTransparentBlt(HDC hDC, RECT RendDomain, POINT RendScale, HDC hImage, POINT ImageScale, COLORREF _color)
{
	GdiTransparentBlt(hDC,
		RendDomain.left, RendDomain.top, RendScale.x, RendScale.y,
		hImage, 0, 0, ImageScale.x, ImageScale.y, _color);
}

void GdiTransparentBlt(HDC hDC, POINT Scroll, RECT RendDomain, POINT RendScale, HDC hImage, POINT ImageScale, COLORREF _color)
{
	GdiTransparentBlt(hDC,
		RendDomain.left - Scroll.x + SCREENCENTER_X, RendDomain.top - Scroll.y + SCREENCENTER_Y, RendScale.x, RendScale.y,
		hImage, 0, 0, ImageScale.x, ImageScale.y, _color);
}