#include "common.hpp"

PC& pc = PC::getPC();

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer* targetLayer = NULL;
ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
ImageLayer stageLayer = DEFAULT_IMAGE_LAYER;
Image imageArray[1000];
Image stageImages[30];
int currentAreaRowIndex;
int currentAreaColIndex;
int blockInfo[1200][1200];
int stageInfo[5][5];
bool isOnStage = true;
char bmpStoneBlockName[] = "stoneBlock.bmp";
char bmpBrokenStoneBlockName[] = "brokenStoneBlock.bmp";

char bmpClearedAreaName[] = "clearedArea.bmp";
char bmpNomalAreaName[] = "nomalArea.bmp";
char bmpHiddenAreaName[] = "hiddenArea.bmp";
char bmpMovableAreaName[] = "movableArea.bmp";
char bmpCharacterStatueName[] = "characterStatus.bmp";
char bmpNameNull[] = "";

char bmpZombieName[] = "NPC.bmp";
char bmpNullName[] = "";
char bmpNameBoss[] = "Boss.bmp";
char bmpNameShop[] = "Shop.bmp";
//
ImageLayer rewardLayer = DEFAULT_IMAGE_LAYER;
Image imagesReward[1000];
int mapInfo[6][6];
int index_UI_HP_Start;
int index_UI_O2_Start;
int index_UI_blockInfo_Start;
int index_UI_mapTile_Start;

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

//


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
	srand((unsigned)time(NULL)); // 추가한 항목
}

// NPC 공간 만들기


void initBlockImages() {

   for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
      for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
         if (y >= AREA_ORIGIN_Y + BLOCKSIZE * 5 && y<= AREA_ORIGIN_Y + BLOCKSIZE * 20 && x >= AREA_ORIGIN_X + BLOCKSIZE * 4 && x <= AREA_ORIGIN_X + BLOCKSIZE * 20) {
            imageArray[imageLayer.imageCount++] = { bmpNullName, x,y,1};
            blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] = 0;
         }
         else {
            imageArray[imageLayer.imageCount++] = { bmpStoneBlockName, x,y,1 };
            blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] = 2;
         }
      }
   }
}

/*void initBlockImages() {
	int rowCount -9
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			//if (y == AREA_ORIGIN_Y && x == AREA_ORIGIN_X + 576) continue;
			imageArray[imageLayer.imageCount++] = { bmpStoneBlockName, x,y,1 };
		}
	}
	for (int i = 0;i < 1200;i++) {
		for (int j = 0;j < 1200;j++) {
			blockInfo[i][j] = 2;
		}
	}
	for (int i = 0;i < BLOCKSIZE;i++) {
		for (int j = 576;j < 576 + BLOCKSIZE;j++) {
			blockInfo[i][j] = 0;
		}
	}
}
*/



void initStageImages() {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (y == 2 && x == 2) {
				stageInfo[y][x] = 0;
			}
			else {
				stageInfo[y][x] = 1;
			}
		}
	}
	int count = 0;
	for (int y = STAGE_ORIGIN_Y; y < STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 5; y += AREA_BLOCK_SIZE) {
		for (int x = STAGE_ORIGIN_X; x < STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 5; x += AREA_BLOCK_SIZE) {
			/*
			if (count == 5 || count == 16) {
				stageImages[stageLayer.imageCount++] = { bmpHiddenAreaName, x,y,1 };
				count++;
				continue;
			}
			*/
			stageImages[stageLayer.imageCount++] = { bmpNomalAreaName, x,y,1 };
			count++;
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



void drawUI() { // 새로운 함수
	imageArray[imageLayer.imageCount++] = { bmpNameUIItemBox, 30, 30, 1 }; // 1
	drawMapUI(); // 2 ~ 31
	index_UI_HP_Start = imageLayer.imageCount;
	//printf("%d\n", imageLayer.imageCount);
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
	imageArray[imageLayer.imageCount++] = { bmpNameHP_100pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 0 };
	imageArray[imageLayer.imageCount++] = { bmpNameMaxHP, UI_HP_ORIGIN_X - 120, UI_HP_ORIGIN_Y, 1 };
	index_UI_O2_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameO2_0pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_10pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_20pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_30pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_40pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_50pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_60pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_70pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_80pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_90pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 0 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_100pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 0 };
	imageArray[imageLayer.imageCount++] = { bmpNameMaxO2, UI_HP_ORIGIN_X - 120, UI_O2_ORIGIN_Y, 1 };
	index_UI_blockInfo_Start = imageLayer.imageCount;
}

void drawMapUI() { // 새로운 함수
	imageArray[imageLayer.imageCount++] = { bmpNameMapPC, 0, 0, 1, 1 }; // 2
	imageArray[imageLayer.imageCount++] = { bmpNameMapX, 0, 0, 1, 1 }; // 3
	imageArray[imageLayer.imageCount++] = { bmpNameMapX, 0, 0, 1, 1 }; // 4
	index_UI_mapTile_Start = imageLayer.imageCount;
	for (int y = 100; y < 100 + (BLOCKSIZE * 5) + 10; y += (BLOCKSIZE + 2)) {
		for (int x = 1590; x < 1590 + (BLOCKSIZE * 5) + 10; x += (BLOCKSIZE + 2)) {
			imageArray[imageLayer.imageCount++] = { bmpNameMapTile, x, y, 1 };
			mapInfo[(y - 100) / BLOCKSIZE][(x - 1590) / BLOCKSIZE] = 2;
		}
	}
	// 1 ~ 25, 25개
	// 5 ~ 29
	imageArray[imageLayer.imageCount++] = { bmpNameMapBox, 1508, 0, 1 }; // 30

	/*imageArray[index_UI_mapTile_Start + 12].fileName = bmpNameMapTileCleared;
	imageArray[index_UI_mapTile_Start + 16].fileName = bmpNameMapTileCleared;
	imageArray[index_UI_mapTile_Start + 17].fileName = bmpNameMapTileCleared;

	imageArray[2].x = imageArray[index_UI_mapTile_Start + 16].x;
	imageArray[2].y = imageArray[index_UI_mapTile_Start + 16].y;
	imageArray[3].x = imageArray[index_UI_mapTile_Start + 4].x;
	imageArray[3].y = imageArray[index_UI_mapTile_Start + 4].y;
	imageArray[4].x = imageArray[index_UI_mapTile_Start + 15].x;
	imageArray[4].y = imageArray[index_UI_mapTile_Start + 15].y;*/
}

void rewardUI() { // 새로운 함수
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &rewardLayer;
	rewardLayer.imageCount = 0;
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalRewardSelected, 400, 300, 1, 0 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalReward, 400, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameDynamicRewardSelected, 1100, 300, 1, 0 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameDynamicReward, 1100, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSelected, 0, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtk, 0, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSpdSelected, 660, 150, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSpd, 660, 150, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalSpdSelected, 1320, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalSpd, 1320, 500, 1, 1 };

	rewardLayer.images = imagesReward;
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
	targetLayer->renderAll(targetLayer);

	int num = 0;
	if (index1 == 1) num = rand() % 3;
	else if (index1 == 2) num = rand() % 11 + (-5);

	if (index2 == 1) pc.setAtkLev(pc.getAtkLev() + num);
	else if (index2 == 2) pc.setAtkSpdLev(pc.getAtkSpdLev() + num);
	else if (index2 == 3) pc.setSpdLev(pc.getSpdLev() + num);

	// printf("%d %d %d %d", num, pc.getAtkLev(), pc.getAtkSpdLev(), pc.getSpdLev());
}

/*

void dig(int x, int y) {
	pc.vibe();
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0 || infoY >= 25 || infoX < 0 || infoX >= 25) return;
	blockInfo[infoY][infoX]--;
	if (!blockInfo[infoY][infoX]) {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = 0;
	}
	else {
		imageLayer.images[infoY * 25 + infoX + 1].fileName = bmpBrokenStoneBlockName;
	}
}
*/

void initArea() {
	for (int i = 0;i < 25;i++) {
		for (int j = 0;j < 25;j++) {
			if (i > 4 && i < 20 && j> 5 && j < 20) imageLayer.images[i * 25 + j + 1].fileName = bmpNameNull;
		}
	}
	for (int y = 240;y < 960;y++) {
		for (int x = 192;x < 960;x++) {
			blockInfo[y][x] = 0;
		}
	}
}