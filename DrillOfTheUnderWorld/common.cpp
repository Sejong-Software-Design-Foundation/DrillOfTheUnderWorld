#include "common.hpp"

PC& pc = PC::getPC();
HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer* targetLayer = NULL;
ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
ImageLayer stageLayer = DEFAULT_IMAGE_LAYER;
Image imageArray[1000];
Image stageImageArray[40];
int currentAreaRowIndex;
int currentAreaColIndex;
int blockInfo[1200][1200];
int stageInfo[5][5];
bool isOnStage = true;
bool isButtonStage = false;
char bmpStoneBlockName[] = "block_Stage1_Normal.bmp";
char bmpBrokenStoneBlockName[] = "block_Stage1_Broken.bmp";

char bmpNamePC[] = "PlayerCharacter.bmp";
char bmpStageLevel[] = "Stage1.bmp";
char bmpClearedAreaName[] = "clearedArea.bmp";
char bmpNomalAreaName[] = "nomalArea.bmp";
char bmpHiddenAreaName[] = "hiddenArea.bmp";
char bmpMovableAreaName[] = "movableArea.bmp";
char bmpCharacterStatusName[] = "UI_character_status.bmp";

char bmpNameNull[] = "";

// NPC BMP
char bmpNullName[] = "";

// 1. NORMAL NPC
char bmpNameBat[] = "Bat.bmp";

// 2. BOSS NPC
char bmpNameMole[] = "Mole.bmp";
char bmpNameFireball[] = "Fireball.bmp";
char bmpNameEmceeTheShyGuy[] = "EmceeTheShyGuy.bmp";

char bmpNameLadder[] = "Ladder.bmp";

// have to add all these bmp files as bitmap resources
// ORE BMP
char bmpNameBronzeOre[] = "block_Stage1_BronzeOre1.bmp";
char bmpNameSilverOre[] = "block_Stage1_SilverOre1.bmp";
char bmpNameGoldOre[] = "block_Stage1_GoldOre1.bmp";
char bmpNameDiamondOre[] = "block_Stage1_DiamondOre1.bmp";

char bmpNameBrokenBronzeOre[] = "block_Stage1_Broken_BronzeOre1.bmp";
char bmpNameBrokenSilverOre[] = "block_Stage1_Broken_SilverOre1.bmp";
char bmpNameBrokenGoldOre[] = "block_Stage1_Broken_GoldOre1.bmp";
char bmpNameBrokenDiamondOre[] = "block_Stage1_Broken_DiamondOre1.bmp";

// MINERAL BMP
char bmpNameBronzeMineral[] = "block_MineralBronze.bmp";
char bmpNameSilverMineral[] = "block_MineralSilver.bmp";
char bmpNameGoldMineral[] = "block_MineralGold.bmp";
char bmpNameDiamondMineral[] = "block_MineralDiamond.bmp";


ImageLayer rewardLayer = DEFAULT_IMAGE_LAYER;
Image imagesReward[1000];
int mapInfo[5][5];

int index_StageImages_Start;
int index_Area_UI_Start;
int index_Area_UI_HP_Start;
int index_Area_UI_O2_Start;
int index_Area_UI_Map_Start;
int index_Area_UI_blockInfo_Start;
int index_Area_UI_mapTile_Start;
int index_RewardImages_Start;

char bmpNameUIItemBox[] = "UI_itemBox.bmp";

char bmpNameMapPC[] = "UI_mapPC.bmp";
char bmpNameMapX[] = "UI_mapX.bmp";
char bmpNameMapTile[] = "UI_mapTile.bmp";
char bmpNameMapTileCleared[] = "UI_mapTileCleared.bmp";
char bmpNameMapBox[] = "UI_mapBox.bmp";

char bmpNameHP_0pct[] = "UI_HP_0pct.bmp";
char bmpNameHP_10pct[] = "UI_HP_10pct.bmp";
char bmpNameHP_20pct[] = "UI_HP_20pct.bmp";
char bmpNameHP_30pct[] = "UI_HP_30pct.bmp";
char bmpNameHP_40pct[] = "UI_HP_40pct.bmp";
char bmpNameHP_50pct[] = "UI_HP_50pct.bmp";
char bmpNameHP_60pct[] = "UI_HP_60pct.bmp";
char bmpNameHP_70pct[] = "UI_HP_70pct.bmp";
char bmpNameHP_80pct[] = "UI_HP_80pct.bmp";
char bmpNameHP_90pct[] = "UI_HP_90pct.bmp";
char bmpNameHP_100pct[] = "UI_HP_100pct.bmp";
char bmpNameMaxHP[] = "UI_maxHP.bmp";

char bmpNameO2_0pct[] = "UI_O2_0pct.bmp";
char bmpNameO2_10pct[] = "UI_O2_10pct.bmp";
char bmpNameO2_20pct[] = "UI_O2_20pct.bmp";
char bmpNameO2_30pct[] = "UI_O2_30pct.bmp";
char bmpNameO2_40pct[] = "UI_O2_40pct.bmp";
char bmpNameO2_50pct[] = "UI_O2_50pct.bmp";
char bmpNameO2_60pct[] = "UI_O2_60pct.bmp";
char bmpNameO2_70pct[] = "UI_O2_70pct.bmp";
char bmpNameO2_80pct[] = "UI_O2_80pct.bmp";
char bmpNameO2_90pct[] = "UI_O2_90pct.bmp";
char bmpNameO2_100pct[] = "UI_O2_100pct.bmp";
char bmpNameMaxO2[] = "UI_maxO2.bmp";

char bmpNameNormalRewardSelected[] = "UI_normalEnforceSelected.bmp";
char bmpNameNormalReward[] = "UI_normalEnforce.bmp";
char bmpNameDynamicRewardSelected[] = "UI_dynamicEnforceSelected.bmp";
char bmpNameDynamicReward[] = "UI_dynamicEnforce.bmp";
char bmpNameNormalAtkSelected[] = "UI_rewardAtkSelected.bmp";
char bmpNameNormalAtk[] = "UI_rewardAtk.bmp";
char bmpNameNormalAtkSpdSelected[] = "UI_rewardAtkSpdSelected.bmp";
char bmpNameNormalAtkSpd[] = "UI_rewardAtkSpd.bmp";
char bmpNameNormalSpdSelected[] = "UI_rewardSpdSelected.bmp";
char bmpNameNormalSpd[] = "UI_rewardSpd.bmp";

char bmpMineralName[] = "Mineral.bmp";

int NPCSpacePosX;
int NPCSpacePosY;
int NPCSpaceHeight;
int NPCSpaceWidth;

char bmpItem1Name[] = "item1.bmp";
char bmpItem2Name[] = "item2.bmp";
char bmpItem3Name[] = "item3.bmp";

bool isButtonRoomClear = false;
std::vector<int> buttonPressedOrderList;
std::vector<int> buttonPressedOrderAnswerList;
std::vector<std::vector<int>> buttonOrderCaseList = { {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1} };
char bmpButton1Name[] = "button1.bmp";
char bmpButton1PressedName[] = "button1Pressed.bmp";
char bmpButton2Name[] = "button2.bmp";
char bmpButton2PressedName[] = "button2Pressed.bmp";
char bmpButton3Name[] = "button3.bmp";
char bmpButton3PressedName[] = "button3Pressed.bmp";

char bmpQuestionMarkName[] = "questionMark.bmp";
char bmpOzPotionName[] = "ozPotion.bmp";
char bmpHpPotionName[] = "hpPotion.bmp";
char bmpBoomName[] = "boom.bmp";
bool isGenerateMobByQuestionBlock = false;
int questionBlockPosX = 0;
int questionBlockPosY = 0;


LPCWSTR ConvertToLPCWSTR(const char* ansiStr) {
    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, ansiStr, -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[requiredSize];
    MultiByteToWideChar(CP_UTF8, 0, ansiStr, -1, wideStr, requiredSize);
    return wideStr;
}

void getHandle() {
    CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    WINDOW_HANDLE = GetConsoleWindow();
}

void removeCursor() {
    CONSOLE_CURSOR_INFO c;
    c.bVisible = FALSE;
    c.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
void resizeConsole(int w, int h) {
    char temp[100];
    sprintf(temp, "mode con cols=%d lines=%d", w, h);
    system(temp);
}

void initialize() {

    getHandle();
    resizeConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    removeCursor();
    srand((unsigned)time(NULL)); // �߰��� �׸�
}

// NPC ���� �����?


void initBlockImages() {
	NPCSpaceHeight = getNPCSpaceHeight();
	NPCSpaceWidth = getNPCSpaceWidth();

	NPCSpacePosX = getNPCSpacePosX();
	NPCSpacePosY = getNPCSpacePosY();
   for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
      for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
         if (y != AREA_ORIGIN_Y + BLOCKSIZE*24 && x != AREA_ORIGIN_X + BLOCKSIZE*24 &&
			 y >= NPCSpacePosY && y<= NPCSpacePosY + BLOCKSIZE* NPCSpaceHeight &&
			 x >= NPCSpacePosX && x <= NPCSpacePosX + BLOCKSIZE * NPCSpaceWidth) {
            imageArray[imageLayer.imageCount++] = { bmpNullName, x,y,1};
			for (int dy = 0;dy < BLOCKSIZE;dy++) {
				for (int dx = 0;dx < BLOCKSIZE;dx++) {
					blockInfo[convertPosToInfoY(y+dy)][convertPosToInfoX(x+dx)] = 0;
				}
			}
         }
         else {
            imageArray[imageLayer.imageCount++] = { bmpStoneBlockName, x,y,1 };
			for (int dy = 0;dy < BLOCKSIZE;dy++) {
				for (int dx = 0;dx < BLOCKSIZE;dx++) {
					blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 2;
				}
			}
         }
      }
   }
}


void getNewArea() {
	NPCSpaceHeight = getNPCSpaceHeight();
	NPCSpaceWidth = getNPCSpaceWidth();

	NPCSpacePosX = getNPCSpacePosX();
	NPCSpacePosY = getNPCSpacePosY();
	int cnt = 1;
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			if (y != AREA_ORIGIN_Y + BLOCKSIZE * 24 && x != AREA_ORIGIN_X + BLOCKSIZE * 24 &&
				y >= NPCSpacePosY && y <= NPCSpacePosY + BLOCKSIZE * NPCSpaceHeight &&
				x >= NPCSpacePosX && x <= NPCSpacePosX + BLOCKSIZE * NPCSpaceWidth) {
				imageArray[cnt++] = { bmpNullName, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 0;
					}
				}
			}
			else {
				imageArray[cnt++] = { bmpStoneBlockName, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 2;
					}
				}
			}
		}
	}
	//setMinerals(10);
	imageArray[0].x = AREA_ORIGIN_X + 576;
	imageArray[0].y = AREA_ORIGIN_Y;
	for (int y = 0;y < BLOCKSIZE;y++) {
		for (int x = 0;x < BLOCKSIZE;x++) {
			blockInfo[y][576 + x] = 0;
		}
	}
	imageArray[13].fileName = bmpNullName;
}

void fillBlockImages() {
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			imageArray[imageLayer.imageCount++] = { bmpStoneBlockName, x,y,1 };
			blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] = 2;
		}
	}
}


void initStageImage() { // 최초 스테이지 관련 이미지를 생성
	stageLayer.images = stageImageArray;
	stageLayer.imageCount = 0;

	index_StageImages_Start = stageLayer.imageCount;
	stageImageArray[stageLayer.imageCount++] = { bmpNamePC, STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 2 + 48, STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 2 + 48, 1 };
	stageImageArray[stageLayer.imageCount++] = { bmpCharacterStatusName, 60 , STAGE_ORIGIN_Y, 1 };
	stageImageArray[stageLayer.imageCount++] = { bmpStageLevel, STAGE_ORIGIN_X + AREA_BLOCK_SIZE + 48, 48, 0.2 };

	for (int y = STAGE_ORIGIN_Y; y < STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 5; y += AREA_BLOCK_SIZE) {
		for (int x = STAGE_ORIGIN_X; x < STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 5; x += AREA_BLOCK_SIZE) {
			//printf("%d %d\n", x, y);
			stageImageArray[stageLayer.imageCount++] = { bmpNomalAreaName, x, y, 1 };
			stageInfo[(y - STAGE_ORIGIN_Y) / AREA_BLOCK_SIZE][(x - STAGE_ORIGIN_X) / AREA_BLOCK_SIZE] = 1;
		}
	}
	//stageInfo[2][2] = 0;

	//stageLayer.images[(2) * 5 + 2 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
}

void setMovableStageInfo(int row, int col) {
	if (row - 1 >= 0) {
		if (stageInfo[row - 1][col] == 1) {
			stageLayer.images[(row - 1) * 5 + col + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row - 1][col] = 0;
		}
	}
	if (row + 1 < 5) {
		if (stageInfo[row + 1][col]) {
			stageLayer.images[(row + 1) * 5 + col + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row + 1][col] = 0;
		}
	}
	if (col - 1 >= 0) {
		if (stageInfo[row][col - 1]) {
			stageLayer.images[(row) * 5 + col - 1 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row][col - 1] = 0;
		}
	}

	if (col + 1 < 5) {
		if (stageInfo[row][col + 1]) {
			stageLayer.images[(row) * 5 + col + 1 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row][col + 1] = 0;
		}
	}
}

void initArea() {
	for (int i = 0;i < AREA_HEIGHT;i++) {
		for (int j = 0;j < AREA_WIDTH;j++) {
			if (i > 4 && i < 20 && j> 5 && j < 20) imageLayer.images[i * 25 + j + 1].fileName = bmpNameNull;
		}
	}
	for (int y = 240;y < 960;y++) {
		for (int x = 192;x < 960;x++) {
			blockInfo[y][x] = 0;
		}
	}
}

int convertPosToInfoX(int x) {
    return (x - AREA_ORIGIN_X);
}
int convertPosToInfoY(int y) {
    return (y - AREA_ORIGIN_Y);
}

bool collisionCheck(int x, int y) {
    int startX = convertPosToInfoX(x);
    int startY = convertPosToInfoY(y);

    for (int curY = startY; curY < startY + BLOCKSIZE; curY++) {
        for (int curX = startX; curX < startX + BLOCKSIZE; curX++) {
            if (curY < 0 || curY >= 1200 || curX < 0 || curX >= 1200) continue;
            if (blockInfo[curY][curX]) return true;
        }
    }
    return false;
}

int convertPosToInfoXInStage(int x) {
    if (x - STAGE_ORIGIN_X <= 0) return -1;
    return (x - STAGE_ORIGIN_X) / AREA_BLOCK_SIZE;
}
int convertPosToInfoYInStage(int y) {
    if (y - STAGE_ORIGIN_Y <= 0) return -1;
    return (y - STAGE_ORIGIN_Y) / AREA_BLOCK_SIZE;
}
bool collisionCheckInStage(int x, int y) {
    int infoX = convertPosToInfoXInStage(x);
    int infoY = convertPosToInfoYInStage(y);
    if (infoY < 0 || infoY >= 5 || infoX < 0 || infoX >= 5)
        return 1;
    //return 0;
    return stageInfo[infoY][infoX];
}

COORD getCurrentCurPos(void) {
    COORD curPoint;
    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;

    return curPoint;
}

void setCurrentCurPos(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void initAreaUI() // 최초 에어리어 UI 관련 이미지를 생성
{
	index_Area_UI_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameUIItemBox, 30, 30, 1, 1 };
	index_Area_UI_HP_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameHP_0pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_10pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_20pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_30pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_40pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_50pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_60pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_70pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_80pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_90pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_100pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameMaxHP, UI_HP_ORIGIN_X - 120, UI_HP_ORIGIN_Y, 1, 1 };

	index_Area_UI_O2_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameO2_0pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_10pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_20pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_30pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_40pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_50pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_60pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_70pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_80pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_90pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_100pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameMaxO2, UI_HP_ORIGIN_X - 120, UI_O2_ORIGIN_Y, 1, 1 };

	//index_Area_UI_blockInfo_Start = imageLayer.imageCount;
	index_Area_UI_Map_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameMapPC, 0, 0, 1, 1 }; // 2
	imageArray[imageLayer.imageCount++] = { bmpNameMapX, 0, 0, 1, 1 }; // 3
	imageArray[imageLayer.imageCount++] = { bmpNameMapX, 0, 0, 1, 1 }; // 4
	index_Area_UI_mapTile_Start = imageLayer.imageCount;
	for (int y = 100; y < 100 + (BLOCKSIZE * 5) + 10; y += (BLOCKSIZE + 2)) {
		for (int x = 1590; x < 1590 + (BLOCKSIZE * 5) + 10; x += (BLOCKSIZE + 2)) {
			imageArray[imageLayer.imageCount++] = { bmpNameMapTile, x, y, 1, 1 };
			mapInfo[(y - 100) / BLOCKSIZE][(x - 1590) / BLOCKSIZE] = 0;
		}
	}
	// 1 ~ 25, 25개
	// 5 ~ 29
	imageArray[imageLayer.imageCount++] = { bmpNameMapBox, 1508, 0, 1, 1 }; // 30
}

void drawUI() { // 에어리어 UI 활성화
	imageArray[index_Area_UI_Start].isHide = 0; // 아이템 창이 보이도록

	imageArray[index_Area_UI_HP_Start + 11].isHide = 0; // HP바가 보이도록
	pc.setHP(pc.getHP());
	imageArray[index_Area_UI_O2_Start + 11].isHide = 0; // O2바가 보이도록
	pc.setOxygen(pc.getOxygen());
	for (int i = index_Area_UI_Map_Start; i < index_Area_UI_Map_Start + 29; i++) // 맵이 보이도록
		imageArray[i].isHide = 0;

	// 에어리어 X가 미구현이기 때문에 임시로 에어리어 지도에서 X가 표시되지 않도록
	imageArray[index_Area_UI_Map_Start + 1].isHide = 1;
	imageArray[index_Area_UI_Map_Start + 2].isHide = 1;

	int count = 0;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (mapInfo[y][x] == 1) imageArray[index_Area_UI_mapTile_Start + count].fileName = bmpNameMapTileCleared;
			count++;
		}
	}
	imageArray[index_Area_UI_Map_Start].x = 1590 + (BLOCKSIZE + 2) * currentAreaColIndex;
	imageArray[index_Area_UI_Map_Start].y = 100 + (BLOCKSIZE + 2) * currentAreaRowIndex;
}

void initRewardImage() {
	rewardLayer.images = imagesReward;
	rewardLayer.imageCount = 0;

	index_RewardImages_Start = rewardLayer.imageCount;
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalRewardSelected, 400, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalReward, 400, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameDynamicRewardSelected, 1100, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameDynamicReward, 1100, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSelected, 0, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtk, 0, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSpdSelected, 660, 150, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSpd, 660, 150, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalSpdSelected, 1320, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalSpd, 1320, 500, 1, 1 };
}

void rewardUI() { // reward 레이어 출력
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &rewardLayer;

	imagesReward[0].isHide = 0;
	imagesReward[2].isHide = 0;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);


	int index1 = 0;
	int flags = 1;

	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case LEFT:
				imagesReward[0].isHide = 0;
				imagesReward[1].isHide = 1;
				imagesReward[2].isHide = 1;
				imagesReward[3].isHide = 0;
				index1 = 1;
				break;
			case RIGHT:
				imagesReward[0].isHide = 1;
				imagesReward[1].isHide = 0;
				imagesReward[2].isHide = 0;
				imagesReward[3].isHide = 1;
				index1 = 2;
				break;
			case SPACE:
				if (index1 == 0) break;
				flags = 0;
				break;
			}
			if (key) targetLayer->renderAll(targetLayer);
		}
	}

	targetLayer->fadeOut(targetLayer, NULL);

	imagesReward[0].isHide = 1;
	imagesReward[1].isHide = 1;
	imagesReward[2].isHide = 1;
	imagesReward[3].isHide = 1;
	imagesReward[4].isHide = 0;
	imagesReward[5].isHide = 1;
	imagesReward[6].isHide = 0;
	imagesReward[7].isHide = 1;
	imagesReward[8].isHide = 0;
	imagesReward[9].isHide = 1;


	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	int index2 = 0;
	flags = 1;


	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case NUM1:
				imagesReward[4].isHide = 0;
				imagesReward[5].isHide = 1;
				imagesReward[6].isHide = 1;
				imagesReward[7].isHide = 0;
				imagesReward[8].isHide = 1;
				imagesReward[9].isHide = 0;
				index2 = 1;
				break;
			case NUM2:
				imagesReward[4].isHide = 1;
				imagesReward[5].isHide = 0;
				imagesReward[6].isHide = 0;
				imagesReward[7].isHide = 1;
				imagesReward[8].isHide = 1;
				imagesReward[9].isHide = 0;
				index2 = 2;
				break;
			case NUM3:
				imagesReward[4].isHide = 1;
				imagesReward[5].isHide = 0;
				imagesReward[6].isHide = 1;
				imagesReward[7].isHide = 0;
				imagesReward[8].isHide = 0;
				imagesReward[9].isHide = 1;
				index2 = 3;
				break;
			case SPACE:
				if (index2 == 0) break;
				flags = 0;
				break;
			}
			if (key) targetLayer->renderAll(targetLayer);
		}
	}
	targetLayer->fadeOut(targetLayer, NULL);
	imagesReward[4].isHide = 1;
	imagesReward[5].isHide = 1;
	imagesReward[6].isHide = 1;
	imagesReward[7].isHide = 1;
	imagesReward[8].isHide = 1;
	imagesReward[9].isHide = 1;

	targetLayer = &stageLayer;
	isOnStage = true;
	targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
	stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
	setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	int num = 0;
	if (index1 == 1) num = rand() % 3;
	//if (index1 == 1) num = -5;
	//else if (index1 == 2) num = 6;
	else if (index1 == 2) num = rand() % 11 + (-5);
	if (index2 == 1) pc.setAtkLev(pc.getAtkLev() + num);
	else if (index2 == 2) pc.setAtkSpdLev(pc.getAtkSpdLev() + num);
	else if (index2 == 3) pc.setSpdLev(pc.getSpdLev() + num);

	pc.setStone(pc.getStone() + 100);

	//targetLayer->fadeIn(targetLayer, NULL);
	//printf("%d %d %d %d", num, pc.getAtkLev(), pc.getAtkSpdLev(), pc.getSpdLev());
}

void updateCharacterStatus() {

	wchar_t playerStone[20];
	wchar_t playerHp[20];
	wchar_t playerOz[20];
	wchar_t playerAttackPower[20];
	wchar_t playerAttackSpeed[20];
	wchar_t playerMoveSpeed[20];

	swprintf(playerStone, sizeof(playerStone) / sizeof(playerStone[0]), L"%d", pc.getStone());
	swprintf(playerHp, sizeof(playerHp) / sizeof(playerHp[0]), L"%d / %d", pc.getHP(), pc.getMaxHP());
	swprintf(playerOz, sizeof(playerOz) / sizeof(playerOz[0]), L"%d / %d", pc.getOxygen(), pc.getMaxOxygen());
	swprintf(playerAttackPower, sizeof(playerAttackPower) / sizeof(playerAttackPower[0]), L"Lv.%d", pc.getAtkLev());
	swprintf(playerAttackSpeed, sizeof(playerAttackSpeed) / sizeof(playerAttackSpeed[0]), L"Lv.%d", pc.getAtkSpdLev());
	swprintf(playerMoveSpeed, sizeof(playerMoveSpeed) / sizeof(playerMoveSpeed[0]), L"Lv.%d", pc.getSpdLev());


	printText(targetLayer->_consoleDC, 390, 332, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
	printText(targetLayer->_consoleDC, 250, 432, 40, 0, RGB(255, 255, 255), TA_LEFT, playerHp);
	printText(targetLayer->_consoleDC, 250, 498, 40, 0, RGB(255, 255, 255), TA_LEFT, playerOz);
	printText(targetLayer->_consoleDC, 250, 564, 40, 0, RGB(255, 255, 255), TA_LEFT, playerAttackPower);
	printText(targetLayer->_consoleDC, 250, 634, 40, 0, RGB(255, 255, 255), TA_LEFT, playerAttackSpeed);
	printText(targetLayer->_consoleDC, 250, 700, 40, 0, RGB(255, 255, 255), TA_LEFT, playerMoveSpeed);
}


void initItemImages() {
	std::vector<int> itemList = pc.getitemList();

	for (int i = 0; i < itemList.size(); i++) {
		if (itemList[i] == 1) {
			stageImageArray[stageLayer.imageCount++] = { bmpItem1Name, UI_ITEM_START_POS_X + UI_ITEM_SIZE * ((i + 1) % 2 == 0), UI_ITEM_START_POS_Y + UI_ITEM_SIZE * ((i) / 2), 1}; 
		}
		if (itemList[i] == 2) {
			stageImageArray[stageLayer.imageCount++] = { bmpItem2Name, UI_ITEM_START_POS_X + UI_ITEM_SIZE * ((i + 1) % 2 == 0), UI_ITEM_START_POS_Y + UI_ITEM_SIZE * ((i) / 2), 1 };
		}
		if (itemList[i] == 3) {
			stageImageArray[stageLayer.imageCount++] = { bmpItem3Name, UI_ITEM_START_POS_X + UI_ITEM_SIZE * ((i + 1) % 2 == 0), UI_ITEM_START_POS_Y + UI_ITEM_SIZE * ((i) / 2), 1 };
		}
	}


}

int getNPCSpaceHeight() { return (rand() % 10 + 5); }
int getNPCSpaceWidth() { return (rand() % 10 + 5); }
int getNPCSpacePosX() { return((rand() % (NPCSpaceWidth) + 1) * BLOCKSIZE + AREA_ORIGIN_X); }
int getNPCSpacePosY() { return ((rand() % (NPCSpaceHeight) + 1) * BLOCKSIZE + AREA_ORIGIN_Y); }
void setMinerals(int max) {
   while (max) {
      int x = (rand() % 25) * BLOCKSIZE + AREA_ORIGIN_X;
      int y = (rand() % 25) * BLOCKSIZE + AREA_ORIGIN_Y;
      if (blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] == 2) {
         int imageIndex = convertPosToInfoY(y) / BLOCKSIZE * 25 + convertPosToInfoX(x) / BLOCKSIZE + 1;
         imageArray[imageIndex].fileName = bmpMineralName;
         blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] = 3;
         max--;
      }
   }
}


bool printButtonStageStatus() {
	wchar_t playerStone[100] = L"Pessed Button List";
	wchar_t pressed_button_info[20] = L"";
	wchar_t pressed_button_status[20] = L"";
	bool isClear = true;
	bool isButtonReset = false;

	if (buttonPressedOrderList.size() == 1) {
		swprintf(pressed_button_info, sizeof(pressed_button_info) / sizeof(pressed_button_info[0]), L"%d", buttonPressedOrderList[0]);
	}
	else if (buttonPressedOrderList.size() == 2) {
		swprintf(pressed_button_info, sizeof(pressed_button_info) / sizeof(pressed_button_info[0]), L"%d -> %d", buttonPressedOrderList[0], buttonPressedOrderList[1]);
	}
	else if (buttonPressedOrderList.size() == 3) {
		swprintf(pressed_button_info, sizeof(pressed_button_info) / sizeof(pressed_button_info[0]), L"%d -> %d -> %d", buttonPressedOrderList[0], buttonPressedOrderList[1], buttonPressedOrderList[2]);

		for (int i = 0; i < 3; i++) {
			if (buttonPressedOrderList[i] != buttonPressedOrderAnswerList[i]) {
				isClear = false;
				break;
			}
		}
		if (isClear) {
			isButtonRoomClear = true;
			swprintf(pressed_button_status, sizeof(pressed_button_status) / sizeof(pressed_button_status[0]), L"Correct Answer!");
			printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
			printText(targetLayer->_consoleDC, 1600, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_info);
			printText(targetLayer->_consoleDC, 1600, 800, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_status);
		}
		else {
			imageArray[0].y = imageArray[0].y + 96;
			isButtonReset = true;
			buttonPressedOrderList.clear();
			swprintf(pressed_button_status, sizeof(pressed_button_status) / sizeof(pressed_button_status[0]), L"Not Correct Answer!");
			printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
			printText(targetLayer->_consoleDC, 1600, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_info);
			printText(targetLayer->_consoleDC, 1600, 800, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_status);
			Sleep(300);
		}
		
		swprintf(pressed_button_status, sizeof(pressed_button_status) / sizeof(pressed_button_status[0]), L"");
	}

	printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
	printText(targetLayer->_consoleDC, 1600, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_info);
	printText(targetLayer->_consoleDC, 1600, 800, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_status);

	return isButtonReset;
}