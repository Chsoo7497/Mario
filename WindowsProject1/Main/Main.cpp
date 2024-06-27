#include "../Header/framework.h"
#include "Main.h"
#include "../Manager/CharicManager.h"
#include "../Manager/BlockManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ImageManager.h"
#include "../Manager/MapManager.h"
#include "../Manager/SoundManager.h"
#include "../Cursor/Cursor.h"

Cmain::Cmain()
	: m_hDC()
	, deltatime()
	, loding(true)
{
}

Cmain::~Cmain()
{
	Release_MainApp();
}

void Cmain::Loding_MainApp(HWND hWnd)
{
	if (loding == false)
		return;

	CSoundManager::Get_Instance()->Initialize();

	m_hDC = GetDC(hWnd);
	IntersectClipRect(m_hDC, SCREEN_LINE.left, SCREEN_LINE.top, SCREEN_LINE.right, SCREEN_LINE.bottom);

	CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Buffer.bmp", CImageMap::sheet::Buffer);
	CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_MENU);
	loding = false;
}

void Cmain::Time_Update_MainApp(ULONGLONG time)
{
	deltatime = static_cast<float>(GetTickCount64() - time)/1000.f;
	CCursor::Update();
	CSceneManager::Get_Instance()->Update(deltatime);
}

void Cmain::Render_MainApp()
{
	HDC m_hDC_buffer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Buffer,0,0,1280,720);
	HDC hMemDC = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Buffer,0,0,1200,700);
	BitBlt(m_hDC_buffer, 0, 0, SCREENSIZE_X, SCREENSIZE_Y, hMemDC, 0, 0, SRCCOPY);
	CSceneManager::Get_Instance()->Render(m_hDC_buffer);

	CCursor::Render(m_hDC_buffer);
	BitBlt(m_hDC, 0, 0, SCREENSIZE_X, SCREENSIZE_Y, m_hDC_buffer, 0, 0, SRCCOPY);
}

void Cmain::Release_MainApp()
{
	ReleaseDC(g_hWnd, m_hDC);
	CCharicManager::Destroy_Instance();
	CBlockManager::Destroy_Instance();
	CItemManager::Destroy_Instance();
	CSceneManager::Destroy_Instance();
	CImageManager::Destroy_Instance();
	CMapManager::Destroy_Instance();
	CSoundManager::Destroy_Instance();
}
