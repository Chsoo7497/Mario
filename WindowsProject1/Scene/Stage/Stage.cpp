#include "../../Header/framework.h"
#include "Stage.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/CharicManager.h"
#include "../../Manager/BlockManager.h"
#include "../../Manager/ItemManager.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/MapManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Object/Block/Goal/Goal.h"

CStage::CStage()
	: m_fTimeLimit(30.f)
	, m_iTimeOut(30)
	, m_iScore(0)
	, m_sLIfe(3)
{
}

CStage::~CStage()
{
}

int CStage::Ready()
{
	CSoundManager::Get_Instance()->StopAll();
	CSoundManager::Get_Instance()->PlayBGM(L"2-01 Super Mario Bros - Ground.mp3");
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Backgrounds.bmp", CImageMap::sheet::BackGround);
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Enemies.bmp", CImageMap::sheet::Enemy);
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Playables.bmp", CImageMap::sheet::Playable);
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Objects.bmp", CImageMap::sheet::Object);
    CImageManager::Get_Instance()->Insert_Sheet(L"../Sheet/Tileset.bmp", CImageMap::sheet::Tile);
	CMapManager::Get_Instance()->_Ready();
	return 0;
}

void CStage::Update(float deltaTime)
{

	CMapManager::Get_Instance()->_Update(deltaTime);
	CBlockManager::Get_Instance()->_Update(deltaTime);
	CCharicManager::Get_Instance()->_Update(deltaTime);
	CItemManager::Get_Instance()->_Update(deltaTime);

	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player == nullptr) {
		CCharicManager::Destroy_Instance();
		CBlockManager::Destroy_Instance();
		CItemManager::Destroy_Instance();
		--m_sLIfe;
		if (m_sLIfe < 0)
			CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_GAMEOVER);
		else {
			CSoundManager::Get_Instance()->StopAll();
			CSoundManager::Get_Instance()->PlayBGM(L"2-01 Super Mario Bros - Ground.mp3");
		}
		return;
	}
	else if (player->Get_Goal()) {
		CCharicManager::Destroy_Instance();
		CBlockManager::Destroy_Instance();
		CItemManager::Destroy_Instance();
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::ID::SCENE_CLEAR);
		return;
	}

	if (!(player != nullptr && player->Check_Goal()))
	{
		m_fTimeLimit = m_fTimeLimit - deltaTime;
		if (m_fTimeLimit < 0.f) {
			player->Game_Over();
			m_sLIfe = 0;
		}
		else if (m_fTimeLimit - m_iTimeOut < 0.f)
		{
			m_iTimeOut--;
		}
	}
}

void CStage::Render(HDC hDC)
{
	CPlayer* player = CCharicManager::Get_Instance()->Get_Player();
	if (player == nullptr)
		return;
	else if (player->Get_Dead())
		return;
    CMapManager::Get_Instance()->_Render(hDC);
	CBlockManager::Get_Instance()->_Render(hDC, CMapManager::Get_Instance()->Get_Scroll());
	CCharicManager::Get_Instance()->_Render(hDC, CMapManager::Get_Instance()->Get_Scroll());
	CItemManager::Get_Instance()->_Render(hDC, CMapManager::Get_Instance()->Get_Scroll());

	if (player->Check_Goal()) {
		CBlockManager::Get_Instance()->Get_Goal()->Goal_Render(hDC, CMapManager::Get_Instance()->Get_Scroll());
	}

	//UI
	HDC hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1, 9, 15, 16);
	GdiTransparentBlt(hDC, {SCREENCENTER_X,SCREENCENTER_Y}, { 10,10,50,50 }, { 40,40 },
		hplayer, { 15,16 }, RGB(147, 187, 236));

	HDC hItem = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Object, 1 + 153, 1, 16, 16);
	GdiTransparentBlt(hDC, { SCREENCENTER_X,SCREENCENTER_Y }, { 10,60,50,100 }, { 40,40 },
		hItem, { 15,16 }, RGB(147, 187, 236));

	SetBkMode(hDC, TRANSPARENT);
	TCHAR szTemp[1024];
	wsprintf(szTemp, L" X %d ", m_sLIfe);
	TextOut(hDC, 60, 25, szTemp, static_cast<int>(_tcslen(szTemp)));
	wsprintf(szTemp, L" X %d ", m_iScore);
	TextOut(hDC, 60, 75, szTemp, static_cast<int>(_tcslen(szTemp)));
	wsprintf(szTemp, L" TIME  %d ", m_iTimeOut);
	TextOut(hDC, 1100, 20, szTemp, static_cast<int>(_tcslen(szTemp)));
}

void CStage::Release()
{
}
