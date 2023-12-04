#include "common.hpp"
#include "Mole.hpp"
#include "EmceeTheShyGuy.hpp"
#include "Mineral.hpp"
#include "Ladder.hpp"
#include "Bat.hpp"
#include "Button.hpp"

int main() {
	initialize(); // æ¹²ê³—??ê³¸ì”¤ ??€???•ì”ª??ì­ (?„ì„????? ï§?ï§Â€?? ???????????

	// ??‰ì” ????€???•ì”ª??ì­ 
	stageLayer.initialize(&stageLayer);
	imageLayer.initialize(&imageLayer); // imageLayer???ë¨?¼±?±ÑŠë¼± ??‰ì” ??€?ªæ€?è¹‚ë?????
	rewardLayer.initialize(&rewardLayer);

	// ???¸™ ??ê¹?
	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1 }; // PC??imageLayer 0è¸°ë‰ë¿?ï§Â€??
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;

	initStageImage();				// stageLayer?ë¨?½Œ ?????ë’— ï§â‘¤ë±???€?ï§Â€ ï§¤ì’–????¹ê½¦
	fillBlockImages();				// imageLayer???‰ë¶¾ì¤?25x25) ï§¤ì’–????¹ê½¦

	Button* button1 = new Button(1);
	Button* button2 = new Button(2);
	Button* button3 = new Button(3);
	imageArray[button1->imageidx].fileName = bmpButton1Name;
	imageArray[button2->imageidx].fileName = bmpButton2Name;
	imageArray[button3->imageidx].fileName = bmpButton3Name;
	imageArray[button1->imageidx].isHide = 1;
	imageArray[button2->imageidx].isHide = 1;
	imageArray[button3->imageidx].isHide = 1;
	index_Area_Button_Start = button1->imageidx;

	initAreaUI();					// imageLayer??UI ??€?ï§Â€ ï§¤ì’–????¹ê½¦
	initRewardImage();				// rewardLayer?ë¨?½Œ ?????ë’— ï§â‘¤ë±???€?ï§Â€ ï§¤ì’–????¹ê½¦

	// ?ê¾©ì” ??“ë‚µ ?¿Â€??¤ë§‚ ??¥ë‹”??åª›ì’•ì»?ï§ê¾ªë»?ä»?
	pc.addItem(1);
	pc.addItem(2);
	pc.addItem(3);
	initItemImages();

	// ?ë¨?¼±?±ÑŠë¼± ??€??ë¨?½Œ ??“ì»™????ë¦??ê¾ªë¸³ è¹‚Â€??ë±¾
	clock_t start_time = clock();
	clock_t end_time;
	clock_t timee;
	clock_t minigameStartTime = clock();
	double duration;

	// NPC ??€???•ì”ª??ì­ (ï§¤ì’–???ê¾©íŠ‚???ë¶¾ãˆƒ?ê³¸ë¿‰??è¹‚ëŒ? ï§? ??…ë£„æ¿??¥ë‡ë¦??
	//Mole* mole = new Mole(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	std::vector<Bat*> generatedBatList;
	Bat* bat = new Bat(-48, -48);
	Ladder* ladder = new Ladder(-48, -48);
	EmceeTheShyGuy* Emcee = new EmceeTheShyGuy(-BLOCKSIZE*BOSS_SCALE, -BLOCKSIZE * BOSS_SCALE);
	Mole *mole = new Mole(-48, -48);

	targetLayer = &stageLayer;
	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	while (1) {
		if (isOnStage) { // PCåª›Â€ ??½ë€??? ï§ë“­ë¿?è­°ëŒ???ë’— å¯ƒìŒ??
			generatedBatList.clear();
			imageArray[ladder->imageidx].isHide = 0;
			imageArray[button1->imageidx].isHide = 1;
			imageArray[button2->imageidx].isHide = 1;
			imageArray[button3->imageidx].isHide = 1;

			updateCharacterStatus(); // PC ?ê³¹ê¹­ï§¡ìŒ????…ëœ²??„ë“ƒ
			while (_kbhit() != 0) {
				int key = _getch();
				// PC ?ê¾©íŠ‚ ?ëº£ë‚«????…ëœ²??„ë“ƒ??ë’— è¹‚Â€??ë±¾(??? ?ëº£ë‚«æ¿?
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;

				switch (key) {
				case S:
				{
					// ??•ëœ¡ è¹‚Â€??? ?????ë¿¬ ??€ë¼??ë¨?¼±?±ÑŠë¼±æ¿?ï§ê¾©???ï§Â€ ?ëº¥ë¸¯???„ë¶¾ë±?
					int num = rand() % 4;
					if (currentAreaColIndex == 0 && currentAreaRowIndex == 0) {
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = true;
						getNewBossArea();
						Emcee->NPCSetPosition(AREA_ORIGIN_X + BLOCKSIZE / 2 * 25 - BLOCKSIZE*BOSS_SCALE/2, AREA_ORIGIN_Y + BLOCKSIZE / 2 * 25 - BLOCKSIZE*BOSS_SCALE);
						imageArray[0].x = AREA_ORIGIN_X + BLOCKSIZE / 2 * 25;
						imageArray[0].y = AREA_ORIGIN_Y + BLOCKSIZE * 23;
						ladder->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
						bat->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
						for (int i = 1;i <= Emcee->getMaxHP()+1;i++) {
							imageArray[Emcee->imageidx + i].isHide = false;
						}//MaxHP
						pc.setATK(1000);
					}
					else if (num == 0) { // ?ëªƒì­š ?ë¨?¼±?±ÑŠë¼±æ¿?ï§ê¾©??
						isNormalArea = true;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = false;
						getNewArea();
						//Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						getMoleSpace();
						mole->NPCSetPosition(molePosX, molePosY);
						Mineral* mineral = new Mineral();
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
					}
					else if (num == 1) { // èª˜ëªƒ?²å¯ƒ??—« ?ë¨?¼±?±ÑŠë¼±æ¿?ï§ê¾©??
						isNormalArea = false;
						isMiniGameArea = true;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = false;
						getNewMiniGameArea();
						//Emcee->NPCSetPosition(-48, -48);
						ladder->NPCSetPosition(-48, -48);
						minigameStartTime = clock();
						Mineral* mineral = new Mineral(); // stageLevel ????
					}
					else if (num == 2) { // è¸°ê¾ª???ë¨?¼±?±ÑŠë¼±æ¿?ï§ê¾©??
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = true;
						isFlagArea = false;

						imageArray[button1->imageidx].isHide = 0;
						imageArray[button2->imageidx].isHide = 0;
						imageArray[button3->imageidx].isHide = 0;

						isButtonRoomClear = false;
						int randomNumber = rand() % 6; // 0 ?ë¨?½Œ 6 ???????–ë‹”
						buttonPressedOrderAnswerList = buttonOrderCaseList[randomNumber];
						getNewArea();

						button1->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 - BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button2->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button3->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 + BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);

						//Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						getMoleSpace();
						mole->NPCSetPosition(molePosX, molePosY);

						imageArray[ladder->imageidx].isHide = 1;
						Mineral* mineral = new Mineral(); // stageLevel ????
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
					}
					else if (num == 3) { // ???˜’æ´??ë¨?¼±?±ÑŠë¼±æ¿?ï§ê¾©??
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = true;
						isBossArea = false;

						pc.initFlagCnt();
						getNewArea();
						Mineral* mineral = new Mineral();
						//Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						getMoleSpace();
						mole->NPCSetPosition(molePosX, molePosY);
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
						setFlag(3);
					}

					// ?ë¨?¼±?±ÑŠë¼± ï§ë“­ë¿???ê¾©ì˜± PC ?ê¾©íŠ‚??è«›ì•·ì¾???–ë–†??ë£„æ¿???ë’— ?„ë¶¾ë±???€???ï§£ì„??
					currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
					currentAreaColIndex = convertPosToInfoXInStage(curPosX);
					mapInfo[currentAreaRowIndex][currentAreaColIndex] = 1;

					isOnStage = false;
					isOnArea = true;
					targetLayer->fadeOut(targetLayer, NULL);
					targetLayer = &imageLayer;
					targetLayer->fadeIn(targetLayer, NULL);
					targetLayer->renderAll(targetLayer);
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
					targetLayer->renderAll(targetLayer);
					if (key != S) updateCharacterStatus();
				}
			}
		}
		else if (isOnArea) { // PCåª›Â€ ?ë¨?¼±?±ÑŠë¼±????ˆë’— å¯ƒìŒ??
			targetLayer->renderAll(targetLayer);
			drawUI(); // ?ë¨?¼±?±ÑŠë¼± UI??æ´¹ëªƒ?????¥ë‹”
			printStoneStatus(pc.getStone());
			if (isNormalArea) { // PCåª›Â€ ?ëª? ?ë¨?¼±?±ÑŠë¼±????ˆë’— å¯ƒìŒ??
				// QuestionBlock è«›ëº¤ìª???¹ê½¦ ?¿Â€???„ë¶¾ë±?
				if (isGenerateMobByQuestionBlock) {
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}
				if (!generatedBatList.empty()) {
					for (Bat* mob : generatedBatList) {
						mob->move();
					}
				}
				// NPC????ï§ê³¸???ºÂ€????–ê½¦??
				//mole->move();
				bat->move();
				ladder->move();
				mole->move();
				//Emcee->move();
				// ??»ë‚«????…ì ° ??‘ë»¾
				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							isOnStage = true;
							isOnArea = false;
							isNormalArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
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
			}
			else if (isMiniGameArea) { // PCåª›Â€ èª˜ëªƒ?²å¯ƒ??—« ?ë¨?¼±?±ÑŠë¼±????ˆë’— å¯ƒìŒ??
				printMyOriInMiniGameArea(); // èª˜ëªƒ?²å¯ƒ??—« ?ë¨?¼±?±ÑŠë¼±?ë¨?½Œ information????¾ë±·???¿ë¬Ğª ??? ?°ì’•???ë’— ??¥ë‹”
				// ??»ë‚«????…ì ° ??‘ë»¾
				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							isOnStage = true;
							isOnArea = false;
							isMiniGameArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
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
							break;
						}
					}
					Sleep(5);
				}
				timee = clock();
				float remain_time = 31.0 - (double)(timee - minigameStartTime) / CLOCKS_PER_SEC;
				printTimeInMiniGameArea(remain_time);
				if (remain_time < 0.0) {
					Sleep(3000);
					rewardUI();
				}
			}
			else if (isButtonArea) { // PCåª›Â€ è¸°ê¾ª???ë¨?¼±?±ÑŠë¼±????ˆë’— å¯ƒìŒ??

				if (button1->getIsPressed()) {
					imageArray[button1->imageidx].fileName = bmpButton1PressedName;
				}
				if (button2->getIsPressed()) {
					imageArray[button2->imageidx].fileName = bmpButton2PressedName;
				}
				if (button3->getIsPressed()) {
					imageArray[button3->imageidx].fileName = bmpButton3PressedName;
				}
				if (printButtonStageStatus()) {
					button1->setIsPressed(false);
					imageArray[button1->imageidx].fileName = bmpButton1Name;
					button2->setIsPressed(false);
					imageArray[button2->imageidx].fileName = bmpButton2Name;
					button3->setIsPressed(false);
					imageArray[button3->imageidx].fileName = bmpButton3Name;
				}
				if (isGenerateMobByQuestionBlock) {
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}
				if (!generatedBatList.empty()) {
					for (Bat* mob : generatedBatList) {
						mob->move();
					}
				}
				if (isButtonRoomClear) {
					imageArray[ladder->imageidx].isHide = 0;
					ladder->move();
				}
				bat->move();
				mole->move();
				//Emcee->move();
				button1->move();
				button2->move();
				button3->move();

				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							isOnStage = true;
							isOnArea = false;
							isBossArea = false;
							isButtonArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
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
			}
			else if (isFlagArea) { // PCåª›Â€ ???˜’æ´??ë¨?¼±?±ÑŠë¼±????ˆë’— å¯ƒìŒ??
				printFlagStageStatus(pc.getFlagCnt());
				//mole->move();
				bat->move();
				ladder->move();
				mole->move();
				//Emcee->move();
				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							isOnStage = true;
							isOnArea = false;
							isFlagArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
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
			}
			else if (isBossArea) {
				if (Emcee->NPCDead() == false) {
					Emcee->move();
				}
				else {
					Emcee->AfterDead();
					ladder->NPCSetPosition(AREA_ORIGIN_X + BLOCKSIZE * 25 / 2, AREA_ORIGIN_Y + BLOCKSIZE * 25 / 2);
					ladder->move();
				}
				//vector<PCBullet>::iterator itr;
				for (auto itr = pc.getBulletList().begin(); itr != pc.getBulletList().end(); ) {
					if (Emcee->NPCDead() == false && itr->checkBulletHit(Emcee->x, Emcee->y)) {
						Emcee->NPCHit(pc.getATK());
						itr = pc.getBulletList().erase(itr);
					}
					else if (!(itr->move())) itr = pc.getBulletList().erase(itr);
					else itr++;
				}
				printWarning(Emcee->hp);
				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							isOnStage = true;
							isOnArea = false;
							isFlagArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
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
							if (Emcee->NPCDead() == false) pc.attack(clock());
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
			}
			// ï§â‘¤ë±??ë¨?¼±?±ÑŠë¼±???¨ë“¯???°ì¤ˆ ?ê³¸ìŠœ??ë’— ?„ë¶¾ë±?
			// 3?¥ëˆì­???ê³—ëƒ¼ å¯ƒëš¯? ï§???1??åª›ë¨¯???—ê¶???„ë¶¾ë±?
			end_time = clock();
			duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
			if (duration > 3.0) {
				pc.setOxygen(pc.getOxygen() - 1);
				start_time = end_time;
			}
		}
	}
	return 0;
}