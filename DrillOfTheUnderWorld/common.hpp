#pragma once

#define _CRT_SECURE_NO_WARNINGS
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "ImageLayer.h"
#include "SoundPlayer.h"
#include <math.h>
}

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define S 115
#define M 77
#define SPEED 16
#define ESC 27
#define BLOCKSIZE 48

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
Image imageArray[1000];
int blockInfo[26][26];

//LPCWSTR ConvertToLPCWSTR(const char* ansiStr);
void getHandle();
void removeCursor();
void resizeConsole(int w, int h);
void initialize();
void dig(int x, int y);
bool collisionCheck(int x, int y);
int convertPosToInfoX(int x);
int convertPosToInfoY(int y);
void initBlockInfo();

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

void initBlockInfo() {
	for (int i = 0;i <= 25;i++) {
		for (int j = 0;j <= 25;j++) {
			blockInfo[i][j] = 1;
		}
	}
}

int convertPosToInfoX(int x) {
	return x / BLOCKSIZE;
}
int convertPosToInfoY(int y) {
	return (y - 96) / BLOCKSIZE;
}

bool collisionCheck(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0) return 0;
	return blockInfo[infoY][infoX];
}

void dig(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	if (infoY < 0 || infoY >= 25 || infoX < 0 || infoX >= 25) return;
	char bmpNameReplaceImage[] = "empty.bmp";
	//Image newImage = { bmpNameReplaceImage,0,0,1 };
	imageLayer.images[imageLayer.imageCount] = imageLayer.images[imageLayer.imageCount - 1]; //배경을 뒤로 밀고
	imageLayer.images[imageLayer.imageCount-1] = Image({ bmpNameReplaceImage,x,y,1 }); //그 자리에 empty 삽입
	imageLayer.imageCount++;
	//imageLayer->images[infoY * 25 + infoX + 2] = newImage;
	blockInfo[infoY][infoX] = 0;
}