#include "../../Header/framework.h"
#include "GameOver.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/SoundManager.h"

CGameOver::CGameOver()
	:m_FNomal({ 0.f, 0.1f, 0, 50, false, false })
{
}

CGameOver::~CGameOver()
{
}

int CGameOver::Ready()
{
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/GameOver.bmp", CImageMap::sheet::Game_Over);
	CSoundManager::Get_Instance()->StopAll();
	CSoundManager::Get_Instance()->PlayBGM(L"Game over.wav");
	m_FNomal.start();
    return 0;
}

void CGameOver::Update(float deltaTime)
{
	m_FNomal.Check_Time(deltaTime);
	if (m_FNomal.iCount == m_FNomal.iFrame) {
		m_FNomal.end();
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_MENU);
	}
}

void CGameOver::Render(HDC hDC)
{
	HDC hMemDC = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Game_Over, 0, 0, 1200, 700);
	BitBlt(hDC, 0, 0, SCREENSIZE_X, SCREENSIZE_Y, hMemDC, 0, 0, SRCCOPY);
}

void CGameOver::Release()
{
}
