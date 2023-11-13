#pragma once
#include "Area.hpp"

Area::Area() {
	this->posX = 0;
	this->posY = 0;
	this->isClear = false;
	this->areaType = AreaType::Nomal;
	this->rewardStone = 100;
	this->showedThumnailImageName = bmpNomalAreaName;
	this->originThumnailmageName = bmpNomalAreaName;
} 

int Area::getPosX() {
	return this->posX;
}
void Area::setPosX(int posX) {
	this->posX = posX;
}

int Area::getPosY() {
	return this->posY;
}
void Area::setPosY(int posY) {
	this->posY = posX;
}

void Area::setIsAreaClear(bool isClear) {
	this->isClear = isClear;
}

void Area::setThumnailImage() {
	if (this->isClear) {
		this->showedThumnailImageName = bmpClearedAreaName;
		return;
	}
	this->showedThumnailImageName = originThumnailmageName;
}

void Area::provideReward() {
	pc.setStone(pc.getStone() + this->rewardStone);
	setIsAreaClear(true);
}

void Area::enterArea() {
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &imageLayer;
	isOnStage = false;
	targetLayer->fadeIn(targetLayer, NULL);
}

void Area::exitArea() {
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &stageLayer;
	isOnStage = true;
	targetLayer->fadeIn(targetLayer, NULL);
}
