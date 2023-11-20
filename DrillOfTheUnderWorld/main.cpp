#include "common.hpp"
#include "Zombie.hpp"
#include "Mineral.hpp"
#include "Shop.hpp"
#include "Boss.hpp"

int main() {
	initialize();

	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageLayer.initialize(&imageLayer);
	stageLayer.initialize(&stageLayer);
	rewardLayer.initialize(&rewardLayer);

	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1 };
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;

	initStageImage();
	initBlockImages();
	initAreaUI();
	initRewardImage();

	clock_t start_time = clock();
	clock_t end_time;
	double duration;

	Zombie* zombie = new Zombie(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	Boss* boss = new Boss(AREA_ORIGIN_X + BLOCKSIZE * 7, AREA_ORIGIN_Y + BLOCKSIZE * 16);
	Shop* shop = new Shop(AREA_ORIGIN_X + BLOCKSIZE * 6, AREA_ORIGIN_Y + BLOCKSIZE * 14);

	char bmpNameTmp[] = "emptyTile.bmp";

	/*
	Stage stage;
	std::vector<std::vector<Area>> areaList = stage.getAreaList();

	for (int i = 0; i < 5; i++) { 
		for (int j = 0; j < 5; j++ ) {
			printf("%d\n", areaList[i][j].getPosX());
		}
	}
	*/
	//Mineral* mineral = new Mineral();

	char bmpStageLevel[] = "Stage1.bmp"; 

	stageLayer.imageCount = STAGE_EXTRA_IMAGE_COUNT;
	//initStageImages();
	stageLayer.images = stageImageArray;
	stageLayer.images[0] = { bmpNamePC, STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 2 + 48
										, STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 2 + 48, 1 };
	stageLayer.images[1] = { bmpCharacterStatusName, 60 , STAGE_ORIGIN_Y, 1 };
	stageLayer.images[2] = { bmpStageLevel, STAGE_ORIGIN_X + AREA_BLOCK_SIZE + 48, 48, 0.2 };

	stageLayer.images[(2) * 5 + 2 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;

	int immutableImagesInStage[1] = { 1 };

	stageLayer.imageCount = 30;

	pc.addItem(1);
	pc.addItem(2);
	pc.addItem(3);

	initItemImages();

	targetLayer = &stageLayer;
	targetLayer->renderAll(targetLayer);
	updateCharacterStatus();

	while (1) {
		//num += 0.00007;
		//printf("%f\n", num);
		if (isOnStage) {
			updateCharacterStatus();
			while (_kbhit() != 0) {
				int key = _getch();
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;
				switch (key) {
				case S:
					if (isOnStage) {
						targetLayer->fadeOut(targetLayer, NULL);
						targetLayer = &imageLayer;
						isOnStage = false;
						currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
						currentAreaColIndex = convertPosToInfoXInStage(curPosX);
						mapInfo[currentAreaRowIndex][currentAreaColIndex] = 1;
						/*
						imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, 48, 1 };
						imageLayer.images = imageArray;
						imageLayer.imageCount = 1;

						initBlockImages();
						*/

						targetLayer->fadeIn(targetLayer, NULL);
					}
					else {
						targetLayer->fadeOut(targetLayer, NULL);
						targetLayer = &stageLayer;
						isOnStage = true;
						targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
						stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
						targetLayer->fadeIn(targetLayer, NULL);
					}
					break;

				case LEFT:
					pc.setDirLeft();
					if (!collisionCheckInStage(curPosX - AREA_BLOCK_SIZE, curPosY)) pc.moveInStage();
					break;
				case RIGHT:
					pc.setDirRight();
					if (!collisionCheckInStage(curPosX + AREA_BLOCK_SIZE, curPosY)) pc.moveInStage();
					break;
				case UP:
					pc.setDirUp();
					if (!collisionCheckInStage(curPosX, curPosY - AREA_BLOCK_SIZE)) pc.moveInStage();
					break;
				case DOWN:
					pc.setDirDown();
					if (!collisionCheckInStage(curPosX, curPosY + AREA_BLOCK_SIZE)) pc.moveInStage();
					break;
				}
				if (key) {
					//targetLayer->renderCertain(targetLayer, immutableImagesInStage, 1);
					targetLayer->renderAll(targetLayer);
				}
			}
		}
		else {
			targetLayer->renderAll(targetLayer);
			zombie->move(&imageLayer);
			boss->move(&imageLayer);
			shop->move(&imageLayer);
			drawUI();
			for (int i = 0; i < 10; i++) {
				if (_kbhit() != 0) {
					int key = _getch();
					int curPosX = imageLayer.images[0].x;
					int curPosY = imageLayer.images[0].y;
					COORD afterMovedPos;

					switch (key) {
					case S:
						targetLayer->fadeOut(targetLayer, NULL);
						if (isOnStage) {
							targetLayer = &imageLayer;
							isOnStage = false;
							currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
							currentAreaColIndex = convertPosToInfoXInStage(curPosX);

							/*
							imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, 48, 1 };
							imageLayer.images = imageArray;
							imageLayer.imageCount = 1;

							initBlockImages();
							*/

							targetLayer->fadeIn(targetLayer, NULL);
						}
						else {
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							isOnStage = true;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
						}
						break;


					case LEFT:
						pc.setDirLeft();
						afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
						if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
						break;
					case RIGHT:
						pc.setDirRight();
						afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
						if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
						break;
					case UP:
						pc.setDirUp();
						afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
						if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
						break;
					case DOWN:
						pc.setDirDown();
						afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
						if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
						break;
					case ESC:
						rewardUI();
						break;
					case SPACE:
						COORD targetPos = pc.getTargetPos(curPosX, curPosY);
						pc.dig(targetPos.X, targetPos.Y);
						//pc.setOxygen(pc.getOxygen() - 1);
						break;

					case O:
						pc.setHP(pc.getHP() - 10);
						break;
					case P:
						pc.setHP(pc.getHP() + 10);
						break;

					}
				}

				Sleep(5);
			}
			end_time = clock();
			duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
			//printf("%d", pc.getOxygen());
			if (duration > 3.0) {
				pc.setOxygen(pc.getOxygen() - 1);
				start_time = end_time;
			}
		}
	}
	return 0;
}