#include "../../../Header/framework.h"
#include "Player.h"
#include "../../../Manager/ImageManager.h"
#include "../../../Manager/BlockManager.h"
#include "../../../Manager/CharicManager.h"
#include "../../../Manager/ItemManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Onggum/Onggum.h"
#include"../RedOnggum/RedOnggum.h"

CPlayer::CPlayer()
	: m_bGoal(false)
	, m_LR(1)
	, m_time()
	, m_sPower(0)
	, m_sPrevPower(0)
	, m_FJump({ 0.f, 0.05f, 0, 10, false, false })
	, m_FDown({ 0.f, 0.1f, 0, 0, false, false })
	, m_FStamp({ 0.f, 0.05f, 0, 4, false, false })
	, m_FPower({ 0.f, 0.1f, 0, 10, false, false })
	, m_FFire({ 0.f, 0.125f, 0, 3, false, false })
	, m_FGoal({ 0.f, 0.1f, 0, 100, false, false })
	, keymanager()
{
	m_CTag = ID::PLAYER;
	m_Info.Posi = Coordi(0.f, 0.f);
	m_Info.Velo = Coordi(0.1f, 0.f);
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(40.f, 40.f);
	m_FMove.iFrame = 2;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Start()
{
	m_FDead = { 0.f, 0.05f, 0, 100, false, false };
	m_Info.Posi = Coordi{ static_cast<float>((m_Space.x * 50) + 25), static_cast<float>((m_Space.y * 50) + 25) };
	m_Info.Velo = Coordi(0.1f, 0.f);
	m_Info.RendScale = Coordi(50.f, 50.f);
	m_Info.CollidScale = Coordi(40.f, 40.f);
	m_sPower = 0;
	m_sPrevPower = 0;
	m_bDead = false;
	m_bScreenOut = false;
	m_FMove.end();
	m_FDead.end();
	m_FJump.end();
	m_FDown.end();
	m_FStamp.end();
	m_FPower.end();
	m_FFire.end();
	m_FGoal.end();
}

void CPlayer::Time_Update(float deltaTime)
  {
	Dead_Checker(deltaTime);
	Power_Check();
	_Goal(deltaTime);
	m_FMove.Check_Time(deltaTime);
	m_FJump.Check_Time(deltaTime);
	m_FDown.Check_Time(deltaTime);
	m_FStamp.Check_Time(deltaTime);
	m_FPower.Check_Time(deltaTime);
	m_FFire.Check_Time(deltaTime);
	m_FGoal.Check_Time(deltaTime);

	if (m_FDead.bAct)
		return;
	
	if (m_FPower.bAct && m_FPower.iCount < 5)
		return;

	if (m_FGoal.bAct)
		return;

	if (m_FMove.bAct) 
		m_time += deltaTime;


	if (m_FFire.bAct) {
		if (m_FFire.iCount == m_FFire.iFrame) {
			m_FFire.end();
		}
	}

	if (m_FStamp.bTrigger) {
		if (m_FStamp.iCount == 0) {
			m_FStamp.iCount = m_FStamp.iFrame;
		}
	}

	_Move(deltaTime);

	keymanager.Key_Input();
	if (keymanager.Key_Up(KEY_DOWN)) {
		m_FDown.end();
		m_FStamp.end();
		if (m_sPower > 0)
			m_Info.Posi.fy -= 25.f;
	}	

	if (m_FStamp.bAct || m_FDown.bAct)
		return;
	if (keymanager.Key_Press(KEY_SPACE)) {
		if (!m_FJump.bAct) {
			m_FJump.start();
			m_Info.Get_Force(Coordi(0.f, -200.f));
			CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::PLAYER);
			CSoundManager::Get_Instance()->PlaySound(L"Jump.wav", CSoundManager::CHANNELID::PLAYER);
		}
		else if (m_FJump.bTrigger) {
			switch (m_FJump.iCount)
			{
			case 1:
				m_Info.Get_Force(Coordi(0.f, -200.f));
				break;
			case 2:
				m_Info.Get_Force(Coordi(0.f, -200.f));
				break;
			case 3:
				m_Info.Get_Force(Coordi(0.f, -100.f));
				break;
			case 4:
				m_Info.Get_Force(Coordi(0.f, -100.f));
				break;
			case 10:
				m_FJump.iCount = 9;
			default:
				break;
			}
		}
		if (keymanager.Key_Down(KEY_DOWN)) {
			m_FStamp.start();
			m_Info.Velo = {0.f, 200.f};
		}
	}
	if (keymanager.Key_Down(KEY_DOWN)) {
		m_FDown.start();
	}

	if (keymanager.Key_Press(KEY_LEFT)) {
		m_Info.Get_Force(Coordi(-20.f, 0.f));
		m_FMove.start();
	}
	if (keymanager.Key_Press(KEY_RIGHT)) {
		m_Info.Get_Force(Coordi(20.f, 0.f));
		m_FMove.start();
	}
	if (keymanager.Key_Up(KEY_LEFT) || keymanager.Key_Up(KEY_RIGHT)) {
		m_time = 0.f;
	}
	if (keymanager.Key_Press(KEY_Z)) {
		if (m_sPower == 2 && !m_FFire.bAct) {
			m_FFire.start();
			CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::PLAYER);
			CSoundManager::Get_Instance()->PlaySound(L"Throwing fireball.wav", CSoundManager::CHANNELID::PLAYER);
			CItemManager::Get_Instance()->Add_Item({-1,0}, CItem::ID::FIRE);
		}
		if (m_sPower == 3 && !m_FFire.bAct) {
			m_FFire.start();
			CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::PLAYER);
			CSoundManager::Get_Instance()->PlaySound(L"Throwing fireball.wav", CSoundManager::CHANNELID::PLAYER);
			CItemManager::Get_Instance()->Add_Item({ -1,0 }, CItem::ID::SUPERBALL);
		}
	}
	if (keymanager.Key_Up(KEY_Z)) {
			m_FFire.end();
	}

}

void CPlayer::Update()
{
	if (m_FDead.bAct)
		return;

	m_Info.Update_Domain();
	POINT xy = (m_Info.Posi / 50.f).Point();
	for (long i = -1; i <= +1; i++)
	{
		for (long j = -1; j <= +1; j++)
		{
			CBlock* temp = CBlockManager::Get_Instance()->Get_Object({ xy.x + i, xy.y + j });
			if (temp == nullptr)
				continue;
			USHORT Collid = temp->Collision(this);
			if (Collid & 0x1000) {
				m_Info.Velo.fy = 0.f;
				m_FJump.end();
				if(temp->Get_BTag() == CBlock::ID::HALFGROUND)
					if (Check_Down() && keymanager.Key_Down(KEY_SPACE)) {
						m_Info.Posi.fy += 25.f;
					}
			}
			else if (Collid & 0x0100) {
				m_Info.Velo.fy = 0.f;
			}
			else if (Collid & 0x0011)
				m_Info.Velo.fx = 0.f;
			m_Info.Update_Domain();
		}
	}

	if (m_FGoal.bAct)
		return;
	if (m_FPower.bAct && m_FPower.iCount < m_FPower.iFrame)
		return;

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::GOOMBA))
	{
		if (monster->Dead_Checker())
			continue;
		USHORT Collid = Collision(monster);
		if (Collid & 0x0100) {
			m_Info.Velo.fy = 0.f;
			m_Info.Get_Force(Coordi(0.f, -300.f));
			m_FJump.end();
			m_FJump.start();
		}
		else if (Collid & 0x1011)
			Power_Down();
	}

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::GOOMBRAT))
	{
		if (monster->Dead_Checker())
			continue;
		USHORT Collid = Collision(monster);
		if (Collid & 0x0100) {
			m_Info.Velo.fy = 0.f;
			m_Info.Get_Force(Coordi(0.f, -300.f));
			m_FJump.end();
			m_FJump.start();
		}
		else if (Collid & 0x1011)
			Power_Down();
	}

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::ONGGUM))
	{
		if (monster->Dead_Checker())
			continue;
		USHORT Collid = Collision(monster);
		if (Collid & 0x0100) {
			m_Info.Velo.fy = 0.f;
			m_Info.Get_Force(Coordi(0.f, -300.f));
			m_FJump.end();
			m_FJump.start();
		}
		else if (monster->Check_Sleep())
			return;
		else if (Collid & 0x1011)
			Power_Down();
	}

	for (CCharic* monster : *CCharicManager::Get_Instance()->Get_MonsterList(CCharic::ID::REDONGGUM))
	{
		if (monster->Dead_Checker())
			continue;
		USHORT Collid = Collision(monster);
		if (Collid & 0x0100) {
			m_Info.Velo.fy = 0.f;
			m_Info.Get_Force(Coordi(0.f, -300.f));
			m_FJump.end();
			m_FJump.start();
		}
		else if (monster->Check_Sleep())
			return;
		else if (Collid & 0x1011)
			Power_Down();
	}

	for (CItem* Item : *CItemManager::Get_Instance()->Get_ItemList(CItem::ID::MUSHROOM))
	{
		if (Item->Get_Dead())
			continue;
		USHORT Collid = Collision(Item);
		if (Collid) {
			Power_Up(1);
		}
	}

	for (CItem* Item : *CItemManager::Get_Instance()->Get_ItemList(CItem::ID::FIREFLOWER))
	{
		if (Item->Get_Dead())
			continue;
		USHORT Collid = Collision(Item);
		if (Collid) {
			Power_Up(2);
		}
	}

	for (CItem* Item : *CItemManager::Get_Instance()->Get_ItemList(CItem::ID::SUPERFLOWER))
	{
		if (Item->Get_Dead())
			continue;
		USHORT Collid = Collision(Item);
		if (Collid) {
			Power_Up(3);
		}
	}
}

void CPlayer::Render(HDC hDC, Coordi Scroll)
{
	if (m_bDead || m_bGoal)
		return;
	m_Info.Update_Domain();
	if (m_FDead.bAct)
	{
		Find_Sheet_Power(hDC, Scroll, 16, 1, 0);
	}
	else if (m_FGoal.bAct && m_FGoal.iCount < 20)
	{
		Find_Sheet_Power(hDC, Scroll, 14, -1, m_sPower);
	}
	else if (m_FPower.bAct && m_FPower.iCount < 5)
	{
		//9,43,
		if (m_FPower.iCount % 2 == 0)
			Find_Sheet_Power(hDC, Scroll, 1, m_LR, m_sPower);
		if (m_FPower.iCount % 2 == 1) 	
			Find_Sheet_Power(hDC, Scroll, 1, m_LR, m_sPrevPower);
	}
	else if (m_FFire.bAct && m_FFire.iCount  == 0)
	{
		Find_Sheet_Power(hDC, Scroll, 16, m_LR, m_sPower);
	}
	else if (m_FStamp.bAct)
	{
		if(m_FStamp.iCount == m_FStamp.iFrame)
			Find_Sheet_Power(hDC, Scroll, 15, m_LR, m_sPower);
		else {
			HDC hplayer = nullptr;
			switch (m_sPower)
			{
			case 0:
				m_Info.RendScale = Coordi(50.f, 50.f);
				m_Info.CollidScale = Coordi(30.f, 30.f);
				hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 9 + 3, 15 * m_LR, 16 - 3, -PI * m_FStamp.iCount / 2);																		   	
				GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
					hplayer, { 15,16 - 3 }, RGB(147, 187, 236));
				break;
			case 1:
				m_Info.RendScale = Coordi(50.f, 50.f);
				m_Info.CollidScale = Coordi(30.f, 30.f);
				hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 43 + 10, 15 * m_LR, 32 - 10, -PI * m_FStamp.iCount / 2);																		   	
				GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
					hplayer, { 15,32 - 10 }, RGB(147, 187, 236));
				break;
			case 2:
				m_Info.RendScale = Coordi(50.f, 50.f);
				m_Info.CollidScale = Coordi(30.f, 30.f);
				hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 76 + 10, 15 * m_LR, 32 - 10, -PI * m_FStamp.iCount / 2);																		   	
				GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
					hplayer, { 15,32 - 10 }, RGB(147, 187, 236));
				break;
			case 3:
				m_Info.RendScale = Coordi(50.f, 50.f);
				m_Info.CollidScale = Coordi(30.f, 30.f);
				hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 109 + 10, 15 * m_LR, 32 - 10, -PI * m_FStamp.iCount / 2);																		   	
				GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
					hplayer, { 15,32 - 10 }, RGB(147, 187, 236));
				break;
			default:
				break;
			}
		}
	}
	else if (m_FDown.bAct)
	{
		HDC hplayer = nullptr;
		switch (m_sPower)
		{
		case 0:
			m_Info.RendScale = Coordi(50.f, 40.f);
			m_Info.CollidScale = Coordi(30.f, 20.f);
			hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 9+3, 15 * m_LR, 16-3);
			GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
				hplayer, { 15,16-3 }, RGB(147, 187, 236));
			break;
		case 1:
			m_Info.RendScale = Coordi(50.f, 50.f);
			m_Info.CollidScale = Coordi(30.f, 30.f);
			hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 43+10, 15 * m_LR, 32-10);
			GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
				hplayer, { 15,32-10 }, RGB(147, 187, 236));
			break;
		case 2:
			m_Info.RendScale = Coordi(50.f, 50.f);
			m_Info.CollidScale = Coordi(30.f, 30.f);
			hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 76+10, 15 * m_LR, 32-10);
			GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
				hplayer, { 15,32-10 }, RGB(147, 187, 236));
			break;
		case 3:
			m_Info.RendScale = Coordi(50.f, 50.f);
			m_Info.CollidScale = Coordi(30.f, 30.f);
			hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 18, 109+10, 15 * m_LR, 32-10);
			GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
				hplayer, { 15,32-10 }, RGB(147, 187, 236));
			break;
		default:
			break;
		}
	}
	else if (m_FJump.bAct)
	{
		Find_Sheet_Power(hDC, Scroll, 7, m_LR, m_sPower);
	}
	else if (m_LR < 0 && m_Info.Velo.fx > -10.f || m_LR > 0 && m_Info.Velo.fx < 10.f) {
		Find_Sheet_Power(hDC, Scroll, 1, m_LR, m_sPower);
		m_FMove.end();
	}
	else if (m_FMove.bAct) {
		if(m_LR < 0 && keymanager.Key_Press(KEY_RIGHT) || m_LR > 0 && keymanager.Key_Press(KEY_LEFT)) {
			Find_Sheet_Power(hDC, Scroll, 6, m_LR, m_sPower);
		}
		else {
			Find_Sheet_Power(hDC, Scroll, 3 + m_FMove.iCount, m_LR, m_sPower);
		}
	}
	m_Info.Update_Domain();
	//Output_Rectangle(hDC, m_Info.CollidDomain, Scroll.Point(), RGB(0, 0, 0));
}

void CPlayer::Release()
{
}

USHORT CPlayer::Collision(CObject* other)
{
	USHORT Collision = 0;

	if (m_FDead.bAct || m_bDead)
		return Collision;

	if (TopCollision(other))
		Collision |= 0x1000;
	if (BottomCollision(other))
		Collision |= 0x0100;
	if (LeftCollision(other))
		Collision |= 0x0010;
	if (RightCollision(other))
		Collision |= 0x0001;

	return Collision;
}

void CPlayer::Do_Dead(float deltaTime)
{

	if (m_FDead.iCount <= 1) {
		if (m_FDead.bTrigger) {
			CSoundManager::Get_Instance()->StopAll();
			CSoundManager::Get_Instance()->PlaySound(L"Mario dies.wav", CSoundManager::CHANNELID::PLAYER);
			m_Info.Velo = { 0.f, -400.f };
		}
		m_FMove.end();
		m_FJump.end();
		m_FDown.end();
		m_FStamp.end();
		m_FPower.end();
		m_FFire.end();
		m_FGoal.end();
	}
	else if (m_FDead.iCount < 40) {
		m_Info.Move(deltaTime);
		m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	}
	if (m_FDead.iCount == 80)
		m_bDead = true;
}

void CPlayer::Power_Up(short Power)
{
 	if ((m_sPower == 0 && Power == 1) || (m_sPower != Power && Power != 1)) {
		CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::PLAYER);
		CSoundManager::Get_Instance()->PlaySound(L"Power up.wav", CSoundManager::CHANNELID::PLAYER);
		m_FPower.start();
		m_sPower = Power;
		m_Info.Posi.fy -= 5.f;
	}
}

void CPlayer::Power_Down()
{
	if (m_sPower == 0) {
		m_FDead.start();
		return;
	}
	else if (m_sPower == 1)
		m_sPower = 0;
	else if (m_sPower > 1)
		m_sPower = 1;
	m_FPower.start();
	CSoundManager::Get_Instance()->StopSound(CSoundManager::CHANNELID::PLAYER);
	CSoundManager::Get_Instance()->PlaySound(L"Power down.wav", CSoundManager::CHANNELID::PLAYER);
}


bool CPlayer::Power_Check()
{
	if (!m_FPower.bAct)
		return m_FPower.bAct;
	if (m_FPower.iCount == m_FPower.iFrame) {
		m_FPower.end();
		m_sPrevPower = m_sPower;
	}
	return m_FPower.bAct;
}

void CPlayer::_Move(float deltaTime)
{
	if (!m_FJump.bAct)
		if (m_Info.Velo.fx < 0.f)
			m_LR = -1;
		else if (m_Info.Velo.fx > 0.f)
			m_LR = 1;

	if (m_LR < 0 ? m_Info.Velo.fx < 400.f * m_LR : m_Info.Velo.fx > 400.f * m_LR)
		m_Info.Velo.fx = 400.f * m_LR;
	else if (m_LR < 0 ? m_Info.Velo.fx < 200.f * m_LR : m_Info.Velo.fx > 200.f * m_LR)
		m_FMove.fNextTime = 0.05f;
	else
		m_FMove.fNextTime = 0.1f;

	if (m_Info.Posi.fx > SCREENSIZE_X * 7 - 25) {
		m_Info.Posi.fx = SCREENSIZE_X * 7 - 25;
		m_Info.Velo.fx = 0.f;
	}
	if (m_Info.Posi.fx < 25) {
		m_Info.Posi.fx = 25;
		m_Info.Velo.fx = 0.f;
	}
	if (m_Info.Posi.fy > SCREENSIZE_Y * 2 + 50) {
		m_FDead.start();
	}
	m_Info.Move(deltaTime);
	m_Info.Get_Force(Coordi(-m_Info.Velo.fx * deltaTime, 0.9f * deltaTime * 1000.f));

	if (m_LR < 0 && m_Info.Velo.fx > -50.f || m_LR > 0 && m_Info.Velo.fx < 50.f)
		m_Info.Get_Force(Coordi(-m_Info.Velo.fx * deltaTime * 2, 0.f));
	if (m_Info.Velo.fy > 600.f) {
		m_Info.Velo.fy = 600.f;
	}
}

void CPlayer::Find_Sheet_Power(HDC hDC, Coordi Scroll, int number, short LR, short Power)
{
	HDC hplayer = nullptr;
	switch (Power)
	{
	case 0:
		m_Info.RendScale = Coordi(50.f, 50.f);
		m_Info.CollidScale = Coordi(30.f, 30.f);
		hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * (number - 1), 9, 15 * LR, 16);
		GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
			hplayer, { 15,16 }, RGB(147, 187, 236));
		break;
	case 1:
		m_Info.RendScale = Coordi(50.f, 90.f);
		m_Info.CollidScale = Coordi(30.f, 70.f);
		hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * (number - 1), 43, 15 * LR, 32);
		GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
			hplayer, { 15,32 }, RGB(147, 187, 236));
		break;
	case 2:
		m_Info.RendScale = Coordi(50.f, 90.f);
		m_Info.CollidScale = Coordi(30.f, 70.f);
		hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * (number - 1), 76, 15 * LR, 32);
		GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
			hplayer, { 15,32 }, RGB(147, 187, 236));
		break;
	case 3:
		m_Info.RendScale = Coordi(50.f, 90.f);
		m_Info.CollidScale = Coordi(30.f, 70.f);
		hplayer = CImageManager::Get_Instance()->Find_Sheet(CImageMap::sheet::Playable, 1 + 17 * (number - 1), 109, 15 * LR, 32);
		GdiTransparentBlt(hDC, Scroll.Point(), m_Info.RendDomain, m_Info.RendScale.Point(),
		hplayer, { 15,32 }, RGB(147, 187, 236));
		break;
	default:
		break;
	}
}

void CPlayer::_Goal(float deltaTime)
{
	if (!m_FGoal.bAct)
		return;

	if (m_FGoal.iCount == 1 && m_FGoal.bTrigger) {
		m_Info.Velo = { 0.f, 0.f }; 
		CCharicManager::Get_Instance()->Monster_Dead();
		CSoundManager::Get_Instance()->StopAll();
		CSoundManager::Get_Instance()->PlaySound(L"Clear.mp3",CSoundManager::CHANNELID::PLAYER);
		m_FMove.end();
		m_FDead.end();
		m_FJump.end();
		m_FDown.end();
		m_FStamp.end();
		m_FPower.end();
		m_FFire.end();
	}
	else if (m_FGoal.iCount == 10 && m_FGoal.bTrigger) {
		m_Info.Velo = { 0.f, 500.f };
	}
	else if (m_FGoal.iCount == 20 && m_FGoal.bTrigger) {
		m_Info.Velo = { 200.f, 0.f };
		m_FMove.start();
	}
	else if (m_FGoal.iCount == 40 && m_FGoal.bTrigger) {
		m_Info.Velo = { 0.f, 0.f };
		m_FMove.end();
	}
	else if (m_FGoal.iCount == m_FGoal.iFrame) {
		m_FGoal.iCount -= 1;
		m_bGoal = true;
	}


	if (m_FGoal.iCount > 10) {
		m_Info.Move(deltaTime);
		if (m_FGoal.iCount > 20)
			m_Info.Get_Force(Coordi(0.f, 0.9f * deltaTime * 1000.f));
	}
}
