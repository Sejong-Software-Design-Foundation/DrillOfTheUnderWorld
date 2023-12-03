#include "common.hpp"
#include "Mole.hpp"
#include "EmceeTheShyGuy.hpp"
#include "Mineral.hpp"
#include "Ladder.hpp"
#include "Bat.hpp"
#include "Button.hpp"

int main() {
	initialize(); // ê¸°ì´ˆ?ì¸ ?´ë‹ˆ?œë¼?´ì§•(ì½˜ì†” ?¬ì´ì¦?ì§€?? ?¬ì¸???? œ ??

	// ?ˆì´???´ë‹ˆ?œë¼?´ì§•
	stageLayer.initialize(&stageLayer);
	imageLayer.initialize(&imageLayer); // imageLayer???ì–´ë¦¬ì–´ ?ˆì´?´ë¼ê³?ë³´ë©´ ??
	rewardLayer.initialize(&rewardLayer);
	safetyLayer.initialize(&safetyLayer);
	rShopLayer.initialize(&rShopLayer);
	lShopLayer.initialize(&lShopLayer);

	// ?Œì•… ?¬ìƒ
	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1 }; // PC??imageLayer 0ë²ˆì— ì§€??
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;

	initStageImage();				// stageLayer?ì„œ ?¬ìš©?˜ëŠ” ëª¨ë“  ?´ë?ì§€ ìµœì´ˆ ?ì„±
	fillBlockImages();				// imageLayer??ë¸”ë¡(25x25) ìµœì´ˆ ?ì„±

	initSafetyImage();
	initRShopImage();
	initLShopImage();

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

	initAreaUI();					// imageLayer??UI ?´ë?ì§€ ìµœì´ˆ ?ì„±
	initRewardImage();				// rewardLayer?ì„œ ?¬ìš©?˜ëŠ” ëª¨ë“  ?´ë?ì§€ ìµœì´ˆ ?ì„±

	// ?„ì´?œê³¼ ê´€?¨ëœ ?¨ìˆ˜??ê°œë°œ ì§„í–‰ ì¤?
	pc.addItem(1);
	pc.addItem(2);
	pc.addItem(3);
	initItemImages();
	
	// ?ì–´ë¦¬ì–´ ?´ë??ì„œ ?œê°„???¬ê¸° ?„í•œ ë³€?˜ë“¤
	clock_t start_time = clock();
	clock_t end_time;
	clock_t timee;
	clock_t minigameStartTime = clock();
	double duration;

	// NPC ?´ë‹ˆ?œë¼?´ì§•(ìµœì´ˆ ?„ì¹˜???”ë©´?ì—??ë³´ì´ì§€ ?Šë„ë¡?ì´ˆê¸°??
	//Mole* mole = new Mole(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	std::vector<Bat*> generatedBatList;
	Bat* bat = new Bat(-48, -48);
	Ladder* ladder = new Ladder(-48, -48);
	EmceeTheShyGuy* Emcee = new EmceeTheShyGuy(-48, -48);

	targetLayer = &stageLayer;
	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	while (1) {
		if (isOnStage) { // PCê°€ ?¤í…Œ?´ì? ë§µì— ì¡´ì¬?˜ëŠ” ê²½ìš°
			generatedBatList.clear();
			imageArray[ladder->imageidx].isHide = 0;
			imageArray[button1->imageidx].isHide = 1;
			imageArray[button2->imageidx].isHide = 1;
			imageArray[button3->imageidx].isHide = 1;

			updateCharacterStatus(); // PC ?íƒœì°½ì„ ?…ë°?´íŠ¸
			while (_kbhit() != 0) {
				int key = _getch();
				// PC ?„ì¹˜ ?•ë³´ë¥??…ë°?´íŠ¸?˜ëŠ” ë³€?˜ë“¤(?½ì? ?•ë³´ë¡?
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;

				switch (key) {
				case S:
				{
					// ?œë¤ ë³€?˜ë? ?¬ìš©?˜ì—¬ ?´ë–¤ ?ì–´ë¦¬ì–´ë¡?ì§„ì…??ì§€ ?•í•˜??ì½”ë“œ
					int num = rand() % 4;
					if (currentAreaColIndex == 2 && currentAreaRowIndex == 1) {
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = true;
						getNewBossArea();
						Emcee->NPCSetPosition(AREA_ORIGIN_X + BLOCKSIZE / 2 * 25, AREA_ORIGIN_Y + BLOCKSIZE / 2 * 25);
						imageArray[0].x = AREA_ORIGIN_X + BLOCKSIZE / 2 * 25;
						imageArray[0].y = AREA_ORIGIN_Y + BLOCKSIZE * 23;
						ladder->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
						bat->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
					}
					else if (num == 0) { // ?¸ë§ ?ì–´ë¦¬ì–´ë¡?ì§„ì…
						isNormalArea = true;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = false;
						getNewArea();
						//Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						Mineral* mineral = new Mineral();
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
					}
					else if (num == 1) { // ë¯¸ë‹ˆê²Œì„ ?ì–´ë¦¬ì–´ë¡?ì§„ì…
						isNormalArea = false;
						isMiniGameArea = true;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = false;
						getNewMiniGameArea();
						//Emcee->NPCSetPosition(-48, -48);
						ladder->NPCSetPosition(-48, -48);
						minigameStartTime = clock();
						Mineral* mineral = new Mineral(); // stageLevel ?€??
					}
					else if (num == 2) { // ë²„íŠ¼ ?ì–´ë¦¬ì–´ë¡?ì§„ì…
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = true;
						isFlagArea = false;

						imageArray[button1->imageidx].isHide = 0;
						imageArray[button2->imageidx].isHide = 0;
						imageArray[button3->imageidx].isHide = 0;

						isButtonRoomClear = false;
						int randomNumber = rand() % 6; // 0 ?ì„œ 6 ?¬ì´???œìˆ˜
						buttonPressedOrderAnswerList = buttonOrderCaseList[randomNumber];
						getNewArea();

						button1->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 - BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button2->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button3->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 + BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);

						//Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);

						imageArray[ladder->imageidx].isHide = 1;
						Mineral* mineral = new Mineral(); // stageLevel ?€??
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
					}
					else if (num == 3) { // ?Œë˜ê·??ì–´ë¦¬ì–´ë¡?ì§„ì…
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
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
						setFlag(3);
					}

					// ?ì–´ë¦¬ì–´ ë§µì—???„ì¬ PC ?„ì¹˜ë¥?ë°ê²Œ ?œì‹œ?˜ë„ë¡??˜ëŠ” ì½”ë“œ(?´ë¦¬??ì²˜ë¦¬)
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
				case ESC:
					pc.setStone(pc.getStone() + 5000);
					visitSafety();
					break;
				}
				if (key) {
					targetLayer->renderAll(targetLayer);
					if (key != S) updateCharacterStatus();
				}
			}
		}
		else if (isOnArea) { // PCê°€ ?ì–´ë¦¬ì–´???ˆëŠ” ê²½ìš°
			targetLayer->renderAll(targetLayer);
			drawUI(); // ?ì–´ë¦¬ì–´ UIë¥?ê·¸ë¦¬???¨ìˆ˜
			printStoneStatus(pc.getStone());
			if (isNormalArea) { // PCê°€ ?¸ë? ?ì–´ë¦¬ì–´???ˆëŠ” ê²½ìš°
				// QuestionBlock ë°•ì¥ ?ì„± ê´€??ì½”ë“œ
				if (isGenerateMobByQuestionBlock) {
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}
				if (!generatedBatList.empty()) {
					for (Bat* mob : generatedBatList) {
						mob->move();
					}
				}
				// NPC???€ì§ì„ ë¶€???œì„±??
				//mole->move();
				bat->move();
				ladder->move();
				//Emcee->move();
				// ?¤ë³´???…ë ¥ ?˜í–‰
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
			else if (isMiniGameArea) { // PCê°€ ë¯¸ë‹ˆê²Œì„ ?ì–´ë¦¬ì–´???ˆëŠ” ê²½ìš°
				printMyOriInMiniGameArea(); // ë¯¸ë‹ˆê²Œì„ ?ì–´ë¦¬ì–´?ì„œ informationê³??ë“??ê´‘ë¬¼ ?˜ë? ì¶œë ¥?˜ëŠ” ?¨ìˆ˜
				// ?¤ë³´???…ë ¥ ?˜í–‰
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
			else if (isButtonArea) { // PCê°€ ë²„íŠ¼ ?ì–´ë¦¬ì–´???ˆëŠ” ê²½ìš°

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
			else if (isFlagArea) { // PCê°€ ?Œë˜ê·??ì–´ë¦¬ì–´???ˆëŠ” ê²½ìš°
				printFlagStageStatus(pc.getFlagCnt());
				//mole->move();
				bat->move();
				ladder->move();
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
				Emcee->move();
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
			// ëª¨ë“  ?ì–´ë¦¬ì–´??ê³µí†µ?¼ë¡œ ?ìš©?˜ëŠ” ì½”ë“œ
			// 3ì´ˆë§ˆ???°ì†Œ ê²Œì´ì§€ë¥?1??ê°ì†Œ?œí‚¤??ì½”ë“œ
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