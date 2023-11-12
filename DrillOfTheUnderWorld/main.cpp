#include "common.hpp"
#include "zombie.hpp"
#include "Boss.hpp"
#include "Shop.hpp"
#include "Mineral.hpp"

int main() {
	initialize();

	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageLayer.initialize(&imageLayer);
	testLayer.initialize(&testLayer);

	char bmpNamePC[] = "PlayerCharacter.bmp";
	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, 48, 1 };
	char bmpNameNPC[] = "NPC.bmp";
	imageArray[1] = { bmpNameNPC, AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10, 1 };
	char bmpNameBoss[] = "Boss.bmp";
	imageArray[2] = { bmpNameBoss,AREA_ORIGIN_X + BLOCKSIZE * 7, AREA_ORIGIN_Y + BLOCKSIZE * 16, 1 };
	char bmpNameShop[] = "Shop.bmp";
	imageArray[3] = { bmpNameShop, AREA_ORIGIN_X + BLOCKSIZE * 6, AREA_ORIGIN_Y + BLOCKSIZE * 14, 1 };

	imageLayer.images = imageArray;
	imageLayer.imageCount = 4;
	initBlockImages();

	// 맨 초기 화면 설정
	char bmpNameTmp[] = "emptyTile.bmp";
	Image testImages[1] = { bmpNameTmp, 100, 100, 1 };
	testLayer.images = testImages;
	testLayer.imageCount = 1;
	targetLayer = &testLayer;

	Zombie* zombie = new Zombie(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	Boss* boss = new Boss(AREA_ORIGIN_X + BLOCKSIZE * 7, AREA_ORIGIN_Y + BLOCKSIZE * 16);
	Shop* shop = new Shop(AREA_ORIGIN_X + BLOCKSIZE * 6, AREA_ORIGIN_Y + BLOCKSIZE * 14);
	Mineral* mineral = new Mineral();

	while (1) {
		targetLayer->renderAll(targetLayer);
		zombie->move(&imageLayer);
		boss->move(&imageLayer);
		shop->move(&imageLayer);

		for (int i = 0; i < 10; i++) {
			if (_kbhit() != 0) {
				int key = _getch();
				// PC 좌표 받기
				int curPosX = imageLayer.images[0].x;
				int curPosY = imageLayer.images[0].y;

				switch (key) {
				// S면 스테이지 이동
				case S:
					targetLayer->fadeOut(targetLayer, NULL);
					if (isOnStage) {
						targetLayer = &imageLayer;
						isOnStage = false;
					}
					else {
						targetLayer = &testLayer;
						isOnStage = true;
					}
					targetLayer->fadeIn(targetLayer, NULL);
					break;
				case LEFT:
					pc.setDirLeft();
					if (!collisionCheck(curPosX - BLOCKSIZE, curPosY)) pc.move();
					break;
				case RIGHT:
					pc.setDirRight();
					if (!collisionCheck(curPosX + BLOCKSIZE, curPosY)) pc.move();
					break;
				case UP:
					pc.setDirUp();
					if (!collisionCheck(curPosX, curPosY - BLOCKSIZE)) pc.move();
					break;
				case DOWN:
					pc.setDirDown();
					if (!collisionCheck(curPosX, curPosY + BLOCKSIZE)) pc.move();
					break;
				case ESC:
					return 0;
					break;
				case SPACE:
					COORD posAfterMoved = pc.getPosAfterMove(curPosX, curPosY);
					pc.dig(posAfterMoved.X, posAfterMoved.Y);
				}
			}
			Sleep(5);
		}
	}

	return 0;
}