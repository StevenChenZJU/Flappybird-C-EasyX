//the pictures is stored in D:\\sources\\
//place a tube every 50 
//have not figure out why the flashing happens


//to do list: 
//1.get setting at the entrance


#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Queue.h"
#include "flappybird.h"

//Global Variable List
//extern
extern Queue Q;

extern COLORREF SkyBlue, GrassGreen;
extern RECT whole;

//local
struct bird Bird;
static int score;
static char cscore[10];
//Queue

Queue Tube;
//image
//[1]is the origin picture and [0] is the mask
IMAGE BirdPic[2];
IMAGE TubeUpPic[2];
IMAGE TubeMiddlePic[2];
IMAGE TubeDownPic[2];


int main()
{
	//initialize the window
	initgraph(WIDTH, HEIGHT);
	//the entry page
	Entrance();
	//begin the game
	InitGame();
	Click();
	while (true)
	{
		if (!Update())
			break;
		Draw();
		Delay();

	}
	EndGame();
	//to do:
	

	//鸟上下运动
	//tube随机生成并且会向左移动
	//碰撞与游戏结束
	
	system("pause");

	return 0;

	
}

void InitGame(void)
{
	setbkcolor(SkyBlue);
	cleardevice();
	PrintBackground();
	//initialize the bird
	InitBird();
	PrintBird();
	//initialize the tube
	InitTubeImage();
	InitTube();
	PrintTube();
	BeginBatchDraw();
	
}

void Click(void)
{
	MOUSEMSG m;

	while (true)
	{
		m = GetMouseMsg();
		if (m.mkLButton)
			break;
	}
}
void my_putimage(int x, int y , IMAGE* img)
{
	putimage(x, y, &img[0], SRCAND);//the original picture
	putimage(x, y, &img[1], SRCINVERT);//the mask
}
void EndGame(void)
{
	Sleep(1000);
	EndBatchDraw();
	Click();
	cleardevice();
	settextcolor(BLACK);
	settextstyle(40, 30, _T("黑体"));
	outtextxy(WIDTH / 2 - 140, 200, _T("GAME OVER"));
	system("pause");
}
void PrintBackground(void)
{
	loadimage(NULL, "D://sources//background.png", 500, 500);
}
void InitBird(void)
{
	Bird.x = BIRD_X;
	Bird.y = HEIGHT/2;
	Bird.v = V_ORIGIN;
	InitBirdImage();
}
void InitBirdImage(void)
{
	loadimage(&BirdPic[1], _T("D://sources//bird.bmp"), 20, 20);//what is _T mean?
	loadimage(&BirdPic[0], _T("D://sources//birdmask.bmp"), 20, 20);
	
}
void PrintBird(void)
{
	my_putimage(Bird.x, Bird.y, BirdPic);
}
void InitTubeImage(void)
{
	//load the image
	loadimage(&TubeUpPic[1], _T("D://sources//tube_up.bmp"),50,500);
	loadimage(&TubeUpPic[0], _T("D://sources//tube_up_mask.bmp"), 50, 500);
	loadimage(&TubeDownPic[1], _T("D://sources//tube_down.bmp"), 50, 500);
	loadimage(&TubeDownPic[0], _T("D://sources//tube_down_mask.bmp"), 50, 500);
	loadimage(&TubeMiddlePic[1], _T("D://sources//tube_middle.bmp"), 50, 500);
	loadimage(&TubeMiddlePic[0], _T("D://sources//tube_middle_mask.bmp"), 50, 500);
}
int Random()
{
	int RandomNum;
	srand((unsigned int)time(NULL));
	RandomNum = rand() % 3;
	return RandomNum;
}
void InitTube(void)
{
	int RandomTube;
	TubePair *Temp;
	
	int i;

	//initialize the queue
	Tube = CreateQueue(MAX_ELEMENTS_TUBE);
	MakeEmpty(Tube);
	for (i = 0; i < INIT_ELEMENTS_TUBE; i++)
	{
		RandomTube = Random();
		switch (RandomTube)
		{
		case 0: 
			Temp = (TubePair*)malloc(sizeof(TubePair));
			Temp->center = tup; Temp->x = INIT_TUBE + LEN_BETWEEN_TUBE * i;
			Enqueue(*Temp,Tube);
			break;
		case 1:
			Temp = (TubePair*)malloc(sizeof(TubePair));
			Temp->center = tmiddle; Temp->x = INIT_TUBE + LEN_BETWEEN_TUBE * i;
			Enqueue(*Temp, Tube);
			break;
		case 2:
			Temp = (TubePair*)malloc(sizeof(TubePair));
			Temp->center = tdown; Temp->x = INIT_TUBE + LEN_BETWEEN_TUBE * i;
			Enqueue(*Temp, Tube);
			break;
		}

	}
}
void PrintTube(void)
{
	int i, index;
	index = Tube->Front;
	for (i = 0; i < Tube->Size;i++)
	{
		switch (Tube->Array[index].center)
		{
		case tup:
			my_putimage(Tube->Array[index].x, 0, TubeUpPic); break;
		case tmiddle:
			my_putimage(Tube->Array[index].x, 0, TubeMiddlePic); break;
		case tdown:
			my_putimage(Tube->Array[index].x, 0, TubeDownPic); break;			
		}
		index = (index + 1 >= Tube->Capacity) ? 0 : index + 1;
	}
}
void Delay()
{
	static int CurTime = GetTickCount();
	static int PreTime = GetTickCount();
	while (CurTime - PreTime < DELAY)
	{
		CurTime = GetTickCount();
		Sleep(1);
	}
	PreTime = CurTime;
}
void UpdateBird()
{
	MOUSEMSG M;
	if (MouseHit())
	{
		M = GetMouseMsg();
		if (M.mkLButton)
			Bird.v = V_ORIGIN;
	}
	//move the bird
	Bird.y += Bird.v;
	Bird.v += GRAVITY;
}
ElementType NewTube()
{
	ElementType T;
	T.x = WIDTH ;
	switch (Random())
	{
	case 0:
		T.center = tup; break;
	case 1:
		T.center = tmiddle; break;
	case 2:
		T.center = tdown; break;
	}
	return T;
}
void UpdateTube()
{
	int i,index;
	index = Tube->Front;

	if (Tube->Array[Tube->Front].x <= BIRD_X - LEN_TUBE)
		Dequeue(Tube);
	if (Tube->Array[Tube->Rear].x < WIDTH - LEN_BETWEEN_TUBE)
	{
		Enqueue(NewTube(),Tube);
	}
	//move the tube
	for (i = 0; i < Tube->Size; i++)
	{
		Tube->Array[index].x -= V_TUBE;
		index = (index + 1 >= Tube->Capacity) ? 0 : index + 1;
	}

}
bool Crash(void)
{
	if (CheckBorderCrash())
		return true;
	else if (Tube->Array[Tube->Front].x <= BIRD_X + BIRD_SIZE - 6 && Tube->Array[Tube->Front].x >= BIRD_X - LEN_TUBE + BIRD_SIZE )// 6 and Bird_size is for correction
	{
		if (CheckTubeCrash())
			return true;
		
	}
	else
		return false;
}
	
bool CheckBorderCrash()
{
	if (Bird.y >= HEIGHT || Bird.y <= 0)
		return true;
	else
		return false;
}
bool CheckTubeCrash()
{
	//only the first tube in the queue has the chance to make the bird crashed
	switch (Tube->Array[Tube->Front].center)
	{
	case tup:
		if (Bird.y >= TUP_FLOOR - BIRD_SIZE + 10 || Bird.y <= TUP_CEILING )
			return true;
		break;
	case tmiddle:
		if (Bird.y >= TMIDDLE_FLOOR - BIRD_SIZE + 10 || Bird.y <= TMIDDLE_CEILING )
			return true;
		break;
	case tdown:
		if (Bird.y >= TDOWN_FLOOR - BIRD_SIZE + 10 || Bird.y <= TDOWN_CEILING )
			return true;
		break;
	}
	return false;
}
bool Update(void)
{
	UpdateBird();
	UpdateTube();
	UpdateScore();
	if (!Crash())
		return true;
	else
		return false;
	
}
void Draw(void)
{
	//background
	cleardevice();
	PrintBackground();
	//bird and tube
	PrintTube();
	PrintBird();
	PrintScore();
	
	FlushBatchDraw();
}
void PrintScore(void)
{
	settextcolor(BLACK);
	settextstyle(20, 10, _T("黑体"));
	outtextxy(WIDTH -100, 0, _T("Score : "));
	_itoa_s(score, cscore, 10);// transform the intager to string
	outtextxy(WIDTH - 20 , 0, _T(cscore));
}
void UpdateScore(void)
{
	if (Bird.x >= Tube->Array[Tube->Front].x - 1 && Bird.x <= Tube->Array[Tube->Front].x)
		++score;
}