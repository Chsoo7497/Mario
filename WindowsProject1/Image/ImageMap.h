#pragma once
#include "../Object/Object.h"
class CImageMap
{
public:
	enum class sheet
	{
		Buffer,
		Main,
		BackGround,
		Enemy,
		Playable,
		Object,
		Tile,
		Game_Over,
		Course_Clear,
		Butten_Play,
		Butten_Make
	};
private:
	HDC		m_hImegeSheet; // �ٸ� ��ȭ���� �׸� �׷��� ��. 
	HBITMAP m_hSheetBitmap;
	HBITMAP m_hSheetOldBitmap;

	HDC		m_hImegeClear; //������ �̹��� ���찳
	HBITMAP m_hClearBitmap;
	HBITMAP m_hClearOldBitmap;

	HDC		m_hImege; //sheet���� ����� �̹����� �ҷ���
	HBITMAP m_hBitmap; // ���������� �׸��� ���� ������ ������ ������. 
	HBITMAP m_hOldBitmap; // ���� ����� ���� ����� ��. 

	HDC		m_hSubImege; 
	HBITMAP m_hSubBitmap;
	HBITMAP m_hSubOldBitmap; 
public:
	explicit CImageMap();
	virtual ~CImageMap();
public:
	HDC choice_Image(int x, int y, int xsize, int ysize);
	HDC choice_Image(int x, int y, int xsize, int ysize, float angle);
	// wchar_t*
	void Insert_Bitmap(const TCHAR* pFilePath);
	void Release_Bitmap();

};

