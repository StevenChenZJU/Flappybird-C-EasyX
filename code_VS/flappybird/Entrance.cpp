#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Queue.h"
#include "flappybird.h"

COLORREF SkyBlue, GrassGreen;
RECT whole;
void Entrance(void)
{
	SkyBlue = RGB(78, 192, 202);
	GrassGreen = RGB(94, 226, 112);
	IMAGE BeginBack;
	char bstr[] = "BEGIN PLAY";
	char sstr[] = "SETTINGS";
	RECT whole = { 0,0,500,500 };//the whole window

	//the background picture
	setbkcolor(SkyBlue);
	cleardevice();
	loadimage(&BeginBack, "D:\\sources\\beginplace.jpg");
	putimage(0, 0, &BeginBack);


	//the entry button
	setfillcolor(WHITE);
	solidroundrect(200, 300, 300, 350, 20, 20);
	RECT BeginButton = { 200,300,300,350 };
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	drawtext(bstr, &BeginButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//the setting button
	setfillcolor(WHITE);
	solidroundrect(200, 380, 300, 430, 20, 20);
	RECT SettingButton = { 200,380,300,430 };
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	drawtext(sstr, &SettingButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//click entry button to enter the game
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();

		if (m.x >= 200 && m.x <= 300 && m.y >= 300 && m.y <= 350 && m.mkLButton)
		{
			break;
		}
		else if (m.x >= 200 && m.x <= 300 && m.y >= 300 && m.y <= 350 && m.mkLButton)
		{
			Setting();
		}
	}
}
void Setting()
{
	
}