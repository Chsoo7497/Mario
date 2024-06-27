#include "../Header/framework.h"
#include "ImageMap.h"

CImageMap::CImageMap()
	: m_hImegeSheet()
	, m_hSheetBitmap()
	, m_hSheetOldBitmap()
	, m_hImegeClear()
	, m_hClearBitmap()
	, m_hClearOldBitmap()
	, m_hSubImege()
	, m_hSubBitmap()
	, m_hSubOldBitmap()
	, m_hImege()
	, m_hBitmap()
	, m_hOldBitmap()
{	 
}

CImageMap::~CImageMap()
{
	Release_Bitmap();
}

HDC CImageMap::choice_Image(int x, int y, int xsize, int ysize)
{
	BitBlt(m_hImege, 0, 0, 100, 100, m_hImegeClear, 0, 0, SRCCOPY);
	StretchBlt(m_hImege, 
		0,
		0,
		xsize < 0 ? -xsize : xsize,
		ysize < 0 ? -ysize : ysize,
		m_hImegeSheet,
		xsize < 0 ? (x-xsize) : x,
		ysize < 0 ? (y-ysize) : y,
		xsize,
		ysize, SRCCOPY);
	return m_hImege;
}

HDC CImageMap::choice_Image(int x, int y, int xsize, int ysize, float angle)
{
	POINT _point[3] = {};
	Coordi _radius = { static_cast<float>((xsize < 0 ? -xsize : xsize) / 2) , static_cast<float>((ysize < 0 ? -ysize : ysize) / 2) };
	_point[0] = (_radius + (Coordi{ cosf((PI * 3 / 4) + angle), -sinf((PI * 3 / 4) + angle) }*_radius.Length())).Point();
	_point[1] = (_radius + (Coordi{ cosf((PI * 1 / 4) + angle), -sinf((PI * 1 / 4) + angle) }*_radius.Length())).Point();
	_point[2] = (_radius + (Coordi{ cosf((PI * 5 / 4) + angle), -sinf((PI * 5 / 4) + angle) }*_radius.Length())).Point();
	BitBlt(m_hSubImege, 0, 0, 100, 100, m_hImegeClear, 0, 0, SRCCOPY);
	PlgBlt(m_hSubImege, _point, m_hImegeSheet,
		x,
		y,
		xsize < 0 ? -xsize : xsize,
		ysize < 0 ? -ysize : ysize,
		NULL, NULL, NULL);
	BitBlt(m_hImege, 0, 0, 100, 100, m_hImegeClear, 0, 0, SRCCOPY);
	StretchBlt(m_hImege,
		0,
		0,
		xsize < 0 ? -xsize : xsize,
		ysize < 0 ? -ysize : ysize,
		m_hSubImege,
		xsize < 0 ? - xsize : 0,
		ysize < 0 ? - ysize : 0,
		xsize,
		ysize, SRCCOPY);
	return m_hImege;
}

void CImageMap::Insert_Bitmap(const TCHAR* pFilePath)
{
	HDC hDC = GetDC(g_hWnd);
	m_hImegeSheet = CreateCompatibleDC(hDC);
	m_hImegeClear = CreateCompatibleDC(hDC);
	m_hSubImege = CreateCompatibleDC(hDC);
	m_hImege = CreateCompatibleDC(hDC);

	m_hSheetBitmap = (HBITMAP)LoadImage(NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hClearBitmap = (HBITMAP)LoadImage(NULL, L"../Sheet/Clear.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hSubBitmap = CreateCompatibleBitmap(hDC, SCREENSIZE_X, SCREENSIZE_Y);
	m_hBitmap = CreateCompatibleBitmap(hDC, SCREENSIZE_X, SCREENSIZE_Y);
	ReleaseDC(g_hWnd, hDC);
	m_hSheetOldBitmap = (HBITMAP)SelectObject(m_hImegeSheet, m_hSheetBitmap);
	m_hClearOldBitmap = (HBITMAP)SelectObject(m_hImegeClear, m_hClearBitmap);
	m_hSubOldBitmap = (HBITMAP)SelectObject(m_hSubImege, m_hSubBitmap);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hImege, m_hBitmap);

}

void CImageMap::Release_Bitmap()
{
	SelectObject(m_hImegeSheet, m_hSheetOldBitmap);
	SelectObject(m_hImegeClear, m_hClearOldBitmap);
	SelectObject(m_hSubImege, m_hSubOldBitmap);
	SelectObject(m_hImege, m_hOldBitmap);
	DeleteObject(m_hSheetBitmap);
	DeleteObject(m_hClearBitmap);
	DeleteObject(m_hSubBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hImegeSheet);
	DeleteDC(m_hImegeClear);
	DeleteDC(m_hSubImege);
	DeleteDC(m_hImege);
}
