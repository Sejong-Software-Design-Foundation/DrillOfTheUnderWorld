#include "common.hpp"
#include "Stage.hpp"


Stage::Stage() : stageLevel(1) {
	// Assuming you want a 5x5 grid
	//areaList.resize(5, std::vector<Area>(5));
	//initAreasPos();
}
/*
void Stage::initAreasPos() {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			areaList[y].push_back(Area());
		}
	}
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			areaList[y][x].setPosX(STAGE_ORIGIN_X + AREA_BLOCK_SIZE * x);
			areaList[y][x].setPosY(STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * y);
		}
	}
}
*/
int Stage::getLevel() {
	return this->stageLevel;
}
void Stage::setLevel(int level) {
	this->stageLevel = level;
}
/*
Area& Stage::getArea(int row, int col) {
	return areaList[row][col];
}*/