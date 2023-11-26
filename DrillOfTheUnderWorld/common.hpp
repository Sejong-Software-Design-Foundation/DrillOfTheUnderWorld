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
#include "Text.hpp"

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
#define SPEED 16
#define BLOCKSIZE 48
#define AREA_ORIGIN_X 96
#define AREA_ORIGIN_Y 336
#define AREA_WIDTH 25
#define AREA_HEIGHT 25


#define STAGE_ORIGIN_X 600
#define STAGE_ORIGIN_Y 240
#define AREA_BLOCK_SIZE 144
#define STAGE_EXTRA_IMAGE_COUNT 3

#define UI_ITEM_START_POS_X 1450
#define UI_ITEM_START_POS_Y 220
#define UI_ITEM_SIZE 170

#define REWARD_BRONZE = 10
#define REWARD_SILVER = 30
#define REWARD_GLOD = 50
#define REWARD_DIAMOND = 100
#define REWARD_POSSION = 50

extern PC& pc;
extern HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
extern HWND WINDOW_HANDLE;
extern ImageLayer* targetLayer;
extern ImageLayer imageLayer;
extern ImageLayer stageLayer;
extern Image imageArray[1000];
extern Image stageImageArray[40];
extern int stageInfo[5][5];
extern int blockInfo[1200][1200];
extern bool isButtonStage;
extern bool isOnStage;
extern char bmpNamePC[];
extern char bmpStoneBlockName[];
extern char bmpBrokenStoneBlockName[];
extern char bmpNameNull[];

// NPC BMP
// 1. NORMAL NPC
extern char bmpNameBat[];

// 2. BOSS NPC
extern char bmpNameMole[];
extern char bmpNameFireball[];
extern char bmpNameEmceeTheShyGuy[];


extern char bmpNameLadder[];
extern char bmpNameMineral[];

// ORE BMP
extern char bmpNameBronzeOre[];
extern char bmpNameSilverOre[];
extern char bmpNameGoldOre[];
extern char bmpNameDiamondOre[];

extern char bmpNameBrokenBronzeOre[];
extern char bmpNameBrokenSilverOre[];
extern char bmpNameBrokenGoldOre[];
extern char bmpNameBrokenDiamondOre[];

// MINERAL BMP
extern char bmpNameBronzeMineral[];
extern char bmpNameSilverMineral[];
extern char bmpNameGoldMineral[];
extern char bmpNameDiamondMineral[];


extern ImageLayer rewardLayer;
extern int mapInfo[5][5];
extern int index_StageImages_Start;
extern int index_Area_UI_Start;
extern int index_Area_UI_HP_Start;
extern int index_Area_UI_O2_Start;
extern int index_Area_UI_Map_Start;
extern int index_Area_UI_blockInfo_Start;
extern int index_Area_UI_mapTile_Start;
extern int index_RewardImages_Start;

extern char bmpNullName[];
// stage Image
extern char bmpStageLevel[];
extern char bmpClearedAreaName[];
extern char bmpNomalAreaName[];
extern char bmpHiddenAreaName[];
extern char bmpMovableAreaName[];
extern char bmpCharacterStatusName[];

extern char bmpMineralName[];
extern char bmpBedrockName[];
extern char bmpFlagName[];
// item Image
extern char bmpItem1Name[];
extern char bmpItem2Name[];
extern char bmpItem3Name[];

extern int NPCSpacePosX;
extern int NPCSpacePosY;
extern int NPCSpaceHeight;
extern int NPCSpaceWidth;


extern int currentAreaRowIndex;
extern int currentAreaColIndex;

extern std::vector<int> buttonPressedOrderList;
extern std::vector<int> buttonPressedOrderAnswerList;
extern std::vector<std::vector<int>> buttonOrderCaseList;
extern bool isButtonRoomClear;
extern char bmpButton1Name[];
extern char bmpButton1PressedName[];
extern char bmpButton2Name[];
extern char bmpButton2PressedName[];
extern char bmpButton3Name[];
extern char bmpButton3PressedName[];

extern char bmpQuestionMarkName[];

extern int rewardItemImageIndex;

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
void initAreaUI();
void initStageImage();
void initStageImages();
void initRewardImage();
void setMovableStageInfo(int row, int col);
void drawUI();
void drawMapUI();
void rewardUI();
void initArea();

void updateCharacterStatus();
void initItemImages();
void fillBlockImages();
//void getNewArea(int zombieIndex);
int getNPCSpaceHeight();
int getNPCSpaceWidth();
int getNPCSpacePosX();
int getNPCSpacePosY();
void setMinerals(int max);
void getNewArea();

bool printButtonStageStatus();
void setBedrock(int max);
void setFlag(int cnt);
#endif COMMON_HPP