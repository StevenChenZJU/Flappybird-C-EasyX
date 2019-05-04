#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Queue.h"
#include "flappybird.h"

COLORREF SkyBlue, GrassGreen;
RECT whole;
//local struct
static struct button
{
	int top, bottom, left, right;
	RECT area;
	char name[20];
	COLORREF color;
};
typedef struct button Button;

//local function
Button CreateButton(int top, int bottom, int left, int right, COLORREF color, char name[]);
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
	Button BeginButton = CreateButton(300, 350, 200, 300, WHITE, bstr);
	//the setting button
	Button SettingButton = CreateButton(380, 430, 200, 300, WHITE, sstr);
	//click entry button to enter the game
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();

		if (m.x >= 200 && m.x <= 300 && m.y >= 300 && m.y <= 350 && m.mkLButton)
		{
			break;
		}
		else if (m.x >= SettingButton.left && m.x <= SettingButton.right && m.y >= SettingButton.top && m.y <= SettingButton.bottom && m.mkLButton)
		{
			Setting();
		}
	}
}
void Setting()
{
	cleardevice();
	//the back button
	char bstr[] = "Back";
	Button BackButton = CreateButton(20, 80, 20, 80, WHITE, bstr);
	while (true)
	{
		MOUSEMSG m;
		m = GetMouseMsg();

		if (m.x >= BackButton.left && m.x <= BackButton.right && m.y >= BackButton.top && m.y <= BackButton.bottom && m.mkLButton)
		{
			Entrance();
		}
	}
}
Button CreateButton(int top, int bottom, int left, int right, COLORREF color, char name[])
{
	Button B;
	setfillcolor(color);
	solidroundrect(left, top, right, bottom, (left + top + right + bottom)/40, (left + top + right + bottom) / 40);
	RECT BR = { left, top, right, bottom };
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	drawtext(name, &BR, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	B.area = BR;
	B.color = color;
	B.top = top;
	B.left = left;
	B.right = right;
	B.bottom = bottom;
	strcpy_s(B.name, name);

	return B;
}