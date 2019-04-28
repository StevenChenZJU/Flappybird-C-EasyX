
#ifndef _flappybird_h_
#define _flappybird_h_
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"

//Game Data
//Window
#define WIDTH 500
#define HEIGHT 500
//Position
#define BIRD_X 50
//Length
#define BIRD_SIZE 20
#define INIT_TUBE 300
#define LEN_BETWEEN_TUBE 150
#define LEN_TUBE 80
#define TUP_CEILING 110
#define TUP_FLOOR 220
#define TMIDDLE_CEILING 170
#define TMIDDLE_FLOOR 290
#define TDOWN_CEILING 250
#define TDOWN_FLOOR 380
//Speed
#define V_TUBE 2
#define V_ORIGIN -8
#define GRAVITY 1
//Time
#define DELAY 18
//Macro in Queue
#define INIT_ELEMENTS_TUBE 2
#define MAX_ELEMENTS_TUBE 5

//SkyBlue is 78 192 202
//GrassGreen is 94 226 112

//structure
struct bird
{
	int x;
	int y;
	int v;// take down as positive
};
//typedef
enum tubepos {tup , tmiddle, tdown };
typedef struct tubepair
{
	int x;//horizontal position
	enum tubepos center;//the vertical center of the pair of tubes
}TubePair;
typedef TubePair ElementType;

//Function List
void Entrance(void);
void InitGame(void);
void Click(void);
void my_putimage(int x, int y, IMAGE*);
void UpdateBird(void);
void UpdateTube(void);
bool Crash(void);
bool Update(void);
void Draw(void);
void EndGame(void);
void PrintBackground(void);
void InitBird(void);
void PrintBird(void);
void InitTubeImage(void);
void InitTube(void);
void PrintTube(void);
void Delay();
ElementType NewTube(void);
int Random(void);
bool CheckTubeCrash(void);
bool CheckBorderCrash(void);
void InitBirdImage(void);
void PrintScore(void);
void UpdateScore(void);
void Setting(void);
#endif