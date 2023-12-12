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
#include "Item.hpp"
#include <vector>

#define NUM1 49  
#define NUM2 50  
#define NUM3 51
#define O 111
#define P 112
#define UI_HP_ORIGIN_X 330
#define UI_HP_ORIGIN_Y 80
#define UI_O2_ORIGIN_Y 140
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
#define AREA_ORIGIN_Y 336
#define AREA_WIDTH 25
#define AREA_HEIGHT 25
#define STAGE_ORIGIN_X 540
#define STAGE_ORIGIN_Y 300
#define AREA_BLOCK_SIZE 144
#define STAGE_EXTRA_IMAGE_COUNT 3
#define UI_ITEM_START_POS_X 80
#define UI_ITEM_START_POS_Y 1000
#define UI_ITEM_MARGIN 160
#define UI_ITEM_SIZE 170
#define BOSS_SCALE 4
#define EMCEE_SCALE 4
#define RAWKHAWK_SCALE 3
#define CHARIZARD_SCALE 3
#define BOSS_HP_BAR_WIDTH 16

#define REWARD_BRONZE = 10
#define REWARD_SILVER = 30
#define REWARD_GLOD = 50
#define REWARD_DIAMOND = 100
#define REWARD_POSSION = 50

#define DEFAULT_LAYER_MARGIN_X 640 //5:8���� �ݿ� : 400 -> 640

extern int stageLevel;

extern char bgmName[];
extern char bgmArea[];
extern char bgmBoss[];
extern char bgmStage[];
extern char bgmSafety[];

extern char bgmExplosion[];
extern char bgmClear[];
extern char bgmBuy[];

extern PC& pc;
extern HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
extern HWND WINDOW_HANDLE;
extern ImageLayer uiLayer;
extern Image uiImageArray[50];
extern ImageLayer* targetLayer;

extern ImageLayer stageLayer;
extern Image stageImageArray[40];
extern int stageInfo[5][5];

extern ImageLayer imageLayer;
extern Image imageArray[2000];
extern int blockInfo[1200][1200];
extern int mapInfo[5][5];
extern int currentAreaRowIndex;
extern int currentAreaColIndex;
extern int NPCSpacePosX;
extern int NPCSpacePosY;
extern int NPCSpaceHeight;
extern int NPCSpaceWidth;
extern int OrichalcumNum;
extern int molePosX;
extern int molePosY;

// BUTTON
extern std::vector<int> buttonPressedOrderList;
extern std::vector<int> buttonPressedOrderAnswerList;
extern std::vector<std::vector<int>> buttonOrderCaseList;
extern bool isButtonRoomClear;
extern bool isGenerateMobByQuestionBlock;
extern int questionBlockPosX;
extern int questionBlockPosY;

extern ImageLayer rewardLayer;

extern bool isOnStage;
extern bool isOnArea;
extern bool isNormalArea;
extern bool isMiniGameArea;
extern bool isFlagArea;
extern bool isButtonArea;
extern bool isBossArea;
extern bool isTreasureArea;

extern int index_StageImages_Start;
extern int index_Area_PC;
extern int index_Area_Button_Start;
extern int index_Area_UI_Start;
extern int index_Area_UI_HP_Start;
extern int index_Area_UI_O2_Start;
extern int index_Area_UI_Map_Start;
extern int index_Area_UI_blockInfo_Start;
extern int index_Area_UI_mapTile_Start;
extern int index_Area_UI_MiniGame_Start;
extern int index_RewardImages_Start;

extern char bmpNameNull[];

// STAGE MAP BMP
extern char bmpNamePC[];
extern char bmpStageLevel1[];
extern char bmpStageLevel2[];
extern char bmpStageLevel3[];
extern char bmpClearedAreaName[];
extern char bmpNomalAreaName[];
extern char bmpHiddenAreaName[];
extern char bmpMovableAreaName[];
extern char bmpMovableHiddenAreaName[];
extern char bmpCharacterStatusName[];

// NORMAL NPC
extern char bmpNameBat[];
extern char bmpNameMole[];
extern char bmpNameMoleDigging[];
// NULL BMP

// BOSS NPC
extern char bmpNameEmceeTheShyGuy[];
extern char bmpNameFireball[];

extern char bmpNameRawkHawk[];
extern char bmpNameRawkHawk_ready[];
extern char bmpNameRawkHawk_digging[];

extern char bmpNameCharizard[];
extern char bmpNameFireground[];

// LADDER 
extern char bmpNameLadder[];

// AREA UI BMP
extern char bmpNameStar0[];
extern char bmpNameStar1[];
extern char bmpNameStar2[];
extern char bmpNameStar3[];
extern char bmpBossHPName[];

// BLOCK BMP
extern char bmpStoneBlockName[3][40];
extern char bmpBrokenStoneBlockName[3][40];

// ORE BMP
extern char bmpNameBronzeOre1[3][40];
extern char bmpNameBronzeOre2[3][40];
extern char bmpNameSilverOre1[3][40];
extern char bmpNameSilverOre2[3][40];
extern char bmpNameGoldOre1[3][40];
extern char bmpNameGoldOre2[3][40];
extern char bmpNameDiamondOre1[3][40];
extern char bmpNameDiamondOre2[3][40];
extern char bmpNameOrichalcumOre1[3][40];
extern char bmpNameOrichalcumOre2[3][40];
extern char bmpNameBrokenBronzeOre[3][40];
extern char bmpNameBrokenSilverOre[3][40];
extern char bmpNameBrokenGoldOre[3][40];
extern char bmpNameBrokenDiamondOre[3][40];

// MINERAL BMP
extern char bmpNameBronzeMineral[];
extern char bmpNameSilverMineral[];
extern char bmpNameGoldMineral[];
extern char bmpNameDiamondMineral[];
extern char bmpNameOrichalcumMineral[];

// BUTTON BMP
extern char bmpButton1Name[];
extern char bmpButton1PressedName[];
extern char bmpButton2Name[];
extern char bmpButton2PressedName[];
extern char bmpButton3Name[];
extern char bmpButton3PressedName[];

// QUESTIONBLOCK BMP
extern char bmpQuestionMarkName[];
extern char bmpOzPotionName[];
extern char bmpHpPotionName[];
extern char bmpBoomName[];

// FLAG, BEDROCK BMP
extern char bmpBedrockName[];
extern char bmpFlagName[];

// item Image
extern char bmpUndergroundTicketName[];
extern char bmpMetalDetectorName[];
extern char bmpThornCrownName[];
extern char bmpBeggarDollName[];
extern char bmpOrichalcumName[];
extern char bmpTwoHeartsName[];
extern char bmpLuckyCharmName[];
extern char bmpDisassemblerName[];
extern char bmpBatFangName[];
extern char bmpMoleClawName[];
extern char bmpDiceName[];
extern char bmpLuckStoneName[];
extern char bmpBloodBagName[];
extern char bmpSupplyOxygenTankName[];
extern char bmpFreshBrewedCoffeeName[];
extern char bmpPortableOxygenCanName[];
extern char bmpEnergyBarName[];
extern char bmpAttackBoostName[];
extern char bmpAttackSpeedBoostName[];
extern char bmpMovementSpeedBoostName[];
extern char bmpPrisonerShacklesName[];
extern char bmpCursedTotemName[];
extern char bmpAncientVirusName[];
extern char bmpCaveSnakeName[];

extern char bmpBackgroundTestName[];

// ?�든 ?�어리어 관�?
extern std::vector<std::vector<int>> hiddenAreaPosList;
extern std::vector<int> bossAreaPos;
extern std::vector<int> treasureAreaPos;

LPCWSTR ConvertToLPCWSTR(const char* ansiStr);

COORD getCurrentCurPos(void);
void setCurrentCurPos(int x, int y);

void getHandle();
void removeCursor();
void resizeConsole(int w, int h);
void initialize();
bool collisionCheck(int x, int y, int scale);
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
void initUIImage();
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
void getNewMiniGameArea();

bool printButtonStageStatus();
void printFlagStageStatus(int curFlagCnt);
void setBedrock(int max);
void setFlag(int cnt);

void getNewBossArea();
void printStoneStatus(int curStone);
void printWarning(int curHP);
void getMoleSpace();

// Ãß°¡
extern ImageLayer lShopLayer;
extern ImageLayer rShopLayer;
extern bool isOnSafety;
void initLShopImage();
void initRShopImage();
#define LSHOP_ITEMBOX_ORIGIN_X 850
#define LSHOP_ITEMBOX_ORIGIN_Y 350
#define RSHOP_ITEMBOX_ORIGIN_X 50
#define RSHOP_ITEMBOX_ORIGIN_Y 350
void visitLShop();
void printItemTextInLShop();
void printStatusInLShop(int price1, int price2, int num);
void visitRShop();
void printItemTextInRShop();
void printStatusInRShop(int price1, int price2, int price3, int num);

void stringToWchar(const std::string& input, wchar_t* output, size_t outputSize);
void generateShopItem();
char getRandomRank();
Item* getRandomItem();
bool isItemExistItemVector(Item* targetItem, std::vector<Item*> itemList);

extern ImageLayer safetyLayer;
void initSafetyImage();
void visitSafety();
extern int index_Safety_Object_Start;

std::vector<int> getRandomHiddenAreaPos();
void setHiddenAreaPos();

void renderImageLayer();
void renderTargetLayer();

extern ImageLayer gameStartLayer;
extern ImageLayer gameOverLayer;

void printGameStart();
void printGameOver();

// define my areaImageLayer
extern ImageLayer areaLayer;
extern ImageLayer progressLayer;
extern Image progressImageArray[100];
void initProgressImage();
void drawProgress();
extern int index_Timer_Start;
extern int timerIndex;

bool isRetry();
void resetPcStatus();
extern char bmpTreasure[];
extern char bmpTreasureOpen[];
extern char bgmAchive[];
#endif COMMON_HPP
