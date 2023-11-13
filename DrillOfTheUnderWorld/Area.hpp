#pragma once
#include "common.hpp"

extern "C" {
#include <Windows.h>
}

enum class AreaType
{
	Nomal,
	Boss,
	Treasure,
	MiniGame
};

class Area {
private:
	int posX;
	int posY;
	bool isClear;
	AreaType areaType;
	int rewardStone;
	char* showedThumnailImageName;
	char* originThumnailmageName;
public:
	Area();
	int getPosX();
	void setPosX(int posX);
	int getPosY();
	void setPosY(int posY);
	void setIsAreaClear(bool isClear);
	void setThumnailImage();
	void provideReward();
	void enterArea();
	void exitArea();;
};