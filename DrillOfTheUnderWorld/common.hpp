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

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define S 115
#define C 99
#define M 77
#define ESC 27
#define SPACE 32
#define SPEED 24
#define BLOCKSIZE 48
#define AREA_ORIGIN_X 96
#define AREA_ORIGIN_Y 96

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


// stage Image
extern char bmpClearedAreaName[];
extern char bmpNomalAreaName[];
extern char bmpHiddenAreaName[];
extern char bmpMovableAreaName[];
extern char bmpCharacterStatueName[];


extern int currentAreaRowIndex;
extern int currentAreaColIndex;

LPCWSTR ConvertToLPCWSTR(const char* ansiStr);

void getHandle();
void removeCursor();
void resizeConsole(int w, int h);
void initialize();
void dig(int x, int y);
bool collisionCheck(int x, int y);
int convertPosToInfoX(int x);
int convertPosToInfoY(int y);
bool collisionCheckInStage(int x, int y);
int convertPosToInfoXInStage(int x);
int convertPosToInfoYInStage(int y);
void initBlockImages();
void initStageImages();
void setMovableStageInfo(int row, int col);

#endif COMMON_HPP