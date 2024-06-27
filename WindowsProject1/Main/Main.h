#pragma once

class Cmain
{
public:
	Cmain();
	~Cmain();
	void Loding_MainApp(HWND hWnd);
	void Time_Update_MainApp(ULONGLONG time);
	void Render_MainApp();
	void Release_MainApp();

private:
	
	
	//for fps
private:
	HDC	m_hDC;
	float deltatime;
	bool loding;
};

