#include "common.hpp"

 PC& pc = PC::getPC();

 HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
 HWND WINDOW_HANDLE;
 ImageLayer* targetLayer = NULL;
 ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
 ImageLayer testLayer = DEFAULT_IMAGE_LAYER;
 Image imageArray[1000];
 int blockInfo[26][26];
 bool isOnStage = true;
 char bmpStoneBlockName[] = "stoneBlock.bmp";
 char bmpBrokenStoneBlockName[] = "brokenStoneBlock.bmp";

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
}

void initBlockImages() {
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			imageArray[imageLayer.imageCount++] = { bmpStoneBlockName, x,y,1 };
			blockInfo[convertPosToInfoX(y)][convertPosToInfoY(x)] = 2;
		}
	}
}

int convertPosToInfoX(int x) {
	return (x - AREA_ORIGIN_X) / BLOCKSIZE;
}
int convertPosToInfoY(int y) {
	return (y - AREA_ORIGIN_Y) / BLOCKSIZE;
}

bool collisionCheck(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0) return 0;
	return blockInfo[infoY][infoX];
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
