#ifndef COMMON_HPP
#define COMMON_HPP

#define _CRT_SECURE_NO_WARNINGS
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "ImageLayer.h"
#include "SoundPlayer.h"
}
#include "PC.hpp"
#include "Stage.hpp"

#define NUM1 49  
#define NUM2 50  
#define NUM3 51
#define O 111
#define P 112
#define UI_HP_ORIGIN_X 400
#define UI_HP_ORIGIN_Y 60
#define UI_O2_ORIGIN_Y 120

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define S 115
#define C 99
#define M 77
#define ESC 27
#define SPACE 32
#define SPEED 48
#define BLOCKSIZE 48
#define AREA_ORIGIN_X 96
#define AREA_ORIGIN_Y 48 *  7

#define STAGE_ORIGIN_X 600
#define STAGE_ORIGIN_Y 240
#define AREA_BLOCK_SIZE 144
#define STAGE_EXTRA_IMAGE_COUNT 3

extern PC& pc;

extern HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
extern HWND WINDOW_HANDLE;
extern ImageLayer* targetLayer;
extern ImageLayer imageLayer;
extern ImageLayer stageLayer;
extern Image imageArray[1000];
extern Image stageImages[30];
extern int stageInfo[5][5];
extern int blockInfo[1200][1200];
extern bool isOnStage;
extern char bmpStoneBlockName[];
extern char bmpBrokenStoneBlockName[];
extern char bmpNameNull[];

extern char bmpZombieName[];
extern char bmpNameBoss[];
extern char bmpNameShop[];

extern ImageLayer rewardLayer;
extern int mapInfo[6][6];
extern int index_UI_HP_Start;
extern int index_UI_O2_Start;
extern int index_UI_blockInfo_Start;
extern int index_UI_mapTile_Start;

extern char bmpNullName[];
// stage Image
extern char bmpClearedAreaName[];
extern char bmpNomalAreaName[];
extern char bmpHiddenAreaName[];
extern char bmpMovableAreaName[];
extern char bmpCharacterStatueName[];


extern int currentAreaRowIndex;
extern int currentAreaColIndex;

extern int NPCSpacePosX;
extern int NPCSpacePosY;
extern int NPCSpaceHeight;
extern int NPCSpaceWidth;

LPCWSTR ConvertToLPCWSTR(const char* ansiStr);

COORD getCurrentCurPos(void);
void setCurrentCurPos(int x, int y);

void getHandle();
void removeCursor();
void resizeConsole(int w, int h);
void initialize();
bool collisionCheck(int x, int y);
int convertPosToInfoX(int x);
int convertPosToInfoY(int y);
bool collisionCheckInStage(int x, int y);
int convertPosToInfoXInStage(int x);
int convertPosToInfoYInStage(int y);
void initBlockImages();
void initStageImages();
void setMovableStageInfo(int row, int col);
void drawUI();
void drawMapUI();
void rewardUI();
void initArea();

void fillBlockImages();
//void getNewArea(int zombieIndex);
int getNPCSpaceHeight();
int getNPCSpaceWidth();
int getNPCSpacePosX();
int getNPCSpacePosY();

#endif COMMON_HPP